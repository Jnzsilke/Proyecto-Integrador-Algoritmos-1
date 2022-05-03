#include "ubx_nav_posllh.h"
#include <stdio.h>
#include <stdlib.h>

status_t ubx_nav_posllh_load_longitude(unsigned char *sentence,ubx_nav_posllh_t *ubx_nav_posllh){
	status_t st;
	double longitude;

	if(!sentence || !ubx_nav_posllh){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=little_endian_to_double(&longitude,sentence+UBX_NAV_POSLLH_LONGITUDE_POS,UBX_NAV_POSLLH_LONGITUDE_BYTES))!= ST_OK){
		return st;
	}
	ubx_nav_posllh->longitude=longitude*UBX_DEG_SCALE;
	return ST_OK;
}

status_t ubx_nav_posllh_load_latitude(unsigned char *sentence,ubx_nav_posllh_t *ubx_nav_posllh){
	status_t st;
	double latitude;

	if(!sentence || !ubx_nav_posllh){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=little_endian_to_double(&latitude,sentence+UBX_NAV_POSLLH_LATITUDE_POS,UBX_NAV_POSLLH_LATITUDE_BYTES))!= ST_OK){
		return st;
	}

	ubx_nav_posllh->latitude=latitude*UBX_DEG_SCALE;
	return ST_OK;
}

status_t ubx_nav_posllh_load_elevation(unsigned char *sentence,ubx_nav_posllh_t *ubx_nav_posllh){
	status_t st;
	double elevation;
	if(!sentence || !ubx_nav_posllh){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=little_endian_to_double(&elevation,sentence+UBX_NAV_POSLLH_ELEVATION_POS,UBX_NAV_POSLLH_ELEVATION_BYTES))!= ST_OK){
		return st;
	}

	ubx_nav_posllh->elevation=elevation;
	return ST_OK;
}

status_t ubx_nav_posllh_load_to_ubx_nav_posllh_t(unsigned char * sentence, ubx_nav_posllh_t *ubx_nav_posllh){
	status_t st;
	
	if(!sentence || !ubx_nav_posllh){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=ubx_nav_posllh_load_longitude(sentence,ubx_nav_posllh))!=ST_OK){
		return st;
	}

	if((st=ubx_nav_posllh_load_latitude(sentence,ubx_nav_posllh))!=ST_OK){
		return st;
	}

	if((st=ubx_nav_posllh_load_elevation(sentence,ubx_nav_posllh))!=ST_OK){
		return st;
	}

	return ST_OK;
}