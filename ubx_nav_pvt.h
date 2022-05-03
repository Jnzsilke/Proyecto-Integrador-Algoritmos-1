#ifndef UBX_NAV_PVT__H
#define UBX_NAV_PVT__H 

#include "utilities.h"
#include "types.h"

#define UBX_NAV_PVT_LONGITUDE_POS 30
#define UBX_NAV_PVT_LONGITUDE_BYTES 4
#define UBX_NAV_PVT_LATITUDE_POS 34
#define UBX_NAV_PVT_LATITUDE_BYTES 4
#define UBX_NAV_PVT_ELEVATION_POS 40
#define UBX_NAV_PVT_ELEVATION_BYTES 4
#define UBX_NAV_PVT_YEAR_POS 10
#define UBX_NAV_PVT_YEAR_BYTES 2
#define UBX_NAV_PVT_MONTH_POS 12
#define UBX_NAV_PVT_DAY_POS 13
#define UBX_NAV_PVT_HOUR_POS 14
#define UBX_NAV_PVT_MINUTE_POS 15
#define UBX_NAV_PVT_SECOND_POS 16
#define UBX_NAV_PVT_FIX_TYPE_POS 26
#define UBX_NAV_PVT_FLAGS_POS 27
#define UBX_NAV_PVT_FIX_STATUS_MASK 0x01
#define UBX_NAV_PVT_NUM_SATELITE_POS 29





#define UBX_DEG_SCALE 0.00000001

typedef enum{
	UBX_PVT_NO_FIX,
	UBX_PVT_FIX_DEAD_RECKONING,
	UBX_PVT_FIX_2D,
	UBX_PVT_FIX_3D,
	UBX_PVT_FIX_COMBINED,
	UBX_PVT_FIX_TIME
}ubx_nav_pvt_fix_t;

typedef struct{
	timestamp_day_t fix_hour;
	timestamp_date_t date;
	double latitude;
	double longitude;
	double elevation;
	ubx_nav_pvt_fix_t fix_type;
	bool_t fix_status;
	unsigned char num_satelite;
}ubx_nav_pvt_t;

status_t ubx_nav_pvt_load_to_ubx_nav_pvt_t( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_num_satelite( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_fix_status( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_fix_type( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_fix_hour( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_date( unsigned char * sentence, ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_elevation( unsigned char *sentence,ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_latitude( unsigned char *sentence,ubx_nav_pvt_t *ubx_nav_pvt);
status_t ubx_nav_pvt_load_longitude( unsigned char *sentence,ubx_nav_pvt_t *ubx_nav_pvt);

#endif