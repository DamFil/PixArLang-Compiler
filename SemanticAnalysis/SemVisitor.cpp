#include "SemVisitor.h"
#include "../Parser/AST.h"

inline type returnType(string t)
{
    if (t == "int")
        return integer;
    if (t == "float")
        return floater;
    if (t == "bool")
        return boolean;
    if (t == "colour")
        return colour;

    return NotAType;
}

type SemanticVisitor::visit(ASTLit *lit)
{
    if (lit->intl != nullptr)
        return lit->intl->accept(this);
    else if (lit->floatl != nullptr)
        return lit->floatl->accept(this);
    else if (lit->colourl != nullptr)
        return lit->colourl->accept(this);
    else if (lit->booll != nullptr)
        return lit->booll->accept(this);
    else
    {
        cout << "Error during Semantic Analysis: Problem with the Lit node" << endl;
        return ERROR;
    }
}

type SemanticVisitor::visit(ASTIntLit *intl)
{
    return integer;
}

type SemanticVisitor::visit(ASTFloatLit *floatl)
{
    return floater;
}

type SemanticVisitor::visit(ASTColourLit *coll)
{
    return colour;
}

type SemanticVisitor::visit(ASTBoolLit *booll)
{
    return boolean;
}

type SemanticVisitor::visit(ASTPadH *padh)
{
    return integer;
}

type SemanticVisitor::visit(ASTPadH *padw)
{
    return integer;
}

type SemanticVisitor::visit(ASTId *id)
{
    TypeObject *found = symboltable->lookup(id->name);
    if (found == nullptr)
    {
        cout << "No Identifier with the name: \"" << id->name << "\" has been found" << endl;
        return ERROR;
    }

    if (found->r == fun)
    {
        cout << "\"" << id->name << "\" is a function. To call it you have to do: \"" << id->name << "()\"" << endl;
        return ERROR;
    }

    return found->types.at(0);
}

type SemanticVisitor::visit(ASTVarDecl *vardecl)
{
    type t = returnType(vardecl->type);

    TypeObject *newvar = new TypeObject({t}, var);
    pair toinsert(vardecl->id->name, newvar);
    res r = symboltable->insert(toinsert);

    if (r == sameScope)
    {
        cout << "Cannot declare 2 entities with the same Identifier name in the same scope: \"" << vardecl->id->name << "\"." << endl;
        return ERROR;
    }

    return NotAType;
}

type SemanticVisitor::visit(ASTAssignment *assi)
{
    type t = assi->id->accept(this);
    if (t == ERROR)
    {
        cout << "Identifer: \"" << assi->id->name << "\" does not exist" << endl;
        return t;
    }
    else if (t != assi->expr->accept(this))
    {
        cout << "Type mismatch between \"" << assi->id->name << "\" and the expression" << endl;
        return ERROR;
    }

    return t;
}

type SemanticVisitor::visit(ASTFactor *factor)
{
    if (factor->fncall != nullptr)
        return factor->fncall->accept(this);
    else if (factor->id != nullptr)
        return factor->id->accept(this);
    else if (factor->lit != nullptr)
        return factor->lit->accept(this);
    else if (factor->padh != nullptr)
        return factor->padh->accept(this);
    else if (factor->padw != nullptr)
        return factor->padw->accept(this);
    else if (factor->randi != nullptr)
        return factor->randi->accept(this);
    else if (factor->read != nullptr)
        return factor->read->accept(this);
    else if (factor->subexpr != nullptr)
        return factor->subexpr->accept(this);
    else if (factor->unary != nullptr)
        return factor->unary->accept(this);
    else
    {
        cout << "Error during Semantic Analysis - Problem with factor nodes" << endl;
        return ERROR;
    }
}

type SemanticVisitor::visit(ASTResultExpr *rexpr)
{
    if (rexpr->binop != nullptr)
        return rexpr->binop->accept(this);
    else if (rexpr->factor != nullptr)
        return rexpr->factor->accept(this);
    else
    {
        cout << "Error generating the XML Code - Problem with the ResultExpr node" << endl;
        return ERROR;
    }
}

type SemanticVisitor::visit(ASTExpr *expr)
{
    return expr->expr->accept(this);
}

type SemanticVisitor::visit(ASTBinOp *binop)
{
    type t1, t2;
    t1 = binop->left->accept(this);
    t2 = binop->right->accept(this);
    if (t1 != t2)
    {
        cout << "Type Mismatch Between the 2 Expressions" << endl;
        return ERROR;
    }

    if (t1 == boolean)
    {
        if (binop->op == "+" || binop->op == "-" ||
            binop->op == "*" || binop->op == "/" ||
            binop->op == "=")
        {
            cout << "Cannot use non-relational operators on boolean expressions" << endl;
            return ERROR;
        }
    }
    else
    {
        if (binop->op == "and" || binop->op == "or" ||
            binop->op == "not")
        {
            cout << "Cannot use \"and\",\"or\" and \"not\" operators on non-boolean types" << endl;
            return ERROR;
        }
    }

    return t1;
}

type SemanticVisitor::visit(ASTUnaryOp *unary)
{
    type t1 = unary->expr->accept(this);
    if (t1 == boolean && (unary->op != "not"))
    {
        cout << "Cannot use " << unary->op << " on booleans" << endl;
        return ERROR;
    }
    else if (t1 != boolean && (unary->op != "-"))
    {
        cout << "Cannot use " << unary->op << " on non-booleans" << endl;
        return ERROR;
    }

    return t1;
}

type SemanticVisitor::visit(ASTDelayStmnt *delay)
{
    type t = delay->expr->accept(this);
    if (t != integer)
    {
        cout << "Calling __delay needs to be followed by an expression of type integer" << endl;
        return ERROR;
    }

    return t;
}

type SemanticVisitor::visit(ASTPrintStmnt *print)
{
    type t = print->expr->accept(this);
    if (t != integer)
    {
        cout << "Calling __print needs to be followed by an expression of type integer" << endl;
        return ERROR;
    }

    return t;
}

type SemanticVisitor::visit(ASTRandiStmnt *randi)
{
    type t = randi->expr->accept(this);
    if (t != integer)
    {
        cout << "Calling __randi needs to be followed by an expression of type integer" << endl;
        return ERROR;
    }

    return t;
}

type SemanticVisitor::visit(ASTReadStmnt *read)
{
    type t1 = read->expr1->accept(this);
    type t2 = read->expr2->accept(this);

    if (t1 != integer || t2 != integer)
    {
        cout << "Calling __read needs to be followed by 2 expressions, both of type integer" << endl;
        return ERROR;
    }

    return t1;
}

type SemanticVisitor::visit(ASTPixelStmnt *pixel)
{
    type t1 = pixel->col->accept(this);
    type t2 = pixel->amount->accept(this);
    type t3 = pixel->col->accept(this);

    if (pixel->expr1 != nullptr && pixel->expr2 != nullptr)
    {
        type t4 = pixel->expr1->accept(this);
        type t5 = pixel->expr2->accept(this);

        if (t1 != integer || t2 != integer ||
            t3 != integer || t4 != integer ||
            t5 != colour)
        {
            cout << "__pixelr needs to be followed by 5 expressions of types: integer, integer, integer, integer and colour, respectively" << endl;
            return ERROR;
        }
    }

    if (t1 != integer || t2 != integer || t3 != colour)
    {
        cout << "__pixel needs to be followed by 3 expressions of types integer, integer and colour respectively" << endl;
        return ERROR;
    }

    return NotAType;
}

type SemanticVisitor::visit(ASTStatement *s, type funtype)
{
    if (s->assi != nullptr)
        return s->assi->accept(this);
    else if (s->block != nullptr)
        return s->block->accept(this, funtype);
    else if (s->delay != nullptr)
        return s->delay->accept(this);
    else if (s->forstmnt != nullptr)
        return s->forstmnt->accept(this, funtype);
    else if (s->fundec != nullptr)
        return s->fundec->accept(this);
    else if (s->ifstmnt != nullptr)
        return s->ifstmnt->accept(this, funtype);
    else if (s->pixel != nullptr)
        return s->pixel->accept(this);
    else if (s->print != nullptr)
        return s->print->accept(this);
    else if (s->rtrn != nullptr)
        return s->rtrn->accept(this, funtype);
    else if (s->vardec != nullptr)
        return s->vardec->accept(this);
    else if (s->whilestmnt != nullptr)
        return s->whilestmnt->accept(this, funtype);
    else
    {
        cout << "Error during Semantic Analysis: Problem with the Statement node" << endl;
        return ERROR;
    }
}

type SemanticVisitor::visit(ASTFunCall *fncall)
{
    TypeObject *func = symboltable->lookup(fncall->id->name);
    if (func == nullptr)
    {
        cout << "Function with the name of \"" << fncall->id->name << "\" has not been declared yet" << endl;
        return ERROR;
    }

    if (func->r != fun)
    {
        cout << "The identifer \"" << fncall->id->name << "\" is not a function" << endl;
        return ERROR;
    }

    // I need to check for the validity of the parameters
    vector<type> types = fncall->params->accept(this);
    for (int i = 0; i < types.size(); i++)
    {
        if (types.at(i) != func->types.at(i))
        {
            cout << "The arguments do not match the defentition of the function: \"" << fncall->id->name << "\"." << endl;
            return ERROR;
        }
    }

    // returns the type of the function declaration
    return func->types.at(func->types.size() - 1); // the last type in the types field is the return type
}

type SemanticVisitor::visit(ASTFunDec *fndec)
{
    // obtaining the type of the function declaration i.e. type = (type param1, type param2, ..., rtrn type)
    vector<type> types{};
    for (int i = 0; i < fndec->params->params.size(); i++)
    {
        types.push_back(returnType(fndec->params->params.at(i)->type));
    }
    types.push_back(returnType(fndec->rtrntype));

    // create the TypeObject instance and insert it into the current scope in the symbol table
    TypeObject *newfun = new TypeObject(types, fun);
    pair toinsert(fndec->id->name, newfun);
    if (symboltable->insert(toinsert) == sameScope)
        return ERROR;

    // params will create a new scope and then so will block i.e.(params(block(---)))
    fndec->params->accept(this);
    type t = fndec->block->accept(this, types.at(types.size() - 1));

    if (t != *(types.end())) // equivalent to types.at(types.size() - 1)
    {
        cout << "The return type is not the same as the type of the function" << endl;
        return ERROR;
    }

    // pop is called twice because params creates a new scope and block creates a new scope as well
    symboltable->pop();
    symboltable->pop();

    return NotAType;
}

type SemanticVisitor::visit(ASTRtrnStmnt *rtrn, type funtype)
{
    type t = rtrn->expr->accept(this);
    if (t != funtype)
    {
        cout << "Ther returned value does not matcht the type of the function" << endl;
        return ERROR;
    }

    return NotAType;
}

vector<type> SemanticVisitor::visit(ASTParams *actualparams)
{
    vector<type> types{};
    for (int i = 0; i < actualparams->expressions.size(); i++)
    {
        types.push_back(actualparams->expressions.at(i)->accept(this));
    }

    return types;
}

type SemanticVisitor::visit(ASTFormalParam *par)
{
    type t = returnType(par->type);
    TypeObject *newparam = new TypeObject({t}, param);
    pair toinsert(par->id->name, newparam);
    symboltable->insert(toinsert);

    return NotAType;
}

type SemanticVisitor::visit(ASTFormalParams *params)
{
    symboltable->push();
    for (int i = 0; i < params->params.size(); i++)
    {
        params->params.at(i)->accept(this);
    }

    return NotAType;
}

type SemanticVisitor::visit(ASTIfStmn *ifstmnt, type funtype)
{
    type cond = ifstmnt->cond->accept(this);
    if (cond != boolean)
    {
        cout << "The condition inside if statements has to be of type bool" << endl;
        return ERROR;
    }

    ifstmnt->ifbody->accept(this, funtype);
    if (ifstmnt->elsebody != nullptr)
    {
        ifstmnt->elsebody->accept(this, funtype);
    }

    return NotAType;
}

type SemanticVisitor::visit(ASTWhile *whilestmnt, type funtype)
{
    type cond = whilestmnt->condtn->accept(this);
    if (cond != boolean)
    {
        cout << "The condition inside for the while loophas to be of type bool" << endl;
        return ERROR;
    }

    whilestmnt->stmnts->accept(this, funtype);

    return NotAType;
}

type SemanticVisitor::visit(ASTFor *forstmnt, type funtype)
{
    // create a new block
    symboltable->push();

    if (forstmnt->vardec != nullptr)
        forstmnt->vardec->accept(this);

    type cond = forstmnt->expr->accept(this);
    if (cond != boolean)
    {
        cout << "The condition inside the for loop declaration needs to be of type bool" << endl;
        return ERROR;
    }

    if (forstmnt->assignment != nullptr)
    {
        if (forstmnt->assignment->accept(this) == ERROR)
            return ERROR;
    }

    type t = forstmnt->block->accept(this, funtype);

    return t;
}

type SemanticVisitor::visit(ASTBlock *block, type funtype)
{
    symboltable->push();

    for (int i = 0; i < block->stmnts.size(); i++)
    {
        block->stmnts.at(i)->accept(this, funtype);
    }

    symboltable->pop();

    return NotAType;
}

type SemanticVisitor::visit(ASTIfBody *ifbody, type funtype)
{
    symboltable->push();

    for (int i = 0; i < ifbody->stmnts.size(); i++)
    {
        ifbody->stmnts.at(i)->accept(this, funtype);
    }

    symboltable->pop();

    return NotAType;
}

type SemanticVisitor::visit(ASTElseBody *elsebody, type funtype)
{
    symboltable->push();

    for (int i = 0; i < elsebody->stmnts.size(); i++)
    {
        elsebody->stmnts.at(i)->accept(this, funtype);
    }

    symboltable->pop();

    return NotAType;
}

type SemanticVisitor::visit(ASTProgram *program)
{
    symboltable->push();

    for (int i = 0; i < program->stmnts.size(); i++)
    {
        program->stmnts.at(i)->accept(this, NotAType);
    }

    symboltable->pop();

    return NotAType;
}