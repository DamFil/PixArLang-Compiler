#pragma once

#include "../Scanner/TokenStruct.h"
#include "../Scanner/Scanner.h"

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
    bool padRead();
    bool padRandI();
    bool lit();
    bool mulOp();
    bool addOp();
    bool relOp();
    bool actualParams();
    bool actualParamsPrime();
    bool funCall();
    bool subExpr();
    bool unary();
    bool term();
    bool termPrime();
    bool simpleExpr();
    bool simpleExprPrime();
    bool expr();
    bool exprPrime();
    bool assignment();
    bool varDec();
    // statements
    bool printStmnt();
    bool delayStmnt();
    bool pixelStmnt();
    bool rtrnStmnt();
    bool ifStmnt();
    bool forStmnt();
    bool statement();

    bool block();
    bool proagram();
};
