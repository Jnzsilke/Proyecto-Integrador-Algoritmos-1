#ifndef UTILITIES__H
#define UTILITIES__H
#include "types.h"



status_t get_data_field(const char *line,size_t field_pos,char *aux_string,int delimiter);
status_t destroy_string_array(char ***parray, size_t *n);
void* sentencedupl(const void *sentence);
void* unsignedsentencedupl(const void *sentence);
status_t strdupl(const char *original, char **copy);
status_t split_strpbrk(const char *s,char *delim, char ***fields,size_t *length);
status_t readline(FILE* f,char **s, bool_t *eof);
status_t print(void *s,void *file);
void* trackpoint_dupl(const void *data);
status_t little_endian_to_uint(unsigned int * r, const unsigned char* byte_arr, size_t n);
status_t little_endian_to_double(double * r, const unsigned char* byte_arr, size_t n);
#endif