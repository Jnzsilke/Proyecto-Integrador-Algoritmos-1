#ifndef LOGS__H
#define LOGS__H 

#include "types.h"


extern FILE *log_file;

#define LOG_WARN_MSG "[WARNI]: "
#define LOG_ERR_MSG "[ERROR]: "
#define LOG_DEBUG_MSG "[DEBUG]: "

#define LOG_DEBUG_LIST_CREATE_MSG "Se creo una lista."

#define LOG_DEBUG_LIST_APPEND_MSG "Se ha agregado un mensaje a la lista."
#define LOG_WARN_LIST_APPEND_MSG "No pudo agregarse el mensaje a la lista."

#define LOG_ERROR_CLOSE_LOG_FILE_MSG "No pudo cerrarse el archivo de logs."

#define LOG_DEBUG_OPEN_OUTPUT_FILE_MSG "Se abrio un archivo de salida."
#define LOG_ERROR_OPEN_OUTPUT_FILE_MSG "No pudo abrirse el archivo de salida."
#define LOG_ERROR_CLOSE_OUTPUT_FILE_MSG "No pudo cerrarse el archivo de salida."

#define LOG_DEBUG_OPEN_INPUT_FILE_MSG "Se abrio un archivo de entrada."
#define LOG_ERROR_OPEN_INPUT_FILE_MSG "No pudo abrirse el archivo de entrada."
#define LOG_ERROR_CLOSE_INPUT_FILE_MSG "No pude cerrarse el archivo de entrada."

#define LOG_ERROR_PROTOCOL_DETECTION_MSG "No pudo detectarse el protocolo."
#define LOG_ERROR_READLINE_MSG "No pudo leerse una sentencia correctamente."

#define LOG_DEBUG_NMEA_PROTOCOL_DETECTED_MSG "Se detecto el protocolo NMEA-0183."
#define LOG_DEBUG_UBX_PROTOCOL_DETECTED_MSG "Se detecto el protocolo UBX."
#define LOG_DEBUG_UNKNOWN_PROTOCOL_MSG "Protocolo desconocido."
#define LOG_DEBUG_PRINT_TRACKPOINTS_MSG "Se imprimen los trackpoints en el archivo GPX."
#define LOG_DEBUG_PRINT_FOOTER_MSG "Se imprimen el footer."
#define LOG_DEBUG_INPUT_FILE_CLOSE_MSG "Se cerro el archivo de entrada."
#define LOG_DEBUG_OUTPUT_FILE_CLOSE_MSG "Se cerro el archivo de salida."
#define LOG_DEBUG_PRINT_HEADER_MSG "Se imprimio el encabezado."
#define LOG_DEBUG_CLOSE_ALL_FILES_MSG "Se cerraron todos los archivos."

#define LOG_ERROR_NOT_NMEA_SENTENCE_MSG "Sentencia NMEA mal formada."
#define LOG_DEBUG_CALCULATE_CHECKSUM_MSG "Se calcula el checksum."
#define LOG_DEBUG_VERIFY_CHECKSUM_MSG "Se verifica que el checksum sea correcto."
#define LOG_ERROR_INCORRECT_CHECKSUM_MSG "El checksum es incorrecto."
#define LOG_ERROR_CORRECT_CHECKSUM_MSG "El checksum es correcto."
#define LOG_DEBUG_ID_NMEA_SENTENCE_MSG "Se identifica el tipo de sentencia NMEA."
#define LOG_DEBUG_NMEA_GGA_SENTENCE_MSG "Se identifica una sentencia NMEA de tipo GGA."
#define LOG_DEBUG_NMEA_RMC_SENTENCE_MSG "Se identifica una sentencia NMEA de tipo RMC."
#define LOG_DEBUG_NMEA_ZDA_SENTENCE_MSG "Se identifica una sentencia NMEA de tipo ZDA."
#define LOG_WARN_UNKNOWN_SENTENCE_MSG "No se reconoce el tipo de sentencia."
#define LOG_WARN_GGA_QF_INVALID_MSG "Calidad del fix invalida. Se descarta mensaje GGA."

#define LOG_DEBUG_UBX_BUFFER_READ_MSG "Mensaje leido correctamente."
#define LOG_DEBUG_ID_UBX_SENTENCE_MSG "Se identifica el tipo de sentencia UBX."
#define LOG_DEBUG_UBX_NAV_POSLLH_SENTENCE_MSG "Se identifica una sentencia UBX de tipo UBX_NAV_POSLLH."
#define LOG_DEBUG_UBX_NAV_PVT_SENTENCE_MSG "Se identifica una sentencia UBX de tipo UBX_NAV_PVT."
#define LOG_DEBUG_UBX_TIM_TOS_SENTENCE_MSG "Se identifica una sentencia UBX de tipo UBX_TIM_TOS."


typedef enum{
	LOG_WARN,
	LOG_ERR,
	LOG_DEBUG
}log_lvl;

status_t print_log(FILE * fo, log_lvl lvl,const char* msg);

#endif