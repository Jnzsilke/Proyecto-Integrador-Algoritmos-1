#include "ubx_nav_pvt.h"
#include <stdio.h>
#include <stdlib.h>

status_t ubx_nav_pvt_load_longitude(unsigned char *sentence,ubx_nav_pvt_t *ubx_nav_pvt){
	status_t st;
	double longitude;

	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=little_endian_to_double(&longitude,sentence+UBX_NAV_PVT_LONGITUDE_POS,UBX_NAV_PVT_LONGITUDE_BYTES))!= ST_OK){
		return st;
	}

	ubx_nav_pvt->longitude=longitude*UBX_DEG_SCALE;
	return ST_OK;
}

status_t ubx_nav_pvt_load_latitude(unsigned char *sentence,ubx_nav_pvt_t *ubx_nav_pvt){
	status_t st;
	double latitude;

	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=little_endian_to_double(&latitude,sentence+UBX_NAV_PVT_LATITUDE_POS,UBX_NAV_PVT_LATITUDE_BYTES))!= ST_OK){
		return st;
	}

	ubx_nav_pvt->latitude=latitude*UBX_DEG_SCALE;
	return ST_OK;
}

status_t ubx_nav_pvt_load_elevation(unsigned char *sentence,ubx_nav_pvt_t *ubx_nav_pvt){
	status_t st;
	double elevation;

	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=little_endian_to_double(&elevation,sentence+UBX_NAV_PVT_ELEVATION_POS,UBX_NAV_PVT_ELEVATION_BYTES))!= ST_OK){
		return st;
	}

	ubx_nav_pvt->elevation=elevation;
	return ST_OK;
}

status_t ubx_nav_pvt_load_date(unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt){
	status_t st;
	timestamp_date_t date;
	unsigned int temp;
	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}


	if((st=little_endian_to_uint(&temp,sentence+UBX_NAV_PVT_YEAR_POS,UBX_NAV_PVT_YEAR_BYTES))!= ST_OK){
		return st;
	}

	date.year=temp;
	date.month=sentence[UBX_NAV_PVT_MONTH_POS];
	date.day=sentence[UBX_NAV_PVT_DAY_POS];

	ubx_nav_pvt->date=date;
	return ST_OK;
}

status_t ubx_nav_pvt_load_fix_hour( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt){
	timestamp_day_t fix_hour;
	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	fix_hour.hour=sentence[UBX_NAV_PVT_HOUR_POS];
	fix_hour.minutes=sentence[UBX_NAV_PVT_MINUTE_POS];
	fix_hour.seconds=sentence[UBX_NAV_PVT_SECOND_POS];

	ubx_nav_pvt->fix_hour=fix_hour;
	return ST_OK;
}

status_t ubx_nav_pvt_load_fix_type(unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt){
	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	ubx_nav_pvt->fix_type = sentence[UBX_NAV_PVT_FIX_TYPE_POS];

	return ST_OK;
}

status_t ubx_nav_pvt_load_fix_status( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt){
	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}
	ubx_nav_pvt->fix_status=sentence[UBX_NAV_PVT_FLAGS_POS]&UBX_NAV_PVT_FIX_STATUS_MASK;
	if(ubx_nav_pvt->fix_status==FALSE){
		return ST_ERROR_FIX_STATUS_NOT_SET;
	}

	return ST_OK;
}


status_t ubx_nav_pvt_load_num_satelite( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt){
	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	ubx_nav_pvt->fix_type = sentence[UBX_NAV_PVT_NUM_SATELITE_POS];

	return ST_OK;
}

status_t ubx_nav_pvt_load_to_ubx_nav_pvt_t( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt){
	status_t st;
	
	if(!sentence || !ubx_nav_pvt){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=ubx_nav_pvt_load_longitude(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_latitude(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_elevation(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_date(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_fix_hour(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_fix_type(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_fix_status(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	if((st=ubx_nav_pvt_load_num_satelite(sentence,ubx_nav_pvt))!=ST_OK){

		return st;
	}

	return ST_OK;
}