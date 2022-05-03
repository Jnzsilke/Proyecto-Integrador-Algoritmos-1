#ifndef OUTPUT__H
#define OUTPUT__H
#include <stdio.h>
#include "types.h"

status_t print_gpx_header(FILE* fo,gpx_metadata_t *gpx);
status_t print_gpx_track_point(void* f,void *t);
status_t print_gpx_footer(FILE* fo);
status_t print_help_msg(FILE* fo);


#endif