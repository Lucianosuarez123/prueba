#include "../includes/memoria.h"

int main(int argc, char* argv[]) {
    //INICIAR MEMORIA
    iniciar_memoria();
    //INICIAR SERVIDOR KERNEL
    puerto_escucha_kernel_fd = iniciar_servidor(PUERTO_ESCUCHA, memoria_logger);
    log_info(memoria_log_debug, "Se inicio el server para kernel!");
    //INICIAR SERVIDOR CPU
     puerto_escucha_cpu_fd= iniciar_servidor(PUERTO_ESCUCHA, memoria_logger);
     log_info(memoria_log_debug, "Se inicio el server para CPU!");
    // ESPERAR CLIENTE KERNEL
    cl_kernel_fd=esperar_cliente(puerto_escucha_kernel_fd,memoria_logger);
    log_info(memoria_log_debug, "Se conecto KERNEL!");

     //Esperar cliente CPU
     cl_cpu_fd=esperar_cliente(puerto_escucha_cpu_fd, memoria_logger);
     log_info(memoria_log_debug, "Se conecto CPU!");

    //Atender los mensajes de CPU
    pthread_t hilo_cpu;
    pthread_create(&hilo_cpu,NULL,(void*)atender_memoria_cpu,NULL);
    pthread_detach(hilo_cpu);
    //Atender los mensajes de Kernel
    pthread_t hilo_kernel;
    pthread_create(&hilo_kernel,NULL,(void*)atender_memoria_kernel,NULL);
    pthread_join(hilo_kernel,NULL);
}
