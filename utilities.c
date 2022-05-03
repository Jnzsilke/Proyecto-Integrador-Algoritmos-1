#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

#define CHOP_SIZE 300 
#define INIT_CHOP 150
status_t destroy_string_array(char ***parray, size_t *n)
{
	size_t i;
	if(parray==NULL||n==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	if(*parray) /* Si es Null no hace nada*/
	{
		for(i=0;i<*n;i++)
		{
			free((parray)[i]);
			(*parray)[i]=NULL;
		}
		free(*parray);
		*n=0;
	}
	return ST_OK;
}
void* sentencedupl(const void *sentence)
{
	char *copy;
	char *original=(char*)sentence;
	
	if(sentence==NULL)	
	{
		return NULL;
	}
	copy=(char*)malloc((strlen(original)+1)*sizeof(char));
	
	if(copy==NULL)
	{
		return NULL;
	}
	
	return strcpy(copy,original);
}

void* unsignedsentencedupl(const void *sentence)
{
	unsigned char *copy;
	unsigned_sentence_t original=*(unsigned_sentence_t *)sentence;
	
	if(sentence==NULL)	
	{
		return NULL;
	}
	copy=(unsigned char*)malloc(original.size*sizeof(unsigned char));
	
	if(copy==NULL)
	{
		return NULL;
	}
	
	return memcpy(copy,original.sentence,original.size);
}

void* trackpoint_dupl(const void *data)
{
	trackpoint_t *original=(trackpoint_t*)data;
	trackpoint_t *copy;
	if(data==NULL)
	{
		return NULL;
	}
	copy=(trackpoint_t *)malloc(sizeof(trackpoint_t));
	if(copy==NULL)
	{
		return NULL;
	}
	memcpy(copy,original,sizeof(trackpoint_t));
	return copy;
}

status_t strdupl(const char *original, char **copy)
{
	if(original==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	*copy=(char*)malloc((strlen(original)+1)*sizeof(char));
	if(copy==NULL)
	{
		return ST_ERROR_NO_MEMORY;
	}

	strcpy(*copy,original);

	return ST_OK;
}
status_t print(void *s,void *file)
{
	char *string=(char*)s;
	FILE *fout=(FILE*)file;
	fprintf(fout,"%s\n",string);
	return ST_OK;
}



status_t split_strpbrk(const char *s,char *delim, char ***fields,size_t *length) /*funcion dada en clase*/
{
	size_t i;
	const char *aux;
	const char *q;
	status_t st;

	if(s==NULL||delim==NULL||length==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	for(q=s,*length=1;*q!='\0';q++)/*cuenta cantidad de campos*/
	{
		if(strchr(delim,*q)!=NULL)
		{
			(*length)++;
		}
	}
	(*fields)=(char**)malloc((*length)*sizeof(char*));/*pide el vector del largo contado*/
	if((*fields)==NULL)
	{
		*length=0;
		return	ST_ERROR_NO_MEMORY;

	}
	for(i=0,q=s;(aux=strpbrk(q,delim));i++,q=aux)/*pide memoria para el campo y lo asigna al vector*/
	{
		aux++;
		(*fields)[i]=(char*)malloc(aux-q);
		if((*fields)[i]==NULL)
		{
			destroy_string_array(fields,&i);
			*length=0;
			return ST_ERROR_NO_MEMORY;

		}
		memcpy((*fields)[i],q,aux-q);
		(*fields)[i][aux-q-1]='\0';

	}/*el ultimo campo no lo copia, hay que hacerlo aparte*/

	st=strdupl(q,&(*fields)[i]);
	if(st!=ST_OK)
	{
		destroy_string_array(fields,&i);
		*length=0;
		return st;
	}

	return ST_OK;
}	

status_t readline(FILE* f,char **s, bool_t *eof)
{
	char* aux;
	size_t inicio;
	
	if(f==NULL||s==NULL||eof==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	*s=(char*)malloc((CHOP_SIZE+1)*sizeof(char));
	if(*s==NULL)
	{
		return ST_ERROR_NO_MEMORY;
	}

	*eof=FALSE;
	inicio=0;

	while(fgets(*s+inicio,CHOP_SIZE+1,f)!=NULL)
	{
		if((*s+inicio)[strlen(*s+inicio)-1]=='\n')
		{
			(*s+inicio)[strlen(*s+inicio)-1]='\0';
			return ST_OK;
		}

		inicio+=CHOP_SIZE;
		aux=(char*)realloc(*s,(inicio+1+CHOP_SIZE)*sizeof(char));
		if(aux==NULL)
		{
			free(*s);
			*s=NULL;
			return ST_ERROR_NO_MEMORY;
		}
		*s=aux;
	}
	if(ferror(f))
	{	

		free(*s);
		*s=NULL;
		return ST_ERROR_IO;

	}
	if(feof(f))
	{
		*eof=TRUE;
	}
	if(inicio==0)
	{
		free(*s);
		*s=NULL;
	}
	return ST_OK;
}

status_t little_endian_to_double(double * r, const unsigned char* byte_arr, size_t n){
	size_t i;

	unsigned int temp;

	if(!r||!byte_arr){
		return ST_ERROR_NULL_POINTER;
	}

	for (i = 0; i < n; ++i)
	{
		temp|= byte_arr[i] << i*8;
	}
	*r=temp;
	return ST_OK;
}

status_t little_endian_to_uint(unsigned int * r, const unsigned char* byte_arr, size_t n){
	size_t i;

	unsigned int temp;

	if(!r||!byte_arr){
		return ST_ERROR_NULL_POINTER;
	}

	for (i = 0; i < n; ++i)
	{
		temp|= byte_arr[i] << i*8;
	}
	*r=temp;
	return ST_OK;
}
