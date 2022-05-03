#ifndef ARGS__H
#define ARGS__H 

#include "types.h"

#define MAX_VALID_ARGS 14
#define MIN_ARGC 1

arg_t arg_num(const char *argv);
status_t validate_arguments(int argc,char *argv[],cla_t *cla);

#endif