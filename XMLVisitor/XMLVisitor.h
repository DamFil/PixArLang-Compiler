#pragma once

#include <iostream>
#include "../Parser/AST.h"

class XMLVisitor
{
public:
    XMLVisitor();
    // literals
    void visit(ASTIntLit *);
    void visit(ASTFloatLit *);
    void visit(ASTColourLit *);
    void visit(ASTBoolLit *);
    void visit(ASTPadLit *);

    void visit(ASTVarDecl *);
    void visit(ASTAssignment *);

    void visit(ASTExpr *);
    void visit(ASTSimpleExpr *);
    void visit(ASTTerm *);

    void visit(ASTBinOp *);
    void visit(ASTUnaryOp *);

    void visit(ASTDelayStmnt *);
    void visit(ASTPrintStmnt *);
    void visit(ASTRandiStmnt *);
    void visit(ASTReadStmnt *);
    void visit(ASTPixelStmnt *);
    void visit(ASTPixelrStmnt *);

    void visit(ASTFunCall *);
    void visit(ASTFunDec *);
    void visit(ASTParams *);
    void visit(ASTFormalParam *);
    void visit(ASTFormalParams *);

    void visit(ASTIfStmn *);
    void visit(ASTIfBody *);
    void visit(ASTElseBody *);
    void visit(ASTWhile *);
    void visit(ASTFor *);

    void visit(ASTProgram *);
    void visit(ASTBlock *);
};