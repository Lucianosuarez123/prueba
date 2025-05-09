#include "../includes/kernel_io.h"

void atender_kernel_io(){
	bool salida = 1;
	while (salida) {
		int cod_op = recibir_operacion(cl_io_fd);
		//todo: ver si hay que poner aca esta linea: *t_buffer buffer= recibir_buffer(socket); , ya que creo que todos los llamados lo utilizan
		switch (cod_op) {
		case ENVIAR_NOMBRE_DE_IO_A_KERNEL:
			recibir_nombre_io(cl_io_fd);
			break;
		case -1:
			log_error(kernel_logger, "DESCONEXION DE IO.");
			salida = 0;
		//  exit(EXIT_FAILURE);
			break;
		default:
			log_warning(kernel_logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
}


void recibir_nombre_io(int socket) {//? no se si es necesario el socket como argumento, ya que el socket de io es variable global
	t_buffer* buffer= recibir_buffer(socket);
	char* nombre_io = extraer_string(buffer);
	log_info(kernel_log_debug, "El nombre del io es: %s", nombre_io);
	liberar_buffer(buffer);
}

void enviar_bloqueo_io(int socket,int pid, int tiempo_bloqueo) {
	t_buffer* buffer = crear_buffer();
	agregar_int_a_buffer(buffer, pid);
	agregar_int_a_buffer(buffer, tiempo_bloqueo);
	t_paquete* paquete = crear_paquete_con_codigo_de_operacion(BLOQUEAR_DISPOSITIVO_IO, buffer);
	enviar_paquete(paquete, socket);
	liberar_paquete(paquete);
}
