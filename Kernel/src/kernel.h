/*
 * kernel.h
 *
 *  Created on: May 27, 2023
 *      Author: utnso
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "utils.h"
#include <sys/time.h>

t_list* new;


typedef struct{
	char* valores; // re definir
}registro;
typedef struct{
	unsigned id;
	int * direccion_base;
	unsigned tamanio;
}segmento_datos;

typedef enum{
	abierto,
	cerrado
}estado_archivo;

typedef struct{
	char* path;
	estado_archivo file_open;
}archivo;

typedef enum{
	N,  // NEW
	R,	// READY
	E,	// EXEC
	B	// BREAK interrumpido
}estado;


typedef struct{
	estado estado_proceso;
	unsigned pid;
	t_list * instrucciones;
	unsigned program_counter;
	t_list* registros_cpu;
	t_list* tabla_segmentos;
	double estimado_prox_rafaga; // double porque hrrn_alfa es de tipo double
	double tiempo_llegada;
	t_list* tabla_archivos_abiertos;
}pcb_;


#endif /* KERNEL_H_ */
