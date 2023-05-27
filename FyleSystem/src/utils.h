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

typedef struct{
	char* ip_memoria;
	int puerto_memoria;
	int puerto_escucha;

	char* path_superbloque;
	char* path_bitmap;
	char* path_bloques;
	char* path_fcb;

	int retardo_acceso_bloque;

}config_struct;

#endif /* UTILS_H_ */
