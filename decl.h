
int scan(struct token *t);

struct ASTnode *mkastnode(int op, int intvalue, struct ASTnode *left,
        struct ASTnode *right);

struct ASTnode *mkastleaf(int op, int intvalue);

struct ASTnode *mkastunary(int op, int intvalue, struct ASTnode *left);

struct ASTnode *binexpr(int ptp);

int interpretAST(struct ASTnode *node);

void generatecode(struct ASTnode *n);

void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
