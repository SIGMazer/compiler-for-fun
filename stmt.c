#include "defs.h"
#include "decl.h" 
#include "data.h"

// parse statements
void statements(){

    struct ASTnode *t;
    int reg;

    while(1){
        // match a print statement as first token
        match(T_PRINT,"print");

        //parse the following expretion 
        //and generate the assembly code

        t = binexpr(0);
        reg = genAST(t);
        genprintint(reg);
        genfreeregs();

        // match the semicolon 
        semi();
        
        // stop if we are at EOF
        if(Token.token == T_EOF)
            return;
    }
}
