#include "defs.h"
#include "decl.h" 
#include "data.h"


// Parse print statement
void print_statement(void){
    struct ASTnode *t;
    int reg;

    // match a print statement as first token
    match(T_PRINT,"print");

    //parse the following expresstion 
    //and generate the assembly code

    t = binexpr(0);
    reg = genAST(t,-1);
    genprintint(reg);
    genfreeregs();

    // match the semicolon 
    semi();
}

// Parse the declaration of a variable 
static void var_declaration(void){
    // statement: 'int' identifier ';'
    //
    // identifier: T_IDENT

    match(T_INT, "int");
    ident();
    addglob(Text);
    genglobsym(Text);
}

// Parse the initialization of a variable
void var_initialization(void){
    // statement: 'int' identifier '=' expression ';'
    //
    // identifier: T_IDENT

    // Ensure we have int token 
    struct ASTnode *left, *right, *t;
    int iden; 

    // declaration part 
    var_declaration();

    // check it's been define 
    // then make a leaf node for it 
    if((iden = findglob(Text)) == -1)
        fatals("Undeclared variable", Text);
    right = mkastleaf(A_LVIDENT, iden);

    // Ensure we have equal sign 
    // if not check of semicolon and return 
    // i.e. stop at declaration
    if(cmatch(T_EQUALS, "=") == -1){
        semi();
        return;
    }

    // Parse following expression
    left = binexpr(0);

    // make an assignment tree 
    t = mkastnode(A_ASSIGN, 0, left, right);


    // Generate the assembly code for the assignment
    genAST(t, -1);
    genfreeregs();

    semi();

}
void assignment_statement(void){
    // statement: identifier '=' expression 
    //
    // identifier: T_IDENT
    struct ASTnode *left, *right, *t;
    int iden; 

    // Ensure we have an identifier
    ident();

    // check it's been define 
    // then make a leaf node for it 
    if((iden = findglob(Text)) == -1)
        fatals("Undeclared variable", Text);
    right = mkastleaf(A_LVIDENT, iden);

    // Ensure we have equal sign 
    match(T_EQUALS, "=");

    // Parse following expression
    left = binexpr(0);

    // make an assignment tree 
    t = mkastnode(A_ASSIGN, 0, left, right);


    // Generate the assembly code for the assignment
    genAST(t, -1);
    genfreeregs();

    semi();

}

// Parse statements
void statements(){

    for(;;){
        switch (Token.token) {
    case T_PRINT:
      print_statement();
      break;
    case T_INT:
      var_initialization();
      break;
    case T_IDENT:
      assignment_statement();
      break;
    case T_EOF:
      return;
    default:
      fatald("Syntax error, token", Token.token);
    }
    }
}
