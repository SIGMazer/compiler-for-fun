#include "decl.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define extern_
#include "data.h"
#undef extern_
#include <errno.h>

// List of tokens
char *tokstr[] = {"+","-","*","/","int"};

// Initialise global variables
static void init(){
    Line = 1;
    Putback = '\n';
}

// loop in all token in input file 
// and print details of each token
static void scanfile(){
    struct token T;
    
    while(scan(&T)){
        printf("Token %s",tokstr[T.token]);
        if(T.token == T_INT)
            printf(", value %d", T.intvalue);
        printf("\n");
    }
}
// Print out a usage if using incurrent input 
static void usage(char * prog){
    fprintf(stderr,"Usage: %s infile\n", prog);
    exit(1);
}



int main(int argc, char *argv[])
{
    struct ASTnode *n;
    if (argc != 2)
        usage(argv[0]);

    init();
    
    if((Infile = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"Unable to open %s: %s\n",argv[1], strerror(errno));
        exit(1);
    }
    scan(&Token);
    n = binexpr(0);
    printf("%d", interpretAST(n));
    return EXIT_SUCCESS;
}
