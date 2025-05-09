#include "../includes/memoria_kernel.h"

void atender_memoria_kernel(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(cl_kernel_fd);
		switch (cod_op) {
		case -1:
			log_error(memoria_logger, "DESCONEXION DE KERNEL.");
			salida = 0;
		//  exit(EXIT_FAILURE);
			break;
		default:
			log_warning(memoria_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}