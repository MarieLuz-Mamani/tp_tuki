/*
 * utils.c
 *
 *  Created on: May 26, 2023
 *      Author: utnso
 */


#include"utils.h"

t_log* logger;

int iniciar_servidor(char* puerto_escucha)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	//assert(!"no implementado!");

	int socket_servidor;

	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, puerto_escucha, &hints, &servinfo);

	// Creamos el socket de escucha del servidor
	for(p=servinfo;p!=NULL;p= p->ai_next){
		if( (socket_servidor = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
			continue;
		if(bind(socket_servidor,p->ai_addr,p->ai_addrlen) == -1){
			close(socket_servidor);
			continue;
		}
		break;
	}

	// Asociamos el socket a un puerto

	// Escuchamos las conexiones entrantes
	if(listen(socket_servidor,SOMAXCONN) == -1) {
		printf("error en listen()\n");
	 exit(-1);
	 }

	freeaddrinfo(servinfo);
	log_trace(logger, "Listo para escuchar a mi cliente");

	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	 //assert(!"no implementado espera a cliente!");

	// Aceptamos un nuevo cliente
	struct sockaddr_in dir_cliente;
	int tam_direccion=sizeof(struct sockaddr_in);

	//int socket_cliente= socket();
	int socket_cliente=accept(socket_servidor,(void*)&dir_cliente,&tam_direccion);

	if(socket_cliente<0)
	  {
	    printf("Error al aceptar trafico\n");
	    close(socket_servidor);
	    return 1;
	  }

	log_info(logger, "Se conecto un cliente!");
	//pthread_create(&thread,NULL,(int*)recibir_operacion,&socket_cliente);

	return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}
