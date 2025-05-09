#include "../includes/kernel_cpu_interrupt.h"

void atender_kernel_cpu_interrupt(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(cl_interrupt_fd);
		switch (cod_op) {
		case ENVIAR_NOMBRE_CPU_INTERRUPT_KERNEL:
			recibir_nombre_cpu_interrupt(cl_interrupt_fd);
			break;
		default:
			log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}
void recibir_nombre_cpu_interrupt(int socket_interrupt){
	t_buffer* buffer= recibir_buffer(socket_interrupt);
	char* nombre_cpu_interrupt = extraer_string(buffer);
	log_info(kernel_log_debug, "El nombre del cpu interrupt es: %s", nombre_cpu_interrupt);
	liberar_buffer(buffer);
}