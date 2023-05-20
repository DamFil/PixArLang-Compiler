#pragma once

#include "../Scanner/TokenStruct.h"
#include "../Scanner/Scanner.h"
#include "AST.h"
using namespace std;

/*TODO:
 * 1) Create functions for each non terminal
 * 2) Create the AST
 */

class Parser
{
private:
    // wrappers for functions in the parser class
    void nextToken()
    {
        this->currentToken = this->scan->getNextToken();
    }
    void prevToken()
    {
        this->currentToken = this->scan->rollBackToken();
    }
    token peekToken()
    {
        return this->scan->peekNextToken();
    }

    bool isLit(token t)
    {
        switch (t.type)
        {
        case INT_LIT:
        case FLOAT_LIT:
        case COL_LIT:
        case KEY_BOOL_LIT_T:
        case KEY_BOOL_LIT_F:
        case KEY_PAD_W:
        case KEY_PAD_H:
            return true;
        default:
            false;
        }
    }
    bool isId(token t)
    {
        return t.type == IDENTIFIER ? true : false;
    }
    bool isUnary(token t)
    {
        return t.type == OP_UNARY_NOT || t.type == OP_ADD_SUB ? true : false;
    }

public:
    Scanner *scan;
    token currentToken;
    ASTNode *root{};
    Parser(string path);
    Parser(Scanner *scanner);
    ~Parser();

    bool isType(token t);
    ASTNode *lit();
    ASTNode *intLit();
    ASTNode *floatLit();
    ASTNode *colLit();
    ASTNode *boolLit();
    ASTNode *padLit();
    ASTNode *padRead();
    ASTNode *padRandI();
    ASTNode *actualParams();
    ASTNode *funCall();
    ASTNode *subExpr();
    ASTNode *unary();
    ASTNode *factor();
    ASTNode *term();
    ASTNode *simpleExpr();
    ASTNode *expr();
    ASTNode *assignment();
    ASTNode *varDec();
    // statements
    ASTNode *printStmnt();
    ASTNode *delayStmnt();
    ASTNode *pixelStmnt();
    ASTNode *rtrnStmnt();
    ASTNode *ifStmnt();
    ASTNode *forStmnt();
    ASTNode *whileStmnt();
    ASTNode *formalParam();
    ASTNode *formalParams();
    ASTNode *funDec();
    ASTNode *statement();
    // groups of statements
    ASTNode *block();
    ASTNode *program();
    // parsing function (wrapper for program())
    void parse();
};
