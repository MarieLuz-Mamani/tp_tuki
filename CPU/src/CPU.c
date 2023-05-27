/*
 ============================================================================
 Name        : CPU.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "cpu.h"

config_struct configuracion;

void leer_config(char* path_configuracion)
{
	t_config *config_cpu ;

	if( (config_cpu=config_create(path_configuracion)) == NULL) {
		puts("No se pudo leer la configuracion \n ");
		exit(2);
	}
	else{
		//puts("Se pudo leer la configuracion \n ");
		configuracion.retardo_instruccion = config_get_int_value(config_cpu,"RETARDO_INSTRUCCION");
		configuracion.ip_memoria = config_get_string_value(config_cpu,"IP_MEMORIA");
		configuracion.puerto_memoria = config_get_int_value(config_cpu,"PUERTO_MEMORIA");
		configuracion.puerto_escucha = config_get_int_value(config_cpu,"PUERTO_ESCUCHA");
		configuracion.tam_max_segmento = config_get_int_value(config_cpu,"TAM_MAX_SEGMENTO");
	}

}

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	leer_configuracion("cpu.config");
	int conexionMemoria=crear_conexion(configuracion.ip_memoria,string_itoa(configuracion.puerto_memoria));


	return EXIT_SUCCESS;
}
