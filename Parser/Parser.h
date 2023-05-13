#pragma once

#include "../Scanner/TokenStruct.h"
#include "../Scanner/Scanner.h"
#include "AST.h"

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
        this->currentToken = this->scan.getNextToken();
    }
    void prevToken()
    {
        this->currentToken = this->scan.rollBackToken();
    }
    token peekToken()
    {
        return this->scan.peekNextToken();
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
        if (t.type == OP_UNARY_NOT || OP_ADD_SUB)
            return true;
        else
            return false;
    }

public:
    Scanner scan;
    token currentToken;
    Parser() : scan(Scanner()), currentToken(scan.getNextToken()) {}

    bool type();
    bool boolLit();
    ASTNode *padRead();
    ASTNode *padRandI();
    ASTNode *lit();
    ASTNode *mulOp();
    ASTNode *addOp();
    ASTNode *relOp();
    ASTNode *actualParams();
    ASTNode *actualParamsPrime();
    ASTNode *funCall();
    ASTNode *subExpr();
    ASTNode *unary();
    ASTNode *factor();
    ASTNode *term();
    ASTNode *termPrime();
    ASTNode *simpleExpr();
    ASTNode *simpleExprPrime();
    ASTNode *expr();
    ASTNode *exprPrime();
    ASTNode *assignment();
    ASTNode *varDec();
    // statements
    ASTNode *printStmnt();
    ASTNode *delayStmnt();
    ASTNode *pixelStmnt();
    ASTNode *rtrnStmnt();
    ASTNode *ifStmnt();
    ASTNode *forStmnt();
    ASTNode *statement();

    ASTNode *block();
    ASTNode *program();
};
