#ifdef __cplusplus
extern "C" {
#endif

	enum TypeCode {
		TYPE_INT, TYPE_STRING, TYPE_VOID
	};

	typedef struct {
		enum TypeCode code;
		char* name;
	} ASTType;

	enum ExprCode {
		EXPR_INT, EXPR_VAR, EXPR_ADDI, EXPR_SUBI
	};

	typedef struct ASTExprS {
		enum ExprCode code;
		union uExpr {
			int value;
			char* var;
			struct UOp {
				struct ASTExprS* expr;
			};
			struct BiOp {
				struct ASTExprS* left;
				struct ASTExprS* right;
			};
		} u;
	} ASTExpr;

	enum InstrCode {
		INSTR_AFFECT, INSTR_DECLARE, INSTR_CALL
	};

	typedef struct ASTInstr {
		enum InstrCode code;
		ASTType* declare;
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

	void error(Token* token, char* messageError, ...);

#ifdef __cplusplus
}
#endif

