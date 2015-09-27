#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./container/list.h"
//#include "./parse-lisp.h"

int main(/*int argc, char **argv*/) {
    int v0 = 0, v1 = 1, v2 = 1, v3 = 2, v4 = 3, v5 = 5, v6 = 8, v7 = 13;
    ImmutableListNode *list = list_create(8, 
                                      0, &v0,
                                      0, &v1,
                                      0, &v2,
                                      0, &v3,
                                      0, &v4,
                                      0, &v5,
                                      0, &v6,
                                      0, &v7);

    ImmutableListNode *orig = list;

    // test prepend
    printf("Testing Prepend:\n");
    printf("length before: %d\n", list->length);
    int pref = 42;
    list = list_prepend(list, 0, &pref);
    printf("length after: %d\n", list->length);

    // test append
    printf("Testing Append (2x):\n");
    printf("length before: %d\n", list->length);
    int aff = 21;
    list = list_append(list, 0, &aff);
    printf("length after 1x: %d\n", list->length);
    list = list_append(list, 0, &aff);
    printf("length after 2x: %d\n", list->length);

    // test concat
    printf("Testing Concatenation:\n");
    printf("length a: %d, length b: %d\n", orig->length, list->length);
    ImmutableListNode *cattd = list_concat(orig, list);

    unsigned int l = 0;

    printf("orig: [ ");
    l = orig->length;
    for(unsigned int i = 0; i < l; i++) {
        if(i != 0) printf(", ");
        ImmutableListNode *n = list_head(orig);
        if(n != NULL) {
            orig = list_tail(orig);
            printf("%d", *(int *)(n->value));
        }
    }
    printf(" ]\n");

    printf("update: [ ");
    l = list->length;
    for(unsigned int i = 0; i < l; i++) {
        if(i != 0) printf(", ");
        ImmutableListNode *n = list_head(list);
        if(n != NULL) {
            list = list_tail(list);
            printf("%d", *(int *)(n->value));
        }
    }
    printf(" ]\n");

    printf("cattd: [ ");
    l = cattd->length;
    for(unsigned int i = 0; i < l; i++) {
        if(i != 0) printf(", ");
        ImmutableListNode *n = list_head(cattd);
        if(n != NULL) {
            cattd = list_tail(cattd);
            printf("%d", *(int *)(n->value));
        }
    }
    printf(" ]\n");

    //printf("free orig: %d\n", list_free(orig));

    return 0;
}

