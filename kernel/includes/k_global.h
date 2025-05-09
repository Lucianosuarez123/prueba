#ifndef K_GLOBAL_H_
#define K_GLOBAL_H_
// Variables globales.
// -Para evitar errores de variables declaradas doble.
// -Para modularizar el trabajo. Evitar dependencias circulares.

#include <utils/utils.h>
#include <commons/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include "iniciar_k.h" 
#include "kernel_cpu_dispatch.h"
#include "kernel_cpu_interrupt.h"
#include "kernel_io.h"
#include "kernel_memoria.h"
#include <pthread.h>

extern t_log* kernel_logger;
extern t_log* kernel_log_debug;
extern t_config* kernel_config;

extern int escucha_interrupt_fd;
extern int escucha_dispatch_fd;
extern int escucha_io_fd;
extern int cl_io_fd;
extern int cl_interrupt_fd;
extern int cl_dispatch_fd;
extern int memoria_fd;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* PUERTO_ESCUCHA_DISPATCH;
extern char* PUERTO_ESCUCHA_INTERRUPT;
extern char* PUERTO_ESCUCHA_IO;
extern char* ALGORITMO_PLANIFICACION;
extern char* ALGORITMO_COLA_NEW;
extern char* ALFA;
extern char* TIEMPO_SUSPENSION;
extern char* LOG_LEVEL;

#endif 