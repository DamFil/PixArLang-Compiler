#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"
#include "../XMLVisitor/XMLVisitor.h"

int main()
{

    Scanner *lexer = new Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test.txt");
    Scanner *lexer2 = new Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test2.txt");
    Scanner *lexer3 = new Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test3.txt");
    Scanner *lexer4 = new Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test4.txt");
    Scanner *lexer5 = new Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test5.txt");

    lexer->scanInput();
    lexer2->scanInput();
    lexer3->scanInput();
    lexer4->scanInput();
    lexer5->scanInput();

    XMLVisitor *visitor = new XMLVisitor();

    Parser parser = Parser(lexer);
    parser.parse();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    visitor->visit(parser.root);

    Parser parser2 = Parser(lexer2);
    parser2.parse();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    visitor->visit(parser2.root);

    Parser parser3 = Parser(lexer3);
    parser3.parse();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 3~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    visitor->visit(parser3.root);

    Parser parser4 = Parser(lexer4);
    parser4.parse();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 4~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    visitor->visit(parser4.root);

    Parser parser5 = Parser(lexer5);
    parser5.parse();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~PROGRAM 5~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    visitor->visit(parser5.root);

    return 0;
}