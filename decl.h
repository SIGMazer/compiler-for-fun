
int scan(struct token *t);

// ast.c
struct ASTnode *mkastnode(int op, int intvalue, struct ASTnode *left,
        struct ASTnode *right);

struct ASTnode *mkastleaf(int op, int intvalue);

struct ASTnode *mkastunary(int op, int intvalue, struct ASTnode *left);

// expr.c
struct ASTnode *binexpr(int ptp);

int interpretAST(struct ASTnode *node);


// gen.c
int genAST(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);

//cg.c
void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);

// misc.c
void match(int t, char *what);
void semi(void);

// stmt.c
void statements(void);

