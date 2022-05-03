#include "nmea.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "logs.h"
#include "nmea_gga.h"
#include "nmea_zda.h"
#include "nmea_rmc.h"
#include "ADT_List.h"






status_t nmea_get_checksum_from_sentence(const char *sentence,unsigned long int* checksum)
{	

		size_t i;
		char *checksum_token_pos;
		char aux_checksum_string[MAX_CHECKSUM_LEN];

		if(sentence==NULL)
		{
			return ST_ERROR_NULL_POINTER;
		}

		checksum_token_pos=strchr(sentence,CHECK_SUM_TOKEN); /*se busca el token del checksum*/

		if(checksum_token_pos==NULL) /*se verifica si el token esta o no*/
		{
			print_log(log_file,LOG_ERR,LOG_ERROR_NOT_NMEA_SENTENCE_MSG);
			return ST_ERROR_NO_CHECKSUM_TOKEN_FOUND;
		}

		checksum_token_pos++; /*se aumenta la posicion para empezar a copiar desde el primer caracter siguiente distinto del token*/
		for(i=0;*checksum_token_pos;checksum_token_pos++,i++)
		{
			aux_checksum_string[i]=*checksum_token_pos;
		}
		aux_checksum_string[i]='\0'; /*tenemos en un string auxiliar al valor de checksum, falta pasarlo a unsigned long*/
		*checksum=strtoul(aux_checksum_string,&checksum_token_pos,16); /*reutilizamos la variable checksum_token_pos ya que no se necesita mas*/
		
		if(*checksum_token_pos&&*checksum_token_pos!='\n') /*se verifica que lo que se paso a la cadena auxiliar haya sido correcto*/
		{
			print_log(log_file,LOG_ERR,LOG_ERROR_NOT_NMEA_SENTENCE_MSG);
			return ST_ERROR_INVALID_CHECKSUM_VALUE;
		}

		return ST_OK;
}

status_t nmea_calculate_checksum(const char * sentence,unsigned char *checksum) 
{	
	size_t i=SENTENCE_START; /*se considera que la linea tiene incluido $*/
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_CALCULATE_CHECKSUM_MSG);
	
	*checksum=0;
	

	if(sentence==NULL)
	{
			return ST_ERROR_NULL_POINTER;
	}

	while (sentence[i]!=CHECK_SUM_TOKEN) /*la cuenta se hace hasta el token*/
	{
		*checksum ^= sentence[i];
		i++;
	}

	return ST_OK;
}

status_t nmea_check(const char *sentence,const char *sentence_type)/*verifica si el checksum de la sentencia es correcto*/
{
	
	unsigned char checksum_calc;
	unsigned long int checksum_sentence;
	status_t st;

	print_log(log_file,LOG_DEBUG,LOG_DEBUG_VERIFY_CHECKSUM_MSG);
	if(sentence==NULL||sentence_type==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	st=nmea_get_checksum_from_sentence(sentence,&checksum_sentence);
	if(st!=ST_OK)
	{
		return st;
	}

	st=nmea_calculate_checksum(sentence,&checksum_calc);
	if(st!=ST_OK)
	{
		return st;
	}

	if(checksum_calc!=checksum_sentence)
	{
		print_log(log_file,LOG_ERR,LOG_ERROR_INCORRECT_CHECKSUM_MSG);
		return ST_ERROR_INVALID_CHECKSUM_IN_SENTENCE;
	}
	print_log(log_file,LOG_DEBUG,LOG_ERROR_CORRECT_CHECKSUM_MSG);
	return ST_OK;

}
status_t nmea_sentence_identifier(const char *sentence,nmea_sentence_t *gp)
{
	status_t st;
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_ID_NMEA_SENTENCE_MSG);
	if(sentence==NULL||gp==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	if(strstr(sentence,SENTENCE_GGA)!=NULL)
	{
		st=nmea_check(sentence,SENTENCE_GGA);
		if(st!=ST_OK)
		{
			return st;
		}
		*gp=GP_GGA;
		print_log(log_file,LOG_DEBUG,LOG_DEBUG_NMEA_GGA_SENTENCE_MSG);
		return ST_OK;

	}else if(strstr(sentence,SENTENCE_RMC)!=NULL)
	{
		st=nmea_check(sentence,SENTENCE_RMC);
		if(st!=ST_OK)
		{
			return st;
		}
		*gp=GP_RMC;
		print_log(log_file,LOG_DEBUG,LOG_DEBUG_NMEA_RMC_SENTENCE_MSG);
		return ST_OK;

	}else if(strstr(sentence,SENTENCE_ZDA)!=NULL)
	{
		st=nmea_check(sentence,SENTENCE_ZDA);
		if(st!=ST_OK)
		{
			return st;
		}
		*gp=GP_ZDA;
		print_log(log_file,LOG_DEBUG,LOG_DEBUG_NMEA_ZDA_SENTENCE_MSG);
		return ST_OK;

	}else
	{
		print_log(log_file,LOG_WARN,LOG_WARN_UNKNOWN_SENTENCE_MSG);
		*gp=GP_UNKNOWN;
		return ST_OK;
	}
}

status_t nmea_to_track_to_gpx(const char *sentence,trackpoint_t *track,List *List)
{	
	status_t st;
	nmea_sentence_t gp;
	double temporal_elevation=ELEVATION_ZERO;
	gga_t gga;
	rmc_t rmc;
	zda_t zda;
	
	if(sentence==NULL||track==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	st=nmea_sentence_identifier(sentence,&gp);
	if(st!=ST_OK)
	{
		return st;
	}

	switch(gp)
	{
		case GP_GGA:

			st=nmea_gga_load_to_gga_t(sentence,&gga);
			if(st!=ST_OK)
			{	
				return st;
			}
			track->longitude=gga.longitude;
			track->latitude=gga.latitude;
			track->elevation=temporal_elevation=gga.elevation;
			track->day.hour=gga.fix_hour.hour;
			track->day.minutes=gga.fix_hour.minutes;
			track->day.seconds=gga.fix_hour.seconds;
			
			if(gga.quality_fix==QF_INVALID)
			{
				print_log(log_file,LOG_WARN,LOG_WARN_GGA_QF_INVALID_MSG);
				break;
			}
			else
			{
				ADT_List_append(List,track,trackpoint_dupl);
				break;
			}
			

		case GP_ZDA:
			nmea_zda_load_to_zda_t(sentence,&zda);
			track->date.day=zda.date.day;
			track->date.month=zda.date.month;
			track->date.year=zda.date.year;
			break;

		case GP_RMC:
			nmea_rmc_load_to_rmc_t(sentence,&rmc);
			track->longitude=rmc.longitude;
			track->latitude=rmc.latitude;
			track->elevation=temporal_elevation;
			track->day.hour=rmc.fix_hour.hour;
			track->day.minutes=rmc.fix_hour.minutes;
			track->day.seconds=rmc.fix_hour.seconds;
			track->date.day=rmc.date.day;
			track->date.month=rmc.date.month;
			track->date.year=rmc.date.year;
			ADT_List_append(List,track,trackpoint_dupl);
			break;

		case GP_UNKNOWN:
			break;
	}
	return ST_OK;
}