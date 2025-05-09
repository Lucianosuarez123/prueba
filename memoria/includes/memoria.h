#ifndef MEMORIA_H_
#define MEMORIA_H_

#include "m_global.h"
#include "iniciar_m.h"
#include "memoria_cpu.h"
#include "memoria_kernel.h"

t_log* memoria_logger;
t_log* memoria_log_debug;
t_config* memoria_config;

char* PUERTO_ESCUCHA;
char* TAM_MEMORIA;
char* TAM_PAGINA;
char* ENTRADAS_POR_TABLA;
char* CANTIDAD_NIVELES;
char* RETARDO_MEMORIA;
char* PATH_SWAPFILE;
char* RETARDO_SWAP;
char* LOG_LEVEL;
char* DUMP_PATH;

int puerto_escucha_cpu_fd;
int puerto_escucha_kernel_fd;
int cl_cpu_fd;
int cl_kernel_fd;
#endif