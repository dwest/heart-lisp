#if !defined(PARSE_LISP)
#define PARSE_LISP

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

typedef int (*parsefn)(FILE *stream, int argc, ParserArg **args);

typedef struct Parser {
    parsefn fn;
    int argc;
    ParserArg **args;
} Parser;

int apply_parser(FILE *stream, Parser *p);

int parse_char(FILE *stream, int argc, ParserArg **args);

int parse_repeatedly(FILE *stream, int argc, ParserArg **args);

#endif
