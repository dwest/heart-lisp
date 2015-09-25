#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "./list.h"

ImmutableList* list_create(int length, ...) {
    va_list vargs;
    ImmutableList *list = malloc(sizeof(ImmutableList));
    list->length = length;

    ImmutableListNode *prev = NULL;
    va_start(vargs, length);
    for(int i = 0; i < length; i++) {
        ImmutableListNode *node = malloc(sizeof(ImmutableListNode));
        node->type = va_arg(vargs, unsigned int);
        node->value = va_arg(vargs, void*);
        node->next = NULL; // may not be strictly necessary, but I hate uninitialized vars

        if(i == 0) {
            list->head = node;
        }
        else {
            prev->next = node;
        }
        prev = node;
    }
    va_end(vargs);
    return list;
}

ImmutableListNode* list_head(ImmutableList *list) {
    if(!list_empty(list)) 
        return list->head;
    return NULL;
}

ImmutableList* list_tail(ImmutableList *list) {
    if(list_empty(list))
        return NULL;

    ImmutableList *tail = malloc(sizeof(ImmutableList));
    tail->length = list->length-1;
    tail->head = list->head->next;

    return tail;
}

bool list_empty(ImmutableList *list) {
    if(list->length == 0)
        return true;

    return false;
}

ImmutableList* list_prepend(ImmutableList *list, unsigned int type, void *value) {
    ImmutableList *changed  = malloc(sizeof(ImmutableList));
    ImmutableListNode *head = malloc(sizeof(ImmutableListNode));
    
    changed->length = list->length+1;
    changed->head   = head;
    head->type      = type;
    head->next      = list->head;
    head->value     = value;

    return changed;
}

ImmutableList* list_append(ImmutableList *list, unsigned int type, void *value) {
    unsigned int nodecount = list->length+1;
    ImmutableList *changed = malloc(sizeof(ImmutableList));
    ImmutableListNode *nodes = malloc(nodecount*sizeof(ImmutableListNode));

    ImmutableListNode *curr = list->head;
    for(unsigned int i = 0; i < nodecount; i++) {
        if(i < nodecount-1) {
            nodes[i] = *curr;
            nodes[i].next = &nodes[i+1];
            curr = curr->next;
        }
        else {
            nodes[i].type  = type;
            nodes[i].value = value;
            nodes[i].next  = NULL;
        }
    }

    changed->head   = &nodes[0];
    changed->length = nodecount;

    return changed;
}

ImmutableList* list_concat(ImmutableList *a, ImmutableList *b) {
    if(a->length == 0) {
        return b;
    }
    if(b->length == 0) {
        return a;
    }

    unsigned int nodecount  = a->length;
    ImmutableList *combined = malloc(sizeof(ImmutableList));
    ImmutableListNode *as   = malloc(nodecount*sizeof(ImmutableListNode));

    ImmutableListNode *curr = a->head;
    for(unsigned int i = 0; i < nodecount; i++) {
        as[i] = *curr;
        if(i < nodecount-1) {
            as[i].next = &as[i+1];
            curr = curr->next;
        }
        else {
            as[i].next = b->head;
        }
    }

    combined->length = a->length + b->length;
    combined->head = as;

    return combined;
}

