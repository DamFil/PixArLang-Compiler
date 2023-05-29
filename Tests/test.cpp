#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"

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

    Parser parser = Parser(lexer);
    parser.parse();

    Parser parser2 = Parser(lexer2);
    parser2.parse();

    Parser parser3 = Parser(lexer3);
    parser3.parse();

    Parser parser4 = Parser(lexer4);
    parser.parse();

    Parser parser5 = Parser(lexer5);
    parser.parse();

    return 0;
}