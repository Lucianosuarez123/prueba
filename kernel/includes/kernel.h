#ifndef KERNEL_H_
#define KERNEL_H_

#include "k_global.h"
#include "iniciar_k.h"

#include "kernel_cpu_dispatch.h"
#include "kernel_cpu_interrupt.h"
#include "kernel_io.h"
#include "kernel_memoria.h"
t_log* kernel_logger;
t_log* kernel_log_debug;
t_config* kernel_config;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PUERTO_ESCUCHA_DISPATCH;
char* PUERTO_ESCUCHA_INTERRUPT;
char* PUERTO_ESCUCHA_IO;
char* ALGORITMO_PLANIFICACION;
char* ALGORITMO_COLA_NEW;
char* ALFA;
char* TIEMPO_SUSPENSION;
char* LOG_LEVEL;

int escucha_interrupt_fd;
int escucha_dispatch_fd;
int escucha_io_fd;
int cl_io_fd;
int cl_interrupt_fd;
int cl_dispatch_fd;
int memoria_fd;

#endif