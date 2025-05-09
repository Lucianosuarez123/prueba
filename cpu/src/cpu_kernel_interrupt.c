#include "../includes/cpu_kernel_interrupt.h"

void atender_cpu_kernel_interrupt(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(socket_kernel_interrupt_fd);
		switch (cod_op) {
		case -1:
			log_error(cpu_logger, "DESCONEXION KERNEL - INTERRUPT.");
			salida = 0;
		//  exit(EXIT_FAILURE);
			break;
		default:
			log_warning(cpu_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}
void enviar_nombre_a_kernel_interrupt(){
	t_buffer* buffer = crear_buffer();
	agregar_string_a_buffer(buffer, nombre_cpu);
	t_paquete* paquete= crear_paquete_con_codigo_de_operacion(ENVIAR_NOMBRE_CPU_INTERRUPT_KERNEL, buffer);
	serializar_paquete(paquete);
	enviar_paquete(paquete, cl_interrupt_fd);
	log_info(cpu_debug_logger, "envio paquete ");
	liberar_paquete(paquete);
}