#include "defs.h"
#include "data.h"
#include "decl.h"

// Create new AST node 
struct ASTnode *mkastnode(int op, int intvalue, struct ASTnode *left,
        struct ASTnode *right){
    struct ASTnode *node = (struct ASTnode *)malloc(sizeof(struct ASTnode));

    if( node == NULL){
        fprintf(stderr,"Unable to malloc in mkastnode()\n");
        exit(1);
    }

    // Return a node with stored data

    node->intvalue =intvalue;
    node->op = op;
    node->left =left;
    node->right = right;
    return node;
}

// Create leaf AST node
struct ASTnode *mkastleaf(int op, int intvalue){
    return mkastnode(op, intvalue, NULL, NULL);
}

// Create unary AST node 
struct ASTnode *mkastunary(int op, int intvalue, struct ASTnode *left){
    return mkastnode(op, intvalue, left, NULL);
}

