#ifndef CPU_H_
#define CPU_H_

#include "cpu_global.h"
#include "iniciar_cpu.h"
#include "cpu_kernel_dispatch.h"
#include "cpu_kernel_interrupt.h"
#include "cpu_memoria.h"


char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* IP_KERNEL;
char* PUERTO_ESCUCHA_DISPATCH;
char* PUERTO_ESCUCHA_INTERRUPT;
char* LOG_LEVEL;

t_log* cpu_logger;
t_log* cpu_debug_logger;
t_config* cpu_config;

int socket_memoria_fd;
int socket_kernel_dispatch_fd;
int socket_kernel_interrupt_fd;

int cl_dispatch_fd;
int cl_interrupt_fd;
char* nombre_cpu;

#endif