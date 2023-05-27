/*
 ============================================================================
 Name        : FyleSystem.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "utils.h"

config_struct configuracion;

void leer_config(char* path_config){
	t_config *config_fs ;

		if( (config_fs=config_create(path_config)) == NULL) {
			puts("No se pudo leer la configuracion \n ");
			exit(2);
		}
		else{
			puts("Se pudo leer la configuracion \n ");
			configuracion.ip_memoria = config_get_string_value(config_fs,"IP_MEMORIA");
			configuracion.puerto_memoria = config_get_int_value(config_fs,"PUERTO_MEMORIA");
			configuracion.puerto_escucha = config_get_int_value(config_fs,"PUERTO_ESCUCHA");

			configuracion.path_superbloque = config_get_string_value(config_fs,"PATH_SUPERBLOQUE");
			configuracion.path_bitmap = config_get_string_value(config_fs,"PATH_BITMAP");
			configuracion.path_bloques = config_get_string_value(config_fs,"PATH_BLOQUES");
			configuracion.path_fcb = config_get_string_value(config_fs,"PATH_FCB");

			configuracion.retardo_acceso_bloque = config_get_int_value(config_fs,"RETARDO_ACCESO_BLOQUE");
		}
}

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */


	char* path_config_fs="filesystem.config";
	leer_config(path_config_fs);


	return EXIT_SUCCESS;
}
