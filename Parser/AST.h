#pragma once
#include "../Scanner/TokenStruct.h"
#include "../XMLVisitor/XMLVisitor.h"

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
    virtual ~ASTId() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

//! REMOVE THIS
class ASTLit : public ASTNode
{
public:
    string value;
    ASTLit(string v) : value(v) {}
    virtual ~ASTLit() override {}
};

class ASTIntLit : public ASTNode
{
public:
    string value;
    ASTIntLit(string v) : value(v) {}
    virtual ~ASTIntLit() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFloatLit : public ASTNode
{
public:
    string value;
    ASTFloatLit(string v) : value(v) {}
    virtual ~ASTFloatLit() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTColourLit : public ASTNode
{
public:
    string value;
    ASTColourLit(string v) : value(v) {}
    virtual ~ASTColourLit() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTBoolLit : public ASTNode
{
public:
    bool value;
    ASTBoolLit(string boolStr)
    {
        if (boolStr == "true")
            value = true;
        else
            value = false;
    }
    virtual ~ASTBoolLit() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTPadLit : public ASTNode
{
public:
    string padl;
    ASTPadLit(string pl) : padl(pl) {}
    virtual ~ASTPadLit() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTType : public ASTNode
{
public:
    string type;
    ASTType(string type) : type(type) {}
    virtual ~ASTType() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTBinOp : public ASTNode
{
public:
    string op;
    ASTNode *left;
    ASTNode *right;
    ASTBinOp(string op, ASTNode *l, ASTNode *r) : op(op), left(l), right(r) {}
    virtual ~ASTBinOp() override
    {
        delete left;
        delete right;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTUnaryOp : public ASTNode
{
public:
    string op;
    ASTNode *expr;
    ASTUnaryOp(string op, ASTNode *expr) : op(op), expr(expr) {}
    virtual ~ASTUnaryOp() override
    {
        delete expr;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTProgram : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTProgram(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTProgram() override
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTBlock : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTBlock(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTBlock() override
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTVarDecl : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *init;
    ASTVarDecl(ASTNode *id, ASTNode *init) : id(id), init(init) {}
    virtual ~ASTVarDecl() override
    {
        delete id;
        delete init;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTIfStmn : public ASTNode
{
public:
    ASTNode *cond;     // should be the ASTBinOP
    ASTNode *ifbody;   // same as ASTBlock
    ASTNode *elsebody; // same as ASTBlock
    ASTIfStmn(ASTNode *cond, ASTNode *ifbody, ASTNode *elsebody = nullptr) : cond(cond), ifbody(ifbody), elsebody(elsebody) {}
    virtual ~ASTIfStmn() override
    {
        delete cond;
        delete ifbody;
        delete elsebody;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTIfBody : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTIfBody(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTIfBody() override
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTElseBody : public ASTNode
{
public:
    vector<ASTNode *> stmnts;
    ASTElseBody(vector<ASTNode *> stmnts) : stmnts(stmnts) {}
    virtual ~ASTElseBody() override
    {
        for (int i = 0; i < stmnts.size(); i++)
        {
            delete stmnts[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTWhile : public ASTNode
{
public:
    ASTNode *condtn;
    ASTNode *stmnts;
    ASTWhile(ASTNode *condtn, ASTNode *stmnts) : condtn(condtn), stmnts(stmnts) {}
    virtual ~ASTWhile() override
    {
        delete condtn;
        delete stmnts;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFor : public ASTNode
{
public:
    ASTNode *vardec;
    ASTNode *expr;
    ASTNode *assignment;
    ASTNode *block;
    ASTFor(ASTNode *vardec = nullptr, ASTNode *expr = nullptr, ASTNode *assignment = nullptr, ASTNode *block = nullptr)
        : vardec(vardec), expr(expr), assignment(assignment), block(block) {}
    virtual ~ASTFor() override
    {
        delete vardec;
        delete expr;
        delete assignment;
        delete block;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFunDec : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *params;
    ASTNode *rtrntype;
    ASTNode *block;
    ASTFunDec(ASTNode *id, ASTNode *params, ASTNode *rtrntype, ASTNode *block) : id(id), params(params), rtrntype(rtrntype), block(block) {}
    virtual ~ASTFunDec() override
    {
        delete id;
        delete params;
        delete rtrntype;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFunCall : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *params;
    ASTFunCall(ASTNode *id, ASTNode *params) : id(id), params(params) {}
    virtual ~ASTFunCall() override
    {
        delete id;
        delete params;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTParams : public ASTNode
{
public:
    vector<ASTNode *> expressions;
    ASTParams(vector<ASTNode *> expressions) : expressions(expressions) {}
    virtual ~ASTParams() override
    {
        for (int i = 0; i < expressions.size(); i++)
        {
            delete expressions[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFormalParam : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *type;
    ASTFormalParam(ASTNode *id, ASTNode *type) : id(id), type(type) {}
    virtual ~ASTFormalParam() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFormalParams : public ASTNode
{
public:
    vector<ASTNode *> params;
    ASTFormalParams(vector<ASTNode *> params) : params(params) {}
    virtual ~ASTFormalParams() override
    {
        for (int i = 0; i < params.size(); i++)
        {
            delete params[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTPrintStmnt : public ASTNode
{
public:
    ASTNode *expression;
    ASTPrintStmnt(ASTNode *expression) : expression(expression) {}
    virtual ~ASTPrintStmnt() override
    {
        delete expression;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTRandiStmnt : public ASTNode
{
public:
    ASTNode *expression;
    ASTRandiStmnt(ASTNode *expression) : expression(expression) {}
    virtual ~ASTRandiStmnt() override
    {
        delete expression;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTPixelStmnt : public ASTNode
{
public:
    ASTNode *pixel;
    ASTNode *amount;
    ASTNode *col;
    ASTPixelStmnt(ASTNode *pixel, ASTNode *amount, ASTNode *col) : pixel(pixel), amount(amount), col(col) {}
    virtual ~ASTPixelStmnt() override
    {
        delete pixel;
        delete amount;
        delete col;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTPixelrStmnt : public ASTNode
{
public:
    // TODO: change this approach by merging the class with ASTPixelSDtmnt and setting the extra 2 expressions to nullptr as default values
    ASTNode *expr1;
    ASTNode *expr2;
    ASTNode *expr3;
    ASTNode *expr4;
    ASTNode *expr5;
    ASTPixelrStmnt(ASTNode *expr1, ASTNode *expr2, ASTNode *expr3, ASTNode *expr4, ASTNode *expr5) : expr1(expr1), expr2(expr2), expr3(expr3), expr4(expr4), expr5(expr5) {}
    virtual ~ASTPixelrStmnt() override
    {
        delete expr1;
        delete expr2;
        delete expr3;
        delete expr4;
        delete expr5;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTDelayStmnt : public ASTNode
{
public:
    ASTNode *expression;
    ASTDelayStmnt(ASTNode *expression) : expression(expression) {}
    virtual ~ASTDelayStmnt() override
    {
        delete expression;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTReadStmnt : public ASTNode
{
public:
    ASTNode *expr1;
    ASTNode *expr2;
    ASTReadStmnt(ASTNode *expr1, ASTNode *expr2) : expr1(expr1), expr2(expr2) {}
    virtual ~ASTReadStmnt() override
    {
        delete expr1;
        delete expr2;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

// TODO: Merge the below 3 classes into 1 class as they are effectively the same

class ASTTerm : public ASTNode
{
public:
    vector<ASTNode *> factors;
    ASTTerm(vector<ASTNode *> factors) : factors(factors) {}
    virtual ~ASTTerm() override
    {
        for (int i = 0; i < factors.size(); i++)
        {
            delete factors[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTSimpleExpr : public ASTNode
{
public:
    vector<ASTNode *> terms;
    ASTSimpleExpr(vector<ASTNode *> terms) : terms(terms) {}
    virtual ~ASTSimpleExpr() override
    {
        for (int i = 0; i < terms.size(); i++)
        {
            delete terms[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTExpr : public ASTNode
{
public:
    vector<ASTNode *> simpleExprs;
    ASTExpr(vector<ASTNode *> simpleExprs) : simpleExprs(simpleExprs) {}
    virtual ~ASTExpr() override
    {
        for (int i = 0; i < simpleExprs.size(); i++)
        {
            delete simpleExprs[i];
        }
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

// TODO: you can actually merge this with VarDec class
class ASTAssignment : public ASTNode
{
public:
    ASTNode *id;
    ASTNode *expr;
    ASTAssignment(ASTNode *id, ASTNode *expr) : id(id), expr(expr) {}
    virtual ~ASTAssignment() override
    {
        delete id;
        delete expr;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};