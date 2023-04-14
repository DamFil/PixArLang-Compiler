#include "Scanner.h"

//constructors
Scanner::Scanner() {
    ScannedTokens = {};
    file = FileHandler();
}

Scanner::Scanner(string path) {
    ScannedTokens = {};
    file = FileHandler(path);
}

void Scanner::displayTokens() {
    cout << "Format: <lexeme,category>" << endl;
    for (auto tn : Scanner::ScannedTokens) {
        cout << "<" + tn.lexeme + "," + to_str(tn.type) + ">" << endl;
    }
}

int Scanner::getTransitionTableRow(char c) {
    if ('a' <= c <= 'f')
        return 0;
    else if ('g' <= c <= 'z')
        return 1;
    else if (isdigit(c))
        return 2;
    else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ':' || c == ',')
        return 16;
    
    switch(c) {
        case '+':
            return 3;
        case '-':
            return 4;
        case '<':
            return 5;
        case '>':
            return 6;
        case '#':
            return 7;
        case '/':
            return 8;
        case '!':
            return 9;
        case '=':
            return 10;
        case '*':
            return 11;
        case '_':
            return 12;
        case '.':
            return 13;
        case '\n':
            return 14;
    }
}

token Scanner::handleKeyword(string word) {
    int i;
    int check = -1;
    for (i = 0; i < keywords.size(); i++) {
        if (word == keywords.at(i)) {
            check = i;
            break;
        }
    }

    //checking for 2 underscores
    if (word.compare(0, 2, "__") == 0 && (i < 16))
        //regular identifiers cannot start with an underscore
        return token(word, INVALID_TOKEN);
    
    if (check == -1)
        return token(word, IDENTIFIER);
    
    return token(word, KeyToToken[word]);
}

token Scanner::handleNumbers(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word.at(i) == '.' && i < word.length() - 1)
            return token(word,FLOAT_LIT);
    }

    return token(word,INT_LIT);
}

token Scanner::handlePunctuation(string word) {
    return token(word,PuncToToken[word]);
}

token Scanner::handleOperator(string word) {
    return token(word, OpToToken[word]);
}

token Scanner::handleRelationalOperator(string word) {
    return token(word, RelToToken[word]);
}

void Scanner::getCategoryFromState(int state, string word) {
    switch(state) {
        case 0:
            ScannedTokens.push_back(token()); 
            break;
        case 1:
            ScannedTokens.push_back(handleKeyword(word));
            break;
        case 2:
            ScannedTokens.push_back(handleNumbers(word));
            break;
        case 3:
            ScannedTokens.push_back(token(word, INVALID_TOKEN));
            break;
        case 4: case 5: case 6: case 7: case 8: case 9:
            ScannedTokens.push_back(token(word,INVALID_TOKEN));
            break;
        case 10:
            ScannedTokens.push_back(token(word,COL_LIT));
            break;
        case 11:
            ScannedTokens.push_back(handleOperator(word));
            break;
        case 12: case 13:
            ScannedTokens.push_back(handleRelationalOperator(word));
            break;
        case 14:
            cout << "Invalid Syntax: Incorrect use of \"!\"" << endl;
            ScannedTokens.push_back(token(word,INVALID_TOKEN));
            break;
        case 15:
            ScannedTokens.push_back(token(word,OP_REL_NOT_EQUAL)); //! CHANGE THE HANDLE RELATIONAL OPERATORS FUNCTION
            break;
        case 16:
            ScannedTokens.push_back(token(word,OP_MUL_DIV));
            break;
        case 17: case 18: case 22: case 26:
            break; //comments are ignored
        case 19: case 20: case 21:
            cout << "Invalid Syntax: Incomplete comment" << word << endl;
            ScannedTokens.push_back(token(word,INVALID_TOKEN));
            break;
        case 23:
            ScannedTokens.push_back(handlePunctuation(word));
            break;
        case 24:
            ScannedTokens.push_back(token(word,OP_ADD_SUB));
            break;
        case 25:
            ScannedTokens.push_back(token(word,OP_RET_TYPE));
            break;
    }
}