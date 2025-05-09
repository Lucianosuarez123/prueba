#ifndef CPU_KERNEL_INTERRUPT_H_
#define CPU_KERNEL_INTERRUPT_H_
#include "cpu_global.h"

void atender_cpu_kernel_interrupt();
void enviar_nombre_a_kernel_interrupt();
void recibir_bloqueo(int socket);
#endif