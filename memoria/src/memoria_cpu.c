#include "../includes/memoria_cpu.h"

void atender_memoria_cpu(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(cl_cpu_fd);
		switch (cod_op) {
		case -1:
			log_error(memoria_logger, "DESCONEXION DE CPU.");
			salida = 0;
		//  exit(EXIT_FAILURE);
			break;
		default:
			log_warning(memoria_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}