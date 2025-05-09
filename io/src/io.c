#include "../includes/io.h"

int main(int argc, char* argv[]) {
    //iniciar io
    nombre_io = argv[1];
    iniciar_io();
    //Conectarse con el servidor
    cl_io_fd= crear_conexion_cliente(IP_KERNEL, PUERTO_KERNEL);
    enviar_nombre_a_kernel();
    //atender los mensajes de kernel
    pthread_t hilo_kernel;
    pthread_create(&hilo_kernel,NULL,(void*)atender_io_kernel,NULL);
    pthread_join(hilo_kernel,NULL);
    
}

