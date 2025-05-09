#include "../includes/iniciar_cpu.h"


 void iniciar_loggers(){ 
    cpu_logger = log_create("cliente.log", "CL_LOG", 1, LOG_LEVEL_INFO);
    if (cpu_logger == NULL){
        perror("No se pudo crear o encontrar el archivo. (log CPU)");
        exit(EXIT_FAILURE);
    }
     cpu_debug_logger = log_create("cliente.log", "CL_LOG", 1, LOG_LEVEL_INFO);
    if (cpu_debug_logger == NULL){
        perror("No se pudo crear o encontrar el archivo. (log debug CPU)");
        exit(EXIT_FAILURE);
    }
    }

    void iniciar_config(){
    cpu_config = config_create("../cpu.config");
    if(cpu_config == NULL){
        cpu_config = config_create("./cpu.config");
        if(cpu_config == NULL){
            perror("No se pudo cargar el archivo de configuracion");
            exit(EXIT_FAILURE);
        }
    }  
    IP_MEMORIA = config_get_string_value(cpu_config, "IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(cpu_config, "PUERTO_MEMORIA");
    IP_KERNEL = config_get_string_value(cpu_config, "IP_KERNEL");
    PUERTO_ESCUCHA_DISPATCH = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_DISPATCH");
    PUERTO_ESCUCHA_INTERRUPT = config_get_string_value(cpu_config, "PUERTO_ESCUCHA_INTERRUPT");
    // LOG_LEVEL = config_get_string_value(cpu_config, "LOG_LEVEL");

    log_info(cpu_logger, "IP_MEMORIA: %s", IP_MEMORIA);
    log_info(cpu_debug_logger, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
    log_info(cpu_logger, "IP_KERNEL: %s", IP_KERNEL);
    log_debug(cpu_debug_logger, "PUERTO_ESCUCHA_DISPATCH: %s", PUERTO_ESCUCHA_DISPATCH);
    log_trace(cpu_debug_logger, "PUERTO_ESCUCHA_INTERRUPT: %s", PUERTO_ESCUCHA_INTERRUPT);

    if(IP_MEMORIA == NULL || PUERTO_MEMORIA == NULL || IP_KERNEL == NULL || PUERTO_ESCUCHA_DISPATCH == NULL || PUERTO_ESCUCHA_INTERRUPT == NULL){
    printf("Error al intentar cargar el config.");
    exit(EXIT_FAILURE);}

}
                  
void inicializar_cpu(){
    iniciar_loggers();
    iniciar_config();
}


   

/* int conectar_a_servidor(char* ip, int puerto, char* nombre) {
    struct sockaddr_in direccion;
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = inet_addr(ip);
    direccion.sin_port = htons(puerto);

    int socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(socket_cliente, (void*)&direccion, sizeof(direccion)) != 0) {
        log_error(logger, "No se pudo conectar con %s", nombre);
        return -1;
    }

    log_info(logger, "Conectado a %s (socket: %d)", nombre, socket_cliente);
    return socket_cliente;
}
int get_log_level_from_string(const char* level) {
    if (strcmp(level, "TRACE") == 0) return LOG_LEVEL_TRACE;
    if (strcmp(level, "DEBUG") == 0) return LOG_LEVEL_DEBUG;
    if (strcmp(level, "INFO") == 0) return LOG_LEVEL_INFO;
    if (strcmp(level, "WARNING") == 0) return LOG_LEVEL_WARNING;
    if (strcmp(level, "ERROR") == 0) return LOG_LEVEL_ERROR;
    return LOG_LEVEL_INFO; 
}
 */

