#if !defined(PARSE_LISP)
#define PARSE_LISP

typedef enum TokenType {
    PTOK_INTEGER,
    PTOK_STRING,
    PTOK_LIST,
    PTOK_FUNCTION
} TokenType;

typedef union Token {
    struct {
        int type;
        int row;
        int col;
    } all;
    struct {
        int type;
        int row;
        int col;
        int value;
    } integer;
    struct {
        int type;
        int row;
        int col;
        char *value;
    } string;
    struct {
        int type;
        int row;
        int col;
        union Token **value;
        int length;
    } list;
    struct {
        int type;
        int row;
        int col;
        void *value;
        int arity;
    } function;
} Token;

typedef enum ParserArgType {
    PARG_CHAR,
    PARG_LITERAL,
    PARG_STRING,
    PARG_PARSER
} ParserArgType;

typedef union ParserArg {
    struct {
        int type;
    } all;
    struct {
        int type;
        char lit;
    } literal;
    struct {
        int type;
        int len;
        char *str;
    } string;
    struct {
        int type;
        struct Parser *parser;
    } parser;
} ParserArg;

typedef int (*parsefn)(FILE *stream, int argc, ParserArg **args, Token *tok);

typedef struct Parser {
    parsefn fn;
    int argc;
    ParserArg **args;
} Parser;

void print_tree(Token *tok);

int apply_parser(FILE *stream, Parser *p, Token *tok);

int parse_char(FILE *stream, int argc, ParserArg **args, Token *tok);

/**
 * Similar to the star operator in a regex.  This parser accepts zero
 * or more matches for the provided list of parsers.  It cycles
 * through all provides parsers until one of them returns false,
 * starting over from the first if necessary.
 *
 * Args:
 *     FILE      *stream - the stream to read from
 *     int       argc    - count of the arglist
 *     ParserArg **args  - argument list
 *     Token     *tok    - token list to append to
 */
int parse_many(FILE *stream, int argc, ParserArg **args, Token *tok);

#endif
