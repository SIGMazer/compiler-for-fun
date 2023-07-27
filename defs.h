#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN 512 
// Tokens
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_PRINT
};

// ASP node type 
enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

// Abstract Syntax tree structure
struct ASTnode{
    int op;  // Operation 
    int intvalue; // For interger value 'A_INT'
    struct ASTnode *left;
    struct ASTnode *right;
};

// Tokens structure
struct token{
    int token;
    int intvalue; // For interger value 'T_INT'
};
