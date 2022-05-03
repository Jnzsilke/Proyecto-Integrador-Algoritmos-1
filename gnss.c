#include "gnss.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>






status_t get_protocol(FILE *fi,protocol_t *protocol);
status_t load_cla_default(cla_t *cla);
status_t free_cla(cla_t *cla);

int	main(int argc,char  *argv[])
{

	
	trackpoint_t track;
	char *sentence;
	unsigned char * unsigned_sentence;
	
	cla_t cla;
	struct tm *machine_time;
	status_t st;
	gpx_metadata_t gpx;
	time_t 	this_time;
	FILE * input_file, *output_file;
	bool_t eof=FALSE;
	List list;
	size_t i,msg_to_read,saved_msg=0;
	
	/*carga estructura cla por default*/
	st=load_cla_default(&cla);
	if(st!=ST_OK)
	{	

		return st;
	}
	
	/* obtener horario de la maquina*/

	time(&this_time);
	machine_time=localtime(&this_time);
	track.date.year=gpx.date.year=machine_time->tm_year+1900;
	track.date.month=gpx.date.month=machine_time->tm_mon+1;
	track.date.day=gpx.date.day=machine_time->tm_mday;
	track.day.hour=gpx.day.hour=machine_time->tm_hour;
	track.day.minutes=gpx.day.minutes=machine_time->tm_min;
	track.day.seconds=gpx.day.seconds=machine_time->tm_sec;


	
	st=validate_arguments(argc,argv,&cla);
	
	if(st!=ST_CMD_ARG_NEED_HELP&&st!=ST_OK)

	{	free_cla(&cla);
		print_cla_error_msg(st);
		return st;
	}
	if(st==ST_CMD_ARG_NEED_HELP)
	{
		free_cla(&cla);
		print_help_msg(stdout);
		return ST_OK;
	}

	gpx.name=(char*)malloc(sizeof(char)*strlen(cla.name)+1);
	if(gpx.name==NULL)
	{
		free_cla(&cla);
		return ST_ERROR_NO_MEMORY;
	}
	strcpy(gpx.name,cla.name);

	log_file=fopen(cla.logfile,"wt");
	if(log_file==NULL)
	{
		free_cla(&cla);
		free(gpx.name);
		print_error_msg(st); /*"No pudo abrirse el archivo de logs."*/
		return ST_ERROR_CANNOT_OPEN_LOG_FILE;
	}

	st=ADT_List_create(&list);
	if(st!=ST_OK)
	{
		
		if(fclose(log_file)==EOF)
		{
			print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_LOG_FILE_MSG);
		}
		print_error_msg(st);  /*"No pudo crearse una lista."*/
		free_cla(&cla);
		free(gpx.name);
		return ST_ERROR_CANNOT_CREATE_LIST;
	}
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_LIST_CREATE_MSG);

	output_file=fopen(cla.outfile,"wt");/*si no se indica archivo de salida, se crea uno por defecto*/
	if(output_file==NULL)
	{
		ADT_List_free_list(&list,free);
		print_log(log_file,LOG_ERR,LOG_ERROR_OPEN_OUTPUT_FILE_MSG);
		if(fclose(log_file)==EOF)
		{
			print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_OUTPUT_FILE_MSG);
		}
		free_cla(&cla);
		free(gpx.name);
		return ST_ERROR_CANNOT_OPEN_OUTPUT_FILE;
	}
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_OPEN_OUTPUT_FILE_MSG);
	if(!strcmp(cla.infile,DEFAULT_INPUT_FILE)) /*si no se ingreso nombre de input, se asume stdin*/
	{	
		input_file=stdin;
		cla.protocol=PROTOCOL_NMEA; /*Si el usuario ingresa por stdin se asume automaticamente que es nmea*/
				
	}
	else
	{
		input_file=fopen(cla.infile,"rb"); /*se abre en binario para poder detectar protocolo*/
		if(input_file==NULL)
		{	
			print_error_msg(st); /*"No pudo abrirse el archivo de entrada."*/
			ADT_List_free_list(&list,free);
			print_log(log_file,LOG_ERR,LOG_ERROR_OPEN_INPUT_FILE_MSG);
			if(fclose(log_file)==EOF)
			{
				print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_OUTPUT_FILE_MSG);
			}
			if(fclose(output_file)==EOF)
			{	
				print_log(log_file,LOG_DEBUG,LOG_ERROR_CLOSE_OUTPUT_FILE_MSG);
			}
			free_cla(&cla);
			free(gpx.name);
			return ST_ERROR_CANNOT_OPEN_INPUT_FILE;
		}
		print_log(log_file,LOG_DEBUG,LOG_DEBUG_OPEN_INPUT_FILE_MSG);
	}
	
	if(cla.protocol==PROTOCOL_AUTO)
	{	
		st=get_protocol(input_file,&(cla.protocol));
		if(st!=ST_OK)
		{	
			print_error_msg(st); /* "No pudo detectarse el protocolo" */
			
			if(fclose(log_file)==EOF)
			{
				print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_OUTPUT_FILE_MSG);
			}
			if(fclose(output_file)==EOF)
			{
				print_log(log_file,LOG_DEBUG,LOG_ERROR_CLOSE_OUTPUT_FILE_MSG);	
			}
			if(fclose(input_file)==EOF)
			{
				print_log(log_file,LOG_DEBUG,LOG_ERROR_OPEN_INPUT_FILE_MSG);
			}		
			ADT_List_free_list(&list,free);
			free_cla(&cla);
			free(gpx.name);
			return st;
		}
	}
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_PRINT_HEADER_MSG);
	print_gpx_header(output_file,&gpx);
	free(gpx.name);
	
	

	
	switch(cla.protocol)
	{
		case PROTOCOL_NMEA: /*se decide no hacer una funcion para esto ya que tendria que recibir demasiados parametros*/
			print_log(log_file,LOG_DEBUG,LOG_DEBUG_NMEA_PROTOCOL_DETECTED_MSG);
			msg_to_read=rand();

			while((st=readline(input_file,&sentence,&eof))&&eof!=TRUE)
			{	
				if(st!=ST_OK)
				{	free(sentence);
					print_error_msg(st); /*No pudo leerse una sentencia correctamente*/
					print_log(log_file,LOG_ERR,LOG_ERROR_READLINE_MSG);
				}

				st=nmea_to_track_to_gpx(sentence,&track,&list);
				if(st!=ST_OK)
				{

					print_log(log_file,LOG_WARN,LOG_WARN_LIST_APPEND_MSG);
				}
				else
				{
					saved_msg++;	
				}
				free(sentence);
				if(saved_msg==cla.maxlen)/* si se llena, imprimir*/
				{	
					ADT_List_traverse(list,print_gpx_track_point,output_file);
					print_log(log_file,LOG_DEBUG,LOG_DEBUG_PRINT_TRACKPOINTS_MSG);
					for(i=0;i<=saved_msg;i++)
					{	
						ADT_List_destroy_first_node(&list,free);
					}
					msg_to_read=rand();
					saved_msg=0;
				}
				if(saved_msg==msg_to_read)/*si se guardo la cantidad elegida por el numero random*/
				{	ADT_List_traverse(list,print_gpx_track_point,output_file);
					print_log(log_file,LOG_DEBUG,LOG_DEBUG_PRINT_TRACKPOINTS_MSG);
					for(i=0;i<=saved_msg;i++)
					{
						ADT_List_destroy_first_node(&list,free);
					}
					msg_to_read=rand();
					saved_msg=0;
				}

			}
			free(sentence);
			/*liberar sentence*/
			break;

		case PROTOCOL_UBX:
			/* mensaje ubx*/
			msg_to_read=rand();
			while(!eof&&((st=ubx_get_sentence(input_file,&unsigned_sentence,&eof))==ST_OK)){
				if(st!=ST_OK){
					free(unsigned_sentence);
					print_error_msg(st); /*No pudo leerse una sentencia correctamente*/
					print_log(log_file,LOG_ERR,LOG_ERROR_READLINE_MSG);
				}
				if((st=ubx_to_track_to_gpx(unsigned_sentence,&track,&list))!=ST_OK){
					print_log(log_file,LOG_WARN,LOG_WARN_LIST_APPEND_MSG);
				}else{
					saved_msg++;
				}
				free(unsigned_sentence);
			
				if(saved_msg==cla.maxlen)/* si se llena, imprimir*/
				{	
					ADT_List_traverse(list,print_gpx_track_point,output_file);
					print_log(log_file,LOG_DEBUG,LOG_DEBUG_PRINT_TRACKPOINTS_MSG);
					for(i=0;i<=saved_msg;i++)
					{	
						ADT_List_destroy_first_node(&list,free);
					}
					msg_to_read=rand();
					saved_msg=0;
				}
				if(saved_msg==msg_to_read)/*si se guardo la cantidad elegida por el numero random*/
				{	ADT_List_traverse(list,print_gpx_track_point,output_file);
					print_log(log_file,LOG_DEBUG,LOG_DEBUG_PRINT_TRACKPOINTS_MSG);
					for(i=0;i<=saved_msg;i++)
					{
						ADT_List_destroy_first_node(&list,free);
					}
					msg_to_read=rand();
					saved_msg=0;
				}
			}
			break;

		case PROTOCOL_AUTO:
			break;

		case PROTOCOL_UNKNOWN:
			print_log(log_file,LOG_DEBUG,LOG_DEBUG_UNKNOWN_PROTOCOL_MSG);
			break;
	}


	ADT_List_free_list(&list,free);
	print_gpx_footer(output_file);
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_PRINT_FOOTER_MSG);
	
	if(fclose(output_file)==EOF)
	{
		print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_OUTPUT_FILE_MSG);	
	}
	if(fclose(input_file)==EOF)
	{
		print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_INPUT_FILE_MSG);
	}
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_OUTPUT_FILE_CLOSE_MSG);
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_INPUT_FILE_CLOSE_MSG);
	
	if(fclose(log_file)==EOF)
	{
		print_log(log_file,LOG_ERR,LOG_ERROR_CLOSE_LOG_FILE_MSG);
	}
	free_cla(&cla);
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_CLOSE_ALL_FILES_MSG);
	return ST_OK;
}

status_t get_protocol(FILE *fi,protocol_t *protocol)
{	
	unsigned char bitscheck[MAX_BITS_CHECK];
	if(fi==NULL)
	{	
		return ST_ERROR_NULL_POINTER;
	}

	if(fread(bitscheck,sizeof(unsigned char),MAX_BITS_CHECK,fi)!=MAX_BITS_CHECK)
	{	
		return ST_ERROR_IO;
	}
	if(bitscheck[0]==UBX_SYNC_1&&bitscheck[1]==UBX_SYNC_2)
	{	
		*protocol=PROTOCOL_UBX;
		print_log(log_file,LOG_DEBUG,LOG_DEBUG_UBX_PROTOCOL_DETECTED_MSG);
		if(fseek(fi,0,SEEK_SET))
		{	
			return ST_ERROR_IO;	
		}
		return ST_OK;
	}
	else if(bitscheck[0]==NMEA_IDENTIFIER_MONEY&&bitscheck[1]==NMEA_IDENTIFIER_G&&bitscheck[2]==NMEA_IDENTIFIER_P)
	{
		*protocol=PROTOCOL_NMEA;
		print_log(log_file,LOG_DEBUG,LOG_DEBUG_NMEA_PROTOCOL_DETECTED_MSG);
		if(fseek(fi,0,SEEK_SET))
		{	
			return ST_ERROR_IO;	
		}

		return ST_OK;

	}
	else
	{
		*protocol=PROTOCOL_UNKNOWN;
		if(fseek(fi,0,SEEK_SET))
		{
			return ST_ERROR_IO;	
		}
		return ST_OK;	
	}
}
status_t load_cla_default(cla_t *cla)
{
	if(cla==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	cla->name=(char*)malloc(sizeof(char)*strlen(DEFAULT_METADATA_NAME)+1);
	if(cla->name==NULL)
	{
		return ST_ERROR_NO_MEMORY;
	}
	strcpy(cla->name,DEFAULT_METADATA_NAME);
	
	cla->protocol=PROTOCOL_AUTO;

	cla->infile=(char*)malloc(sizeof(char)*strlen(DEFAULT_INPUT_FILE)+1);
	if(cla->infile==NULL)
	{
		free(cla->name);
		free(cla->infile);
		return ST_ERROR_NO_MEMORY;
	}
	strcpy(cla->infile,DEFAULT_INPUT_FILE);

	cla->outfile=(char*)malloc(sizeof(char)*strlen(DEFAULT_OUTPUT_FILE)+1);
	if(cla->outfile==NULL)
	{
		free(cla->name);
		free(cla->infile);
		return ST_ERROR_NO_MEMORY;
	}

	strcpy(cla->outfile,DEFAULT_OUTPUT_FILE);

	cla->logfile=(char*)malloc(sizeof(char)*strlen(DEFAULT_LOG_FILE)+1);
	if(cla->logfile==NULL)
	{
		free(cla->name);
		free(cla->infile);
		free(cla->outfile);
		return ST_ERROR_NO_MEMORY;
	}
	strcpy(cla->logfile,DEFAULT_LOG_FILE);

	cla->maxlen=MAX_MSG_TO_SAVE;

	return ST_OK;
}

status_t free_cla(cla_t *cla)
{
	if(cla==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}
	free(cla->name);
	free(cla->infile);
	free(cla->outfile);
	free(cla->logfile);
	return ST_OK;
}