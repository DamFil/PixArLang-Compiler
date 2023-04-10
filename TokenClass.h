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
    COL_LIT            //* (([A...F]|[a...f])([0...9]))^6
};