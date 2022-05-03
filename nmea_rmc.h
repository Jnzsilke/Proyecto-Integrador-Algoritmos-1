#ifndef NMEA_RMC__H
#define NMEA_RMC__H 
#include "utilities.h"
#include "types.h"

#define RMC_FIX_HOUR_POS		1
#define RMC_STATUS_POS			2
#define RMC_LATITUDE_POS		3
#define RMC_LATITUDE_CARD_POS	4	
#define RMC_LONGITUDE_POS		5
#define RMC_LONGITUDE_CARD_POS	6
#define RMC_DATE_POS			9

#define RMC_DAY_DIV_FACTOR 10000
#define RMC_MONTH_DIV_FACTOR 100
#define RMC_STATUS_ACTIVE 'A'
#define RMC_STATUS_VOID 'V'
#define RMC_YEAR_SUM 2000
#define HOUR_DIV_FACTOR 10000
#define MINUTE_DIV_FACTOR 100
#define LATITUDE_DIV_FACTOR 100
#define LATITUDE_CARDINAL_S 'S'
#define LONGITUDE_DIV_FACTOR 100
#define LONGITUDE_CARDINAL_W 'W'
#define DEGREE_TO_MINUTES_FACTOR 60

status_t nmea_rmc_load_fix_hour(const char *field,rmc_t *rmc);
status_t nmea_rmc_load_latitude(const char *field,const char *cardinal,rmc_t *rmc);
status_t nmea_rmc_load_longitude(const char *field,const char *cardinal,rmc_t *rmc);
status_t nmea_rmc_load_to_rmc_t(const char *sentence,rmc_t *rmc);
status_t nmea_rmc_load_status(const char *field,rmc_t *rmc);
status_t nmea_rmc_load_date(const char *field,rmc_t *rmc);


#endif