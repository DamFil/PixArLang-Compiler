#include "Scanner.h"

int main(int argc, char *argv[]) {
    //string path;
    //cout << "enter pathL: ";
    //cin >> path;

    Scanner lexer = Scanner("/home/damfil/Uni/CompilerTheory/Assignment/test.txt");

    lexer.scanInput();
    lexer.displayTokens();

    return 0;
}