#pragma once

#include "../Scanner/TokenStruct.h"
#include "../XMLVisitor/XMLVisitor.h"
#include "../SemanticAnalysis/SemVisitor.h"

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

class ASTNode
{
public:
    virtual ~ASTNode() {}
};

class ASTResultExpr : public ASTNode
{
public:
    ASTFactor *factor = nullptr;
    ASTBinOp *binop = nullptr;

    virtual ~ASTResultExpr() override;

    void setFactor(ASTFactor *factor)
    {
        this->factor = factor;
    }

    void setBinOp(ASTBinOp *binop)
    {
        this->binop = binop;
    }

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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
    ASTLit(ASTIntLit *intl)
    {
        this->intl = intl;
    }
    ASTLit(ASTFloatLit *floatl)
    {
        this->floatl = floatl;
    }
    ASTLit(ASTColourLit *colourl)
    {
        this->colourl = colourl;
    }
    ASTLit(ASTBoolLit *booll)
    {
        this->booll = booll;
    }

    virtual ~ASTLit() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTPadH : public ASTNode
{
public:
    ASTPadH() {}
    virtual ~ASTPadH() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTPadW : public ASTNode
{
public:
    ASTPadW() {}
    virtual ~ASTPadW() override {}

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTBinOp : public ASTNode
{
public:
    string op;
    ASTResultExpr *left;
    ASTResultExpr *right;

    ASTBinOp(string op, ASTResultExpr *l, ASTResultExpr *r)
        : op(op), left(l), right(r) {}

    virtual ~ASTBinOp() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTUnaryOp : public ASTNode
{
public:
    string op;
    ASTExpr *expr;

    ASTUnaryOp(string op, ASTExpr *expr) : op(op), expr(expr) {}

    virtual ~ASTUnaryOp() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTProgram : public ASTNode
{
public:
    vector<ASTStatement *> stmnts;

    ASTProgram(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

    virtual ~ASTProgram() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTBlock : public ASTNode
{
public:
    vector<ASTStatement *> stmnts;

    ASTBlock(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

    virtual ~ASTBlock() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    virtual ~ASTVarDecl() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    typeOfIdentifer accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTIfStmn : public ASTNode
{
public:
    ASTExpr *cond;
    ASTIfBody *ifbody;
    ASTElseBody *elsebody;

    ASTIfStmn(ASTExpr *cond, ASTIfBody *ifbody, ASTElseBody *elsebody = nullptr)
        : cond(cond), ifbody(ifbody), elsebody(elsebody) {}

    virtual ~ASTIfStmn() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTIfBody : public ASTNode
{
public:
    vector<ASTStatement *> stmnts;

    ASTIfBody(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

    virtual ~ASTIfBody() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTElseBody : public ASTNode
{
public:
    vector<ASTStatement *> stmnts;

    ASTElseBody(vector<ASTStatement *> stmnts) : stmnts(stmnts) {}

    virtual ~ASTElseBody() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTWhile : public ASTNode
{
public:
    ASTExpr *condtn;
    ASTBlock *stmnts;

    ASTWhile(ASTExpr *condtn, ASTBlock *stmnts) : condtn(condtn), stmnts(stmnts) {}

    virtual ~ASTWhile() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    virtual ~ASTFor() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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

    virtual ~ASTFunDec() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTFunCall : public ASTNode
{
public:
    ASTId *id;
    ASTParams *params;

    ASTFunCall(ASTId *id, ASTParams *params) : id(id), params(params) {}

    virtual ~ASTFunCall() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTParams : public ASTNode
{
public:
    vector<ASTExpr *> expressions;

    ASTParams(vector<ASTExpr *> expressions) : expressions(expressions) {}

    virtual ~ASTParams() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTFormalParam : public ASTNode
{
public:
    ASTId *id;
    string type;

    ASTFormalParam(ASTId *id, string type) : id(id), type(type) {}

    virtual ~ASTFormalParam() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    typeOfIdentifer accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTFormalParams : public ASTNode
{
public:
    vector<ASTFormalParam *> params;

    ASTFormalParams(vector<ASTFormalParam *> params) : params(params) {}

    virtual ~ASTFormalParams() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTPrintStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTPrintStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTPrintStmnt() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTRandiStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTRandiStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTRandiStmnt() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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
        : pixel(pixel), amount(amount), col(col), expr1(expr1), expr2(expr2) {}

    virtual ~ASTPixelStmnt() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTDelayStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTDelayStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTDelayStmnt() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTReadStmnt : public ASTNode
{
public:
    ASTExpr *expr1;
    ASTExpr *expr2;

    ASTReadStmnt(ASTExpr *expr1, ASTExpr *expr2) : expr1(expr1), expr2(expr2) {}

    virtual ~ASTReadStmnt() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
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
    ASTFactor(ASTLit *lit)
    {
        this->lit = lit;
    }
    ASTFactor(ASTId *id)
    {
        this->id = id;
    }
    ASTFactor(ASTFunCall *fncall)
    {
        this->fncall = fncall;
    }
    ASTFactor(ASTExpr *subexpr)
    {
        this->subexpr = subexpr;
    }
    ASTFactor(ASTUnaryOp *unary)
    {
        this->unary = unary;
    }
    ASTFactor(ASTRandiStmnt *randi)
    {
        this->randi = randi;
    }
    ASTFactor(ASTPadH *padh)
    {
        this->padh = padh;
    }
    ASTFactor(ASTPadW *padw)
    {
        this->padw = padw;
    }
    ASTFactor(ASTReadStmnt *read)
    {
        this->read = read;
    }

    virtual ~ASTFactor() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTExpr : public ASTNode
{
public:
    ASTResultExpr *expr;

    ASTExpr(ASTResultExpr *expr) : expr(expr) {}

    virtual ~ASTExpr() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTAssignment : public ASTNode
{
public:
    ASTId *id;
    ASTExpr *expr;

    ASTAssignment(ASTId *id, ASTExpr *expr) : id(id), expr(expr) {}

    virtual ~ASTAssignment() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

class ASTRtrnStmnt : public ASTNode
{
public:
    ASTExpr *expr;

    ASTRtrnStmnt(ASTExpr *expr) : expr(expr) {}

    virtual ~ASTRtrnStmnt() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
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
    ASTStatement(ASTVarDecl *vardec)
    {
        this->vardec = vardec;
    }
    ASTStatement(ASTAssignment *assi)
    {
        this->assi = assi;
    }
    ASTStatement(ASTPrintStmnt *print)
    {
        this->print = print;
    }
    ASTStatement(ASTDelayStmnt *delay)
    {
        this->delay = delay;
    }
    ASTStatement(ASTPixelStmnt *pixel)
    {
        this->pixel = pixel;
    }
    ASTStatement(ASTIfStmn *ifstmnt)
    {
        this->ifstmnt = ifstmnt;
    }
    ASTStatement(ASTFor *forstmnt)
    {
        this->forstmnt = forstmnt;
    }
    ASTStatement(ASTWhile *whilestmnt)
    {
        this->whilestmnt = whilestmnt;
    }
    ASTStatement(ASTRtrnStmnt *rtrn)
    {
        this->rtrn = rtrn;
    }
    ASTStatement(ASTFunDec *fundec)
    {
        this->fundec = fundec;
    }
    ASTStatement(ASTBlock *block)
    {
        this->block = block;
    }

    virtual ~ASTStatement() override;

    void accept(XMLVisitor *visitor)
    {
        visitor->visit(this);
    }

    type accept(SemanticVisitor *visitor)
    {
        return visitor->visit(this);
    }
};

// inline to avoid multiple defenition errors - compiler replaces function call with the function body directly
inline ASTResultExpr::~ASTResultExpr()
{
    delete factor;
    delete binop;
}

inline ASTLit::~ASTLit()
{
    delete intl;
    delete floatl;
    delete colourl;
    delete booll;
}

inline ASTBinOp::~ASTBinOp()
{
    delete left;
    delete right;
}

inline ASTUnaryOp::~ASTUnaryOp()
{
    delete expr;
}

inline ASTProgram::~ASTProgram()
{
    for (int i = 0; i < stmnts.size(); i++)
    {
        delete stmnts[i];
    }
}

inline ASTBlock::~ASTBlock()
{
    for (int i = 0; i < stmnts.size(); i++)
    {
        delete stmnts[i];
    }
}

inline ASTVarDecl::~ASTVarDecl()
{
    delete id;
    delete init;
}

inline ASTIfStmn::~ASTIfStmn()
{
    delete cond;
    delete ifbody;
    delete elsebody;
}

inline ASTIfBody::~ASTIfBody()
{
    for (int i = 0; i < stmnts.size(); i++)
    {
        delete stmnts[i];
    }
}

inline ASTElseBody::~ASTElseBody()
{
    for (int i = 0; i < stmnts.size(); i++)
    {
        delete stmnts[i];
    }
}

inline ASTWhile::~ASTWhile()
{
    delete condtn;
    delete stmnts;
}

inline ASTFor::~ASTFor()
{
    delete vardec;
    delete expr;
    delete assignment;
    delete block;
}

inline ASTFunDec::~ASTFunDec()
{
    delete id;
    delete params;
    delete block;
}

inline ASTFunCall::~ASTFunCall()
{
    delete id;
    delete params;
}

inline ASTParams::~ASTParams()
{
    for (int i = 0; i < expressions.size(); i++)
    {
        delete expressions[i];
    }
}

inline ASTFormalParam::~ASTFormalParam()
{
    delete id;
}

inline ASTFormalParams::~ASTFormalParams()
{
    for (int i = 0; i < params.size(); i++)
    {
        delete params[i];
    }
}

inline ASTPrintStmnt::~ASTPrintStmnt()
{
    delete expr;
}

inline ASTRandiStmnt::~ASTRandiStmnt()
{
    delete expr;
}

inline ASTPixelStmnt::~ASTPixelStmnt()
{
    delete pixel;
    delete amount;
    delete col;
    delete expr1;
    delete expr2;
}

inline ASTDelayStmnt::~ASTDelayStmnt()
{
    delete expr;
}

inline ASTReadStmnt::~ASTReadStmnt()
{
    delete expr1;
    delete expr2;
}

inline ASTFactor::~ASTFactor()
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

// inline ASTTerm::~ASTTerm()
//{
//     for (int i = 0; i < factors.size(); i++)
//     {
//         delete factors[i];
//     }
// }
//
// inline ASTSimpleExpr::~ASTSimpleExpr()
//{
//     for (int i = 0; i < terms.size(); i++)
//     {
//         delete terms[i];
//     }
// }

inline ASTExpr::~ASTExpr()
{
    delete expr;
}

inline ASTAssignment::~ASTAssignment()
{
    delete id;
    delete expr;
}

inline ASTRtrnStmnt::~ASTRtrnStmnt()
{
    delete expr;
}

inline ASTStatement::~ASTStatement()
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