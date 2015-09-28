#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "./list.h"

ImmutableListNode* list_create(unsigned int length, ...) {
    va_list vargs;
    unsigned int node_len = length;
    ImmutableListNode *head = NULL, *curr, *prev;

    va_start(vargs, length);
    for(unsigned int i = 0; i < length; i++) {
        curr = malloc(sizeof(ImmutableListNode));
        *curr = (ImmutableListNode) {
            .type   = va_arg(vargs, unsigned int),
            .value  = va_arg(vargs, void*),
            .length = node_len--,
            .refs   = 1
        };

        if(i == 0) {
            head = curr;
        }
        else {
            prev->next = curr;
        }

        prev = curr;
    }
    va_end(vargs);

    return head;
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
    ImmutableListNode *head = NULL, *curr, *prev = NULL;
    ImmutableListNode *np = list;

    for(unsigned int i = 0; i < nodecount; i++) {
        curr = malloc(sizeof(ImmutableListNode));

        if(i < nodecount-1) {
            *curr = *np;
            ++curr->length;
            np = np->next;
        }
        else {
            *curr = (ImmutableListNode) {
                .type   = type,
                .value  = value,
                .length = 1,
                .next   = NULL
            };
        }

        if(i == 0) {
            head = curr;
        }
        else {
            prev->next = curr;
        }

        curr->refs = 1;
        prev = curr;
    }

    return head;
}

ImmutableListNode* list_concat(ImmutableListNode *a, ImmutableListNode *b) {
    if(list_empty(a)) {
        return b;
    }
    if(list_empty(b)) {
        return a;
    }

    b->refs++;

    unsigned int nodecount = a->length;
    unsigned int node_len  = a->length + b->length;
    ImmutableListNode *head = NULL, *curr = NULL, *prev = NULL, *np = a;

    for(unsigned int i = 0; i < nodecount; i++) {
        curr = malloc(sizeof(ImmutableListNode));
        *curr = *np;
        curr->length = node_len--;
        curr->refs = 1;

        if(i < nodecount-1) {
            np = np->next;
        }
        else {
            curr->next = b;
        }

        if(i == 0) {
            head = curr;
        }
        else {
            prev->next = curr;
        }

        prev = curr;
    }

    return head;
}

void list_print(FILE *stream, ImmutableListNode *list) {
    ImmutableListNode *head = list_head(list);
    ImmutableListNode *tail = list_tail(list);
    ImmutableListNode *prev;
    unsigned int l = head->length;

    fprintf(stream, "`( ");
    for(unsigned int i = 0; i < l; i++) {
        if(i) fprintf(stream, ", ");

        fprintf(stream, "%d", *(unsigned int *)head->value);
        list_free(head);
        head = list_head(tail);
        prev = tail;
        tail = list_tail(tail);
        list_free(prev);
    }
    fprintf(stream, " )\n");
}

ImmutableListNode* list_free(ImmutableListNode *list) {
    if(list_empty(list)) {
        return NULL;
    }

    ImmutableListNode *curr = list, *next;
    while((--curr->refs) == 0) {
        next = curr->next;
        free(curr);
        if(!next) {
            return NULL;
        }
        curr = next;
    }

    return curr;
}

void list_dump(FILE *stream, ImmutableListNode *list) {
    ImmutableListNode *curr = list;
    fprintf(stream, "(\n");
    while(curr) {
        fprintf(stream, 
                "\t %p: { type = %u, refs = %u, length = %u, next = %p, value = %u }\n",
                curr,
                curr->type,
                curr->refs,
                curr->length,
                curr->next,
                *(unsigned int *)curr->value);
        curr = curr->next;
    }
    fprintf(stream, ")\n");
}

