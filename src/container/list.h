#if !defined(CONTAINER_LIST)
#define CONTAINER_LIST

#include <stdbool.h>

typedef struct ImmutableListNode {
    unsigned int type;
    unsigned int refs;
    unsigned int length;
    struct ImmutableListNode *next;
    void *value;
} ImmutableListNode;

ImmutableListNode* list_create(unsigned int length, ...);
ImmutableListNode* list_head(ImmutableListNode *list);
ImmutableListNode* list_tail(ImmutableListNode *list);
bool list_empty(ImmutableListNode *list);
ImmutableListNode* list_prepend(ImmutableListNode *list, unsigned int type, void *value);
ImmutableListNode* list_append(ImmutableListNode *list, unsigned int type, void *value);
ImmutableListNode* list_concat(ImmutableListNode *a, ImmutableListNode *b);
/* unsigned int list_free(ImmutableList *list); */

#endif
