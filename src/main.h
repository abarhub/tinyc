#ifdef __cplusplus
extern "C" {
#endif

	enum TokenCode { IDENTIFIER, SEPARATOR, NUMBER };

	typedef struct TokenStruct {
		enum TokenCode code;
		char* text;
		int pos;
		int line;
		int column;
		struct TokenStruct* next;
	} Token;

	Token* newToken(enum TokenCode code, char* text, int pos, int line, int column, Token* next);

	Token* parse(char fichier[]);

	void start(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif



