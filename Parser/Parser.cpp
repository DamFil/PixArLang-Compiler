#include "Parser.h"

/*
*Rules For Determining when to call nextToken();
1) nextToken should be called at the beginning of every function
2) Same applies for peekToken
3) The caller must not call nextToken() before calling the function
*/

// constructor
Parser::Parser(string path) : scan(new Scanner(path))
{
    this->scan->scanInput();
    currentToken = scan->getNextToken();
}

Parser::Parser(Scanner *scanner) : scan(scanner), currentToken(generated_token()) {}

Parser::~Parser()
{
    delete this->scan;
    delete this->root;
}

bool Parser::isType(token t)
{
    switch (t.type)
    {
    case KEY_T_INT:
    case KEY_T_BOOL:
    case KEY_T_FLOAT:
    case KEY_T_COLOUR:
        return true;
    default:
        return false;
    }
}

bool Parser::boolLit()
{
    nextToken();
    switch (currentToken.type)
    {
    case KEY_BOOL_LIT_T:
    case KEY_BOOL_LIT_F:
        return true;
    default:
        return false;
    }
}

ASTNode *Parser::padRead()
{
    nextToken();
    if (currentToken.type != KEY_PAD_READ)
    {
        cout << "Syntax Error: Missing keyword \"__read\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node1 = expr();
    ASTNode *node2 = expr();
    return new ASTReadStmnt(node1, node2);
}

ASTNode *Parser::padRandI()
{
    nextToken();
    if (currentToken.type != KEY_PAD_RANDI)
    {
        cout << "Syntax Error: Missing keyword \"__randi\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node = expr();
    return new ASTRandiStmnt(node);
}

ASTNode *Parser::lit()
{
    nextToken();
    switch (currentToken.type)
    {
    case INT_LIT:
    case FLOAT_LIT:
    case COL_LIT:
    case KEY_BOOL_LIT_T:
    case KEY_BOOL_LIT_F:
    case KEY_PAD_W:
    case KEY_PAD_H:
        return new ASTLit(currentToken.lexeme);
    case KEY_PAD_READ:
        prevToken(); // since padRead already calls nextToken() itself
        return padRead();
    default:
        exit(EXIT_FAILURE);
    }
}

ASTNode *Parser::actualParams()
{
    // nextToken(); - because this is going to be called by the call to the expr()
    vector<ASTNode *> nodes{};
    while (currentToken.type != PUNCT_CLOSED_PAR)
    {
        nodes.push_back(expr());
        nextToken();
    }
    // because we do want to consume the closed parenthesis in the caller
    prevToken();
    return new ASTParams(nodes);
}

ASTNode *Parser::funCall()
{
    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Syntax Error: Missing Identifier for the Function" << endl;
        exit(EXIT_FAILURE);
    }
    // identifier node
    ASTNode *node1 = new ASTId(currentToken.lexeme);

    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node2 = actualParams();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    return new ASTFunCall(node1, node2);
}

ASTNode *Parser::subExpr()
{
    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node = expr();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    return node;
}

ASTNode *Parser::unary()
{
    nextToken();
    if (currentToken.type != OP_UNARY_NOT && currentToken.type != OP_ADD_SUB)
    {
        cout << "Syntax Error: Missing a unary operator (\"-\" or \"not\")" << endl;
        exit(EXIT_FAILURE);
    }

    string op = currentToken.lexeme;
    ASTNode *node = expr();
    return new ASTUnaryOp(op, node);
}

ASTNode *Parser::factor()
{
    // TODO: Do a switch statement instead of spamming ifs
    switch (peekToken().type)
    {
    case INT_LIT:
    case FLOAT_LIT:
    case COL_LIT:
    case KEY_BOOL_LIT_F:
    case KEY_BOOL_LIT_T:
    case KEY_PAD_W:
    case KEY_PAD_H:
        return lit();
    case IDENTIFIER:
        nextToken();
        if (peekToken().type == PUNCT_OPEN_PAR)
        {
            prevToken();
            return funCall();
        }
        else
            return new ASTId(currentToken.lexeme);
    case PUNCT_OPEN_PAR:
        return subExpr();
    case OP_UNARY_NOT:
    case OP_ADD_SUB:
        return unary();
    case KEY_PAD_RANDI:
        return padRandI();
    default:
        cout << "Syntax Error: Expected 1 of the following: litera, identifer, function call, sub-expression, unary, or a PadRandI" << endl;
        exit(EXIT_FAILURE);
    }
}

ASTNode *Parser::term()
{
    // nextToken();
    ASTNode *f;
    ASTBinOp *binop;
    vector<ASTNode *> binops{};

    f = factor();

    while (peekToken().type == OP_MUL_MUL || peekToken().type == OP_MUL_DIV || peekToken().type == OP_MUL_AND)
    {
        // creates a vector of binary operation nodes where the value of the node is one of the mul operations
        // and the children are the factors on which the operations happen
        nextToken();

        binop = new ASTBinOp(currentToken.lexeme, f, f = factor());
        binops.push_back(binop);
    }

    if (binops.size() == 0)
    {
        vector<ASTNode *> factors{f};
        return new ASTTerm(factors);
    }

    return new ASTTerm(binops);
}

ASTNode *Parser::simpleExpr()
{
    // nextToken();
    ASTNode *t;
    ASTBinOp *binop;
    vector<ASTNode *> binops{};

    t = term();

    while (peekToken().type == OP_ADD_ADD || peekToken().type == OP_ADD_SUB || peekToken().type == OP_ADD_OR)
    {
        nextToken();

        binop = new ASTBinOp(currentToken.lexeme, t, t = term());
        binops.push_back(binop);
    }

    if (binops.size() == 0)
    {
        vector<ASTNode *> terms{t};
        return new ASTTerm(terms);
    }

    return new ASTSimpleExpr(binops);
}

ASTNode *Parser::expr()
{
    // nextToken(); - this will be handled on later in the factor()
    ASTNode *se;
    ASTBinOp *cond;
    vector<ASTNode *> conds{};

    se = simpleExpr();

    while (peekToken().type == OP_REL_EQUAL || peekToken().type == OP_REL_NOT_EQUAL || peekToken().type == OP_REL_GREAT || peekToken().type == OP_REL_LESS || peekToken().type == OP_REL_GREAT_EQ || peekToken().type == OP_REL_LESS_EQ)
    {
        nextToken(); // - consuming the relational operator

        cond = new ASTBinOp(currentToken.lexeme, se, se = factor());
        conds.push_back(cond);
    }

    if (conds.size() == 0)
    {
        vector<ASTNode *> ses{se};
        return new ASTTerm(ses);
    }

    return new ASTSimpleExpr(conds);
}

ASTNode *Parser::assignment()
{
    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Syntax Error: Expected an identifer" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *id = new ASTId(currentToken.lexeme);

    nextToken();
    if (currentToken.type != OP_ASSIGNMENT)
    {
        cout << "Syntax Error: Expected assignment operator '='" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node = expr();
    return new ASTAssignment(id, node);
}

ASTNode *Parser::varDec()
{
    nextToken();
    if (currentToken.type != KEY_VAR_DEC)
    {
        cout << "Syntax Error: Missing 'let'" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Syntax Error: Need to specify the name of the variable" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *id = new ASTId(currentToken.lexeme);

    nextToken();
    if (currentToken.type != PUNCT_COLON)
    {
        cout << "Syntax Error: Missing ':'" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (!isType(currentToken))
    {
        cout << "Syntax Error: Missing type" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != OP_ASSIGNMENT)
    {
        cout << "Syntax Error: Missing '='" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node = expr();
    return new ASTVarDecl(id, node);
}

ASTNode *Parser::printStmnt()
{
    nextToken();
    if (currentToken.type != KEY_PRINT)
    {
        cout << "Syntax Error: Missing \"__print\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node = expr();
    return new ASTPrintStmnt(node);
}

ASTNode *Parser::delayStmnt()
{
    nextToken();
    if (currentToken.type != KEY_DELAY)
    {
        cout << "Syntax Error: Missing \"__delay\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node = expr();
    return new ASTDelayStmnt(node);
}

ASTNode *Parser::pixelStmnt()
{
    nextToken();
    if (currentToken.type != KEY_PIX)
    {
        if (currentToken.type != KEY_PIX_R)
        {
            cout << "Syntax Error: Missing \"__pixel\" or \"__pixelr\"" << endl;
            exit(EXIT_FAILURE);
        }
        ASTNode *node1 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTNode *node2 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTNode *node3 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTNode *node4 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTNode *node5 = expr();

        return new ASTPixelrStmnt(node1, node2, node3, node4, node5);
    }
    ASTNode *node1 = expr();

    nextToken();
    if (currentToken.type != PUNCT_COMMA)
    {
        cout << "Syntax Error: Missing ','" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node2 = expr();

    nextToken();
    if (currentToken.type != PUNCT_COMMA)
    {
        cout << "Syntax Error: Missing ','" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *node3 = expr();

    return new ASTPixelStmnt(node1, node2, node3);
}

ASTNode *Parser::rtrnStmnt()
{
    nextToken();
    if (currentToken.type != KEY_RETURN)
    {
        cout << "Syntax Error: Missing the return statement (\"return\")" << endl;
        exit(EXIT_FAILURE);
    }

    return expr();
}

ASTNode *Parser::ifStmnt()
{
    nextToken();
    if (currentToken.type != KEY_IF)
    {
        cout << "Syntax Error: Missing \"if\"" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *conditon = expr();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing '')" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *ifbody = block();

    if (peekToken().type != KEY_ELSE)
    {
        return new ASTIfStmn(conditon, ifbody);
    }

    nextToken();
    ASTNode *elsebody = block();

    return new ASTIfStmn(conditon, ifbody, elsebody);
}

ASTNode *Parser::forStmnt()
{
    nextToken();
    if (currentToken.type != KEY_FOR)
    {
        cout << "Syntax Error: Missing keyword \"for\"" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *vd = nullptr;
    if (peekToken().type == KEY_VAR_DEC)
        // we know there is a variable declaraion in this case
        vd = varDec();

    ASTNode *condition = expr();

    ASTNode *assnmt = nullptr;
    if (peekToken().type == IDENTIFIER)
        // we know there is an assignment statement
        assnmt = assignment();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *b = block();
    return new ASTFor(vd, condition, assnmt, b);
}

ASTNode *Parser::whileStmnt()
{
    nextToken();
    if (currentToken.type != KEY_WHILE)
    {
        cout << "Syntax Error: Missing keyword \"while\"" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *condition = expr();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *b = block();

    return new ASTWhile(condition, b);
}

ASTNode *Parser::formalParam()
{
    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Sytnax Error: Expected an Identifer" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *id = new ASTId(currentToken.lexeme);

    nextToken();
    if (currentToken.type != PUNCT_COLON)
    {
        cout << "Syntax Error: Expected ':'" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (!isType(currentToken))
    {
        cout << "Syntax Error: Expected a type" << endl;
        exit(EXIT_FAILURE);
    }
    ASTNode *type = new ASTType(currentToken.lexeme);

    return new ASTFormalParam(id, type);
}

ASTNode *Parser::formalParams()
{
    vector<ASTNode *> parameters{};
    parameters.push_back(formalParam());

    while (peekToken().type == PUNCT_COMMA)
    {
        nextToken(); // - consuming the comma
        parameters.push_back(formalParam());
    }

    return new ASTFormalParams(parameters);
}

ASTNode *Parser::funDec()
{
    nextToken();
    if (currentToken.type != KEY_FUN_DEC)
    {
        cout << "Syntax Error: Missing \"fun\"" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Syntax Error: Missing identifier" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *id = new ASTId(currentToken.lexeme);
    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTNode *params = formalParams();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != OP_RET_TYPE)
    {
        cout << "Syntax Error: Missing \"->\"" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (!isType(currentToken))
    {
        cout << "Syntax Error: Missing type" << endl;
        exit(EXIT_FAILURE);
    }
    ASTType *t = new ASTType(currentToken.lexeme);

    ASTNode *b = block();

    return new ASTFunDec(id, params, t, b);
}

ASTNode *Parser::statement()
{
    ASTNode *n = nullptr;
    token t = peekToken();
    switch (peekToken().type)
    {
    case KEY_VAR_DEC:
        n = varDec();
        break;
    case IDENTIFIER:
        n = assignment();
        break;
    case KEY_PRINT:
        n = printStmnt();
        break;
    case KEY_DELAY:
        n = delayStmnt();
        break;
    case KEY_PIX:
    case KEY_PIX_R:
        n = pixelStmnt();
        break;
    case KEY_IF:
        return ifStmnt();
    case KEY_FOR:
        return forStmnt();
    case KEY_WHILE:
        return whileStmnt();
    case KEY_RETURN:
        n = rtrnStmnt();
        break;
    default:
        if (peekToken().type == KEY_FUN_DEC)
            return funDec();

        if (peekToken().type == PUNCT_OPEN_CURL)
            return block();
        cout << "Syntax Error: Statements are not valid" << endl;
        exit(EXIT_FAILURE);
    }
    nextToken();
    if (currentToken.type != PUNCT_SEMICOLON)
    {
        cout << "Syntax Error: Missing ';'" << endl;
        exit(EXIT_FAILURE);
    }
    return n;
}

ASTNode *Parser::block()
{
    nextToken();
    if (currentToken.type != PUNCT_OPEN_CURL)
    {
        cout << "Syntax Error: Missing '{'" << endl;
        exit(EXIT_FAILURE);
    }

    vector<ASTNode *> stmnts{};
    while (peekToken().type != PUNCT_CLOSED_CURL)
    {
        stmnts.push_back(statement());
    }

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_CURL)
    {
        cout << "Syntax Error: Missing '}'" << endl;
        exit(EXIT_FAILURE);
    }

    return new ASTBlock(stmnts);
}

ASTNode *Parser::program()
{
    vector<ASTNode *> stmnts{};

    while (peekToken().type != INVALID_TOKEN && peekToken().lexeme != "END")
    {
        stmnts.push_back(statement());
    }

    cout << "PARSING SUCCESSFULL" << endl;

    return new ASTProgram(stmnts);
}

void Parser::parse()
{
    this->root = program();
}
