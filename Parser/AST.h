#pragma once
#include "../Scanner/TokenStruct.h"

class ASTNode
{
public:
    virtual ~ASTNode() {}
};

class ASTId : public ASTNode
{
public:
    string name;
    ASTId(string n) : name(n) {}
};

// I do not need any other literals since the token value is all strings
class ASTLit : public ASTNode
{
public:
    string value;
    ASTLit(string v) : value(v) {}
};

class ASTBinOp : public ASTNode
{
public:
    ASTNode *left;
    ASTNode *right;
    string op;
    ASTBinOp(ASTNode *l, ASTNode *r, string op) : left(l), right(r), op(op) {}
    virtual ~ASTBinOp()
    {
        delete left;
        delete right;
    }
};

class ASTUnaryOp : public ASTNode
{
public:
    string op;
    ASTNode *expr;
    ASTUnaryOp(string op, ASTNode *expr) : op(op), expr(expr) {}
    virtual ~ASTUnaryOp()
    {
        delete expr;
    }
};

class ASTProgram : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTProgram(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTProgram()
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }
};

class ASTBlock : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTBlock(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTBlock()
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }
};

class ASTVarDecl : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *init;
    ASTVarDecl(ASTNode *id, ASTNode *init) : id(id), init(init) {}
    virtual ~ASTVarDecl()
    {
        delete id;
        delete init;
    }
};

class ASTIfStmn : public ASTNode
{
    ASTNode *cond;     // should be the ASTBinOP
    ASTNode *ifbody;   // same as ASTBlock
    ASTNode *elsebody; // same as ASTBlock
    ASTIfStmn(ASTNode *cond, ASTNode *ifbody, ASTNode *elsebody = nullptr) : cond(cond), ifbody(ifbody), elsebody(elsebody) {}
    virtual ~ASTIfStmn()
    {
        delete cond;
        delete ifbody;
        delete elsebody;
    }
};
class ASTIfBody : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTIfBody(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTIfBody()
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }
};

class ASTElseBody : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTElseBody(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTElseBody()
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }
};

class ASTWhile : public ASTNode
{
public:
    ASTNode *condtn;
    ASTNode *stmnts;
    ASTWhile(ASTNode *condtn, ASTNode *stmnts) : condtn(condtn), stmnts(stmnts) {}
    virtual ~ASTWhile()
    {
        delete condtn;
        delete stmnts;
    }
};

class ASTFor : public ASTNode
{
    ASTNode *vardec;
    ASTNode *expr;
    ASTNode *assignment;
    vector<ASTNode *> expressions;
    ASTFor(ASTNode *vardec, ASTNode *expr = nullptr, ASTNode *assignment = nullptr, vector<ASTNode *> expressions)
        : vardec(vardec), expr(expr), assignment(assignment), expressions(expressions) {}
    virtual ~ASTFor()
    {
        delete vardec;
        delete expr;
        delete assignment;
        for (int i = 0; i < expressions.size(); i++)
        {
            delete expressions[i];
        }
    }
};

class ASTFunDec : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *params;
    ASTNode *rtrntype;
    ASTFunDec(ASTNode *id, ASTNode *params, ASTNode *rtrntype) : id(id), params(params), rtrntype(rtrntype) {}
    virtual ~ASTFunDec()
    {
        delete id;
        delete params;
        delete rtrntype;
    }
};

class ASTFunCall : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *params;
    ASTFunCall(ASTNode *id, ASTNode *params) : id(id), params(params) {}
    virtual ~ASTFunCall()
    {
        delete id;
        delete params;
    }
};

class ASTParams : public ASTNode
{
public:
    vector<ASTNode *> expressions;
    ASTParams(vector<ASTNode *> expressions) : expressions(expressions) {}
    virtual ~ASTParams()
    {
        for (int i = 0; i < expressions.size(); i++)
        {
            delete expressions[i];
        }
    }
};

class ASTPrintStmnt : public ASTNode
{
public:
    ASTNode *expression;
    ASTPrintStmnt(ASTNode *expression) : expression(expression) {}
    virtual ~ASTPrintStmnt()
    {
        delete expression;
    }
};

class ASTRandiStmnt : public ASTNode
{
public:
    ASTNode *expression;
    ASTRandiStmnt(ASTNode *expression) : expression(expression) {}
    virtual ~ASTRandiStmnt()
    {
        delete expression;
    }
};

class ASTPixelStmnt : public ASTNode
{
    ASTNode *pixel;
    ASTNode *amount;
    ASTNode *col;
    ASTPixelStmnt(ASTNode *pixel, ASTNode *amount, ASTNode *col) : pixel(pixel), amount(amount), col(col) {}
    virtual ~ASTPixelStmnt()
    {
        delete pixel;
        delete amount;
        delete col;
    }
};

class ASTPixelrStmnt : public ASTNode
{
    // TODO: probably make this an vector of 5
    ASTNode *expr1;
    ASTNode *expr2;
    ASTNode *expr3;
    ASTNode *expr4;
    ASTNode *expr5;
    ASTPixelrStmnt(ASTNode *expr1, ASTNode *expr2, ASTNode *expr3, ASTNode *expr4, ASTNode *expr5) : expr1(expr1), expr2(expr2), expr3(expr3), expr4(expr4), expr5(expr5) {}
    virtual ~ASTPixelrStmnt()
    {
        delete expr1;
        delete expr2;
        delete expr3;
        delete expr4;
        delete expr5;
    }
};

class ASTDelayStmnt : public ASTNode
{
    ASTNode *expression;
    ASTDelayStmnt(ASTNode *expression) : expression(expression) {}
    virtual ~ASTDelayStmnt()
    {
        delete expression;
    }
};

class ASTReadStmnt : public ASTNode
{
public:
    ASTNode *expr1;
    ASTNode *expr2;
    ASTReadStmnt(ASTNode *expr1, ASTNode *expr2) : expr1(expr1), expr2(expr2) {}
    virtual ~ASTReadStmnt()
    {
        delete expr1;
        delete expr2;
    }
};