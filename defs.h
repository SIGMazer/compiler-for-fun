#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN     512 
#define NSYMTABLES  1024
// Tokens
enum {
    T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_EQUALS,
    T_IDENT,
    T_PRINT, T_INT

};

// ASP node type 
enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT, A_IDENT, A_LVIDENT,
    A_ASSIGN
};

// Symbol table structure
struct symtable{
    char *name;
};

// Abstract Syntax tree structure
struct ASTnode{
    int op;  // Operation 
    struct ASTnode *left;
    struct ASTnode *right;
    union{
        int intvalue; // For interger value 'A_INTLIT'
        int id;       // for A_IDENT
    }v;
};

// Tokens structure
struct token{
    int token;
    int intvalue; // For interger value 'T_INT'
};
