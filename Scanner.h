#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TokenStruct.h"

using namespace std;

enum types {keyword,punctuation};

const vector<string> keywords = 
{"if","else","for","while","bool","int","float","colour","true","and","or","not"
"false","let","return","fun","__print","__delay","__pixelr","__pixel","__width","__height","__randi","__read"};

const vector<string> punctuation =
{"(", ")", "{", "}", ";", ":", ",", "."};

const vector<string> operators = 
{"+","-","*","/"};

const vector<string> relational_operators =
{"=","<",">","==","<=",">=","!="};

// -1 is an error state
const vector<vector<int>> transition_table =
{//                            0    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26
        /* a-f */           {  1,   1, -1, -1,  5,  6,  7,  8,  9, 10,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* g-z */           {  1,   1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* 0-9 */           {  2,   1,  2,  2,  5,  6,  7,  8,  9, 10,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* + */             { 11,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* - */             { 24,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* < */             { 12,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* > */             { 12,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, 25, -1, -1},
        /* # */             {  4,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1}, 
        /* / */             { 16,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, 17, 17, -1, 19, -1, 22, -1, -1, -1, -1, -1},
        /* ! */             { 14,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* = */             { 12,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, 13, -1, 15, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* * */             { 11,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, 19, 17, -1, 19, 21, 19, -1, -1, -1, -1, -1},
        /* _ */             { -1,   1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* . */             { -1,  -1,  3, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* \n */            { 26,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 18, -1, 20, -1, 19, -1, -1, -1, -1, -1},
        /* (,),{,},;,:,, */ { 23,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1}
};

class Scanner {
private:
        vector<token> ScannedTokens;
        string program_to_scan;
public:
        Scanner();
        Scanner(string path);
        void displayTokens();
        int getTransitionTableRow(char letter);
        bool isKeyword(string word);
        bool isPunctuation(string word);
        bool isOperator(string word);
        bool isRelationalOperator(string word);
        token getCategoryFromState(string word, int state);
        void scanInput(string filestream);
        token getNextToken();
};