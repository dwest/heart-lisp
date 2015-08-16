#include <stdio.h>
#include "./parse-lisp.h"

int apply_parser(FILE *stream, Parser *p) {
    return p->fn(stream, p->argc, p->args);
}

int parse_char(FILE *stream, int argc, ParserArg **args) {
    if(argc > 0) {
        char c = getc(stream);

        if(   args[0]->all.type == PARG_LITERAL
           && args[0]->literal.lit == c
        ) {
            printf("Accepted: '%c'\n", c);
            return 1;
        }
    }

    return 0;
}

int parse_repeatedly(FILE *stream, int argc, ParserArg **args) {
    int result = 1,
        argpos = 0;

    ParserArg *curr;

    if(argc == 0) {
        return result;
    }

    while(result) {
        curr = args[argpos];
        if( curr->all.type != PARG_PARSER ) {
            puts("parse_repeatedly only accepts other parsers\n");

            return 0;
        }
        result = result && apply_parser(stream, curr->parser.parser);
        argpos = (argpos+1) % argc;
    }

    return result;
}
        
