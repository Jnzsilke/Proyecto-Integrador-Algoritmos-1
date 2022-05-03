#ifndef NMEA_ZDA__H
#define NMEA_ZDA__H 

#include "types.h"

#define ZDA_HOUR_POS		1
#define ZDA_DAY_POS			2
#define ZDA_MONTH_POS		3
#define ZDA_YEAR_POS		4


#define NMEA_ZDA_HOUR_DIV_FACTOR 10000
#define NMEA_ZDA_MINUTE_DIV_FACTOR 100

status_t nmea_zda_load_hour(const char *field,zda_t *zda);
status_t nmea_zda_load_day(const char *field,zda_t *zda);
status_t nmea_zda_load_month(const char *field,zda_t *zda);
status_t nmea_zda_load_year(const char *field,zda_t *zda);
status_t nmea_zda_load_to_zda_t(const char *sentence,zda_t *zda);

#endif