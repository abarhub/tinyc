#ifndef PARSER_H
#define PARSER_H

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
		EXPR_INT, EXPR_VAR, EXPR_ADDI, EXPR_SUBI, EXPR_STRING
	};

	typedef struct ASTExprS {
		enum ExprCode code;
		union uExpr {
			int value;
			char* var;
			char* str;
			struct UOp {
				struct ASTExprS* expr;
			} uop;
			struct BiOp {
				struct ASTExprS* left;
				struct ASTExprS* right;
			} biop;
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

	void error(Token* token,const char* messageError, ...);

#ifdef __cplusplus
}
#endif


#endif