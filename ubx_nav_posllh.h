#ifndef UBX_NAV_POSLLH__H
#define UBX_NAV_POSLLH__H 

#include "utilities.h"
#include "types.h"

#define UBX_NAV_POSLLH_LONGITUDE_POS 10
#define UBX_NAV_POSLLH_LONGITUDE_BYTES 4
#define UBX_NAV_POSLLH_LATITUDE_POS 14
#define UBX_NAV_POSLLH_LATITUDE_BYTES 4
#define UBX_NAV_POSLLH_ELEVATION_POS 22
#define UBX_NAV_POSLLH_ELEVATION_BYTES 4
#define UBX_DEG_SCALE 0.00000001

typedef struct{
	double latitude;
	double longitude;
	double elevation;
}ubx_nav_posllh_t;

status_t ubx_nav_posllh_load_longitude(unsigned char *sentence,ubx_nav_posllh_t *ubx_nav_posllh);
status_t ubx_nav_posllh_load_latitude(unsigned char *sentence,ubx_nav_posllh_t *ubx_nav_posllh);
status_t ubx_nav_posllh_load_elevation(unsigned char *sentence,ubx_nav_posllh_t *ubx_nav_posllh);
status_t ubx_nav_posllh_load_to_ubx_nav_posllh_t(unsigned char * sentence, ubx_nav_posllh_t *ubx_nav_posllh);


#endif