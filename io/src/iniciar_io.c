#include "../includes/iniciar_io.h"
void iniciar_io(){
    iniciar_config();
    iniciar_logger();
    imprimir_logger();
}


void iniciar_logger(){
    io_logger = log_create("io.log", "CL,LOG", 1, LOG_LEVEL_INFO);
    if(io_logger == NULL){
        perror("Log Nulo. No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }
    io_log_debug = log_create("io.log", "CL,LOG", 1, LOG_LEVEL_TRACE);
    if(io_log_debug == NULL){
        perror("Log Nulo. No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }
}
void iniciar_config(){
    io_config = config_create("../io.config");
    if(io_config == NULL){
        io_config = config_create("./io.config");
        if(io_config == NULL){
            perror("No se pudo cargar el archivo de configuracion");
            exit(EXIT_FAILURE);
        }
}
    
    
    IP_KERNEL = config_get_string_value(io_config , "IP_KERNEL");
    PUERTO_KERNEL =config_get_string_value(io_config , "PUERTO_KERNEL");
    LOG_LEVEL = config_get_string_value(io_config , "LOG_LEVEL");
    if(IP_KERNEL == NULL || PUERTO_KERNEL == NULL || LOG_LEVEL == NULL){
        perror("Error al intentar cargar el config.");
        exit(EXIT_FAILURE);
    }
}
void imprimir_logger(){
    log_info(io_logger, "IP_KERNEL: %s", IP_KERNEL);
}

