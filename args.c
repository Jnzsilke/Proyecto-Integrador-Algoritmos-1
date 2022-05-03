#include "args.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "config.h"
#include "utilities.h"

arg_t arg_num(const char *argv)
{

			size_t i;
			const char* valid_args[MAX_VALID_ARGS]=
			{
				"-h",
				"--help",
				"-n",
				"--name",
				"-p",
				"--protocol",
				"-i",
				"--infile",
				"-o",
				"--outfile",
				"-l",
				"--logfile",
				"-m",
				"--maxlen"

			};

			for(i=0;i<MAX_VALID_ARGS;i++)
				if(!strcmp(argv,valid_args[i]))
					break;

			return (arg_t)i;
}

status_t validate_arguments(int argc,char *argv[],cla_t *cla)
{

			status_t st;
			size_t i;
			char *temp;

			if(argv==NULL)
			{
				return ST_ERROR_NULL_POINTER;
			}

			if(argc==MIN_ARGC)
			{
				return ST_ERROR_CLA_NO_INPUT;
			}

		

			for(i=1;i<argc;i+=2)
			{

				switch(arg_num(argv[i]))
				{
					case ARG_HELP_SHORT:
					case ARG_HELP_LONG:
						return ST_CMD_ARG_NEED_HELP;
						break;

					case ARG_NAME_SHORT:
					case ARG_NAME_LONG:
						if(!argv[i+1])
						{
							return ST_ERROR_INVALID_CLA_ARG_NUM;
						}
						st=strdupl(argv[i+1],&(cla->name));
						if(st!=ST_OK)
						{
							return st;
						}
						break;

					case ARG_PROTOCOL_SHORT:
					case ARG_PROTOCOL_LONG:
						if(!argv[i+1])
						{
							return ST_ERROR_INVALID_CLA_ARG_NUM;
						}
						if(!strcmp(argv[i+1],NMEA_PROTOCOL_NAME))
						{
							cla->protocol=PROTOCOL_NMEA;
						}
						if(!strcmp(argv[i+1],UBX_PROTOCOL_NAME))
						{
							cla->protocol=PROTOCOL_UBX;
						}
						if(!strcmp(argv[i+1],AUTO_PROTOCOL_NAME))
						{
							cla->protocol=PROTOCOL_AUTO;
						}
						break;

					case ARG_INFILE_SHORT:
					case ARG_INFILE_LONG:
						if(!argv[i+1])
						{
							return ST_ERROR_INVALID_CLA_ARG_NUM;
						}
						st=strdupl(argv[i+1],&(cla->infile));
						if(st!=ST_OK)
						{
							return st;
						}
						break;

					case ARG_OUTFILE_SHORT:
					case ARG_OUTFILE_LONG:
						if(!argv[i+1])
						{
							return ST_ERROR_INVALID_CLA_ARG_NUM;
						}
						st=strdupl(argv[i+1],&(cla->outfile));
							if(st!=ST_OK)
						{
							return st;
						}
						break;

					case ARG_LOGFILE_SHORT:
					case ARG_LOGFILE_LONG:
						if(!argv[i+1])
						{
							return ST_ERROR_INVALID_CLA_ARG_NUM;
						}
						st=strdupl(argv[i+1],&(cla->logfile));
							if(st!=ST_OK)
						{
							return st;
						}
						break;

					case ARG_MAXLEN_SHORT:
					case ARG_MAXLEN_LONG:
						if(!argv[i+1])
						{
							return ST_ERROR_INVALID_CLA_ARG_NUM;
						}
						cla->maxlen=strtoul(argv[i+1],&temp,10);
						if(*temp&&*temp!='\n')
						{
							return ST_ERROR_INVALID_MAXLEN_CONVERSION;
						}

					case ARG_ERROR:
					default: 
			  				return ST_ERROR_INVALID_CLA_INPUT;
				}
			
			}
			
			return ST_OK;
}