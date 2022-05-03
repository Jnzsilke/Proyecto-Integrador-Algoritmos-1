#ifndef NMEA__H
#define NMEA__H
#include <stdio.h>
#include "types.h"


#define CHECK_SUM_TOKEN '*'
#define MAX_CHECKSUM_LEN 5
#define SENTENCE_START 1
#define SENTENCE_GGA "GGA"
#define SENTENCE_RMC "RMC"
#define SENTENCE_ZDA "ZDA"
#define ELEVATION_ZERO 0

status_t nmea_get_checksum_from_sentence(const char *sentence,unsigned long int* checksum);
status_t nmea_calculatechecksum(const char *sentence,unsigned char *checksum);
status_t nmea_check(const char *sentence,const char *sentence_type);
status_t nmea_sentence_identifier(const char *sentence,nmea_sentence_t *gp);
status_t nmea_to_track_to_gpx(const char *sentence,trackpoint_t *track,List *List);


#endif
