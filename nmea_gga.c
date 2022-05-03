#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nmea_gga.h"
#include "types.h"
#include "utilities.h"
#include "config.h"



status_t nmea_gga_load_fix_hour(const char *field,gga_t *gps)
{
	size_t hour;
	size_t minutes;
	
	double seconds; /*se va a convertir el numero sobre esta variable*/
	char *temp;

	if(field==NULL||gps==NULL){
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

	gps->fix_hour.hour=hour;
	gps->fix_hour.minutes=minutes;
	gps->fix_hour.seconds=seconds;

	return	 ST_OK;

}

status_t nmea_gga_load_latitude(const char *field,const char *cardinal,gga_t *gps)
{

	double latitude_nmea;
	double degree;
	double minutes_lat;
	char *temp;

	if(field==NULL||gps==NULL){
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
	gps->latitude=degree;


	return ST_OK;
	
}


status_t nmea_gga_load_longitude(const char *field,const char *cardinal,gga_t *gps)
{
	double longitude_nmea;
	double degree;
	double minutes_long;
	char *temp;

	if(field==NULL||gps==NULL){
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

	gps->longitude=degree;


	return ST_OK;

}

status_t nmea_gga_load_quality_fix(const char *field,gga_t *gps)
{
	qual_fix_t quality_fix;
	char *temp;

	quality_fix=strtoul(field,&temp,10);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_QUALITY_FIX_CONVERSION;
	}

	gps->quality_fix=quality_fix;

	return ST_OK;


}
status_t nmea_gga_load_num_satelite(const char *field,gga_t *gps)
{
	size_t num_satelite;
	char *temp;


	if(field==NULL||gps==NULL){
		return ST_ERROR_NULL_POINTER;
	}

	num_satelite=strtoul(field,&temp,10);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_SATELITE_CONVERSION;
	}


	gps->num_satelite=num_satelite;

	return ST_OK;

}

status_t nmea_gga_load_hdop(const char *field,gga_t *gps)
{
	float hdop;
	char *temp;

	if(field==NULL||gps==NULL){
		return ST_ERROR_NULL_POINTER;
	}


	hdop=strtod(field,&temp);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_HDOP_CONVERSION;
	}

	gps->hdop=hdop;

	return ST_OK;


}

status_t nmea_gga_load_elevation(const char *field,gga_t *gps)
{
	float elevation;
	char *temp;

	if(field==NULL||gps==NULL){
		return ST_ERROR_NULL_POINTER;
	}


	elevation=strtod(field,&temp);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_ELEVATION_CONVERSION;
	}

	gps->elevation=elevation;

	return ST_OK;


}

status_t nmea_gga_load_geoid_separation(const char *field,gga_t *gps)
{
	float geoid_separation;
	char *temp;

	if(field==NULL||gps==NULL){
		return ST_ERROR_NULL_POINTER;
	}

	geoid_separation=strtod(field,&temp);
	if(*temp&&*temp!='\n'){
		return ST_ERROR_INVALID_GEOID_SEPARATION_CONVERSION;
	}

	gps->geoid_separation=geoid_separation;

	return ST_OK;

}

status_t nmea_gga_load_to_gga_t(const char *sentence,gga_t *gps)
{
	status_t st;
	char **fields;
	size_t length;

	st=split_strpbrk(sentence,DELIMITER,&fields,&length);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_gga_load_fix_hour(fields[GGA_FIX_HOUR_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_gga_load_latitude(fields[GGA_LATITUDE_POS],fields[GGA_LATITUDE_CARD_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}

	st=nmea_gga_load_longitude(fields[GGA_LONGITUDE_POS],fields[GGA_LONGITUDE_CARD_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}

	st=nmea_gga_load_quality_fix(fields[GGA_QUALFIX_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_gga_load_num_satelite(fields[GGA_SATELITNUM_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_gga_load_hdop(fields[GGA_HDOP_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_gga_load_elevation(fields[GGA_ELEVAT_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}
	st=nmea_gga_load_geoid_separation(fields[GGA_GEOID_SEP_POS],gps);
	if(st!=ST_OK)
	{
		destroy_string_array(&fields,&length);
		return st;
	}

	

	return ST_OK;

}



