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
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

typedef enum
{
	EXIT,
	YIELD,
	F_READ,
	F_WRITE,
	SET,
	MOV_IN,
	MOV_OUT,
	F_TRUNCATE,
	F_SEEK,
	CREATE_SEGMENT,
	IO,
	WAIT,
	SIGNAL,
	F_OPEN,
	F_CLOSE,
	DELETE_SEGMENT
}op_instruccion;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

typedef struct{
	char* ip_kernel;
	int puerto_kernel;
}config_struct;

int crear_conexion(char* ip, char* puerto);
void enviar_mensaje(char* mensaje, int socket_cliente);
t_paquete* crear_paquete(void);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void liberar_conexion(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);


#endif /* UTILS_H_ */
