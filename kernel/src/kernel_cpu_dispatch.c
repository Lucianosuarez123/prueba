#include "../includes/kernel_cpu_dispatch.h"

void atender_kernel_cpu_dispatch(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(cl_dispatch_fd);
		switch (cod_op) {
		case ENVIAR_NOMBRE_CPU_DISPATCH_KERNEL:
			recibir_nombre_cpu_dispatch(cl_dispatch_fd);
			break;
		default:
			log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}

}
void recibir_nombre_cpu_dispatch(int socket_dispatch){
	t_buffer* buffer= recibir_buffer(socket_dispatch);
	char* nombre_cpu_dispatch = extraer_string(buffer);
	log_info(kernel_log_debug, "El nombre del cpu dispatch: %s", nombre_cpu_dispatch);
	liberar_buffer(buffer);
}