#include "logs.h"
#include <stdio.h>
#include "types.h"

FILE *log_file;
status_t print_log(FILE * fo, log_lvl lvl,const char* msg){

	if(!fo || !msg){
		/*imprimir error*/
	}

	switch(lvl){
		case LOG_WARN:
			fprintf(fo,"%s%s\n",LOG_WARN_MSG,msg);
			break;

		case LOG_ERR:
			fprintf(fo,"%s%s\n",LOG_ERR_MSG,msg);
			break;

		case LOG_DEBUG:
			fprintf(fo,"%s%s\n",LOG_DEBUG_MSG,msg);
			break;
	}

	return ST_OK;
}