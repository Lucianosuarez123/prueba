#include "../includes/kernel_memoria.h"

void atender_kernel_memoria(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(memoria_fd);
		switch (cod_op) {
		case -1:
			log_error(kernel_logger, "DESCONEXION DE MEMORIA.");
			salida = 0;
		//  exit(EXIT_FAILURE);
			break;
		default:
			log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}