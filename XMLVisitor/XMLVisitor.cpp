#include "XMLVisitor.h"

void XMLVisitor::visit(ASTIntLit *intl)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<IntegerLiteral>" << intl->value << "</IntegerLiteral>" << endl;
}

void XMLVisitor::visit(ASTFloatLit *floatl)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<FloatLiteral>" << floatl->value << "</FloatLiteral>" << endl;
}

void XMLVisitor::visit(ASTColourLit *colit)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<ColourLiteral>" << colit->value << "</ColourLiteral>" << endl;
}

void XMLVisitor::visit(ASTBoolLit *boolv)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<BooleanLiteral>" << boolv->value << "</BooleanLiteral>" << endl;
}

void XMLVisitor::visit(ASTPadLit *padv)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<PadLiteral>" << padv->padl << "</PadLiteral>" << endl;
}

void XMLVisitor::visit(ASTId *iden)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<Identifier>" << iden->name << "</Identifier>" << endl;
}

void XMLVisitor::visit(ASTType *t)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<Type>" << t->type << "</Type>" << endl;
}

void XMLVisitor::visit(ASTVarDecl *vd)
{
    for (int i = 0; i < indentation; i++)
    {
        cout << "\t";
    }

    cout << "<Decl>";
}