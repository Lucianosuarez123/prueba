#ifndef KERNEL_IO_H_
#define KERNEL_IO_H_

#include "k_global.h"



void atender_kernel_io();
void recibir_nombre_io(int socket);
void enviar_bloqueo_io(int socket,int pid, int tiempo_bloqueo);

#endif