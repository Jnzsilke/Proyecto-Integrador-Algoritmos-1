#ifndef NMEA_GGA__H
#define NMEA_GGA__H
#include "types.h"

#define MAX_AUX_DATA 20

#define GGA_FIX_HOUR_POS		1
#define GGA_LATITUDE_POS		2
#define GGA_LATITUDE_CARD_POS	3	
#define GGA_LONGITUDE_POS		4
#define GGA_LONGITUDE_CARD_POS	5
#define	GGA_QUALFIX_POS			6
#define GGA_SATELITNUM_POS 		7		
#define GGA_HDOP_POS			8			
#define GGA_ELEVAT_POS 			9	
#define GGA_GEOID_SEP_POS		11

#define HOUR_DIV_FACTOR 10000
#define MINUTE_DIV_FACTOR 100
#define LATITUDE_DIV_FACTOR 100
#define LATITUDE_CARDINAL_S 'S'
#define LONGITUDE_DIV_FACTOR 100
#define LONGITUDE_CARDINAL_W 'W'
#define DEGREE_TO_MINUTES_FACTOR 60

status_t nmea_gga_load_fix_hour(const char *field,gga_t *gps);
status_t nmea_gga_load_latitude(const char *field,const char *cardinal,gga_t *gps);
status_t nmea_gga_load_longitude(const char *field,const char *cardinal,gga_t *gps);
status_t nmea_gga_load_quality_fix(const char *field,gga_t *gps);
status_t nmea_gga_load_num_satelite(const char *field,gga_t *gps);
status_t nmea_gga_load_hdop(const char *field,gga_t *gps);
status_t nmea_gga_load_elevation(const char *field,gga_t *gps);
status_t nmea_gga_load_geoid_separation(const char *field,gga_t *gps);
status_t nmea_gga_load_to_gga_t(const char *field,gga_t *gps);


#endif

