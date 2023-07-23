
int scan(struct token *t);

struct ASTnode *mkastnode(int op, int intvalue, struct ASTnode *left,
        struct ASTnode *right);

struct ASTnode *mkastleaf(int op, int intvalue);

struct ASTnode *mkastunary(int op, int intvalue, struct ASTnode *left);

struct ASTnode *binexpr(int ptp);

int interpretAST(struct ASTnode *node);
