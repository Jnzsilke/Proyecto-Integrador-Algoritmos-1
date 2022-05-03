#include "nmea_rmc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "utilities.h"
#include "config.h"

status_t nmea_rmc_load_date(const char *field,rmc_t *rmc)
{
	size_t date;
	char* temp;

	if(field==NULL||rmc==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	date=strtod(field,&temp);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_DATE;
	}



	rmc->date.day=date/RMC_DAY_DIV_FACTOR;
	rmc->date.month=(date-rmc->date.day*RMC_DAY_DIV_FACTOR)/RMC_MONTH_DIV_FACTOR;
	rmc->date.year=date-rmc->date.day*RMC_DAY_DIV_FACTOR-rmc->date.month*RMC_MONTH_DIV_FACTOR+RMC_YEAR_SUM;

	return	 ST_OK;

}

status_t nmea_rmc_load_status(const char *field,rmc_t *rmc)
{
	rmc_status_t rmc_status;

	if(field==NULL||rmc==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	if(strchr(field,RMC_STATUS_ACTIVE)){
		rmc_status = ST_ACTIVE;
	}
	else if (strchr(field,RMC_STATUS_VOID)){
		rmc_status= ST_VOID;
	}
	else{
 		return ST_ERROR_RMC_STATUS;
	}

	rmc->rmc_status=rmc_status;

	return	 ST_OK;

}


status_t nmea_rmc_load_fix_hour(const char *field,rmc_t *rmc)
{
	unsigned int hour;
	unsigned int minutes;
	
	double seconds; /*se va a convertir el numero sobre esta variable*/
	char *temp;

	if(field==NULL||rmc==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	seconds=strtod(field,&temp);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_FIX_HOUR;
	}

	hour=seconds/HOUR_DIV_FACTOR;
	seconds=seconds-hour*HOUR_DIV_FACTOR;
	minutes=seconds/MINUTE_DIV_FACTOR;
	seconds=seconds-minutes*MINUTE_DIV_FACTOR;

	rmc->fix_hour.hour=hour;
	rmc->fix_hour.minutes=minutes;
	rmc->fix_hour.seconds=seconds;

	return	 ST_OK;

}

status_t nmea_rmc_load_latitude(const char *field,const char *cardinal,rmc_t *rmc)
{

	double latitude_nmea;
	double degree;
	double minutes_lat;
	char *temp;

	if(field==NULL||rmc==NULL){
		return ST_ERROR_NULL_POINTER;
	}

	latitude_nmea=strtod(field,&temp);

	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_LATITUDE_CONVERSION;
	}

	degree=(size_t)latitude_nmea/LATITUDE_DIV_FACTOR; /*se obtiene grados a partir del dato de nmea*/

	minutes_lat=(latitude_nmea-degree*LATITUDE_DIV_FACTOR)/DEGREE_TO_MINUTES_FACTOR; /*se convierte los minutes a grados*/

	degree=degree+minutes_lat;

	if(strchr(cardinal,LATITUDE_CARDINAL_S)!=NULL){ /*verifica si es norte o sur y pone el signo*/
		degree=degree*-1;
	}
	rmc->latitude=degree;


	return ST_OK;
	
}


status_t nmea_rmc_load_longitude(const char *field,const char *cardinal,rmc_t *rmc)
{
	double longitude_nmea;
	double degree;
	double minutes_long;
	char *temp;

	if(field==NULL||rmc==NULL){
		return ST_ERROR_NULL_POINTER;
	}

	longitude_nmea=strtod(field,&temp);

	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_LONGITUDE_CONVERSION;
	}


	degree=(size_t)longitude_nmea/LONGITUDE_DIV_FACTOR; /*se obtiene grados a partir del dato de nmea*/

	minutes_long=(longitude_nmea-degree*LONGITUDE_DIV_FACTOR)/DEGREE_TO_MINUTES_FACTOR; /*se convierte los minutes a grados*/

	degree=degree+minutes_long;

	if(strchr(cardinal,LONGITUDE_CARDINAL_W)!=NULL){ /*verifica si es oeste o este y pone el signo*/
		degree=degree*-1;
	}
	rmc->longitude=degree;


	return ST_OK;

}

status_t nmea_rmc_load_to_rmc_t(const char *sentence,rmc_t *rmc)
{
	status_t st;
	char **fields;
	size_t length;

	st=split_strpbrk(sentence,DELIMITER,&fields,&length);
	if(st!=ST_OK)
	{
		return st;
	}
	st=nmea_rmc_load_fix_hour(fields[RMC_FIX_HOUR_POS],rmc);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_rmc_load_date(fields[RMC_DATE_POS],rmc);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_rmc_load_latitude(fields[RMC_LATITUDE_POS],fields[RMC_LATITUDE_CARD_POS],rmc);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_rmc_load_longitude(fields[RMC_LONGITUDE_POS],fields[RMC_LONGITUDE_CARD_POS],rmc);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	
	return ST_OK;

}