#include "Parser.h"

ASTNode *Parser::program()
{
    ASTNode *node;
    if (currentToken.type == PUNCT_OPEN_CURL)
    {
        node = Parser::block();
        nextToken();
        if (currentToken.type != PUNCT_CLOSED_CURL)
        {
            cout << "Syntax Error: Missing '}'" << endl;
            exit(EXIT_FAILURE);
        }
        else
            return node;
    }
    vector<ASTNode *> stmnts{};
    while (currentToken.lexeme != "EOF")
    {
        stmnts.push_back(statement());
        nextToken();
    }
    return new ASTProgram(stmnts);
}

bool Parser::type()
{
    nextToken();
    switch (currentToken.type)
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
        exit(EXIT_FAILURE);
    ASTNode *node1 = expr();
    ASTNode *node2 = expr();
    return new ASTReadStmnt(node1, node2);
}

ASTNode *Parser::padRandI()
{
    nextToken();
    if (currentToken.type != KEY_PAD_RANDI)
        exit(EXIT_FAILURE);
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
    nextToken();
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
    if (currentToken.type != OP_UNARY_NOT)
    {
        cout << "Syntax Error: Missing 'not' operator" << endl;
        exit(EXIT_FAILURE);
    }
    else if (currentToken.type != OP_ADD_SUB)
    {
        cout << "Syntax Error: Missing '-' operator" << endl;
        exit(EXIT_FAILURE);
    }
    string op = currentToken.lexeme;
    ASTNode *node = expr();
    return new ASTUnaryOp(op, node);
}

ASTNode *Parser::factor()
{
    ASTNode *node;
    token t = peekToken();
    if (isLit(t))
        return lit();
    if (isId(t))
    {
        nextToken(); // currentToken equals t right now
        t = peekToken();
        if (t.type == PUNCT_OPEN_PAR)
        {
            // in this case it is a function call
            prevToken();
            return funCall();
        }
        else
        {
            prevToken();
            t = peekToken(); // t is back to what it was at the start of the function
            return new ASTId(t.lexeme);
        }
    }
    if (t.type == PUNCT_OPEN_PAR)
        return subExpr();
    if (isUnary(t))
        return unary();
    if (t.type == KEY_PAD_RANDI)
        return padRandI();
    cout << "Syntax Error: Expected 1 of the following: litera, identifer, function call, sub-expression, unary, or a PadRandI" << endl;
    exit(EXIT_FAILURE);
}