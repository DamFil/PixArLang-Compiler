#include "Scanner/Scanner.h"

int main() {

    Scanner lexer = Scanner("/home/damfil/Uni/CompilerTheory/Assignment/Tests/test.txt");

    lexer.scanInput();
    lexer.displayTokens();

    return 0;
}