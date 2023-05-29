#pragma once

#include <iostream>

// to prevent cyclic dependencies
class ASTNode;
class ASTResultExpr;
class ASTId;
class ASTLit;
class ASTIntLit;
class ASTFloatLit;
class ASTColourLit;
class ASTBoolLit;
class ASTPadH;
class ASTPadW;
class ASTBinOp;
class ASTUnaryOp;
class ASTProgram;
class ASTBlock;
class ASTVarDecl;
class ASTIfStmn;
class ASTIfBody;
class ASTElseBody;
class ASTWhile;
class ASTFor;
class ASTFunDec;
class ASTFunCall;
class ASTParams;
class ASTFormalParam;
class ASTFormalParams;
class ASTPrintStmnt;
class ASTRandiStmnt;
class ASTPixelStmnt;
class ASTDelayStmnt;
class ASTReadStmnt;
class ASTFactor;
class ASTTerm;
class ASTSimpleExpr;
class ASTExpr;
class ASTAssignment;
class ASTRtrnStmnt;
class ASTStatement;

class XMLVisitor
{
public:
    int indent;
    XMLVisitor() : indent(0) {}
    // literals

    inline void printIndent();

    void visit(ASTLit *);
    void visit(ASTIntLit *);
    void visit(ASTFloatLit *);
    void visit(ASTColourLit *);
    void visit(ASTBoolLit *);
    void visit(ASTPadH *);
    void visit(ASTPadW *);
    void visit(ASTId *);

    void visit(ASTVarDecl *);
    void visit(ASTAssignment *);

    void visit(ASTFactor *);
    void visit(ASTResultExpr *);
    void visit(ASTExpr *);

    void visit(ASTBinOp *);
    void visit(ASTUnaryOp *);

    void visit(ASTDelayStmnt *);
    void visit(ASTPrintStmnt *);
    void visit(ASTRandiStmnt *);
    void visit(ASTReadStmnt *);
    void visit(ASTPixelStmnt *);

    void visit(ASTStatement *);
    void visit(ASTFunCall *);
    void visit(ASTFunDec *);
    void visit(ASTRtrnStmnt *);
    void visit(ASTParams *);
    void visit(ASTFormalParam *);
    void visit(ASTFormalParams *);
    void visit(ASTIfStmn *);
    void visit(ASTIfBody *);
    void visit(ASTElseBody *);
    void visit(ASTWhile *);
    void visit(ASTFor *);

    void visit(ASTBlock *);
    void visit(ASTProgram *);
};