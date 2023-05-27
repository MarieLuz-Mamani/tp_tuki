
#include "consola.h"
config_struct configuracion;

void leer_config(char* path_codigo)
{
	t_config *config ;

	if( (config=config_create(path_codigo)) == NULL) {
		puts("No se pudo leer la configuracion \n ");
		exit(2);
	}
	configuracion.ip_kernel=config_get_string_value(config,"IP_KERNEL");
    configuracion.puerto_kernel=config_get_int_value(config,"PUERTO_KERNEL");

}

t_log* iniciar_logger(void)
{
	t_log* logger;

	 if((logger=log_create("consola.log","Consola",1,LOG_LEVEL_INFO))== NULL){
		printf("No se pudo crear log");
		exit(1);
	}


	return logger;
}

void mostrarLista(t_list* lista){
	instruccion_ *x= malloc(sizeof(instruccion_));
	int i=0;
	while(i<list_size(lista)){
		x=list_get(lista,i); // solo toma lo ultimo guardado
		printf("\n %i :",i+1);
		printf("INST:%s PARAMETROS: %s %s \n",x->instruccion,x->parametros[0],x->parametros[1]);
		i++;
	}
	free(x);
}

void leer_pseudo(char* path_inst,t_paquete* paquete){


	FILE *archivo;
	int max=100;
	char** auxiliar =string_array_new();

	int indice=0; // indice de instruccion solo para mostrar
	char* buffer=string_new();

	if ((archivo = fopen(path_inst, "r")) == NULL)
	{
		puts ( " Error en la apertura. Es posible que el fichero no exista \n ");
	}


	while(fgets(buffer,max,archivo)){

		strtok(buffer,"\n");
		//ahora en buffer tenemos la instruccion y sus parametros
		//printf("\n %i",indice);

		if(!string_is_empty(buffer)){
			instruccion_ * instruccion_consola = malloc(sizeof(instruccion_));
			instruccion_consola->instruccion=string_new();
			instruccion_consola->parametros=string_array_new();

			//divide entre instrucciones y parametros
			auxiliar=string_n_split(buffer,2," ");
			instruccion_consola->instruccion=auxiliar[0];

			if(auxiliar[1] != NULL){
				instruccion_consola->parametros=string_split(auxiliar[1]," ");
				//printf("->  INST:%s PARAMETROS: %s \n",instruccion_consola->instruccion,instruccion_consola->parametros[0]);

			}

			else{
				instruccion_consola->parametros=string_array_new();
				//printf("-->INST: %s PARAMETROS: %s \n",instruccion_consola->instruccion,instruccion_consola->parametros[0]);
			}
			//list_add(lista,instruccion_consola);
			agregar_a_paquete(paquete,instruccion_consola,sizeof(instruccion_));
		}

		indice++;
	}// fin de while
	//printf("\n  Largo de lista %i \n",list_size(lista));

	fclose(archivo);
	//mostrarLista(lista);

	//return lista;
}



void terminar_programa(int conexion, t_log* logger)
{
	log_destroy(logger);

	close(conexion);

}

//-- investigar como en eclipse
int main(int argc, char **argv){

	char* path_config;
	char*path_instrucion;
	path_config = string_new();
	path_instrucion=string_new();

	if (argc < 2) {
		printf("Faltan parametros de entrada\n");
		// para pruebas rapidas
		path_config ="/home/utnso/cooder_v1/Consola/consola.config";
		path_instrucion="/home/utnso/cooder_v1/Consola/pseudocodigo.txt";
		//return -1;
	} else {
		path_config = argv[0];
		path_instrucion=argv[1];
	}
	int conexion_kernel=0;

	t_log* logger;
	logger=iniciar_logger();

	leer_config(path_config);

	conexion_kernel=crear_conexion(configuracion.ip_kernel,string_itoa(configuracion.puerto_kernel));

	t_paquete* paquete=crear_paquete();

	leer_pseudo(path_instrucion,paquete); // arma el paquete

	 //agregar_a_paquete(paquete,instrucciones,sizeof(instruccion_));
	 enviar_paquete(paquete,conexion_kernel);

	 eliminar_paquete(paquete);

	 // deberiamos esperar respuesta de kernel
	 //escuchar_kernel(ip_kernel,puerto_kernel,conexion);

	printf("!!!Soy la Consola !!! ip:%s   puerto:%d  ",configuracion.ip_kernel,configuracion.puerto_kernel); /* prints !!!Hello World!!! */


	terminar_programa(conexion_kernel,logger);
}
