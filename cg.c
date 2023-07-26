#include "defs.h"
#include "data.h"
#include "decl.h"


// code generator for x86-64 intel syntax


// List of registers and freed register 
static int freereg[4];
static char *reglist[4] = {"r8", "r9", "r10", "r11"};


// Mark all registers as free 
void freeall_registers(){
    freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

// Allocat free register 
// and retrun register number 
// exit of no available register 
static int alloc_register(){
   for(int i =0 ; i < 4 ;i++){
        if(freereg[i]){
            freereg[i] = 0;
            return i;
        }
   } 
   // no available register
   fprintf(stderr,"Out of registers\n");
   exit(1);
}

// Mark a register as free 
// check if the register is already freed
static void free_register(int r){
    if(freereg[r] != 0){
        fprintf(stderr,"Error: trying to free register %d\n",r);
        exit(1);
    }
    freereg[r] = 1;
}
// Print out the assembly preamble
void cgpreamble()
{
  freeall_registers();
  fputs(
    "\t.intel_syntax noprefix\n"
	"\t.global\tmain\n"
	"\t.extern\tprintf\n"
	"\t.section\t.text\n"
	"LC0:\t.string\t\"%d\"\n"
	"printint:\n"
	"\tpush\trbp\n"
	"\tmov\trbp, rsp\n"
	"\tsub\trsp, 16\n"
	"\tmov\t[rbp-4], edi\n"
	"\tmov\teax, [rbp-4]\n"
	"\tmov\tesi, eax\n"
	"\tlea	rdi, [rip+LC0]\n"
	"\tmov	eax, 0\n"
	"\tcall	printf\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"main:\n"
	"\tpush\trbp\n"
	"\tmov	rbp, rsp\n",
  Outfile);
}

// Print out the assembly postamble
void cgpostamble()
{
  fputs(
	"\tmov	eax, 0\n"
	"\tpop	rbp\n"
	"\tret\n",
  Outfile);
}

// Load and interger value into a register
// and return register number
int cgload(int value){
    
    // Allocat new register
    int r = alloc_register();

    // print out the code ot initiate it 
    fprintf(Outfile, "\tmov\t%s, %d\n", reglist[r], value);
    return r;
}

// Add two register together and 
// return the number of the register with the result 
int cgadd(int r1, int r2){
    fprintf(Outfile,"\tadd\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r2);
    return r1;
}

// Subtract two register together and 
// return the number of the register with the result 
int cgsub(int r1, int r2){
    fprintf(Outfile,"\tsub\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r2);
    return r1;
}

// Multibly two register together and 
// return the number of the register with the result 
int cgmul(int r1, int r2){
    fprintf(Outfile,"\timul\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r2);
    return r1;
}

// Divide the first register by the second
// and return the number of the register with the result 
int cgdiv(int r1, int r2){
    fprintf(Outfile, "\tmov\trax, %s\n",reglist[r1]);
    fprintf(Outfile, "\tcqo\n"); // Load dividend rax with the number 
    fprintf(Outfile, "\tidiv\t%s\n",reglist[r2]);
    fprintf(Outfile, "\tmov\t%s, rax\n",reglist[r1]); // stor the result in r1
    free_register(r2);
    return r1;
}


// Call printint() 
void cgprintint(int r){
    fprintf(Outfile, "\tmov\rrdi, %s\n", reglist[r]);
    fprintf(Outfile,"\tcall\tprintint\n");
    free_register(r);
}
