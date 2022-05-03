#include "ubx_tim_tos.h"
#include <stdio.h>
#include <stdlib.h>

status_t ubx_tim_tos_load_date(unsigned char * sentence, ubx_tim_tos_t *ubx_tim_tos){
	status_t st;
	timestamp_date_t date;
	unsigned int temp;
	if(!sentence || !ubx_tim_tos){
		return ST_ERROR_NULL_POINTER;
	}
	if((st=little_endian_to_uint(&temp,sentence+UBX_TIM_TOS_YEAR_POS,UBX_TIM_TOS_YEAR_BYTES))!= ST_OK){
		return st;
	}

	date.year=temp;
	date.month=sentence[UBX_TIM_TOS_MONTH_POS];
	date.day=sentence[UBX_TIM_TOS_DAY_POS];
	ubx_tim_tos->date=date;
	return ST_OK;
}

status_t ubx_tim_tos_load_hour(unsigned char * sentence, ubx_tim_tos_t *ubx_tim_tos){
	timestamp_day_t hour;
	if(!sentence || !ubx_tim_tos){
		return ST_ERROR_NULL_POINTER;
	}

	hour.hour=sentence[UBX_TIM_TOS_HOUR_POS];
	hour.minutes=sentence[UBX_TIM_TOS_MINUTE_POS];
	hour.seconds=sentence[UBX_TIM_TOS_SECOND_POS];

	ubx_tim_tos->hour=hour;
	return ST_OK;
}

status_t ubx_tim_tos_load_to_ubx_tim_tos_t(unsigned char * sentence, ubx_tim_tos_t *ubx_tim_tos){
	status_t st;
	
	if(!sentence || !ubx_tim_tos){
		return ST_ERROR_NULL_POINTER;
	}

	if((st=ubx_tim_tos_load_date(sentence,ubx_tim_tos))!=ST_OK){
		return st;
	}

	if((st=ubx_tim_tos_load_hour(sentence,ubx_tim_tos))!=ST_OK){
		return st;
	}

	return ST_OK;
}
