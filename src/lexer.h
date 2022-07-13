#ifdef __cplusplus
extern "C" {
#endif

	enum TokenCode { IDENTIFIER, SEPARATOR, NUMBER };
	enum TokenSubCode {
		// SEPARATOR
		SC_OPEN_PARENTHESIS, SC_CLOSE_PARENTHESIS, SC_OPEN_EMBRACE, SC_CLOSE_EMBRACE, SC_EQUALS, SC_NOT_EQUALS, SC_SEMICOLON, SC_ASSIGNEMENT


	};

	typedef struct TokenStruct {
		enum TokenCode code;
		enum TokenSubCode subCode;
		char* text;
		int pos;
		int line;
		int column;
		struct TokenStruct* next;
	} Token;

	Token* newToken(enum TokenCode code, char* text, int pos, int line, int column, Token* next);

	Token* lexer(char fichier[]);

	typedef struct {
		char* buf;
		unsigned long size;
	} FileStr;


#ifdef __cplusplus
}
#endif
