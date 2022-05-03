#ifndef UBX__H
#define UBX__H 
#include <stdio.h>

#include "types.h"


#define BUFFER_SIZE 150

#define UBX_ID_POS 3
#define UBX_ID_NAV_POSLLH 0x02
#define UBX_ID_NAV_PVT 0x07
#define UBX_ID_TIM_TOS 0x12
#define UBX_NAV_POSLLH_PAYLOAD_LENGTH 28
#define UBX_NAV_PVT_PAYLOAD_LENGTH 92
#define UBX_TIM_TOS_PAYLOAD_LENGTH 56
#define UBX_CHECKSUM_FIRST_BYTE_POS 2
#define UBX_CHECKSUM_LENGTH_NO_PAYLOAD 4
#define UBX_PAYLOAD_LENGTH_BYTES 2
#define UBX_PAYLOAD_POS 6
#define UBX_SYNC_1 0xB5
#define UBX_SYNC_2 0x62

status_t ubx_get_sentence(FILE * input_file,unsigned char **sentence, bool_t *eof);
status_t ubx_sentence_identifier( unsigned char *sentence,ubx_sentence_t * ubx);
status_t ubx_calculate_checksum( unsigned char * sentence, unsigned char * ck_a, unsigned char *ck_b,size_t checksum_length);
status_t ubx_check( unsigned char* sentence,size_t payload_length);
status_t ubx_to_track_to_gpx( unsigned char *sentence,trackpoint_t *track,List *list);

#endif