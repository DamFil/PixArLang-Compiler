#pragma once

#include <string>
using namespace std;

enum TokenName
{
    // syntactic categories
    //? keywords
    KEY_IF,            //* if
    KEY_ELSE,          //* else
    KEY_FOR,           //* for
    KEY_WHILE,         //* while
    KEY_RETURN,        //* return
    KEY_T_BOOL,        //* bool
    KEY_BOOL_LIT_T,    //* true
    KEY_BOOL_LET_F,    //* false
    KEY_T_INT,         //* int
    KEY_T_FLOAT,       //* float
    KEY_T_COLOUR,      //* colour
    KEY_VAR_DEC,       //* let
    KEY_FUN_DEC,       //* fun
    KEY_PRINT,         //* __print
    KEY_DELAY,         //* __delay
    KEY_PIX_R,         //* __pixelr
    KEY_PIX,           //* __pixel
    KEY_PAD_W,         //*__weight
    KEY_PAD_H,         //*__height
    KEY_PAD_RANDI,     //*__randi
    KEY_PAD_READ,      //*__read
                       //? operators
    OP_MUL,            //* * , / , and
    OP_ADD,            //* + , - , or
    OP_REL,            //* < , > , == , != , <=, >=
    OP_MUL_MUL,        //* *
    OP_MUL_DIV,        //* /
    OP_MUL_AND,        //* and
    OP_ADD_ADD,        //* +
    OP_ADD_SUB,        //* -
    OP_ADD_OR,         //* or
    OP_REL_LESS,       //* <
    OP_REL_GREAT,      //* >
    OP_REL_EQUAL,      //* ==
    OP_REL_NOT_EQUAL,  //* !=
    OP_REL_LESS_EQ,    //* <=
    OP_REL_GREAT_EQ,   //* >=
    OP_UNARY_NOT,      //* not
    OP_ASSIGNMENT,     //* =
    OP_RET_TYPE,       //* ->
                       //? punctuation
    PUNCT_OPEN_PAR,    //* (
    PUNCT_CLOSED_PAR,  //* )
    PUNCT_OPEN_CURL,   //* {
    PUNCT_CLOSED_CURL, //* }
    PUNCT_SEMICOLON,   //* ;
    PUNCT_COLON,       //* :
    PUNCT_COMMA,       //* ,
    PUNCT_POINT,       //* .
    PUNCT_HASHTAG,     //* #
                       //? GROUP LEXEMES
    IDENTIFIER,        //* ([A...Z]|[a...z])(_|[A...Z]|[a...z]|[0...9])*
    INT_LIT,           //* [0...9]([0...9])*
    FLOAT_LIT,         //* [0...9]([0...9])*.[0...9]([0...9])*
    COL_LIT,           //* (([A...F]|[a...f])([0...9]))^6
    INVALID_TOKEN      //* this is an invalid token
};

vector<string> StringTokenNames =
{
        "KEY_IF",
        "KEY_ELSE",
        "KEY_FOR",
        "KEY_WHILE",
        "KEY_RETURN",
        "KEY_T_BOOL",
        "KEY_BOOL_LIT_T",
        "KEY_BOOL_LET_F",
        "KEY_T_INT",
        "KEY_T_FLOAT",
        "KEY_T_COLOUR",
        "KEY_VAR_DEC",
        "KEY_FUN_DEC",
        "KEY_PRINT",
        "KEY_DELAY",
        "KEY_PIX_R",
        "KEY_PIX",
        "KEY_PAD_W",
        "KEY_PAD_H",
        "KEY_PAD_RANDI",
        "KEY_PAD_READ",
        "OP_MUL",
        "OP_ADD",
        "OP_REL",
        "OP_MUL_MUL",
        "OP_MUL_DIV",
        "OP_MUL_AND",
        "OP_ADD_ADD",
        "OP_ADD_SUB",
        "OP_ADD_OR",
        "OP_REL_LESS",
        "OP_REL_GREAT",
        "OP_REL_EQUAL",
        "OP_REL_NOT_EQUAL",
        "OP_REL_LESS_EQ",
        "OP_REL_GREAT_EQ",
        "OP_UNARY_NOT",
        "OP_ASSIGNMENT",
        "OP_RET_TYPE",
        "PUNCT_OPEN_PAR",
        "PUNCT_CLOSED_PAR",
        "PUNCT_OPEN_CURL",
        "PUNCT_CLOSED_CURL",
        "PUNCT_SEMICOLON",
        "PUNCT_COLON",
        "PUNCT_COMMA",
        "PUNCT_POINT",
        "PUNCT_HASHTAG",
        "IDENTIFIER",
        "INT_LIT",
        "FLOAT_LIT",
        "COL_LIT",
        "INVALID_TOKEN"
};

string to_str(TokenName category)
{
    return StringTokenNames.at(category);
}

typedef struct generated_token
{
    string lexeme;
    TokenName type;

    generated_token() : lexeme(""), type(INVALID_TOKEN) {}                  // default constructor
    generated_token(string word, TokenName t) : lexeme(word), type(t) {} // parametrized constructor
} token;