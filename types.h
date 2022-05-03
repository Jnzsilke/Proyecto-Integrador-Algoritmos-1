
#ifndef TYPES__H
#define TYPES__H
#include <stdio.h>
#include "config.h" 

typedef enum{
				

				ST_CMD_ARG_NEED_HELP,
				ST_ERROR_INVALID_CLA_INPUT=0,
				ST_ERROR_INVALID_CLA_ARG_NUM,
				ST_ERROR_CLA_NO_INPUT,
				ST_ERROR_INVALID_CHECKSUM_IN_SENTENCE,
				ST_ERROR_NO_CHECKSUM_TOKEN_FOUND,
				ST_ERROR_INVALID_CHECKSUM_VALUE,
				

				ST_ERROR_INVALID_DATE=0,
				ST_ERROR_RMC_STATUS,

				ST_ERROR_INVALID_FIELD_POS,
				ST_ERROR_INVALID_FIX_HOUR,
				ST_ERROR_INVALID_LATITUDE_CONVERSION,
				ST_ERROR_INVALID_LONGITUDE_CONVERSION,
				ST_ERROR_INVALID_QUALITY_FIX_CONVERSION,
				ST_ERROR_INVALID_SATELITE_CONVERSION,
				ST_ERROR_INVALID_HDOP_CONVERSION,
				ST_ERROR_INVALID_ELEVATION_CONVERSION,
				ST_ERROR_INVALID_GEOID_SEPARATION_CONVERSION,

				ST_ERROR_INVALID_MAXLEN_CONVERSION,

				ST_ERROR_FIX_STATUS_NOT_SET,

				ST_ERROR_FSEEK,
				
				ST_ERROR_IO,
				ST_ERROR_CANNOT_CREATE_NODE,
				ST_ERROR_CANNOT_CREATE_LIST,
				ST_ERROR_NO_MEMORY,
				ST_ERROR_NULL_POINTER,
				ST_ERROR_CANNOT_OPEN_INPUT_FILE,
				ST_ERROR_CANNOT_OPEN_OUTPUT_FILE,
				ST_ERROR_CANNOT_OPEN_LOG_FILE,
				ST_OK

}status_t;

typedef enum{

				QF_INVALID=0,
				QF_FIX_GPS=1,
				QF_FIX_DGPS=2,
				QF_FIX_PPS=3,
				QF_REAL_TIME_KINEMATIC=4,
				QF_FLOAT_RTK=5,
				QF_ESTIMATED_DEAD_RECK=6,
				QF_MANUAL=7,
				QF_SIMULATION=8


}qual_fix_t;

typedef enum{
	ST_ACTIVE,
	ST_VOID
}rmc_status_t;

typedef enum{
	FALSE=0,TRUE=1


}bool_t;

typedef enum{

	GP_GGA,
	GP_RMC,
	GP_ZDA,
	GP_UNKNOWN
}nmea_sentence_t;

typedef enum{

	UBX_NAV_POSLLH,
	UBX_NAV_PVT,
	UBX_TIM_TOS,
	UBX_UNKNOWN
}ubx_sentence_t;


typedef enum{
  
  ARG_HELP_SHORT=0,
  ARG_HELP_LONG=1,
  ARG_NAME_SHORT=2,
  ARG_NAME_LONG=3,
  ARG_PROTOCOL_SHORT=4,
  ARG_PROTOCOL_LONG=5,
  ARG_INFILE_SHORT=6,
  ARG_INFILE_LONG=7,
  ARG_OUTFILE_SHORT=8,
  ARG_OUTFILE_LONG=9,
  ARG_LOGFILE_SHORT=10,
  ARG_LOGFILE_LONG=11,
  ARG_MAXLEN_SHORT=12,
  ARG_MAXLEN_LONG=13,
  ARG_ERROR=14
  
} arg_t;

typedef struct 
{
	unsigned char * sentence;
	size_t size;
}unsigned_sentence_t;


typedef struct{

	size_t hour;
	size_t minutes;
	double seconds;

}timestamp_day_t;

typedef struct {

	size_t day;
	size_t month;
	size_t year;
	
}timestamp_date_t;

typedef struct{
	timestamp_day_t fix_hour;
	double latitude;
	double longitude;
	qual_fix_t quality_fix;
	size_t num_satelite;
	float hdop;
	float elevation;
	float geoid_separation;
}gga_t;

typedef struct{
	timestamp_day_t fix_hour;
	timestamp_date_t date;
	double latitude;
	double longitude;
	rmc_status_t rmc_status;
}rmc_t;

typedef struct{

	timestamp_day_t hms;
	timestamp_date_t date;
	
}zda_t;

typedef struct{
	char *name;
	timestamp_date_t date;
	timestamp_day_t day;

}gpx_metadata_t;

typedef struct{

	double longitude;
	double latitude;
	float elevation;
	timestamp_date_t date;
	timestamp_day_t day;
	
}trackpoint_t;

struct node{

	void *data;
	struct node *next;

};
typedef struct node *List;

typedef enum 
{
	PROTOCOL_NMEA=0,
	PROTOCOL_UBX=1,
	PROTOCOL_AUTO=2,
	PROTOCOL_UNKNOWN=3

}protocol_t;

typedef struct{

	char *name;
	protocol_t protocol;
	char *infile;
	char *outfile;
	char *logfile;
	size_t maxlen;

}cla_t;


#endif