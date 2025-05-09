#ifndef IO_H_
#define IO_H_

#include "i_global.h"
#include "iniciar_io.h"
#include "io_kernel.h"

t_log* io_logger;
t_log* io_log_debug;
t_config* io_config;

char* IP_KERNEL;
char* PUERTO_KERNEL;
char* LOG_LEVEL;

int cl_io_fd;

char* nombre_io;
#endif