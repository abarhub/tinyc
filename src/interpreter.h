#ifdef __cplusplus
extern "C" {
#endif

	enum RunExprCode {
		RUN_EXPR_INT, RUN_EXPR_STR
	};

	typedef struct RunValue {
		enum RunExprCode code;
		union uRunExpr {
			int value;
			char* var;
			char* str;
		} u;
	} RunValue;


	typedef struct SymbolTable {
		char* name;
		ASTType* type;
		RunValue value;
		struct SymbolTable* next;
	} SymbolTable;


	void run(ASTFunction* ast);

#ifdef __cplusplus
}
#endif

