#ifndef CONFIG__H
#define CONFIG__H

#include <stdio.h>

#define CMD_ARG_FLAG_HELP_SHORT				"-h"
#define CMD_ARG_FLAG_HELP_LONG				"--help"
#define CMD_ARG_FLAG_METADATA_NAME_SHORT	"-n"
#define CMD_ARG_FLAG_METADATA_NAME_LONG		"--name"
#define CMD_ARG_FLAG_PROTOCOL_SHORT			"-p"
#define CMD_ARG_FLAG_PROTOCOL_LONG			"--protocol"
#define CMD_ARG_FLAG_INPUT_FILE_SHORT		"-i"
#define CMD_ARG_FLAG_INPUT_FILE_LONG		"--infile"
#define CMD_ARG_FLAG_OUTPUT_FILE_SHORT		"-O"
#define CMD_ARG_FLAG_OUTPUT_FILE_LONG		"--outfile"
#define CMD_ARG_FLAG_LOG_FILE_SHORT			"-l"
#define CMD_ARG_FLAG_LOG_FILE_LONG			"--logfile"
#define CMD_ARG_FLAG_MAXLEN_SHORT			"-m"
#define CMD_ARG_FLAG_MAXLEN_LONG			"--maxlen"

#define USR_MSG_PROGRAM_INVOCATION "La forma de invocar este programa es: ..."
#define USR_MSG_FLAG_OPTION  "OPCIONES(flags)"
#define USR_MSG_FLAG_HELP "Imprime mensaje de ayuda."
#define USR_MSG_FLAG_NAME "Carga el archivo destino con el nombre del usuario. Maxima cantidad de caracteres: "
#define USR_MSG_FLAG_PROTOCOL "Se indica el protocolo a leer. Puede tomar los valores nmea, ubx o auto. La opcion auto, hara que el programa detecte el protocolo de forma automatica."
#define USR_MSG_FLAG_INFILE "Indica el nombre del archivo de entrada."
#define USR_MSG_FLAG_OUTFILE "Indica el nombre del archivo de salida (archivo gpx)."
#define USR_MSG_FLAG_LOGFILE "Indica el nombre del archivo log."
#define USR_MSG_FLAG_MAXLEN "Indica la maxima cantidad e mensajes que se pueden almacenar en una lista."

#define USR_MSG_CLA_RESTRICTION_REPEAT "Repetir un flag del mismo tipo es un error."
#define USR_MSG_CLA_RESTRICTION_HELP "Ingresar el flag -h,--help o ambos imprimira directamente este mensaje de ayuda, sin importar los otros flags."




#define DELIMITER ","

#define DEFAULT_METADATA_NAME "Default" 
#define MAX_METADATA_NAME 10
#define NMEA_PROTOCOL_NAME "nmea"
#define UBX_PROTOCOL_NAME "ubx"
#define AUTO_PROTOCOL_NAME "auto"

#define GPX_LABEL_HEADER 		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
#define GPX_ELEMENT_LABEL_START "<gpx version=\"1.1\" creator=\"95.11 TP1 - Tracker\" xmlns=\"http://www.topografix.com/GPX/1/1\">"
#define GPX_ELEMENT_LABEL_END	"</gpx>"

#define GPX_LABEL_START_METADATA	"<metadata>"
#define GPX_LABEL_START_NAME 		"<name>"
#define GPX_LABEL_START_TIME 		"<time>"
#define GPX_LABEL_START_TRK 		"<trk>"
#define GPX_LABEL_START_TRKSEG		"<trkseg>"	

#define GPX_LABEL_START_ELE			"<ele>"

#define GPX_LABEL_END_METADATA	"</metadata>"
#define GPX_LABEL_END_NAME 		"</name>"
#define GPX_LABEL_END_TIME 		"</time>"
#define GPX_LABEL_END_TRK 		"</trk>"
#define GPX_LABEL_END_TRKSEG	"</trkseg>"	
#define GPX_LABEL_END_TRKPT		"</trkpt>"
#define GPX_LABEL_END_ELE		"</ele>"



#endif