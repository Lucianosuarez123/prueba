#ifndef M_GLOBAL_H_
#define M_GLOBAL_H_

//Variables globales

#include <utils/utils.h>
#include <commons/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include "iniciar_m.h" 
#include "memoria_cpu.h" 
#include "memoria_kernel.h" 
#include <pthread.h>

extern t_log* memoria_logger;
extern t_log* memoria_log_debug;
extern t_config* memoria_config;

extern char* PUERTO_ESCUCHA;
extern char* TAM_MEMORIA;
extern char* TAM_PAGINA;
extern char* ENTRADAS_POR_TABLA;
extern char* CANTIDAD_NIVELES;
extern char* RETARDO_MEMORIA;
extern char* PATH_SWAPFILE;
extern char* RETARDO_SWAP;
extern char* LOG_LEVEL;
extern char* DUMP_PATH;

extern int puerto_escucha_cpu_fd;
extern int puerto_escucha_kernel_fd;
extern int cl_cpu_fd;
extern int cl_kernel_fd;
#endif