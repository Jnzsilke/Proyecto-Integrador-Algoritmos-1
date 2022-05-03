#ifndef ERRORS__H
#define ERRORS__H

#include "types.h"
#define MAX_CLA_ERROR_MSGS 7
#define MAX_ERROR_MSGS 21
const char* errors_cla[MAX_ERROR_MSGS]=
{
	
	"Si ingresa un flag,este debe ser valido",
	"Debe ingresar un argumento tras los flags '-p','--protocol','-i','--infile','-o','--outfile','-l','--logfile','-m','--maxlen'",
	"Debe ingresar algun argumento."
	

};

const char* error_msgs[MAX_ERROR_MSGS]=
{

	"Fecha invalida",
	"Error en una sentencia RMC",
	"Posicion invalida",
	"Hora del fix invalida",
	"Conversion de latitud invalida",
	"Conversion de longitud invalida",
	"Conversion del fix de calidad invalida",
	"Conversion del satelite invalida",
	"Conversion del hdop invalida",
	"Conversion de la elevacion invalida",
	"Conversion de la separacion del geoide invalida"
	"Conversion de la cantidad maxima invalida",
	"Estado del fix no fijado",
	"Error de flujo de entrada/salida",
	"No pudo crearse un nodo"
	"No pudo crearse una lista",
	"No hay memoria",
	"Puntero nulo",
	"No pudo abrirse el archivo de entrada.",
	"No pudo abrirse el archivo de salida.",
	"No pudo abrirse el archivo de log."


};

status_t print_cla_error_msg(status_t st);
status_t print_error_msg(status_t st);
#endif
