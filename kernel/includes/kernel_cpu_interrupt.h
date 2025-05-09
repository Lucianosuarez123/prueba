#ifndef KERNEL_CPU_INTERRUPT_H_
#define KERNEL_CPU_INTERRUPT_H_

#include "k_global.h"



void atender_kernel_cpu_interrupt();
void recibir_nombre_cpu_interrupt(int socket_interrupt);

#endif