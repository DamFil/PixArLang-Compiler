#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include "TokenStruct.h"
#include "Scanner/FileStreamHandler.h"

using namespace std;

const vector<string> keywords =
    {"if", "else", "for", "while", "bool", "int", "float", "colour", "true", "false", "and", "or", "not",
     "let", "return", "fun", "__print", "__delay", "__pixelr", "__pixel", "__width", "__height", "__randi", "__read"};

const vector<string> punctuation =
{"(", ")", "{", "}", ";", ":", ","};

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
        /* _ */             {  1,   1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* . */             { -1,  -1,  3, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1},
        /* \n,space,\t */   { 26,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 18, -1, 20, -1, 19, -1, -1, -1, -1, -1},
        /* (,),{,},;,:,, */ { 23,  -1, -1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, 17, -1, 19, -1, 19, -1, -1, -1, -1, -1}
};

const vector<int> acceptingStates {1, 2, 10, 11, 12, 13, 15, 16, 17, 18, 22, 23, 24, 25, 26};

const map<string,TokenName> KeyToToken
{
        {"if",KEY_IF},
        {"else",KEY_ELSE},
        {"for",KEY_FOR},
        {"while",KEY_WHILE},
        {"bool",KEY_T_BOOL},
        {"int",KEY_T_INT},
        {"float",KEY_T_FLOAT},
        {"colour",KEY_T_COLOUR},
        {"true",KEY_BOOL_LIT_T},
        {"false",KEY_BOOL_LIT_F},
        {"and",OP_MUL_AND},
        {"or",OP_ADD_OR},
        {"not",OP_UNARY_NOT},
        {"let",KEY_VAR_DEC},
        {"return",KEY_RETURN},
        {"fun",KEY_FUN_DEC},
        {"__print",KEY_PRINT},
        {"__delay",KEY_DELAY},
        {"__pixelr",KEY_PIX_R},
        {"__pixel",KEY_PIX},
        {"__width",KEY_PAD_W},
        {"__height",KEY_PAD_H},
        {"__randi",KEY_PAD_RANDI},
        {"__read",KEY_PAD_READ}
};

const map<string,TokenName> PuncToToken
{
        {"(",PUNCT_OPEN_PAR},
        {")",PUNCT_CLOSED_PAR},
        {"{",PUNCT_OPEN_CURL},
        {"}",PUNCT_CLOSED_CURL},
        {";",PUNCT_SEMICOLON},
        {":",PUNCT_COLON},
        {",",PUNCT_COMMA}
};

const map<string,TokenName> OpToToken
{
        {"+",OP_ADD_ADD},
        {"-",OP_ADD_SUB},
        {"*",OP_MUL_MUL},
        {"/",OP_MUL_DIV}        
};

const map<string,TokenName> RelToToken
{
        {"=",OP_ASSIGNMENT},
        {"<",OP_REL_LESS},
        {">",OP_REL_GREAT},
        {"==",OP_REL_EQUAL},
        {"<=",OP_REL_LESS_EQ},
        {">=",OP_REL_GREAT_EQ},
        {"!=",OP_REL_NOT_EQUAL}
};

class Scanner {
private:
        string path;
        vector<token> ScannedTokens;
        vector<int> States;
        FileHandler file;
        int current;

        int popState();
        bool isAccepting(int state);
        int getTransitionTableRow(char letter);

        token handleKeyword(string word);
        token handleNumbers(string word);
        token handlePunctuation(string word);
        token handleOperator(string word);
        token handleRelationalOperator(string word);
        void getCategoryFromState(int state, string word);
public:
        //constructors
        Scanner();
        Scanner(string p);

        void displayTokens();        
        void scanInput();
        token peek();
        token getNextToken();
};