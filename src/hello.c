#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./parse-lisp.h"

size_t MAX_INPUT = 1024;

int main(int argc, char **argv) {
    if(! (argc >= 2) ) {
        puts("A filename is expected.\n");
        return 10;
    }

    Parser *p = malloc(sizeof(Parser));
    if( p == NULL ) {
        puts("Out of memory?\n");
        return 20;
    }
    p->fn = &parse_char;
    p->argc = 1;
    p->args = (ParserArg **)malloc(sizeof(ParserArg*));
    if( p->args == NULL ) {
        puts("Out of memory?\n");
        return 20;
    }
    p->args[0] = malloc(sizeof(ParserArg));
    p->args[0]->literal.type = PARG_LITERAL;
    p->args[0]->literal.lit  = 'a';

    Parser *q = malloc(sizeof(Parser));
    if( q == NULL ) {
        puts("Out of memory?\n");
        return 20;
    }
    q->fn = &parse_char;
    q->argc = 1;
    q->args = (ParserArg **)malloc(sizeof(ParserArg*));
    if( q->args == NULL ) {
        puts("Out of memory?\n");
        return 20;
    }
    q->args[0] = malloc(sizeof(ParserArg));
    q->args[0]->literal.type = PARG_LITERAL;
    q->args[0]->literal.lit  = 'b';
    Parser *many_p = malloc(sizeof(Parser));
    if( many_p == NULL ) {
        puts("Out of memory?\n");
        return 20;
    }

    many_p->fn = &parse_repeatedly;
    many_p->argc = 2;
    many_p->args = (ParserArg**)malloc(sizeof(ParserArg*)*2);
    if( many_p->args == NULL ) {
        puts("Out of memory?\n");
        return 20;
    }

    many_p->args[0] = malloc(sizeof(ParserArg));
    many_p->args[0]->parser.type = PARG_PARSER;
    many_p->args[0]->parser.parser = p;
    many_p->args[1] = malloc(sizeof(ParserArg));
    many_p->args[1]->parser.type = PARG_PARSER;
    many_p->args[1]->parser.parser = q;

    FILE *stream = fopen(argv[1], "r");

    printf("%d\n", apply_parser(stream, many_p));
    
    return 0;
}

