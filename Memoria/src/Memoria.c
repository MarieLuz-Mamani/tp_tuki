/*
 ============================================================================
 Name        : Memoria.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "utils.h"

config_struct configuracion;

void leer_config(char* path_config){
	t_config *config_memoria ;
	if( (config_memoria=config_create(path_config)) == NULL) {
		puts("No se pudo leer la configuracion \n ");
		exit(2);
	}
	else{
		configuracion.puerto_escucha = config_get_int_value(config_memoria,"PUERTO_ESCUCHA");
		configuracion.tam_memoria = config_get_int_value(config_memoria,"TAM_MEMORIA");
		configuracion.tam_segmento_0 = config_get_int_value(config_memoria,"TAM_SEGMENTO_0");
		configuracion.cant_segmentos = config_get_int_value(config_memoria,"CANT_SEGMENTOS");
		configuracion.retardo_memoria = config_get_int_value(config_memoria,"RETARDO_MEMORIA");
		configuracion.retardo_compactacion = config_get_int_value(config_memoria,"RETARDO_COMPACTACION");

		configuracion.algoritmo_asignacion = config_get_string_value(config_memoria,"ALGORITMO_ASIGNACION");

	}
}

int main(void) {
	puts("!!!Soy la memoria!!"); /* prints !!!Hello World!!! */

	char* path_config="memoria.config";

	logger = log_create("memoria.log", "Memoria", 1, LOG_LEVEL_DEBUG);
	leer_config(path_config);


	return EXIT_SUCCESS;
}
