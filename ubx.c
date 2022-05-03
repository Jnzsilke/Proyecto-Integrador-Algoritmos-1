#include "ubx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output.h"
#include "ubx_nav_posllh.h"
#include "ubx_nav_pvt.h"
#include "ubx_tim_tos.h"
#include "ADT_List.h"
#include "utilities.h"
#include "logs.h"


status_t ubx_get_sentence(FILE * input_file,unsigned char **sentence, bool_t *eof){

	size_t msg_start, msg_end,bytes_read,sentence_length;
	unsigned char * buffer=(unsigned char *)malloc(sizeof(unsigned char)*BUFFER_SIZE);
	if(!input_file||!sentence||!eof){

		return ST_ERROR_NULL_POINTER;
	}

	if(!buffer){

		return ST_ERROR_NO_MEMORY;
	}
	if((bytes_read=fread(buffer,sizeof(unsigned char),BUFFER_SIZE,input_file))!=BUFFER_SIZE){
		if(feof(input_file)){
			/* busco donde arranca la sentencia */
			for(msg_start=0;!(buffer[msg_start]==UBX_SYNC_1&&buffer[msg_start+1]==UBX_SYNC_2);msg_start++);

			/* busco donde termina la sentencia */
			for(msg_end=msg_start+2;!(buffer[msg_end]==UBX_SYNC_1&&buffer[msg_end+1]==UBX_SYNC_2)&&msg_end!=bytes_read;msg_end++);

			sentence_length = msg_end-msg_start;
			*sentence=(unsigned char*)malloc(sizeof(unsigned char)*sentence_length);
			memmove(*sentence,buffer+msg_start,sentence_length);
			if(!sentence){

				return ST_ERROR_NO_MEMORY;
			}

			if(msg_end==bytes_read){
				*eof=TRUE;
			}else{
				if(fseek(input_file,(bytes_read-sentence_length)*(-1),SEEK_CUR))
				{

					free(buffer);
					return ST_ERROR_FSEEK;
				}
			}

			free(buffer);
			return ST_OK;
		}	
	}

	/* busco donde arranca la sentencia */
	for(msg_start=0;!(buffer[msg_start]==UBX_SYNC_1&&buffer[msg_start+1]==UBX_SYNC_2);msg_start++);

	/* busco donde termina la sentencia */
	for(msg_end=msg_start+2;!(buffer[msg_end]==UBX_SYNC_1&&buffer[msg_end+1]==UBX_SYNC_2);msg_end++);

	sentence_length = msg_end-msg_start;
	*sentence=(unsigned char*)malloc(sizeof(unsigned char)*sentence_length);
	if(!sentence){
		return ST_ERROR_NO_MEMORY;
	}
	memmove(*sentence,buffer+msg_start,sentence_length);
	
	if(fseek(input_file,(BUFFER_SIZE-sentence_length)*(-1),SEEK_CUR))
	{
		free(buffer);
		return ST_ERROR_FSEEK;
	}
	free(buffer);
	return ST_OK;

}

status_t ubx_sentence_identifier(unsigned char *sentence,ubx_sentence_t * ubx)
{
	status_t st;
	if(sentence==NULL||ubx==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	print_log(log_file,LOG_DEBUG,LOG_DEBUG_ID_UBX_SENTENCE_MSG);

	switch(sentence[UBX_ID_POS])
	{
		case UBX_ID_NAV_POSLLH:
			print_log(log_file,LOG_DEBUG,LOG_DEBUG_UBX_NAV_POSLLH_SENTENCE_MSG);
			*ubx=UBX_NAV_POSLLH;
			if((st=ubx_check(sentence,UBX_NAV_POSLLH_PAYLOAD_LENGTH))!=ST_OK)
			{
				return st;
			}
			break;
		case UBX_ID_NAV_PVT:
			print_log(log_file,LOG_DEBUG,LOG_DEBUG_UBX_NAV_PVT_SENTENCE_MSG);
			*ubx=UBX_NAV_PVT;
			if((st=ubx_check(sentence,UBX_NAV_PVT_PAYLOAD_LENGTH))!=ST_OK){	
				return st;
			}
			break;
		case UBX_ID_TIM_TOS:
			print_log(log_file,LOG_DEBUG,LOG_DEBUG_UBX_TIM_TOS_SENTENCE_MSG);
			*ubx=UBX_TIM_TOS;
			if((st=ubx_check(sentence,UBX_TIM_TOS_PAYLOAD_LENGTH))!=ST_OK)
			{	
				return st;
			}

			break;
		default:
			print_log(log_file,LOG_DEBUG,LOG_WARN_UNKNOWN_SENTENCE_MSG);
			*ubx=UBX_UNKNOWN;
			break;
	}

	return ST_OK;
}

status_t ubx_calculate_checksum(unsigned char * sentence, unsigned char * ck_a, unsigned char *ck_b,size_t checksum_length)
{
	size_t i;
	print_log(log_file,LOG_DEBUG,LOG_DEBUG_CALCULATE_CHECKSUM_MSG);

	if(sentence==NULL||ck_a==NULL||ck_b==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}
	for (i= UBX_CHECKSUM_FIRST_BYTE_POS; i<checksum_length;++i)
	{
		*ck_a = *ck_a + sentence[i];
		*ck_b = *ck_b + *ck_a;
	}
	return ST_OK;
}

status_t ubx_check(unsigned char* sentence,size_t payload_length)
{
	unsigned char ck_a=0,ck_b=0;
	size_t ck_a_pos=0, ck_b_pos=0;
	status_t st;

	if(sentence==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	if((st=ubx_calculate_checksum(sentence,&ck_a,&ck_b,UBX_CHECKSUM_FIRST_BYTE_POS+UBX_CHECKSUM_LENGTH_NO_PAYLOAD+payload_length))!= ST_OK)
	{
		return st;
	}
	ck_a_pos = payload_length+UBX_PAYLOAD_POS;
	ck_b_pos = ck_a_pos+1;

	if(sentence[ck_a_pos]!=ck_a || sentence[ck_b_pos]!=ck_b)
	{
		print_log(log_file,LOG_DEBUG,LOG_ERROR_INCORRECT_CHECKSUM_MSG);
		return ST_ERROR_INVALID_CHECKSUM_IN_SENTENCE;
	}
	
	return ST_OK;
}

status_t ubx_to_track_to_gpx(unsigned char *sentence,trackpoint_t *track,List *list)
{
	status_t st;
	ubx_sentence_t ubx_id;
	ubx_nav_posllh_t ubx_nav_posllh;
	ubx_nav_pvt_t ubx_nav_pvt;
	ubx_tim_tos_t ubx_tim_tos;
	if(sentence==NULL||track==NULL)
	{
		return ST_ERROR_NULL_POINTER;
	}

	st=ubx_sentence_identifier(sentence,&ubx_id);
	if(st!=ST_OK)
	{	
		return st;
	}
	
	switch(ubx_id)
	{
		case UBX_NAV_POSLLH:
			if((st=ubx_nav_posllh_load_to_ubx_nav_posllh_t(sentence,&ubx_nav_posllh))!=ST_OK){
				return st;
			}
			track->longitude=ubx_nav_posllh.longitude;
			track->latitude=ubx_nav_posllh.latitude;
			track->elevation=ubx_nav_posllh.elevation;
			ADT_List_append(list,track,trackpoint_dupl);
			break;

		case UBX_TIM_TOS:
			if((st=ubx_tim_tos_load_to_ubx_tim_tos_t(sentence,&ubx_tim_tos))!=ST_OK){
				return st;
			}
			track->date.day=ubx_tim_tos.date.day;
			track->date.month=ubx_tim_tos.date.month;
			track->date.year=ubx_tim_tos.date.year;
			break;

		case UBX_NAV_PVT:
			if((st=ubx_nav_pvt_load_to_ubx_nav_pvt_t(sentence,&ubx_nav_pvt))!=ST_OK){
				return st;
			}
			track->longitude=ubx_nav_pvt.longitude;
			track->latitude=ubx_nav_pvt.latitude;
			track->elevation=ubx_nav_pvt.elevation;
			track->day.hour=ubx_nav_pvt.fix_hour.hour;
			track->day.minutes=ubx_nav_pvt.fix_hour.minutes;
			track->day.seconds=ubx_nav_pvt.fix_hour.seconds;
			track->date.day=ubx_nav_pvt.date.day;
			track->date.month=ubx_nav_pvt.date.month;
			track->date.year=ubx_nav_pvt.date.year;
			
			ADT_List_append(list,track,trackpoint_dupl);
			break;

		case UBX_UNKNOWN:
			break;
	}

	return ST_OK;
}
	