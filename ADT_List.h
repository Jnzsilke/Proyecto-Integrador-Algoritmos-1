#ifndef ADT_LIST__H
#define ADT_LIST__H

#include "types.h"


status_t ADT_List_create(List* List);
struct node* ADT_List_create_node(void *data,void* (*clonator)(const void*));
bool_t ADT_List_is_empty(List l);
status_t ADT_List_push(List* List,void *data,void* (*clonator)(const void*));
void ADT_List_destroy_node(struct node **pnode,void (*destructor)(void*));
void ADT_List_destroy_first_node(List *List,void (*destructor)(void*));
void ADT_List_free_list(List *List,void (*destructor)(void*));
status_t ADT_List_append(List *List,void *data,void* (*clonator)(const void*));
status_t ADT_List_traverse(List l,status_t (*pf)(void*,void*),void* arg);
void* ADT_List_pop(List *l);

#endif