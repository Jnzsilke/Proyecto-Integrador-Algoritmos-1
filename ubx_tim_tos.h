#ifndef UBX_TIM_TOS__H
#define UBX_TIM_TOS__H 

#include "types.h"
#include "utilities.h"

#define UBX_TIM_TOS_YEAR_POS 14
#define UBX_TIM_TOS_YEAR_BYTES 2
#define UBX_TIM_TOS_MONTH_POS 16
#define UBX_TIM_TOS_DAY_POS 17
#define UBX_TIM_TOS_HOUR_POS 18
#define UBX_TIM_TOS_MINUTE_POS 19
#define UBX_TIM_TOS_SECOND_POS 20

typedef struct{
	timestamp_day_t hour;
	timestamp_date_t date;
}ubx_tim_tos_t;

status_t ubx_tim_tos_load_to_ubx_tim_tos_t(unsigned char * sentence, ubx_tim_tos_t *ubx_tim_tos);
status_t ubx_tim_tos_load_hour(unsigned char * sentence, ubx_tim_tos_t *ubx_tim_tos);
status_t ubx_tim_tos_load_date(unsigned char * sentence, ubx_tim_tos_t *ubx_tim_tos);


#endif