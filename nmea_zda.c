#include "nmea_zda.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "utilities.h"
#include "config.h"

status_t nmea_zda_load_hour(const char *field,zda_t *zda){
	unsigned int hour;
	unsigned int minutes;
	double seconds; /*se va a convertir el numero sobre esta variable*/
	char *temp;

	if(field==NULL||zda==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	seconds=strtod(field,&temp);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_FIX_HOUR;
	}

	hour=seconds/NMEA_ZDA_HOUR_DIV_FACTOR;
	seconds=seconds-hour*NMEA_ZDA_HOUR_DIV_FACTOR;
	minutes=seconds/NMEA_ZDA_MINUTE_DIV_FACTOR;
	seconds=seconds-minutes*NMEA_ZDA_MINUTE_DIV_FACTOR;

	zda->hms.hour=hour;
	zda->hms.minutes=minutes;
	zda->hms.seconds=seconds;

	return ST_OK;
}

status_t nmea_zda_load_day(const char *field,zda_t *zda){
	unsigned int day;
	char *temp;

	if(field==NULL||zda==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	day=strtoul(field,&temp,10);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_FIX_HOUR;
	}

	zda->date.day=day;

	return ST_OK;
}

status_t nmea_zda_load_month(const char *field,zda_t *zda){
	unsigned int month;
	char *temp;

	if(field==NULL||zda==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	month=strtoul(field,&temp,10);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_FIX_HOUR;
	}

	zda->date.month=month;

	return ST_OK;
}

status_t nmea_zda_load_year(const char *field,zda_t *zda){
	unsigned int year;
	char *temp;

	if(field==NULL||zda==NULL){
		return ST_ERROR_NULL_POINTER;
	}
	year=strtoul(field,&temp,10);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_FIX_HOUR;
	}

	zda->date.year=year;

	return ST_OK;
}

status_t nmea_zda_load_to_zda_t(const char *sentence,zda_t *zda)
{
	status_t st;
	char **fields;
	size_t length;

	st=split_strpbrk(sentence,DELIMITER,&fields,&length);
	if(st!=ST_OK){
		return st;
	}

	st=nmea_zda_load_hour(fields[ZDA_HOUR_POS],zda);
	if(st!=ST_OK){
		return st;
	}

	st=nmea_zda_load_day(fields[ZDA_DAY_POS],zda);
	if(st!=ST_OK){
		return st;
	}

	st=nmea_zda_load_month(fields[ZDA_MONTH_POS],zda);
	if(st!=ST_OK){
		return st;
	}

	st=nmea_zda_load_day(fields[ZDA_DAY_POS],zda);
	if(st!=ST_OK){
		return st;
	}

	return ST_OK;

}