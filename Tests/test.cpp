#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"
#include "../XMLVisitor/XMLVisitor.h"
#include "../SemanticAnalysis/SemVisitor.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("\nYou need to specify the absolute path of the text file you wish to compile");
        return -1;
    }



    Scanner *lexer = new Scanner(argv[1]);
    //Scanner *lexer2 = new Scanner("C:/Users/dakif/OneDrive/UniCode/CompilerTheory/PixArLang-Compiler/Tests/test2.txt");
    //Scanner *lexer3 = new Scanner("C:/Users/dakif/OneDrive/UniCode/CompilerTheory/PixArLang-Compiler/Tests/test3.txt");
    //Scanner *lexer4 = new Scanner("C:/Users/dakif/OneDrive/UniCode/CompilerTheory/PixArLang-Compiler/Tests/test4.txt");

    lexer->scanInput();
    lexer->displayTokens();
    //lexer2->scanInput();
    //lexer3->scanInput();
    //lexer4->scanInput();

    XMLVisitor *visitor = new XMLVisitor();
    SemanticVisitor *semvisitor = new SemanticVisitor();

    Parser parser = Parser(lexer);
    parser.parse();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    visitor->visit(parser.root);

    //Parser parser2 = Parser(lexer2);
    //parser2.parse();
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //visitor->visit(parser2.root);
//
    //Parser parser3 = Parser(lexer3);
    //parser3.parse();
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 3~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //visitor->visit(parser3.root);
//
    //Parser parser4 = Parser(lexer4);
    //parser4.parse();
    //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 4~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //visitor->visit(parser4.root);

    //semvisitor->visit(parser2.root);
    //semvisitor->visit(parser3.root);
    //semvisitor->visit(parser4.root);
    //semvisitor->visit(parser5.root);

    return 0;
}