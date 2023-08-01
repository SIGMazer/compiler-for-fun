#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// List of tokens
char *tokstr[] = {"+","-","*","/","int"};

// Initialise global variables
static void init(){
    Line = 1;
    Putback = '\n';
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
    
    // open input file 
    if((Infile = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"Unable to open %s: %s\n",argv[1], strerror(errno));
        exit(1);
    }
    // create output file 
    if((Outfile = fopen("out.s","w")) == NULL){
        fprintf(stderr,"Unable to create out.s: %s\n", strerror(errno));
        exit(1);
    }

    scan(&Token);
    genpreamble();
    n = compound_statement(); // parse compound statement in the input 
    genAST(n, NOREG, 0); // generate the assembly 
    genpostamble();
    fclose(Outfile);
    return EXIT_SUCCESS;
}
