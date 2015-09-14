#include <stdio.h>
#include <stdlib.h>
#include "./parse-lisp.h"

int apply_parser(FILE *stream, Parser *p, Token *tok) {
    return p->fn(stream, p->argc, p->args, tok);
}

int parse_char(FILE *stream, int argc, ParserArg **args, Token *tok) {
    if(argc > 0) {
        char c = getc(stream);

        if(   args[0]->all.type == PARG_LITERAL
              && ( args[0]->literal.lit == c || c == EOF)
        ) {
            tok->all.type = PTOK_STRING;
            tok->string.value = &c;
            return 1;
        }
    }

    return 0;
}

int parse_many(FILE *stream, int argc, ParserArg **args, Token *tok) {
    int result = 1,
        argpos = 0;

    ParserArg *curr;

    if(argc == 0) {
        return result;
    }

    tok->all.type = PTOK_LIST;
    tok->list.value = malloc(256 * sizeof(Token*));
    tok->list.length = 0;

    while(result) {
        curr = args[argpos];
        if( curr->all.type != PARG_PARSER ) {
            puts("parse_repeatedly only accepts other parsers\n");

            return 0;
        }
        Token *next = malloc(sizeof(Token));
        result = result && apply_parser(stream, curr->parser.parser, next);
        if( result ) {
            tok->list.value[tok->list.length++] = next;
        }
        argpos = (argpos+1) % argc;
    }

    return result;
}

void print_tree(Token *tok) {
    printf("Tok(type=%d,row=%d,col=%d)\n", tok->all.type, 0, 0);

    if(tok->all.type == PTOK_LIST) {
        for(int i = 0; i < tok->list.length; i++) {
            printf("Tok(type=%d,row=%d,col=%d)\n", tok->list.value[i]->all.type, 0, 0);
        }
    }
    else {
        puts("todo\n");
    }
}

/* int parse_some(FILE *stream, int argc, ParserArg **args, Token *tok) { */
/*     int result = 0, */
/*         argpos = 0; */
    
/*     if(argc == 0) { */
/*         return result; */
/*     } */

/*     do { */
/*         curr = args[argpos]; */
/*         if( curr->all.type != PARG_PARSER ) { */
/*             puts("parse_some only accepts other parsers\n"); */
            
/*             return 0; */
/*         } */

/*         if( apply_parser(stream, curr->parser.parser */
/* } */

/* int exercise_parser(int argc, char **argv) { */
/*     if(! (argc >= 2) ) { */
/*         puts("A filename is expected.\n"); */
/*         return 10; */
/*     } */

/*     Parser *p = malloc(sizeof(Parser)); */
/*     if( p == NULL ) { */
/*         puts("Out of memory?\n"); */
/*         return 20; */
/*     } */
/*     p->fn = &parse_char; */
/*     p->argc = 1; */
/*     p->args = (ParserArg **)malloc(sizeof(ParserArg*)); */
/*     if( p->args == NULL ) { */
/*         puts("Out of memory?\n"); */
/*         return 20; */
/*     } */
/*     p->args[0] = malloc(sizeof(ParserArg)); */
/*     p->args[0]->literal.type = PARG_LITERAL; */
/*     p->args[0]->literal.lit  = 'a'; */

/*     Parser *q = malloc(sizeof(Parser)); */
/*     if( q == NULL ) { */
/*         puts("Out of memory?\n"); */
/*         return 20; */
/*     } */
/*     q->fn = &parse_char; */
/*     q->argc = 1; */
/*     q->args = (ParserArg **)malloc(sizeof(ParserArg*)); */
/*     if( q->args == NULL ) { */
/*         puts("Out of memory?\n"); */
/*         return 20; */
/*     } */
/*     q->args[0] = malloc(sizeof(ParserArg)); */
/*     q->args[0]->literal.type = PARG_LITERAL; */
/*     q->args[0]->literal.lit  = 'b'; */
/*     Parser *many_p = malloc(sizeof(Parser)); */
/*     if( many_p == NULL ) { */
/*         puts("Out of memory?\n"); */
/*         return 20; */
/*     } */

/*     many_p->fn = &parse_many; */
/*     many_p->argc = 2; */
/*     many_p->args = (ParserArg**)malloc(sizeof(ParserArg*)*2); */
/*     if( many_p->args == NULL ) { */
/*         puts("Out of memory?\n"); */
/*         return 20; */
/*     } */

/*     many_p->args[0] = malloc(sizeof(ParserArg)); */
/*     many_p->args[0]->parser.type = PARG_PARSER; */
/*     many_p->args[0]->parser.parser = p; */
/*     many_p->args[1] = malloc(sizeof(ParserArg)); */
/*     many_p->args[1]->parser.type = PARG_PARSER; */
/*     many_p->args[1]->parser.parser = q; */

/*     FILE *stream = fopen(argv[1], "r"); */

/*     Token *root = malloc(sizeof(Token)); */
/*     printf("%d\n", apply_parser(stream, many_p, root)); */
/*     print_tree(root); */
    
/*     return 0; */
/* } */
