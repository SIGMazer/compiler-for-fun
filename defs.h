#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Tokens
enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INT, T_EOF
};

// ASP node type 
enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INT
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
