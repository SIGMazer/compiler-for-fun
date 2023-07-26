#include "defs.h"
#include "decl.h" 
#include "data.h"

// Miscellaneous functions 


// check if the word is a token 
void match(int token, char *word){
    if(Token.token == token){
        scan(&Token);
    }
    else {
        fprintf(stderr,"%s expected in the line %d\n",word,Line);
        exit(1);
    }
}


// match a ';'
void semi(){
    match(T_SEMI, ";");
}
