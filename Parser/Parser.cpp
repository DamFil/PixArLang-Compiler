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
    vector<ASTNode *> stmnts;
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
        return new ASTLit(currentToken.lexeme);
    default:
        exit(EXIT_FAILURE);
    }
}

ASTNode *Parser::actualParams()
{
    nextToken();
    vector<ASTNode *> nodes;
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