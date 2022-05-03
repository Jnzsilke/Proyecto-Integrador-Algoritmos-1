#include <stdio.h>
#include "types.h"
#include "config.h"

#define GPX_LABEL_START_TRKPT "\t  <trkpt lat=""\"""%f""\""" lon=""\"""%f""\""">\n"

status_t print_gpx_header(FILE* fo,gpx_metadata_t *gpx)
{	
	fprintf(fo,"%s\n\n%s\n",GPX_LABEL_HEADER,GPX_ELEMENT_LABEL_START);
	fprintf(fo,"  %s\n",GPX_LABEL_START_METADATA);
	fprintf(fo, "\t%s%s%s\n",GPX_LABEL_START_NAME,gpx->name,GPX_LABEL_END_NAME);
	fprintf(fo, "\t%s",GPX_LABEL_START_TIME);
	fprintf(fo,"%lu-%lu-%lu",gpx->date.year,gpx->date.month,gpx->date.day);
	fprintf(fo,"T%.2lu:%.2lu:%06.3fZ",gpx->day.hour,gpx->day.minutes,gpx->day.seconds);
	fprintf(fo,"%s\n",GPX_LABEL_END_TIME);
	fprintf(fo,"  %s\n",GPX_LABEL_END_METADATA);
	fprintf(fo,"  %s\n",GPX_LABEL_START_TRK);
	fprintf(fo,"\t%s\n",GPX_LABEL_START_TRKSEG);
	
	return ST_OK;
}

status_t print_gpx_track_point(void* f,void *t)
{
	FILE *fo=(FILE*)f;
	trackpoint_t *track=(trackpoint_t*)t;
	
	fprintf(fo,GPX_LABEL_START_TRKPT,track->latitude,track->longitude);
	fprintf(fo,"\t\t%s%f%s\n",GPX_LABEL_START_ELE,track->elevation,GPX_LABEL_END_ELE);
	fprintf(fo, "\t\t%s",GPX_LABEL_START_TIME);
	fprintf(fo,"%lu-%02lu-%02lu",track->date.year,track->date.month,track->date.day);
	fprintf(fo,"T%lu:%lu:%.3fZ",track->day.hour,track->day.minutes,track->day.seconds);	
	fprintf(fo,"%s\n",GPX_LABEL_END_TIME);
	fprintf(fo,"\t  %s\n",GPX_LABEL_END_TRKPT);


	return ST_OK;
}

status_t print_gpx_footer(FILE* fo)
{
	fprintf(fo,"\t%s\n",GPX_LABEL_END_TRKSEG);
	fprintf(fo,"  %s\n",GPX_LABEL_END_TRK);
	fprintf(fo,"%s\n",GPX_ELEMENT_LABEL_END);

	return ST_OK;

}

status_t print_help_msg(FILE* fo)
{
	fprintf(fo,"%s\n",USR_MSG_PROGRAM_INVOCATION);
	fprintf(fo,"%s:\n\n",USR_MSG_FLAG_OPTION);
	/*-h*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_HELP_SHORT,CMD_ARG_FLAG_HELP_LONG);
	fprintf(fo,"\t\t%s\n\n",USR_MSG_FLAG_HELP);

	/*-n*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_METADATA_NAME_SHORT,CMD_ARG_FLAG_METADATA_NAME_LONG);
	fprintf(fo,"\t\t%s%d\n\n",USR_MSG_FLAG_NAME,MAX_METADATA_NAME);
	/*-p*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_PROTOCOL_SHORT,CMD_ARG_FLAG_PROTOCOL_LONG);
	fprintf(fo,"\t\t%s\n\n",USR_MSG_FLAG_PROTOCOL);
	/*-i*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_INPUT_FILE_SHORT,CMD_ARG_FLAG_INPUT_FILE_LONG);
	fprintf(fo,"\t\t%s\n\n",USR_MSG_FLAG_INFILE);
	/*-o*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_OUTPUT_FILE_SHORT,CMD_ARG_FLAG_OUTPUT_FILE_LONG);
	fprintf(fo,"\t\t%s\n\n",USR_MSG_FLAG_OUTFILE);
	/*-l*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_LOG_FILE_SHORT,CMD_ARG_FLAG_LOG_FILE_LONG);
	fprintf(fo,"\t\t%s\n\n",USR_MSG_FLAG_LOGFILE);
	/*-m*/
	fprintf(fo, "\t%s  %s\n",CMD_ARG_FLAG_MAXLEN_SHORT,CMD_ARG_FLAG_MAXLEN_LONG);
	fprintf(fo,"\t\t%s\n\n",USR_MSG_FLAG_MAXLEN);

	fprintf(fo,"%s\n",USR_MSG_CLA_RESTRICTION_REPEAT);
	fprintf(fo,"%s\n",USR_MSG_CLA_RESTRICTION_HELP);
	

	return ST_OK;

}