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

ASTReadStmnt *Parser::padRead()
{
    nextToken();
    if (currentToken.type != KEY_PAD_READ)
    {
        cout << "Syntax Error: Missing keyword \"__read\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node1 = expr();
    ASTExpr *node2 = expr();
    return new ASTReadStmnt(node1, node2);
}

ASTRandiStmnt *Parser::padRandI()
{
    nextToken();
    if (currentToken.type != KEY_PAD_RANDI)
    {
        cout << "Syntax Error: Missing keyword \"__randi\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node = expr();
    return new ASTRandiStmnt(node);
}

ASTIntLit *Parser::intLit()
{
    nextToken();
    if (currentToken.type != INT_LIT)
    {
        cout << "Syntax Error: Missing an integer literal" << endl;
        exit(EXIT_FAILURE);
    }
    return new ASTIntLit(currentToken.lexeme);
}

ASTFloatLit *Parser::floatLit()
{
    nextToken();
    if (currentToken.type != FLOAT_LIT)
    {
        cout << "Syntax Error: Missing a float literal" << endl;
        exit(EXIT_FAILURE);
    }
    return new ASTFloatLit(currentToken.lexeme);
}

ASTColourLit *Parser::colLit()
{
    nextToken();
    if (currentToken.type != COL_LIT)
    {
        cout << "Syntax Error: Missing a float literal" << endl;
        exit(EXIT_FAILURE);
    }
    return new ASTColourLit(currentToken.lexeme);
}

ASTBoolLit *Parser::boolLit()
{
    nextToken();
    if (currentToken.type != KEY_BOOL_LIT_F && currentToken.type != KEY_BOOL_LIT_T)
    {
        cout << "Syntax Error: Missing a Boolean Literal" << endl;
        exit(EXIT_FAILURE);
    }
    return new ASTBoolLit(currentToken.lexeme);
}

//? Do something about this
// ASTNode *Parser::padLit()
//{
//     nextToken();
//     if (currentToken.type != KEY_PAD_H && currentToken.type != KEY_PAD_W)
//     {
//         cout << "Syntax Error: Missing a Pad Literal (__height or __width)" << endl;
//         exit(EXIT_FAILURE);
//     }
//     return new ASTPadLit(currentToken.lexeme);
// }

ASTParams *Parser::actualParams()
{
    // nextToken(); - because this is going to be called by the call to the expr()
    vector<ASTExpr *> nodes{};
    while (currentToken.type != PUNCT_CLOSED_PAR)
    {
        nodes.push_back(expr());
        nextToken();
    }
    // because we do want to consume the closed parenthesis in the caller
    prevToken();
    return new ASTParams(nodes);
}

ASTFunCall *Parser::funCall()
{
    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Syntax Error: Missing Identifier for the Function" << endl;
        exit(EXIT_FAILURE);
    }
    // identifier node
    ASTId *node1 = new ASTId(currentToken.lexeme);

    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTParams *node2 = actualParams();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    return new ASTFunCall(node1, node2);
}

ASTExpr *Parser::subExpr()
{
    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node = expr();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    return node;
}

ASTUnaryOp *Parser::unary()
{
    nextToken();
    if (currentToken.type != OP_UNARY_NOT && currentToken.type != OP_ADD_SUB)
    {
        cout << "Syntax Error: Missing a unary operator (\"-\" or \"not\")" << endl;
        exit(EXIT_FAILURE);
    }

    string op = currentToken.lexeme;
    ASTExpr *node = expr();
    return new ASTUnaryOp(op, node);
}

ASTFactor *Parser::factor()
{
    ASTFactor *factor = nullptr;

    switch (peekToken().type)
    {
    case INT_LIT:
    {
        nextToken();
        ASTLit *lit = new ASTLit(new ASTIntLit(currentToken.lexeme));
        factor = new ASTFactor(lit);
        break;
    }

    case FLOAT_LIT:
    {
        nextToken();
        ASTLit *lit = new ASTLit(new ASTFloatLit(currentToken.lexeme));
        factor = new ASTFactor(lit);
        break;
    }

    case COL_LIT:
    {
        nextToken();
        ASTLit *lit = new ASTLit(new ASTColourLit(currentToken.lexeme));
        factor = new ASTFactor(lit);
        break;
    }

    case KEY_BOOL_LIT_F:
    case KEY_BOOL_LIT_T:
    {
        nextToken();
        ASTLit *lit = new ASTLit(new ASTBoolLit(currentToken.lexeme));
        factor = new ASTFactor(lit);
        break;
    }

    case KEY_PAD_W:
    {
        nextToken();

        factor = new ASTFactor(new ASTPadW());
        break;
    }

    case KEY_PAD_H:
    {
        nextToken();
        factor = new ASTFactor(new ASTPadH());
        break;
    }

    case IDENTIFIER:
    {
        nextToken();
        if (peekToken().type == PUNCT_OPEN_PAR)
        {
            prevToken();
            factor = new ASTFactor(funCall());
        }
        else
            factor = new ASTFactor(new ASTId(currentToken.lexeme));
        break;
    }

    case PUNCT_OPEN_PAR:
    {
        factor = new ASTFactor(subExpr());
        break;
    }

    case OP_UNARY_NOT:
    case OP_ADD_SUB:
    {
        factor = new ASTFactor(unary());
        break;
    }

    case KEY_PAD_RANDI:
    {
        factor = new ASTFactor(padRandI());
        break;
    }

    default:
        cout << "Syntax Error: Expected 1 of the following: literal, identifer, function call, sub-expression, unary, or a PadRandI" << endl;
        exit(EXIT_FAILURE);
    }

    return factor;
}

ASTResultExpr *Parser::term()
{
    ASTResultExpr *f = new ASTResultExpr();
    ASTBinOp *binop = nullptr;
    ASTBinOp *binop2 = nullptr;

    f->setFactor(factor());

    while (peekToken().type == OP_MUL_MUL || peekToken().type == OP_MUL_DIV || peekToken().type == OP_MUL_AND)
    {
        // if there is for example 5 * 7 / 3 then you would return:
        // BinOp(/, BinOp(*, 5, 7), 3))

        nextToken();
        string op = currentToken.lexeme;
        ASTResultExpr *f2 = new ASTResultExpr();

        if (binop2 == nullptr)
        {
            f2->setFactor(factor());
            binop = new ASTBinOp(op, f, f2);

            binop2 = binop;
            continue;
        }

        f = new ASTResultExpr();
        f->setBinOp(binop2);
        f2->setFactor(factor());
        binop = new ASTBinOp(op, f, f2);
    }

    if (binop == nullptr)
        return f;

    f = new ASTResultExpr();
    f->setBinOp(binop);

    return f;
}

ASTResultExpr *Parser::simpleExpr()
{
    ASTResultExpr *t = term();
    ASTBinOp *binop = nullptr;
    ASTBinOp *binop2 = nullptr;

    while (peekToken().type == OP_ADD_ADD || peekToken().type == OP_ADD_SUB || peekToken().type == OP_ADD_OR)
    {
        // Case: 5 + 3 - 4 + 7

        nextToken();
        string op = currentToken.lexeme;
        ASTResultExpr *t2 = new ASTResultExpr();

        if (binop2 == nullptr)
        {
            t2 = term();
            binop = new ASTBinOp(op, t, t2);

            binop2 = binop;
            continue;
        }

        t = new ASTResultExpr();
        t->setBinOp(binop2);
        t2 = term();
        binop = new ASTBinOp(op, t, t2);
        binop2 = binop;
    }

    if (binop == nullptr)
        return t;

    t = new ASTResultExpr();
    t->setBinOp(binop);

    return t;
}

ASTExpr *Parser::expr()
{
    ASTResultExpr *se = simpleExpr();
    ASTBinOp *binop = nullptr;
    ASTBinOp *binop2 = nullptr;

    while (peekToken().type == OP_REL_EQUAL || peekToken().type == OP_REL_NOT_EQUAL || peekToken().type == OP_REL_GREAT || peekToken().type == OP_REL_LESS || peekToken().type == OP_REL_GREAT_EQ || peekToken().type == OP_REL_LESS_EQ)
    {
        nextToken();
        string op = currentToken.lexeme;
        ASTResultExpr *se2 = new ASTResultExpr();

        if (binop2 == nullptr)
        {
            se2 = simpleExpr();
            binop = new ASTBinOp(op, se, se2);

            binop2 = binop;
            continue;
        }

        se = new ASTResultExpr();
        se->setBinOp(binop2);
        se2 = simpleExpr();
        binop = new ASTBinOp(op, se, se2);
        binop2 = binop;
    }

    if (binop == nullptr)
        return new ASTExpr(se);

    se = new ASTResultExpr();
    se->setBinOp(binop);

    return new ASTExpr(se);
}

ASTAssignment *Parser::assignment()
{
    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Syntax Error: Expected an identifer" << endl;
        exit(EXIT_FAILURE);
    }
    ASTId *id = new ASTId(currentToken.lexeme);

    nextToken();
    if (currentToken.type != OP_ASSIGNMENT)
    {
        cout << "Syntax Error: Expected assignment operator '='" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node = expr();
    return new ASTAssignment(id, node);
}

ASTVarDecl *Parser::varDec()
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
    ASTId *id = new ASTId(currentToken.lexeme);

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
    string t = currentToken.lexeme;

    nextToken();
    if (currentToken.type != OP_ASSIGNMENT)
    {
        cout << "Syntax Error: Missing '='" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node = expr();
    return new ASTVarDecl(id, node, t);
}

ASTPrintStmnt *Parser::printStmnt()
{
    nextToken();
    if (currentToken.type != KEY_PRINT)
    {
        cout << "Syntax Error: Missing \"__print\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node = expr();
    return new ASTPrintStmnt(node);
}

ASTDelayStmnt *Parser::delayStmnt()
{
    nextToken();
    if (currentToken.type != KEY_DELAY)
    {
        cout << "Syntax Error: Missing \"__delay\"" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *node = expr();
    return new ASTDelayStmnt(node);
}

ASTPixelStmnt *Parser::pixelStmnt()
{
    nextToken();
    if (currentToken.type != KEY_PIX)
    {
        if (currentToken.type != KEY_PIX_R)
        {
            cout << "Syntax Error: Missing \"__pixel\" or \"__pixelr\"" << endl;
            exit(EXIT_FAILURE);
        }
        ASTExpr *expr1 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTExpr *expr2 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTExpr *expr3 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTExpr *expr4 = expr();

        nextToken();
        if (currentToken.type != PUNCT_COMMA)
        {
            cout << "Syntax Error: Missing ','" << endl;
            exit(EXIT_FAILURE);
        }

        ASTExpr *expr5 = expr();

        return new ASTPixelStmnt(expr1, expr2, expr3, expr4, expr5);
    }
    ASTExpr *expr1 = expr();

    nextToken();
    if (currentToken.type != PUNCT_COMMA)
    {
        cout << "Syntax Error: Missing ','" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *expr2 = expr();

    nextToken();
    if (currentToken.type != PUNCT_COMMA)
    {
        cout << "Syntax Error: Missing ','" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *expr3 = expr();

    return new ASTPixelStmnt(expr1, expr2, expr3);
}

ASTRtrnStmnt *Parser::rtrnStmnt()
{
    nextToken();
    if (currentToken.type != KEY_RETURN)
    {
        cout << "Syntax Error: Missing the return statement (\"return\")" << endl;
        exit(EXIT_FAILURE);
    }

    return new ASTRtrnStmnt(expr());
}

ASTIfStmn *Parser::ifStmnt()
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

    ASTExpr *conditon = expr();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing '')" << endl;
        exit(EXIT_FAILURE);
    }
    ASTIfBody *ifbod = ifbody();

    if (peekToken().type != KEY_ELSE)
    {
        return new ASTIfStmn(conditon, ifbod);
    }

    nextToken();
    ASTElseBody *elsebod = elsebody();

    return new ASTIfStmn(conditon, ifbod, elsebod);
}

ASTFor *Parser::forStmnt()
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

    ASTVarDecl *vd = nullptr;
    if (peekToken().type == KEY_VAR_DEC)
        // we know there is a variable declaraion in this case
        vd = varDec();

    nextToken();
    if (currentToken.type != PUNCT_SEMICOLON)
    {
        cout << "Syntax Error: Missing ';'" << endl;
        exit(EXIT_FAILURE);
    }

    ASTExpr *condition = expr();

    nextToken();
    if (currentToken.type != PUNCT_SEMICOLON)
    {
        cout << "Syntax Error: Missing ';'" << endl;
        exit(EXIT_FAILURE);
    }

    ASTAssignment *assnmt = nullptr;
    if (peekToken().type == IDENTIFIER)
        // we know there is an assignment statement
        assnmt = assignment();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }

    ASTBlock *b = block();
    return new ASTFor(vd, condition, assnmt, b);
}

ASTWhile *Parser::whileStmnt()
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
    ASTExpr *condition = expr();

    nextToken();
    if (currentToken.type != PUNCT_CLOSED_PAR)
    {
        cout << "Syntax Error: Missing ')'" << endl;
        exit(EXIT_FAILURE);
    }
    ASTBlock *b = block();

    return new ASTWhile(condition, b);
}

ASTFormalParam *Parser::formalParam()
{
    nextToken();
    if (currentToken.type != IDENTIFIER)
    {
        cout << "Sytnax Error: Expected an Identifer" << endl;
        exit(EXIT_FAILURE);
    }
    ASTId *id = new ASTId(currentToken.lexeme);

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
    string t = currentToken.lexeme;

    return new ASTFormalParam(id, t);
}

ASTFormalParams *Parser::formalParams()
{
    vector<ASTFormalParam *> parameters{};
    parameters.push_back(formalParam());

    while (peekToken().type == PUNCT_COMMA)
    {
        nextToken(); // - consuming the comma
        parameters.push_back(formalParam());
    }

    return new ASTFormalParams(parameters);
}

ASTFunDec *Parser::funDec()
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

    ASTId *id = new ASTId(currentToken.lexeme);
    nextToken();
    if (currentToken.type != PUNCT_OPEN_PAR)
    {
        cout << "Syntax Error: Missing '('" << endl;
        exit(EXIT_FAILURE);
    }

    ASTFormalParams *params = formalParams();

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
    string t = currentToken.lexeme;

    ASTBlock *b = block();

    return new ASTFunDec(id, params, t, b);
}

ASTStatement *Parser::statement()
{
    ASTStatement *s = nullptr;
    token t = peekToken();

    switch (peekToken().type)
    {
    case KEY_VAR_DEC:
        s = new ASTStatement(varDec());
        break;
    case IDENTIFIER:
        s = new ASTStatement(assignment());
        break;
    case KEY_PRINT:
        s = new ASTStatement(printStmnt());
        break;
    case KEY_DELAY:
        s = new ASTStatement(delayStmnt());
        break;
    case KEY_PIX:
    case KEY_PIX_R:
        s = new ASTStatement(pixelStmnt());
        break;
    case KEY_IF:
        s = new ASTStatement(ifStmnt());
        return s;
    case KEY_FOR:
        s = new ASTStatement(forStmnt());
        return s;
    case KEY_WHILE:
        s = new ASTStatement(whileStmnt());
        return s;
    case KEY_RETURN:
        s = new ASTStatement(rtrnStmnt());
        break;
    case KEY_FUN_DEC:
        s = new ASTStatement(funDec());
        return s;
    case PUNCT_OPEN_CURL:
        s = new ASTStatement(block());
        return s;
    default:
        cout << "Syntax Error: Statements are not valid" << endl;
        exit(EXIT_FAILURE);
    }

    nextToken();
    if (currentToken.type != PUNCT_SEMICOLON)
    {
        cout << "Syntax Error: Missing ';'" << endl;
        exit(EXIT_FAILURE);
    }

    return s;
}

ASTBlock *Parser::block()
{
    nextToken();
    if (currentToken.type != PUNCT_OPEN_CURL)
    {
        cout << "Syntax Error: Missing '{'" << endl;
        exit(EXIT_FAILURE);
    }

    vector<ASTStatement *> stmnts{};
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

ASTIfBody *Parser::ifbody()
{
    nextToken();
    if (currentToken.type != PUNCT_OPEN_CURL)
    {
        cout << "Syntax Error: Missing '{'" << endl;
        exit(EXIT_FAILURE);
    }

    vector<ASTStatement *> stmnts{};
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

    return new ASTIfBody(stmnts);
}

ASTElseBody *Parser::elsebody()
{
    nextToken();
    if (currentToken.type != PUNCT_OPEN_CURL)
    {
        cout << "Syntax Error: Missing '{'" << endl;
        exit(EXIT_FAILURE);
    }

    vector<ASTStatement *> stmnts{};
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

    return new ASTElseBody(stmnts);
}

ASTProgram *Parser::program()
{
    vector<ASTStatement *> stmnts{};

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
