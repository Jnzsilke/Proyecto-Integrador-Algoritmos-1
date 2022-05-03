#ifndef GNSS__H
#define GNSS__H

#include "ADT_List.h"
#include "nmea_gga.h"
#include "nmea_rmc.h"
#include "nmea_zda.h"
#include "nmea.h"
#include "types.h"
#include "config.h"
#include "errors.h"
#include "utilities.h"
#include "args.h"
#include "logs.h"
#include "ubx.h"
#include "output.h"

#define LINES_TO_READ 100
#define MAX_MSG_TO_SAVE 5
#define DEFAULT_LOG_FILE "tp2.log"
#define DEFAULT_OUTPUT_FILE "tp2.gpx"
#define DEFAULT_INPUT_FILE "STDIN"
#define MAX_BITS_CHECK 10
#define NMEA_IDENTIFIER_MONEY 0x24
#define NMEA_IDENTIFIER_G	0x47
#define NMEA_IDENTIFIER_P	0x50



#endif