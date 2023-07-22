#include "defs.h"
#include "data.h"
#include "decl.h"



// Convert a token into an AST operation.
int arithop(int tok) {
  switch (tok) {
    case T_PLUS:
      return (A_ADD);
    case T_MINUS:
      return (A_SUBTRACT);
    case T_STAR:
      return (A_MULTIPLY);
    case T_SLASH:
      return (A_DIVIDE);
    default:
      fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
      exit(1);
  }
}


// Parse primary factor and return it as AST node
static struct ASTnode *primary(){
    struct ASTnode *node;

    // make a leaf node for INT token
    // otherwise a syntax error for other token type 
    switch(Token.token){
        case T_INT:
            node = mkastleaf(A_INT, Token.intvalue);
            scan(&Token);
            return node;
        default:
            fprintf(stderr,"syntax error on line %d\n",Line);
            exit(1);
    }
}

struct ASTnode *binexpr(){
    struct ASTnode *node, *left, *right;
    int nodetype;
    
    // Get the interger in left and fetch next token 
    left = primary();

    // return just left if no left node
    if(Token.token == T_EOF){
        return left;
    }

    // convert token to node type 
    nodetype =arithop(Token.token);
    
    // get the next token 
    scan(&Token);

    // get the right branch recursivly 
    right = binexpr();

    // Create a tree with both left and right 
    node = mkastnode(nodetype,0,left,right);
    return node;
}
