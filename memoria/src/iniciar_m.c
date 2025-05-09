#include "../includes/iniciar_m.h"

void iniciar_memoria() {
    iniciar_loggers();
    iniciar_config();
    imprimir_configs();
}

void iniciar_loggers() {
    memoria_logger = log_create("memoria.log", "MEMORIA", true, LOG_LEVEL_INFO);
    if (memoria_logger == NULL) {
        perror("No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }

    memoria_log_debug = log_create("memoria.log", "MEMORIA", true, LOG_LEVEL_TRACE);
    if (memoria_log_debug == NULL) {
        perror("No se pudo crear o encontrar el archivo");
        exit(EXIT_FAILURE);
    }
}

void iniciar_config() {
    memoria_config = config_create("../memoria.config");
    if(memoria_config == NULL){
        memoria_config = config_create("./memoria.config");
        if(memoria_config == NULL){
            perror("No se pudo cargar el archivo de configuracion");
            exit(EXIT_FAILURE);
        }
}
PUERTO_ESCUCHA = config_get_string_value(memoria_config, "PUERTO_ESCUCHA");
TAM_MEMORIA = config_get_string_value(memoria_config, "TAM_MEMORIA");
TAM_PAGINA = config_get_string_value(memoria_config, "TAM_PAGINA");
ENTRADAS_POR_TABLA = config_get_string_value(memoria_config, "ENTRADAS_POR_TABLA");
CANTIDAD_NIVELES = config_get_string_value(memoria_config, "CANTIDAD_NIVELES");
RETARDO_MEMORIA = config_get_string_value(memoria_config, "RETARDO_MEMORIA");
PATH_SWAPFILE = config_get_string_value(memoria_config, "PATH_SWAPFILE");
RETARDO_SWAP = config_get_string_value(memoria_config, "RETARDO_SWAP");
LOG_LEVEL = config_get_string_value(memoria_config, "LOG_LEVEL");
DUMP_PATH = config_get_string_value(memoria_config, "DUMP_PATH");
}
void imprimir_configs(){
    log_info(memoria_logger, "Entradas por tabla: %s", ENTRADAS_POR_TABLA);
}


