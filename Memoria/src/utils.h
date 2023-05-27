/*
 * utils.h
 *
 *  Created on: May 26, 2023
 *      Author: utnso
 */

#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include<commons/config.h>
#include<commons/string.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>



typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;


typedef struct{
	int puerto_escucha; // podriamos usar unsigned para ser mas eficiente
	int tam_memoria;
	int tam_segmento_0;
	int cant_segmentos;
	int retardo_memoria;
	int retardo_compactacion;
	char* algoritmo_asignacion;

}config_struct;

extern t_log* logger;
// pthread_t thread;

void* recibir_buffer(int*, int);

int iniciar_servidor(char*);
int esperar_cliente(int);
t_list* recibir_paquete(int);
void recibir_mensaje(int);
int recibir_operacion(int);
#endif /* UTILS_H_ */
