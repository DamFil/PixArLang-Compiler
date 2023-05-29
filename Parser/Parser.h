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
    ASTProgram *root = nullptr;
    Parser(string path);
    Parser(Scanner *scanner);
    ~Parser();

    bool isType(token t);
    ASTNode *lit();
    ASTIntLit *intLit();
    ASTFloatLit *floatLit();
    ASTColourLit *colLit();
    ASTBoolLit *boolLit();
    //! ASTNode *padLit();
    ASTPadH *padH();
    ASTPadW *padW();
    ASTReadStmnt *padRead();
    ASTRandiStmnt *padRandI();
    ASTParams *actualParams();
    ASTFunCall *funCall();
    ASTExpr *subExpr();
    ASTUnaryOp *unary();
    ASTFactor *factor();
    ASTResultExpr *term();
    ASTResultExpr *simpleExpr();
    ASTExpr *expr();
    ASTAssignment *assignment();
    ASTVarDecl *varDec();

    // statements
    ASTPrintStmnt *printStmnt();
    ASTDelayStmnt *delayStmnt();
    ASTPixelStmnt *pixelStmnt();
    ASTRtrnStmnt *rtrnStmnt();
    ASTIfStmn *ifStmnt();
    ASTFor *forStmnt();
    ASTWhile *whileStmnt();
    ASTFormalParam *formalParam();
    ASTFormalParams *formalParams();
    ASTFunDec *funDec();
    ASTStatement *statement();

    // groups of statements
    ASTBlock *block();
    ASTIfBody *ifbody();
    ASTElseBody *elsebody();
    ASTProgram *program();

    // parsing function (wrapper for program())
    void parse();
};
