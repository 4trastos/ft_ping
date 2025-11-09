#include "ft_ping.h"

// PASO A PASO - PARSER DE ARGUMENTOS
// PASO 1: Definir estructura de configuración

//     Crear struct para guardar: verbose_mode, hostname, ip_address

// PASO 2: Función de parser principal

//     Recorrer argv empezando desde argv[1]

//     Identificar opciones que empiezan con -

//     Para -v: activar modo verbose

//     Para -?: mostrar ayuda y salir

//     El primer argumento que NO empiece con - es el hostname destino

// PASO 3: Validaciones

//     Máximo 1 hostname permitido

//     Opciones desconocidas → error

//     Si solo hay opciones sin hostname → error

//     Si no hay argumentos → error (ya lo tienes en main)

// PASO 4: Guardar configuración

//     Rellenar la struct con las opciones parseadas

//     El hostname queda listo para resolución DNS

