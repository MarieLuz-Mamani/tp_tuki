/*
 * consola.h
 *
 *  Created on: May 12, 2023
 *      Author: utnso
 */

#ifndef CONSOLA_H_
#define CONSOLA_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include<commons/collections/list.h>
#include "utils.h"

typedef struct
{
	char* instruccion;
	char ** parametros;
}instruccion_;



//t_list * lista;

//char* path_config_consola="/consola.config";
//char* path_pseudocodigo="YIELD";

#endif /* CONSOLA_H_ */
