#include "defs.h"
#include "data.h"
#include <stdio.h>

// Read next character from the intput file 
static int next(void) {
    int c; 

    // Use the character putback if there it one 
    if(Putback){
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile); // read from file 
    if(c == '\n'){
        Line++; // Increment line count 
    }
    return c;
}

// Put back unwanted character
static void putback(int c){
    Putback = c;
}

// Skip the input that we don't need to use
// i.e. whitespace, newline, taps. retrun first chanracter we need to deal with
static int skip(void){
    int c;
    c = next();
    while(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f')
        c= next();


    return c;
}

// Reterun the position of character in string 
// and return -1 if character not found 
static int chrpos(char *s, int c){
    char *p;
    
    p = strchr(s,c);
    
    return p ? p - s : -1;
}

// Scan and return an interger literal 
static int scanint(int c){
    int i , val = 0;
    while((i = chrpos("0123456789", c)) >= 0){
        val = val * 10 + i ;
        c= next();
    }
    return val;
}

// Scan funciton return next token found in input 
// return value 1 if token valid, 0 if no token left 
int scan(struct token *t){
    int c; 
    

    // Skip unwant characters
    c= skip();


    switch (c) {
        case EOF: 
            return 0 ;
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        default:
            // If it's a digit
            if(isdigit(c)){
                t->intvalue = scanint(c);
                t->token = T_INT;
                break;
            }
            printf("Unrecognised character %c on line %d \n", c, Line);
            exit(1);
    }
    return 1;
}



