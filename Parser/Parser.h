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
