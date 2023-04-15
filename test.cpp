#include "Scanner.h"

int main() {

    Scanner lexer = Scanner("/home/damfil/Uni/CompilerTheory/Assignment/test.txt");

    lexer.scanInput();
    lexer.displayTokens();

    return 0;
}