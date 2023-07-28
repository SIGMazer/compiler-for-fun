#include "defs.h"
#include "data.h"
#include "decl.h"



// OPerator precedence for each token 
//                    EOF  +  -   *   /  INT
static int OpPrec[] = {0, 10, 10, 20, 20, 0};

// this function check that we have binary operator 
// and manage syntax error 
static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    exit(1);
  }
  return (prec);
}

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
    int id;
    // make a leaf node for INT token
    // otherwise a syntax error for other token type 
    switch(Token.token){
        case T_INTLIT:
            node = mkastleaf(A_INTLIT, Token.intvalue);
            break;
        case T_IDENT:
            // check that the identifier exist
            if((id = findglob(Text)) == -1)
                fatals("Unknown variable", Text);
            node = mkastleaf(A_IDENT, id);
            break;
        default:
            fatald("syntax error, token %d\n",Token.token);
    }
    scan(&Token);
    return node;
}

struct ASTnode *binexpr(int ptp){
    struct ASTnode *node, *left, *right;
    int nodetype;
    
    // Get the interger in left and fetch next token 
    left = primary();    

    nodetype = Token.token;
    // return just left if no left node
    if(nodetype == T_SEMI)
        return left;
    
    // While the token precedence is more than previous token precedence
    while (op_precedence(nodetype) > ptp) {

        // fetch next token  
        scan(&Token);

        // build sub tree
        right = binexpr(OpPrec[nodetype]);

        // link node together 
        left = mkastnode(arithop(nodetype),0, left, right);


        //update tokentype
        nodetype = Token.token;
        if(nodetype == T_SEMI)
            return left;
    }
    return left;
}
