#ifndef CPU_GLOBAL_H_
#define CPU_GLOBAL_H_

#include "iniciar_cpu.h"
#include <utils/utils.h>
#include <commons/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <string.h>
#include <pthread.h>


extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* IP_KERNEL;
extern char* PUERTO_ESCUCHA_DISPATCH;
extern char* PUERTO_ESCUCHA_INTERRUPT;
extern char* LOG_LEVEL;

extern t_log* cpu_logger;
extern t_log* cpu_debug_logger;
extern t_config* cpu_config;

extern int socket_memoria_fd;
extern int socket_kernel_dispatch_fd;
extern int socket_kernel_interrupt_fd;

extern char* nombre_cpu;
extern int cl_dispatch_fd;
extern int cl_interrupt_fd;
#endif