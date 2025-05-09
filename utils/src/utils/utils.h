#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <string.h>
#include <assert.h>

/**
* @brief Imprime un saludo por consola
* @param quien Módulo desde donde se llama a la función
* @return No devuelve nada
*/

// ----------- Structs -----------

typedef struct {
	uint32_t size;
	char* stream;
} t_buffer;

typedef struct {
	uint32_t codigo_operacion;
	t_buffer* buffer;
} t_paquete;

typedef enum
{
	ENVIAR_NOMBRE_DE_IO_A_KERNEL,//[char* nombre_io]
	ENVIAR_NOMBRE_CPU_DISPATCH_KERNEL,
	ENVIAR_NOMBRE_CPU_INTERRUPT_KERNEL,
	BLOQUEAR_DISPOSITIVO_IO,//[int pid, int tiempo_bloqueo]
}op_code;


int crear_conexion_cliente(char *ip, char* puerto);
int iniciar_servidor(char* puerto, t_log* logger);
int esperar_cliente(int socket_servidor, t_log* logger);
void liberar_conexion(int socket);
int recibir_operacion(int);

// ----------- Funciones Buffer -----------S

t_buffer* crear_buffer();

void liberar_buffer(t_buffer* un_buffer);
t_buffer* recibir_buffer(int conexion);

void agregar_a_buffer(t_buffer* un_buffer, void* valor, int size);
void agregar_int_a_buffer(t_buffer* un_buffer, int valor);
void agregar_uint32_a_buffer(t_buffer* un_buffer, uint32_t valor);
void agregar_string_a_buffer(t_buffer* un_buffer, char* string);

void* extraer_stream(t_buffer* un_buffer);
int extraer_int(t_buffer* un_buffer);
uint32_t extraer_uint32(t_buffer* un_buffer);
char* extraer_string(t_buffer* un_buffer);

// ----------- Funciones Paquete -----------

t_paquete* crear_paquete_con_codigo_de_operacion(op_code cod_op, t_buffer* un_buffer);
// void destruir_paquete(t_paquete* un_paquete);
void* serializar_paquete(t_paquete* un_paquete);
void enviar_paquete(t_paquete* un_paquete, int socket);
void liberar_paquete(t_paquete* un_paquete);
#endif
