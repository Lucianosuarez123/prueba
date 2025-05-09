#include "../includes/cpu.h"
int main(int argc, char* argv[]) {
    //INICIAR CPU
    nombre_cpu = argv[1];
    inicializar_cpu();


    
    //UNIRSE A MEMORIA
    socket_memoria_fd = crear_conexion_cliente(IP_MEMORIA, PUERTO_MEMORIA);
    //UNIRSE A KERNEL DISPATCH
    socket_kernel_dispatch_fd = crear_conexion_cliente(IP_KERNEL, PUERTO_ESCUCHA_DISPATCH);
    // UNIRSE A KERNEL INTERRUPT
    socket_kernel_interrupt_fd = crear_conexion_cliente(IP_KERNEL, PUERTO_ESCUCHA_INTERRUPT);
    log_info(cpu_debug_logger, "CPU iniciada");

    enviar_nombre_a_kernel_dispatch();
    enviar_nombre_a_kernel_interrupt();
    
    //Atender los mensajes de kernel - DISPATCH
    pthread_t hilo_kernel_dispatch;
    pthread_create(&hilo_kernel_dispatch,NULL,(void*)atender_cpu_kernel_dispatch,NULL);
    pthread_detach(hilo_kernel_dispatch);
    //Atender los mensajes de Kernel - INTERRUPT
    pthread_t hilo_kernel_interrupt;
    pthread_create(&hilo_kernel_interrupt,NULL,(void*)atender_cpu_kernel_interrupt,NULL);
    pthread_detach(hilo_kernel_interrupt);
    //Atender los mensajes de memoria
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria,NULL,(void*)atender_cpu_memoria,NULL);
    pthread_join(hilo_memoria,NULL);

    // Esperar mensajes, por ahora no hace más que conectarse.
   /*  // Limpieza
    close(socket_memoria_fd);
    close(socket_kernel_dispatch_fd);
    close(socket_kernel_interrupt_fd);
    config_destroy(config);
    log_destroy(logger); */

    return 0;
} 