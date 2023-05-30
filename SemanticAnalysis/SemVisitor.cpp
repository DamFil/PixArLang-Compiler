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
    typeOfExpression = pad_height;
    return pad_height;
}

type SemanticVisitor::visit(ASTPadH *padw)
{
    typeOfExpression = pad_width;
    return pad_width;
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