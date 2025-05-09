#ifndef I_GLOBAL_H_
#define I_GLOBAL_H_

#include <utils/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include "iniciar_io.h"
#include "io_kernel.h"
#include <pthread.h>
//variables globales
extern t_log* io_logger;
extern t_log* io_log_debug;
extern t_config* io_config;

extern char* IP_KERNEL;
extern char* PUERTO_KERNEL;
extern char* LOG_LEVEL;

extern int cl_io_fd;
extern char* nombre_io;
#endif