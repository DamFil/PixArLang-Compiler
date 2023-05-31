// linked list of maps for symbol tables (scops)
#pragma once

#include "SymbolTable.h"

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

class SemanticVisitor
{
    type typeOfExpression;
    SymbolTable *symboltable;

public:
    SemanticVisitor() : typeOfExpression(NotAType), symboltable(new SymbolTable()) {}
    ~SemanticVisitor()
    {
        delete symboltable;
    }

    inline void printIndent();

    type visit(ASTLit *);
    type visit(ASTIntLit *);
    type visit(ASTFloatLit *);
    type visit(ASTColourLit *);
    type visit(ASTBoolLit *);
    type visit(ASTPadH *);
    type visit(ASTPadW *);
    type visit(ASTId *);

    type visit(ASTVarDecl *);
    type visit(ASTAssignment *);

    type visit(ASTFactor *);
    type visit(ASTResultExpr *);
    type visit(ASTExpr *);

    type visit(ASTBinOp *);
    type visit(ASTUnaryOp *);

    type visit(ASTDelayStmnt *);
    type visit(ASTPrintStmnt *);
    type visit(ASTRandiStmnt *);
    type visit(ASTReadStmnt *);
    type visit(ASTPixelStmnt *);

    type visit(ASTStatement *, type funtype);
    type visit(ASTFunCall *);
    type visit(ASTFunDec *);
    type visit(ASTRtrnStmnt *, type funtype);
    vector<type> visit(ASTParams *);
    type visit(ASTFormalParam *);
    type visit(ASTFormalParams *);
    type visit(ASTIfStmn *, type funtype);
    type visit(ASTIfBody *, type funtype);
    type visit(ASTElseBody *, type funtype);
    type visit(ASTWhile *, type funtype);
    type visit(ASTFor *, type funtype);

    type visit(ASTBlock *, type funtype);
    type visit(ASTProgram *);
};