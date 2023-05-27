/*
 * utils.h
 *
 *  Created on: May 24, 2023
 *      Author: utnso
 */

#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/config.h>

#include<commons/string.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>
// #include<pthread.h>

//#define PUERTO "8000"

typedef struct
{
	char* instruccion;
	char ** parametros;
}instruccion_;

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

typedef struct{
	char* ip_memoria;
	int puerto_memoria;

	char* ip_filesystem;
	int puerto_filesystem;

	char* ip_cpu;
	int puerto_cpu;

	int puerto_escucha;

	char* algoritmo_planificacion;
	double estimacion_iniical;
	int hrrn_alfa;
	int grado_max_multiprogramacion;

	char** recursos;
	char** instancias_recursos;
}config_struct;

extern t_log* logger;
// pthread_t thread;

void* recibir_buffer(int*, int);

int iniciar_servidor(char*);
int esperar_cliente(int);
t_list* recibir_paquete(int);
void recibir_mensaje(int);
int recibir_operacion(int);

// ---- cliente -----

int crear_conexion(char* ip, int puerto);

#endif /* UTILS_H_ */
