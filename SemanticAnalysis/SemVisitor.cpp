#include "SemVisitor.h"
#include "../Parser/AST.h"

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
    typeOfExpression = integer;
    return integer;
}

type SemanticVisitor::visit(ASTFloatLit *floatl)
{
    typeOfExpression = floater;
    return floater;
}

type SemanticVisitor::visit(ASTColourLit *coll)
{
    typeOfExpression = colour;
    return colour;
}

type SemanticVisitor::visit(ASTBoolLit *booll)
{
    typeOfExpression = boolean;
    return boolean;
}

type SemanticVisitor::visit(ASTPadH *padh)
{
    typeOfExpression = integer;
    return integer;
}

type SemanticVisitor::visit(ASTPadH *padw)
{
    typeOfExpression = integer;
    return integer;
}

type SemanticVisitor::visit(ASTId *id)
{
    Entity *found = symboltable->lookup(id->name);
    if (found == nullptr)
    {
        cout << "No Identifier with the name: \"" << id->name << "\" has been found" << endl;
        return ERROR;
    }
    typeOfExpression = found->t;
    return found->t;
}

type SemanticVisitor::visit(ASTVarDecl *vardecl)
{
    type t;
    if (vardecl->type == "int")
        t = integer;
    else if (vardecl->type == "float")
        t = floater;
    else if (vardecl->type == "colour")
        t = colour;
    else if (vardecl->type == "bool")
        t = boolean;

    string scope = symboltable->getCurrent() == 0 ? "global" : "local";

    Entity *newvar = new Entity(vardecl->id->name, scope, t, var);
    pair toinsert(vardecl->id->name, newvar);
    symboltable->insert(toinsert);

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
            cout << "Cannot use non-relational Operators on Boolean Expressions" << endl;
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

type SemanticVisitor::visit(ASTStatement *s)
{
    if (s->assi != nullptr)
        return s->assi->accept(this);
    else if (s->block != nullptr)
        return s->block->accept(this);
    else if (s->delay != nullptr)
        return s->delay->accept(this);
    else if (s->forstmnt != nullptr)
        return s->forstmnt->accept(this);
    else if (s->fundec != nullptr)
        return s->fundec->accept(this);
    else if (s->ifstmnt != nullptr)
        return s->ifstmnt->accept(this);
    else if (s->pixel != nullptr)
        return s->pixel->accept(this);
    else if (s->print != nullptr)
        return s->print->accept(this);
    else if (s->rtrn != nullptr)
        return s->rtrn->accept(this);
    else if (s->vardec != nullptr)
        return s->vardec->accept(this);
    else if (s->whilestmnt != nullptr)
        return s->whilestmnt->accept(this);
    else
    {
        cout << "Error during Semantic Analysis: Problem with the Statement node" << endl;
        return ERROR;
    }
}

type SemanticVisitor::visit(ASTFunCall *fncall)
{
    Entity *newfuncall = symboltable->lookup(fncall->id->name);
    if (newfuncall != nullptr)
    {
        cout << "An identifer with name \"" << fncall->id->name << "already exists" << endl;
        return ERROR;
    }

    //! I need to add type field to the fundec AST class

    // newfuncall = new Entity(fncall->id->name, "global",)
}