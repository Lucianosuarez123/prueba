#include "../includes/cpu_memoria.h"

void atender_cpu_memoria(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(socket_memoria_fd);
		switch (cod_op) {
		case -1:
			log_error(cpu_logger, "Desconexion de memoria");
			salida = 0;
		//	exit(EXIT_FAILURE);
			break;
		default:
			log_warning(cpu_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}