#if !defined(CONTAINER_LIST)
#define CONTAINER_LIST

#include <stdbool.h>

typedef struct ImmutableListNode {
    unsigned int type;
    struct ImmutableListNode *next;
    void *value;
} ImmutableListNode;

typedef struct ImmutableList {
    unsigned int length;
    ImmutableListNode *head;
} ImmutableList;

ImmutableList* list_create(int length, ...);
ImmutableListNode* list_head(ImmutableList *list);
ImmutableList* list_tail(ImmutableList *list);
bool list_empty(ImmutableList *list);
ImmutableList* list_prepend(ImmutableList *list, unsigned int type, void *value);
ImmutableList* list_append(ImmutableList *list, unsigned int type, void *value);
ImmutableList* list_concat(ImmutableList *a, ImmutableList *b);

#endif
