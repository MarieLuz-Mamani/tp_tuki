/*
 ============================================================================
 Name        : Kernel.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "kernel.h"

config_struct configuracion;
unsigned pid_;

void iterator(char* value) {
	log_info(logger,"%s", value);
}

void leer_config(char* path_configuracion)
{
	t_config *config_kernel ;

	if( (config_kernel=config_create(path_configuracion)) == NULL) {
		puts("No se pudo leer la configuracion \n ");
		exit(2);
	}
	else{
		puts("Se pudo leer la configuracion \n ");
			configuracion.ip_memoria=config_get_string_value(config_kernel,"IP_MEMORIA");
		    configuracion.puerto_memoria=config_get_int_value(config_kernel,"PUERTO_MEMORIA");

		    configuracion.ip_filesystem=config_get_string_value(config_kernel,"IP_FILESYSTEM");
		    configuracion.puerto_filesystem=config_get_int_value(config_kernel,"PUERTO_FILESYSTEM");

		    configuracion.ip_cpu=config_get_string_value(config_kernel,"IP_CPU");
		    configuracion.puerto_cpu=config_get_int_value(config_kernel,"PUERTO_CPU");


		    configuracion.puerto_escucha=config_get_int_value(config_kernel,"PUERTA_ESCUCHA"); // error a la hora de leer?
		   // puts("Se pudo leer la configuracion \n ");
		    configuracion.algoritmo_planificacion = config_get_string_value(config_kernel,"ALGORITMO_PLANIFICACION");
		    configuracion.estimacion_iniical = config_get_int_value(config_kernel,"ESTIMACION_INICIAL");
		    configuracion.hrrn_alfa=config_get_double_value(config_kernel,"HRRN_ALFA");
		    configuracion.grado_max_multiprogramacion=config_get_int_value(config_kernel,"GRADO_MAX_MULTIPROGRAMACION");

		    configuracion.recursos=config_get_array_value(config_kernel,"RECURSOS");
		    configuracion.instancias_recursos=config_get_array_value(config_kernel,"INSTANCIAS_RECURSOS");

	}

}

void mostrarLista(t_log* logger,t_list* lista){
	instruccion_ *x= malloc(sizeof(instruccion_));
	x->instruccion=string_new();
	x->parametros=string_array_new();
	int i=0;

	while(i<list_size(lista)){
		x=list_get(lista,i); // solo toma lo ultimo guardado
		printf("\n %i INST:%s PARAMETROS: %s %s \n",i+1,x->instruccion,x->parametros[0],x->parametros[1]);
		i++;
	}
	free(x);
}
void generar_pcb(){
	pcb_* pcb=malloc(sizeof(pcb));
	pcb->estado_proceso=N;
	pcb->pid=pid_;
	log_info(logger,"Se crea el proceso %i en NEW",pcb->pid);
	pcb->program_counter=0; //inicia


}
void pasarAReady(pcb_ *pcb,int conexionMemoria){
	if(configuracion.grado_max_multiprogramacion > 1 && pcb->estado_proceso==N){
		pcb->estado_proceso=R;
		enviar_mensajeMemoria(conexionMemoria,pcb->tabla_segmentos); // funcion aun no implementado
	}
}
void enviar_mensajeMemoria(int conexion,t_list* tabla_seg ){
	// sin implementar
}
int main(void) {
	pid_=0; // inicializar
	puts("!!!Soy el kernel!!!"); /* prints !!!Hello World!!! */

	logger = log_create("kernel.log", "Kernel", 1, LOG_LEVEL_DEBUG);

	leer_config("kernel.config");

		// string_itoa(configuracion.puerto_escucha)
		int server_fd = iniciar_servidor(string_itoa(configuracion.puerto_escucha));
		log_info(logger, "Servidor listo para recibir al cliente");
		int consola_fd = esperar_cliente(server_fd);

		int conexionCPU = crear_conexion(configuracion.ip_cpu,configuracion.puerto_cpu);
		int conexionMemoria = crear_conexion(configuracion.ip_memoria,configuracion.puerto_memoria);
		int conexionFilesystem = crear_conexion(configuracion.ip_filesystem,configuracion.puerto_filesystem);



		t_list* lista=list_create();

		while (1) { //conexion activa
				int cod_op = recibir_operacion(consola_fd);
				switch (cod_op) {
				case MENSAJE:
					recibir_mensaje(consola_fd);
					break;
				case PAQUETE:
					lista = recibir_paquete(consola_fd); //recibe paquete que contiene la lista
					log_info(logger, "Me llegaron los siguientes valores:\n");

					printf("\n Size: %i ",list_size(lista));

					/*
					for(int i=0;i<list_size(lista);i++){
						printf("- %i",i);
						instruccion_ * x= malloc(sizeof(instruccion_));
						x=list_get(lista,i);
						printf("\n --- %s : s  s  s",x->instruccion);
					}
					*/
					//list_iterate(lista, (void*) iterator); // no se puede mostrar los elementos , solo que son 16 arch
					generar_pcb();
					pid_++;
					list_destroy(lista);
					break;
				case -1:
					log_error(logger, "El cliente se desconecto. Terminando Kernel");
					return EXIT_FAILURE;
				default:
					log_warning(logger,"Operacion desconocida.");
					break;
				}
			}

	return EXIT_SUCCESS;
}
