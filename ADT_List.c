#include <stdio.h>
#include <stdlib.h>
#include "types.h"

status_t ADT_List_create(List *List)
{
	if(List==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	*List=NULL;
	return ST_OK;

}

struct node* ADT_List_create_node(void *data,void* (*clonator)(const void*))
{
	struct node *node;

	if(data==NULL||clonator==NULL)
	{
		return NULL;
	}
	node=(struct node*)malloc(sizeof(struct node));
	
	if(!(node->data=(*clonator)(data)))
	{	

		free(node);
		return NULL;

	}
	node->next=NULL;
	return node;
}

bool_t ADT_List_is_empty(List l)
{
	return(l==NULL)?TRUE:FALSE;
}

status_t ADT_List_push(List *List,void *data, void* (*clonator)(const void*))
{
	struct node *node;
	if(List==NULL||data==NULL||clonator==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}
	node=ADT_List_create_node(data,clonator);

	if(node==NULL)
	{

		return ST_ERROR_CANNOT_CREATE_NODE;
	}

	if((*List)==NULL)
	{

		*List=node;
		return ST_OK;
	}
	node->next=*List;

	*List=node;
	return ST_OK;
}
void ADT_List_destroy_node(struct node **pnode, void (*destructor)(void*))
{
	void *data;

	if(pnode==NULL||destructor==NULL||(*pnode)==NULL)
	{
		return;
	}	
	data=(*pnode)->data;
	(*destructor)(data);
	(*pnode)->data=NULL;
	(*pnode)->next=NULL;
	free(*pnode);
	(*pnode)=NULL;

}

void ADT_List_destroy_first_node(List *List,void (*destructor)(void*))
{
	struct node *aux;

	if(List&&destructor&&(*List))
	{
		aux=(*List);
		(*List)=aux->next;
		ADT_List_destroy_node(&aux,destructor);
	}
}

void ADT_List_free_list(List *List,void (*destructor)(void*))
{
	struct node *next;
	if(List==NULL||(*List)==NULL||destructor==NULL)
	{
		return;
	}

	next=(*List)->next;
	ADT_List_destroy_node(List,destructor);
	ADT_List_free_list(&next,destructor);
}

status_t ADT_List_append(List *List,void *data,void* (*clonator)(const void*))
{
	if(List==NULL||clonator==NULL||data==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}
	if(ADT_List_is_empty(*List)==TRUE)
	{

		return ADT_List_push(List,data,clonator);
	}

	return ADT_List_append(&(*List)->next,data,clonator);

}

status_t ADT_List_traverse(List l,status_t (*pf)(void*,void*),void* arg)
{

	if(l==NULL)
	{
		return ST_OK;

	}
	if(pf==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}
		

	(*pf)(arg,l->data);
	
	return ADT_List_traverse(l->next,pf,arg);
}

void* ADT_List_pop(List *l)
{
	void *aux;
	if(l==NULL)
	{
		return NULL;
	}

	if((*l)->next==NULL)
	{
		aux=(*l)->data;
		(*l)->data=NULL;
		free(*l);
		*l=NULL;
		return aux;
	}
	return ADT_List_pop(&(*l)->next);

}