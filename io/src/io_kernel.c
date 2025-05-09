#include "../includes/io_kernel.h"

void atender_io_kernel(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(cl_io_fd); //este
		switch (cod_op) {
		case BLOQUEAR_DISPOSITIVO_IO:
			recibir_bloqueo(cl_io_fd);
			break;
		case -1:
			log_error(io_logger, "DESCONEXION DE KERNEL.");
			salida = 0;
		//  exit(EXIT_FAILURE);
			break;
		default:
			log_warning(io_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}

void enviar_nombre_a_kernel(){
	t_buffer* buffer = crear_buffer();
	log_info(io_log_debug, "creo buffer ");
	agregar_string_a_buffer(buffer, nombre_io);
	log_info(io_log_debug, "agrego string al buffer ");
	t_paquete* paquete= crear_paquete_con_codigo_de_operacion(ENVIAR_NOMBRE_DE_IO_A_KERNEL, buffer);
	log_info(io_log_debug, "creo paquete ");
	serializar_paquete(paquete);
	log_info(io_log_debug, "serializo paquete ");
	enviar_paquete(paquete, cl_io_fd);
	log_info(io_log_debug, "envio paquete ");
	liberar_paquete(paquete);
	log_info(io_log_debug, "libero paquete ");
}

void recibir_bloqueo(int socket) {//? no se si es necesario el socket como argumento, Y ademas hay que ver si hay multiples dispositivos de entrada
	t_buffer* buffer= recibir_buffer(socket);
	int pid = extraer_int(buffer);
	int tiempo_bloqueo = extraer_int(buffer);
	//TODO: VER COMO ES EL TEMA DEL LOG OBLIGATORIO: Inicio de IO: “## PID: <PID> - Inicio de IO - Tiempo: <TIEMPO_IO>”.
	log_info(io_log_debug, "El pid es: %d", pid);
	log_info(io_log_debug, "El tiempo de bloqueo es: %d", tiempo_bloqueo);
	liberar_buffer(buffer);
}