#include "../includes/kernel.h"
int main(int argc, char* argv[]) {
    //INICIAR KERNEL
    iniciar_kernel();
    //Iniciar servidor de IO
    escucha_io_fd = iniciar_servidor(PUERTO_ESCUCHA_IO, kernel_logger);
    //Iniciar servidor de CPU
    escucha_dispatch_fd = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, kernel_logger);
    escucha_interrupt_fd = iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, kernel_logger);
    //Iniciar como cliente de memoria
    memoria_fd = crear_conexion_cliente(IP_MEMORIA,PUERTO_MEMORIA);

    //esperar que se conecte io
    cl_io_fd = esperar_cliente(escucha_io_fd, kernel_logger);
    log_info(kernel_log_debug, "Se conecto IO!");
    //esperar que se conecte cpu
    cl_dispatch_fd = esperar_cliente(escucha_dispatch_fd, kernel_logger);
    log_info(kernel_log_debug, "Se conecto CPU - DISPATCH!");
    cl_interrupt_fd = esperar_cliente(escucha_interrupt_fd, kernel_logger);
    log_info(kernel_log_debug, "Se conecto CPU - INTERRUPT!");

    //Atender los mensajes de cpu - DISPATCH
    pthread_t hilo_cpu_dispatch;
    pthread_create(&hilo_cpu_dispatch, NULL, (void*)atender_kernel_cpu_dispatch, NULL);
    pthread_detach(hilo_cpu_dispatch);
    //Atender los mensajes de cpu- INTERRUPT
    pthread_t hilo_cpu_interrupt;
    pthread_create(&hilo_cpu_interrupt,NULL,(void*)atender_kernel_cpu_interrupt,NULL);
    pthread_detach(hilo_cpu_interrupt);
    //Atender los mensajes de io
    pthread_t hilo_io;
    pthread_create(&hilo_io,NULL,(void*)atender_kernel_io,NULL);
    pthread_detach(hilo_io);
    log_info(kernel_log_debug,"Kernel: Esperando mensajes de  IO");
    //Atender los mensajes de memoria
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria,NULL,(void*)atender_kernel_memoria,NULL);
    pthread_join(hilo_memoria,NULL);


return EXIT_SUCCESS;
}
