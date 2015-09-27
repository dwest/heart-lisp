#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "./list.h"

ImmutableListNode* list_create(unsigned int length, ...) {
    va_list vargs;
    unsigned int node_len    = length;
    ImmutableListNode *nodes = malloc(length*sizeof(ImmutableListNode));

    va_start(vargs, length);
    for(unsigned int i = 0; i < length; i++) {
        nodes[i] = (ImmutableListNode) {
            .type   = va_arg(vargs, unsigned int),
            .value  = va_arg(vargs, void*),
            .length = node_len--,
            .refs   = 1
        };

        if(i < length-1) {
            nodes[i].next = &nodes[i+1];
        }
        else {
            nodes[i].next = NULL; // was probably already null
        }
    }
    va_end(vargs);

    return nodes;
}

ImmutableListNode* list_head(ImmutableListNode *list) {
    if(!list_empty(list)) {
        ++list->refs;
        return list;
    }

    return NULL;
}

ImmutableListNode* list_tail(ImmutableListNode *list) {
    if(list_empty(list) || list->length == 1)
        return NULL;

    ImmutableListNode *tail = list->next;
    ++tail->refs;

    return tail;
}

bool list_empty(ImmutableListNode *list) {
    if(list == NULL)
        return true;

    return false;
}

ImmutableListNode* list_prepend(ImmutableListNode *list, unsigned int type, void *value) {
    ImmutableListNode *head = malloc(sizeof(ImmutableListNode));

    *head = (ImmutableListNode) {
        .type   = type,
        .refs   = 1,
        .next   = list,
        .value  = value,
        .length = list->length+1
    };

    if(!list_empty(list)) {
        list->refs++;
    }

    return head;
}

ImmutableListNode* list_append(ImmutableListNode *list, unsigned int type, void *value) {
    if(list_empty(list)) {
        return list_create(1, type, value);
    }

    unsigned int nodecount = list->length+1;
    ImmutableListNode *nodes = malloc(nodecount*sizeof(ImmutableListNode));

    ImmutableListNode *curr = list;
    for(unsigned int i = 0; i < nodecount; i++) {
        if(i < nodecount-1) {
            nodes[i]      = *curr;
            nodes[i].next = &nodes[i+1];
            ++nodes[i].length;
            curr = curr->next;
        }
        else {
            nodes[i] = (ImmutableListNode) {
                .type   = type,
                .value  = value,
                .length = 1,
                .next   = NULL
            };
        }

        nodes[i].refs = 1;
    }

    return nodes;
}

ImmutableListNode* list_concat(ImmutableListNode *a, ImmutableListNode *b) {
    if(list_empty(a)) {
        return b;
    }
    if(list_empty(b)) {
        return a;
    }

    b->refs++;

    unsigned int nodecount  = a->length;
    unsigned int node_len   = a->length + b->length;
    ImmutableListNode *as   = malloc(nodecount*sizeof(ImmutableListNode));

    ImmutableListNode *curr = a;
    for(unsigned int i = 0; i < nodecount; i++) {
        as[i]        = *curr;
        as[i].length = node_len--;

        if(i < nodecount-1) {
            as[i].next = &as[i+1];
            curr = curr->next;
        }
        else {
            as[i].next = b;
        }
    }

    return as;
}

/* unsigned int list_free(ImmutableListNode *list) { */
/*     if(--(list->refs) != 0) { */
/*         return list->refs; */
/*     } */
/* } */

