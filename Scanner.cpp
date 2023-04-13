#include "Scanner.h"

//constructors
Scanner::Scanner() {
    program_to_scan = "";
    ScannedTokens = {};
}

Scanner::Scanner(string path) {
    ifstream program_file(path, ifstream::in);
    if (!program_file.is_open()) {
        cout << "Error: Cannot open file at: " + path << endl;
        program_to_scan = "";
    }
    program_to_scan = {(std::istreambuf_iterator<char>(program_file)),
                        (std::istreambuf_iterator<char>())};
}

void Scanner::displayTokens() {
    cout << "Format: <lexeme,category>" << endl;
    for (auto tn : Scanner::ScannedTokens) {
        cout << "<" + tn.lexeme + "," + to_str(tn.type) + ">" << endl;
    }
}