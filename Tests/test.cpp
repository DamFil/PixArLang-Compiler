#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"

int main()
{

    Scanner *lexer = new Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test5.txt");

    lexer->scanInput();
    lexer->displayTokens();

    Parser parser = Parser(lexer);
    parser.parse();
    return 0;
}