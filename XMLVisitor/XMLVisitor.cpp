#include "XMLVisitor.h"
#include "../Parser/AST.h"

// inline to avoid the overhead of a function call
inline void XMLVisitor::printIndent()
{
    for (int i = 0; i < indent; i++)
    {
        cout << "\t";
    }
}

void XMLVisitor::visit(ASTLit *lit)
{
    if (lit->intl != nullptr)
        lit->intl->accept(this);
    else if (lit->floatl != nullptr)
        lit->floatl->accept(this);
    else if (lit->colourl != nullptr)
        lit->colourl->accept(this);
    else if (lit->booll != nullptr)
        lit->booll->accept(this);
    else
    {
        printIndent();
        cout << "Error generating XML Code: Problem with the Lit node" << endl;
    }
}

void XMLVisitor::visit(ASTIntLit *intl)
{
    printIndent();
    cout << "<IntegerLiteral>" << intl->value << "</IntegerLiteral>" << endl;
}

void XMLVisitor::visit(ASTFloatLit *floatl)
{
    printIndent();
    cout << "<FloatLiteral>" << floatl->value << "</FloatLiteral>" << endl;
}

void XMLVisitor::visit(ASTColourLit *colit)
{
    printIndent();
    cout << "<ColourLiteral>" << colit->value << "</ColourLiteral>" << endl;
}

void XMLVisitor::visit(ASTBoolLit *boolv)
{
    printIndent();
    cout << "<BooleanLiteral>" << boolv->value << "</BooleanLiteral>" << endl;
}

void XMLVisitor::visit(ASTPadH *padh)
{
    printIndent();
    cout << "<PadLiteral>__height</PadLiteral>" << endl;
}

void XMLVisitor::visit(ASTPadW *padw)
{
    printIndent();
    cout << "<PadLiteral>__width</PadLiteral>" << endl;
}

void XMLVisitor::visit(ASTId *id)
{
    printIndent();

    cout << "<Identifier>" << id->name << "</Identifier>" << endl;
}

void XMLVisitor::visit(ASTVarDecl *vardec)
{
    printIndent();
    cout << "<Variable Decl Type=\"" << vardec->type << "\">" << endl;

    ++indent;
    vardec->id->accept(this);
    vardec->init->accept(this);
    --indent;

    printIndent();
    cout << "</Variable Dec>" << endl;
}

void XMLVisitor::visit(ASTAssignment *assi)
{
    printIndent();

    cout << "<Assignment>" << endl;

    ++indent;
    assi->id->accept(this);
    assi->expr->accept(this);
    --indent;

    printIndent();
    cout << "</Assignment>" << endl;
}

void XMLVisitor::visit(ASTFactor *factor)
{
    if (factor->fncall != nullptr)
        factor->fncall->accept(this);
    else if (factor->id != nullptr)
        factor->id->accept(this);
    else if (factor->lit != nullptr)
        factor->lit->accept(this);
    else if (factor->padh != nullptr)
        factor->padh->accept(this);
    else if (factor->padw != nullptr)
        factor->padw->accept(this);
    else if (factor->randi != nullptr)
        factor->randi->accept(this);
    else if (factor->read != nullptr)
        factor->read->accept(this);
    else if (factor->subexpr != nullptr)
        factor->subexpr->accept(this);
    else if (factor->unary != nullptr)
        factor->unary->accept(this);
    else
    {
        printIndent();
        cout << "Error generating the XML Code - Problem with factor nodes" << endl;
    }
}

void XMLVisitor::visit(ASTResultExpr *rexpr)
{
    if (rexpr->binop != nullptr)
        rexpr->binop->accept(this);
    else if (rexpr->factor != nullptr)
        rexpr->factor->accept(this);
    else
    {
        printIndent();
        cout << "Error generating the XML Code - Problem with the ResultExpr node" << endl;
    }
}

void XMLVisitor::visit(ASTExpr *expr)
{
    expr->expr->accept(this);
}

void XMLVisitor::visit(ASTBinOp *binop)
{
    printIndent();

    cout << "<BinOp Op=\"" << binop->op << "\">>" << endl;
    ++indent;
    binop->left->accept(this);
    binop->right->accept(this);
    --indent;

    printIndent();
    cout << "</BinOp>" << endl;
}

void XMLVisitor::visit(ASTUnaryOp *unary)
{
    printIndent();

    cout << "UnaryOp op=\"" << unary->op << "\">" << endl;
    ++indent;
    unary->expr->accept(this);
    --indent;

    printIndent();
    cout << "</UnaryOp>" << endl;
}

void XMLVisitor::visit(ASTDelayStmnt *delay)
{
    printIndent();

    cout << "<__delay>" << endl;
    ++indent;
    delay->expr->accept(this);
    --indent;

    printIndent();
    cout << "</__delay>" << endl;
}

void XMLVisitor::visit(ASTPrintStmnt *print)
{
    printIndent();

    cout << "<__print>" << endl;
    ++indent;
    print->expr->accept(this);
    --indent;

    printIndent();
    cout << "</__print>" << endl;
}

void XMLVisitor::visit(ASTRandiStmnt *randi)
{
    printIndent();

    cout << "<__randi>" << endl;
    ++indent;
    randi->expr->accept(this);
    --indent;

    printIndent();
    cout << "</__randi>" << endl;
}

void XMLVisitor::visit(ASTReadStmnt *read)
{
    printIndent();

    cout << "<__read>" << endl;
    ++indent;
    read->expr1->accept(this);
    read->expr2->accept(this);
    --indent;

    printIndent();
    cout << "</__read>" << endl;
}

void XMLVisitor::visit(ASTPixelStmnt *pixel)
{
    printIndent();

    cout << "<__pixel>" << endl;
    ++indent;
    pixel->pixel->accept(this);
    pixel->amount->accept(this);
    pixel->col->accept(this);

    if (pixel->expr1 != nullptr && pixel->expr2 != nullptr)
    {
        pixel->expr1->accept(this);
        pixel->expr2->accept(this);
    }

    --indent;
    printIndent();
    cout << "</__pixel>" << endl;
}

void XMLVisitor::visit(ASTStatement *s)
{
    if (s->assi != nullptr)
        s->assi->accept(this);
    else if (s->block != nullptr)
        s->block->accept(this);
    else if (s->delay != nullptr)
        s->delay != nullptr;
    else if (s->forstmnt != nullptr)
        s->forstmnt->accept(this);
    else if (s->fundec != nullptr)
        s->fundec->accept(this);
    else if (s->ifstmnt != nullptr)
        s->ifstmnt->accept(this);
    else if (s->pixel != nullptr)
        s->pixel->accept(this);
    else if (s->print != nullptr)
        s->print->accept(this);
    else if (s->rtrn != nullptr)
        s->rtrn->accept(this);
    else if (s->vardec != nullptr)
        s->vardec->accept(this);
    else if (s->whilestmnt != nullptr)
        s->whilestmnt->accept(this);
    else
    {
        printIndent();
        cout << "Error generating XML Code: Problem with the Statement node" << endl;
    }
}

void XMLVisitor::visit(ASTFunCall *fncall)
{
    printIndent();
    cout << "<FunCall>" << endl;
    ++indent;
    fncall->id->accept(this);
    fncall->params->accept(this);
    --indent;
    printIndent();
    cout << "</FunCall>" << endl;
}

void XMLVisitor::visit(ASTFunDec *fndec)
{
    printIndent();
    cout << "<FunDec type=\"" << fndec->rtrntype << "\">>" << endl;
    ++indent;
    fndec->id->accept(this);
    fndec->params->accept(this);
    fndec->block->accept(this);
    --indent;
    printIndent();
    cout << "</FunDec>" << endl;
}

void XMLVisitor::visit(ASTRtrnStmnt *rtrn)
{
    printIndent();
    cout << "<Return>" << endl;
    ++indent;
    rtrn->expr->accept(this);
    --indent;
    printIndent();
    cout << "</Return>" << endl;
}

void XMLVisitor::visit(ASTParams *params)
{
    printIndent();
    cout << "<ActualParameters>" << endl;
    ++indent;
    for (auto i : params->expressions)
    {
        i->accept(this);
    }
    --indent;
    printIndent();
    cout << "</ActualParameters>" << endl;
}

void XMLVisitor::visit(ASTFormalParam *fparam)
{
    printIndent();
    cout << "<Param type=\"" << fparam->type << "\">" << endl;
    ++indent;
    fparam->id->accept(this);
    --indent;
    printIndent();
    cout << "</Param>" << endl;
}

void XMLVisitor::visit(ASTFormalParams *fparams)
{
    printIndent();
    cout << "<FormalParameters>" << endl;
    ++indent;
    for (auto i : fparams->params)
    {
        i->accept(this);
    }
    --indent;
    printIndent();
    cout << "</FormalParameters>" << endl;
}

void XMLVisitor::visit(ASTIfStmn *ifstmn)
{
    printIndent();
    cout << "<IfStmnt>" << endl;
    ++indent;
    ifstmn->cond->accept(this);
    ifstmn->ifbody->accept(this);
    if (ifstmn->elsebody != nullptr)
        ifstmn->elsebody->accept(this);
    --indent;
    printIndent();
    cout << "</IfStmnt>" << endl;
}

void XMLVisitor::visit(ASTIfBody *ifbody)
{
    printIndent();
    cout << "<IfBody>" << endl;
    ++indent;
    for (int i = 0; i < ifbody->stmnts.size(); i++)
    {
        ifbody->stmnts.at(i)->accept(this);
    }
    --indent;
    printIndent();
    cout << "</IfBody>" << endl;
}

void XMLVisitor::visit(ASTElseBody *elsebody)
{
    printIndent();
    cout << "<ElseBody>" << endl;
    ++indent;
    for (auto i : elsebody->stmnts)
    {
        i->accept(this);
    }
    --indent;
    printIndent();
    cout << "</ElseBody>" << endl;
}

void XMLVisitor::visit(ASTWhile *whilestmnt)
{
    printIndent();
    cout << "<While>" << endl;
    ++indent;
    whilestmnt->condtn->accept(this);
    whilestmnt->stmnts->accept(this);
    --indent;
    printIndent();
    cout << "</While>" << endl;
}

void XMLVisitor::visit(ASTFor *forstmnt)
{
    printIndent();
    cout << "<For>" << endl;
    ++indent;
    if (forstmnt->vardec != nullptr)
        forstmnt->vardec->accept(this);
    forstmnt->expr->accept(this);
    if (forstmnt->assignment != nullptr)
        forstmnt->assignment->accept(this);
    forstmnt->block->accept(this);
    --indent;
    printIndent();
    cout << "</For>" << endl;
}

void XMLVisitor::visit(ASTBlock *block)
{
    printIndent();
    cout << "<Block>" << endl;
    ++indent;
    for (auto i : block->stmnts)
    {
        i->accept(this);
    }
    --indent;
    printIndent();
    cout << "</Block>" << endl;
}

void XMLVisitor::visit(ASTProgram *program)
{
    printIndent();
    cout << "<Program>" << endl;
    ++indent;
    for (auto i : program->stmnts)
    {
        i->accept(this);
    }
    --indent;
    printIndent();
    cout << "</Program>" << endl;
}