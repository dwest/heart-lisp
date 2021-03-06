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
    ImmutableListNode *old;
    old = list;
    ImmutableListNode *orig = list_head(list);
    list_free(old);

    // test prepend
    printf("Testing Prepend:\n");
    printf("length before: %d\n", list->length);
    int pref = 42;
    old = list;
    list = list_prepend(list, 0, &pref);
    printf("prev->head: %p, free old: %p\n", old, list_free(old));
    printf("length after: %d\n", list->length);

    // test append
    printf("Testing Append (2x):\n");
    printf("length before: %d\n", list->length);
    int aff = 21;
    old = list;
    list = list_append(list, 0, &aff);
    printf("length after 1x: %d\n", list->length);
    old = list;
    list = list_append(list, 0, &aff);
    printf("length after 2x: %d\n", list->length);

    // test concat
    printf("Testing Concatenation:\n");
    printf("length a: %d, length b: %d\n", orig->length, list->length);
    ImmutableListNode *cattd = list_concat(orig, list);

    printf("orig: \n");
    list_dump(stdout, orig);
    printf("list: \n");
    list_dump(stdout, list);
    printf("cattd: \n");
    list_dump(stdout, cattd);

    printf("free cattd: %p\n", list_free(cattd));
    printf("free list: %p\n", list_free(list));
    printf("free orig: %p\n", list_free(orig));

    return 0;
}

