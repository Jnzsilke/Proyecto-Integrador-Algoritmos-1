#include <stdio.h>
#include "types.h"



status_t print_cla_error_msg(status_t st)
{	
	extern char* errors_cla[];
	fprintf(stderr,"%s\n",errors_cla[st]);
	return ST_OK;
}

status_t print_error_msg(status_t st)
{
	extern char* error_msgs[];
	fprintf(stderr,"%s\n",error_msgs[st]);
	return ST_OK;
}
