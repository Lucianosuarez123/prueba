#include "../includes/iniciar_k.h"
void iniciar_kernel(){
    iniciar_loggers();
    iniciar_config();
    imprimir_configs();
}
void iniciar_loggers(){
    kernel_logger = log_create("cliente.log", "CL_LOG", 1, LOG_LEVEL_INFO);
if(kernel_logger == NULL){
    perror("Log nulo, no se pudo crear o encontrar el archivo.");
    exit(EXIT_FAILURE);
}
kernel_log_debug = log_create("cliente.log", "CL,LOG", 1, LOG_LEVEL_TRACE);
if(kernel_log_debug == NULL){
    perror("Log Nulo. No se pudo crear o encontrar el archivo");
    exit (EXIT_FAILURE);
}
}
void iniciar_config(){
    kernel_config = config_create("../kernel.config");
    if(kernel_config == NULL){
        kernel_config = config_create("./kernel.config");
        if(kernel_config == NULL){
            perror("No se pudo cargar el archivo de configuracion");
            exit(EXIT_FAILURE);
        }
}
IP_MEMORIA = config_get_string_value(kernel_config, "IP_MEMORIA");
PUERTO_MEMORIA = config_get_string_value(kernel_config, "PUERTO_MEMORIA");
PUERTO_ESCUCHA_DISPATCH = config_get_string_value(kernel_config, "PUERTO_ESCUCHA_DISPATCH");
PUERTO_ESCUCHA_INTERRUPT = config_get_string_value(kernel_config, "PUERTO_ESCUCHA_INTERRUPT");
PUERTO_ESCUCHA_IO = config_get_string_value(kernel_config, "PUERTO_ESCUCHA_IO");
ALGORITMO_PLANIFICACION = config_get_string_value(kernel_config, "ALGORITMO_PLANIFICACION");
ALGORITMO_COLA_NEW = config_get_string_value(kernel_config, "ALGORITMO_COLA_NEW");
ALFA = config_get_string_value(kernel_config, "ALFA");
TIEMPO_SUSPENSION = config_get_string_value(kernel_config, "TIEMPO_SUSPENSION");
LOG_LEVEL = config_get_string_value(kernel_config, "LOG_LEVEL");

if(IP_MEMORIA == NULL || PUERTO_MEMORIA == NULL || PUERTO_ESCUCHA_DISPATCH == NULL || PUERTO_ESCUCHA_INTERRUPT == NULL || PUERTO_ESCUCHA_IO == NULL || ALGORITMO_PLANIFICACION == NULL || ALGORITMO_COLA_NEW == NULL || ALFA == NULL || TIEMPO_SUSPENSION == NULL || LOG_LEVEL == NULL){
    printf("Error al intentar cargar el config.");
    exit(EXIT_FAILURE);}

}
void imprimir_configs(){
log_info(kernel_logger, "KERNEL ALGORITMO PLANIFICACION: %s", ALGORITMO_PLANIFICACION);
}
