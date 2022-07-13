#ifdef __cplusplus
extern "C" {
#endif

	typedef struct {
		char* buf;
		unsigned long size;
	} FileStr;


	typedef struct {
		char* name;
	} ASTType;

	typedef struct {
		int value;
	} ASTExpr;

	typedef struct ASTInstr  {
		char* var;
		ASTExpr* expr;
		struct ASTInstr* next;
	} ASTInstr;

	typedef struct ASTFunction {
		char* name;
		ASTType* returnType;
		ASTInstr* instr;
		struct ASTFunction* next;
	} ASTFunction;


	ASTFunction* parse(Token* tokenList);

	void printAst(ASTFunction* funct);


#ifdef __cplusplus
}
#endif

