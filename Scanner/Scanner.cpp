#include "Scanner.h"

// constructors
Scanner::Scanner() : file(FileHandler(path)), current(0)
{
    cout << "Specify the path to the program: ";
    cin >> path;
    ScannedTokens = {};
    States = {};
}

Scanner::Scanner(string p) : path(p), file(FileHandler(p)), current(-1)
{
    ScannedTokens = {};
    States = {};
}

int Scanner::popState()
{
    if (States.size() == 0)
        return -5;

    int state = States.at(States.size() - 1);
    States.pop_back();
    return state;
}

bool Scanner::isAccepting(int state)
{
    for (int i = 0; i < acceptingStates.size(); i++)
    {
        if (state == acceptingStates.at(i))
            return true;
    }
    return false;
}

void Scanner::displayTokens()
{
    cout << "Format: <lexeme,category>" << endl;
    for (auto tn : Scanner::ScannedTokens)
    {
        cout << tn.to_str() << endl;
    }
}

int Scanner::getTransitionTableRow(char c)
{
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
        return 0;
    else if ((c >= 'g' && c <= 'z') || (c >= 'G' && c <= 'Z'))
        return 1;
    else if (isdigit(c))
        return 2;
    else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ':' || c == ',')
        return 15;

    switch (c)
    {
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
    case ' ':
    case '\t':
        return 16;
    }
}

token Scanner::handleKeyword(string word)
{
    int i;
    int check = -1;
    for (i = 0; i < keywords.size(); i++)
    {
        if (word == keywords.at(i))
        {
            check = i;
            break;
        }
    }

    // checking for 2 underscores
    if (word.compare(0, 2, "__") == 0 && (i < 16))
        // regular identifiers cannot start with an underscore
        return token(word, INVALID_TOKEN);

    if (check == -1)
        return token(word, IDENTIFIER);

    return token(word, KeyToToken.at(word));
}

token Scanner::handleNumbers(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (word.at(i) == '.' && i < word.length() - 1)
            return token(word, FLOAT_LIT);
    }

    return token(word, INT_LIT);
}

token Scanner::handlePunctuation(string word)
{
    return token(word, PuncToToken.at(word));
}

token Scanner::handleOperator(string word)
{
    return token(word, OpToToken.at(word));
}

token Scanner::handleRelationalOperator(string word)
{
    return token(word, RelToToken.at(word));
}

void Scanner::getCategoryFromState(int state, string word)
{
    switch (state)
    {
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
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        ScannedTokens.push_back(token(word, INVALID_TOKEN));
        break;
    case 10:
        ScannedTokens.push_back(token(word, COL_LIT));
        break;
    case 11:
        ScannedTokens.push_back(handleOperator(word));
        break;
    case 12:
    case 13:
        ScannedTokens.push_back(handleRelationalOperator(word));
        break;
    case 14:
        cout << "Invalid Syntax: Incorrect use of \"!\"" << endl;
        ScannedTokens.push_back(token(word, INVALID_TOKEN));
        break;
    case 15:
        ScannedTokens.push_back(token(word, OP_REL_NOT_EQUAL)); //! CHANGE THE HANDLE RELATIONAL OPERATORS FUNCTION
        break;
    case 16:
        ScannedTokens.push_back(token(word, OP_MUL_DIV));
        break;
    case 17:
    case 18:
    case 22:
    case 26:
        break; // comments are ignored
    case 19:
    case 20:
    case 21:
        cout << "Invalid Syntax: Incomplete comment" << word << endl;
        ScannedTokens.push_back(token(word, INVALID_TOKEN));
        break;
    case 23:
        ScannedTokens.push_back(handlePunctuation(word));
        break;
    case 24:
        ScannedTokens.push_back(token(word, OP_ADD_SUB));
        break;
    case 25:
        ScannedTokens.push_back(token(word, OP_RET_TYPE));
        break;
    }
}

void Scanner::scanInput()
{
    while (this->file.peekChar() != 'EOF')
    {
        // initializing
        int state = 0;
        string word = "";
        // used instead of a stack
        this->States = {};
        States.push_back(-2);

        while (state != -1)
        {
            char c = this->file.nextChar();
            word += c;
            if (isAccepting(state))
            {
                this->States = {};
                States.push_back(-2);
            }
            States.push_back(state);
            int row = getTransitionTableRow(c);
            state = transition_table[row][state];
        }

        while (!isAccepting(state) && state != -2)
        {
            state = popState();
            if (state != -2)
            {
                word.pop_back();
                this->file.rollBack();
            }
        }

        getCategoryFromState(state, word);
    }
}

token Scanner::peekNextToken()
{
    if (current < 0)
        return ScannedTokens.at(0);
    try
    {
        return ScannedTokens.at(current + 1);
    }
    catch (std::out_of_range)
    {
        return token("END", INVALID_TOKEN);
    }
}

token Scanner::getNextToken()
{
    ++current;
    try
    {
        return ScannedTokens.at(current);
    }
    catch (std::out_of_range)
    {
        return generated_token("EOF", INVALID_TOKEN);
    }
}

token Scanner::rollBackToken()
{
    if (current > 0)
        --current;
    return ScannedTokens.at(current);
}