#pragma once

#include "../Scanner/TokenStruct.h"
#include "../XMLVisitor/XMLVisitor.h"

class ASTNode
{
public:
    virtual ~ASTNode() {}
};

class ASTResultExpr : public ASTFactor
{
public:
    ASTBinOp *binop = nullptr;

    ~ASTResultExpr()
    {
        delete lit;
        delete id;
        delete fncall;
        delete subexpr;
        delete unary;
        delete randi;
        delete padh;
        delete padw;
        delete read;
        delete binop;
    }

    void setBinOp(ASTBinOp *binop)
    {
        this->binop = binop;
    }
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

class ASTLit : public ASTNode
{
public:
    ASTIntLit *intl = nullptr;
    ASTFloatLit *floatl = nullptr;
    ASTColourLit *colourl = nullptr;
    ASTBoolLit *booll = nullptr;

    ASTLit() {}

    virtual ~ASTLit() override
    {
        delete intl;
        delete floatl;
        delete colourl;
        delete booll;
    }

    // setters
    void setIntL(ASTIntLit *intl)
    {
        this->intl = intl;
    }

    void setFloatL(ASTFloatLit *floatl)
    {
        this->floatl = floatl;
    }

    void setColourL(ASTColourLit *colourl)
    {
        this->colourl = colourl;
    }

    void setBoolL(ASTBoolLit *booll)
    {
        this->booll = booll;
    }
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

class ASTPadH : public ASTNode
{
public:
    ASTPadH() {}
    virtual ~ASTPadH() override {}
};

class ASTPadW : public ASTNode
{
public:
    ASTPadW() {}
    virtual ~ASTPadW() override {}
};

// class ASTPadLit : public ASTNode
//{
// public:
//     string padl;
//     ASTPadLit(string pl) : padl(pl) {}
//     virtual ~ASTPadLit() override {}
//
//     void accept(XMLVisitor *visitor)
//     {
//         visitor->visit(this);
//     }
// };

class ASTBinOp : public ASTNode
{
public:
    string op;
    ASTResultExpr *left;
    ASTResultExpr *right;

    ASTBinOp(string op, ASTResultExpr *l, ASTResultExpr *r)
        : op(op), left(l), right(r) {}

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
    ASTExpr *expr;

    ASTUnaryOp(string op, ASTExpr *expr) : op(op), expr(expr) {}

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
    vector<ASTStatement *> stmnts;

    ASTProgram(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

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
    vector<ASTStatement *> stmnts;

    ASTBlock(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

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
    ASTId *id;
    ASTExpr *init;
    string type;

    ASTVarDecl(ASTId *id, ASTExpr *init, string type)
        : id(id), init(init), type(type) {}

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
    ASTExpr *cond;
    ASTIfBody *ifbody;     // same as ASTBlock
    ASTElseBody *elsebody; // same as ASTBlock

    ASTIfStmn(ASTExpr *cond, ASTIfBody *ifbody, ASTElseBody *elsebody = nullptr)
        : cond(cond), ifbody(ifbody), elsebody(elsebody) {}

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
    vector<ASTStatement *> stmnts;

    ASTIfBody(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

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
    vector<ASTStatement *> stmnts;

    ASTElseBody(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

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
    ASTExpr *condtn;
    ASTBlock *stmnts;

    ASTWhile(ASTExpr *condtn, ASTBlock *stmnts) : condtn(condtn), stmnts(stmnts) {}

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
    ASTVarDecl *vardec;
    ASTExpr *expr;
    ASTAssignment *assignment;
    ASTBlock *block;

    ASTFor(ASTVarDecl *vardec = nullptr, ASTExpr *expr = nullptr,
           ASTAssignment *assignment = nullptr, ASTBlock *block = nullptr)
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
    ASTId *id;
    ASTFormalParams *params;
    string rtrntype;
    ASTBlock *block;

    ASTFunDec(ASTId *id, ASTFormalParams *params, string rtrntype, ASTBlock *block)
        : id(id), params(params), rtrntype(rtrntype), block(block) {}

    virtual ~ASTFunDec() override
    {
        delete id;
        delete params;
        delete block;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFunCall : public ASTNode
{
public:
    ASTId *id;
    ASTParams *params;

    ASTFunCall(ASTId *id, ASTParams *params) : id(id), params(params) {}

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
    vector<ASTExpr *> expressions;

    ASTParams(vector<ASTExpr *> expressions) : expressions(expressions) {}

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
    ASTId *id;
    string type;

    ASTFormalParam(ASTId *id, string type) : id(id), type(type) {}

    virtual ~ASTFormalParam() override
    {
        delete id;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTFormalParams : public ASTNode
{
public:
    vector<ASTFormalParam *> params;

    ASTFormalParams(vector<ASTFormalParam *> params) : params(params) {}

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
    ASTExpr *expr;

    ASTPrintStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTPrintStmnt() override
    {
        delete expr;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTRandiStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTRandiStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTRandiStmnt() override
    {
        delete expr;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTPixelStmnt : public ASTNode
{
public:
    ASTExpr *pixel;
    ASTExpr *amount;
    ASTExpr *col;
    ASTExpr *expr1;
    ASTExpr *expr2;

    ASTPixelStmnt(ASTExpr *pixel, ASTExpr *amount, ASTExpr *col,
                  ASTExpr *expr1 = nullptr, ASTExpr *expr2 = nullptr)
        : pixel(pixel), amount(amount), col(col) {}

    virtual ~ASTPixelStmnt() override
    {
        delete pixel;
        delete amount;
        delete col;
        delete expr1;
        delete expr2;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTDelayStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTDelayStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTDelayStmnt() override
    {
        delete expr;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class ASTReadStmnt : public ASTNode
{
public:
    ASTExpr *expr1;
    ASTExpr *expr2;

    ASTReadStmnt(ASTExpr *expr1, ASTExpr *expr2) : expr1(expr1), expr2(expr2) {}

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

class ASTFactor : public ASTNode
{
public:
    ASTLit *lit = nullptr;
    ASTId *id = nullptr;
    ASTFunCall *fncall = nullptr;
    ASTExpr *subexpr = nullptr;
    ASTUnaryOp *unary = nullptr;
    ASTRandiStmnt *randi = nullptr;
    ASTPadH *padh = nullptr;
    ASTPadW *padw = nullptr;
    ASTReadStmnt *read = nullptr;

    ASTFactor() {}

    virtual ~ASTFactor() override
    {
        delete lit;
        delete id;
        delete fncall;
        delete subexpr;
        delete unary;
        delete randi;
        delete padh;
        delete padw;
        delete read;
    }

    // setters
    void setLit(ASTLit *lit)
    {
        this->lit = lit;
    }

    void setId(ASTId *id)
    {
        this->id = id;
    }

    void setFnCall(ASTFunCall *fncall)
    {
        this->fncall = fncall;
    }

    void setSubExpr(ASTExpr *subexpr)
    {
        this->subexpr = subexpr;
    }

    void setUnary(ASTUnaryOp *unary)
    {
        this->unary = unary;
    }

    void setRandi(ASTRandiStmnt *randi)
    {
        this->randi = randi;
    }

    void setPadH(ASTPadH *padh)
    {
        this->padh = padh;
    }

    void setPadW(ASTPadW *padw)
    {
        this->padw = padw;
    }

    void setRead(ASTReadStmnt *read)
    {
        this->read = read;
    }
};

class ASTTerm : public ASTNode
{
public:
    vector<ASTFactor *> factors;

    ASTTerm(vector<ASTFactor *> factors) : factors(factors) {}

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
    vector<ASTTerm *> terms;

    ASTSimpleExpr(vector<ASTTerm *> terms) : terms(terms) {}

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
    vector<ASTSimpleExpr *> simpleExprs;

    ASTExpr(vector<ASTSimpleExpr *> simpleExprs) : simpleExprs(simpleExprs) {}

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

class ASTAssignment : public ASTNode
{
public:
    ASTId *id;
    ASTExpr *expr;

    ASTAssignment(ASTId *id, ASTExpr *expr) : id(id), expr(expr) {}

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

class ASTRtrnStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTRtrnStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTRtrnStmnt() override
    {
        delete expr;
    }

    // void accept
};

class ASTStatement : public ASTNode
{
public:
    ASTVarDecl *vardec = nullptr;
    ASTAssignment *assi = nullptr;
    ASTPrintStmnt *print = nullptr;
    ASTDelayStmnt *delay = nullptr;
    ASTPixelStmnt *pixel = nullptr;
    ASTIfStmn *ifstmnt = nullptr;
    ASTFor *forstmnt = nullptr;
    ASTWhile *whilestmnt = nullptr;
    ASTRtrnStmnt *rtrn = nullptr;
    ASTFunDec *fundec = nullptr;
    ASTBlock *block = nullptr;

    ASTStatement() {}

    virtual ~ASTStatement() override
    {
        delete vardec;
        delete assi;
        delete print;
        delete delay;
        delete pixel;
        delete ifstmnt;
        delete forstmnt;
        delete whilestmnt;
        delete rtrn;
        delete fundec;
        delete block;
    }

    // setters
    void setVarDec(ASTVarDecl *vardec)
    {
        this->vardec = vardec;
    }

    void setAssi(ASTAssignment *assi)
    {
        this->assi = assi;
    }

    void setPrint(ASTPrintStmnt *print)
    {
        this->print = print;
    }

    void setDelay(ASTDelayStmnt *delay)
    {
        this->delay = delay;
    }

    void setPixel(ASTPixelStmnt *pixel)
    {
        this->pixel = pixel;
    }

    void setIfStmnt(ASTIfStmn *ifstmnt)
    {
        this->ifstmnt = ifstmnt;
    }

    void setForStmnt(ASTFor *forstmnt)
    {
        this->forstmnt = forstmnt;
    }

    void setWhileStmnt(ASTWhile *whilestmnt)
    {
        this->whilestmnt = whilestmnt;
    }

    void setRtrn(ASTRtrnStmnt *rtrn)
    {
        this->rtrn = rtrn;
    }

    void setFunDec(ASTFunDec *fundec)
    {
        this->fundec = fundec;
    }

    void setBlock(ASTBlock *block)
    {
        this->block = block;
    }
};