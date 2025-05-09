#include <utils/utils.h>


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

// Funciones para Cliente
int crear_conexion_cliente(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;
	int err;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err=getaddrinfo(ip, puerto, &hints, &server_info);

	if(err!=0){
		perror("Error en getaddrinfo");
		exit(EXIT_FAILURE);
	}
	// Ahora vamos a crear el socket.
	int socket_cliente = 0;
	socket_cliente = socket(server_info->ai_family,
		server_info->ai_socktype,
		server_info->ai_protocol);
	// Ahora que tenemos el socket, vamos a conectarlo
	err = connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);
	if(err!=0){
		perror("Error en connect");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(server_info);

	return socket_cliente;
}

//Funciones para servidor

int iniciar_servidor(char* puerto, t_log* logger)//TO DO: fijarse si hay que meter una variable mensaje como argumento, para que el mensaje del log_trace cuando se inicia el servidor sea distinto.
{
	int socket_servidor;
	int err;
	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err=getaddrinfo(NULL, puerto, &hints, &servinfo);

	if(err!=0){
		perror("Error en getaddrinfo");
		exit(EXIT_FAILURE);
	}
	// Creamos el socket de escucha del servidor
		socket_servidor = socket(servinfo->ai_family,
		servinfo->ai_socktype,
		servinfo->ai_protocol);
	// Asociamos el socket a un puerto(bind)
	err = setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
	if (err == -1) {
		perror("Error en setsockopt");
		exit(EXIT_FAILURE);
	}
	err = bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);
	if(err!=0){
		perror("Error en bind");
		exit(EXIT_FAILURE);
	}
	// Escuchamos las conexiones entrantes(listen)
	err = listen(socket_servidor, SOMAXCONN);
	if(err!=0){
		perror("Error en listen");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(servinfo);
	log_trace(logger, "Listo para escuchar a mi cliente");//relacionado con el TO DO de arriba, que aca varie el mensaje.

	return socket_servidor;
}

int esperar_cliente(int socket_servidor, t_log* logger)
{
	// Aceptamos un nuevo cliente
	int socket_cliente;
	socket_cliente = accept(socket_servidor, NULL, NULL);
	return socket_cliente;
}


void liberar_conexion(int socket)
{
	close(socket);
}

//cosas necesarias para mandar y recibir mensajes
t_buffer* recibir_buffer(int conexion){
	t_buffer* un_buffer = malloc(sizeof(t_buffer));

	if(recv(conexion, &(un_buffer->size), sizeof(int), MSG_WAITALL) > 0){
		un_buffer->stream=malloc(un_buffer->size);
		if(recv(conexion, un_buffer->stream, un_buffer->size, MSG_WAITALL) > 0){
			return un_buffer;
		}
		else{
			perror("Error al recibir el stream");
			exit(EXIT_FAILURE);
		}
	}
	else{
		perror("Error al recibir el size");
		exit(EXIT_FAILURE);
	}
	return un_buffer;
}

void* extraer_stream(t_buffer* un_buffer){
	if(un_buffer->size==0){
		printf("\n [ERROR] El buffer no tiene nada\n");
		exit(EXIT_FAILURE);
	}
	if(un_buffer->size<0){
		printf("\n [ERROR] El buffer tiene un tamaño negativo\n");
		exit(EXIT_FAILURE);
	}

	int size_stream;
	memcpy(&size_stream, un_buffer->stream, sizeof(int));
	void* stream = malloc(size_stream);
	memcpy(stream, un_buffer->stream+sizeof(int), size_stream);

	int nuevo_size = un_buffer->size - size_stream - sizeof(int);
	if(nuevo_size==0){
		un_buffer->size=0;
		free(un_buffer->stream);
		un_buffer->stream=NULL;
		return stream;
	}
	if(nuevo_size<0){
		printf("\n [ERROR_STREAM] El buffer tiene un tamaño negativo\n");
		exit(EXIT_FAILURE);
	}
	void* nuevo_stream = malloc(nuevo_size);
	memcpy(nuevo_stream, un_buffer->stream+sizeof(int)+size_stream, nuevo_size);
	free(un_buffer->stream);
	un_buffer->size=nuevo_size;
	un_buffer->stream=nuevo_stream;
	return stream;
}

int extraer_int(t_buffer* un_buffer){
	int* valor_entero= extraer_stream(un_buffer);
	int valor_a_retornar = *valor_entero;
	free(valor_entero);
	return valor_a_retornar;
}

char* extraer_string(t_buffer* un_buffer){
	char* string= extraer_stream(un_buffer);
	char* string_a_retornar = malloc(strlen(string)+1);
	strcpy(string_a_retornar, string);
	free(string);
	return string_a_retornar;
}
uint32_t extraer_uint32(t_buffer* un_buffer){
	uint32_t* valor_entero= extraer_stream(un_buffer);
	uint32_t valor_a_retornar = *valor_entero;
	free(valor_entero);
	return valor_a_retornar;
}

void liberar_buffer(t_buffer* un_buffer){
	if(un_buffer->stream!=NULL){
		free(un_buffer->stream);
	}
	free(un_buffer);
}
void liberar_paquete(t_paquete* un_paquete){
	if(un_paquete->buffer!=NULL){
		liberar_buffer(un_paquete->buffer);
	}
	free(un_paquete);
}

t_buffer* crear_buffer(){
	t_buffer* un_buffer = malloc(sizeof(t_buffer));
	un_buffer->size = 0;
	un_buffer->stream = NULL;
	return un_buffer;
}

void agregar_a_buffer(t_buffer* un_buffer, void* valor, int size){
	if(un_buffer->size==0){
		un_buffer->stream=malloc(sizeof(int)+size);
		memcpy(un_buffer->stream, &size, sizeof(int));
		memcpy(un_buffer->stream+sizeof(int), valor, size);
	}
	else{
		un_buffer->stream=realloc(un_buffer->stream, un_buffer->size+sizeof(int)+size);
		memcpy(un_buffer->stream+un_buffer->size, &size, sizeof(int));
		memcpy(un_buffer->stream+un_buffer->size+sizeof(int), valor, size);
	}
	un_buffer->size+=sizeof(int)+size;
}

void agregar_int_a_buffer(t_buffer* un_buffer, int valor){
	agregar_a_buffer(un_buffer, &valor, sizeof(int));
}
void agregar_uint32_a_buffer(t_buffer* un_buffer, uint32_t valor){
	agregar_a_buffer(un_buffer, &valor, sizeof(uint32_t));
}
void agregar_string_a_buffer(t_buffer* un_buffer, char* string){
	agregar_a_buffer(un_buffer, string, strlen(string)+1);
}

t_paquete* crear_paquete_con_codigo_de_operacion(op_code cod_op, t_buffer* un_buffer){
	t_paquete* un_paquete = malloc(sizeof(t_paquete));
	un_paquete->codigo_operacion = cod_op;
	un_paquete->buffer = un_buffer;
	return un_paquete;
}
// void destruir_paquete(t_paquete* un_paquete){
// 	liberar_buffer(un_paquete->buffer);
// 	free(un_paquete);
// }

void* serializar_paquete(t_paquete* un_paquete){
	int size = 2*sizeof(uint32_t) + un_paquete->buffer->size;
	void* stream = malloc(size);
	int offset = 0;

	memcpy(stream + offset, &(un_paquete->codigo_operacion), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &(un_paquete->buffer->size), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, un_paquete->buffer->stream, un_paquete->buffer->size);
	offset += un_paquete->buffer->size;
	return stream;
}

void enviar_paquete(t_paquete* un_paquete, int socket){
	void* stream = serializar_paquete(un_paquete);
	int size = 2*sizeof(uint32_t) + un_paquete->buffer->size;
	send(socket, stream, size, 0);
	free(stream);
}