# ft_ping
### Explicación de cómo funciona `ping`

**1. Propósito básico:**
`ping` es una utilidad de diagnóstico que verifica la conectividad entre dos máquinas en una red IP. Utiliza el protocolo **ICMP (Internet Control Message Protocol)** para enviar un mensaje **ECHO_REQUEST** y espera una respuesta **ECHO_REPLY** desde el destino.

---

**2. Flujo paso a paso:**

- **Paso 1: Resolución de DNS (si es necesario):**  
  Si se proporciona un nombre de dominio (FQDN), `ping` lo resuelve a una dirección IPv4 usando el sistema DNS. En tu caso, el sujeto indica que **no debes hacer la resolución DNS en el retorno del paquete**, pero sí en el inicio.

- **Paso 2: Creación del socket:**  
  Se crea un socket **raw** de tipo **SOCK_RAW** con el protocolo **ICMP**. Este socket permite enviar y recibir paquetes ICMP directamente.

- **Paso 3: Construcción del paquete ICMP ECHO_REQUEST:**  
  - **Cabecera IP:** Se construye con la dirección destino, TTL (Time To Live), etc.  
  - **Cabecera ICMP:**  
    - **Tipo:** 8 (ECHO_REQUEST)  
    - **Código:** 0  
    - **Checksum:** Se calcula sobre toda la cabecera ICMP y los datos.  
    - **Identificador (ID):** Generalmente el PID del proceso.  
    - **Número de secuencia:** Incremental para cada paquete enviado.  
  - **Datos:** Pueden ser arbitrarios, pero suelen incluir un timestamp para calcular el RTT.

- **Paso 4: Envío del paquete:**  
  Se envía el paquete a la dirección destino usando `sendto()`.

- **Paso 5: Recepción de la respuesta (ECHO_REPLY):**  
  - Se espera a recibir un paquete con `recvmsg()` o `recvfrom()`.  
  - El tipo ICMP debe ser **0** (ECHO_REPLY).  
  - Se verifica que el ID coincida con el del proceso.  
  - Se calcula el **RTT (Round-Trip Time)** restando el timestamp actual del timestamp enviado.

- **Paso 6: Estadísticas:**  
  - Se muestran paquetes enviados/recibidos, % de pérdida, y RTT (mínimo, promedio, máximo).  
  - Al terminar (con `SIGINT`), se muestra un resumen.

---

**3. Manejo de errores:**
- Si no hay respuesta, se debe indicar "Request timeout".
- Errores como "Destination Unreachable" se reciben como mensajes ICMP de error.

---

**4. Opciones relevantes en el sujeto:**
- `-v`: Modo verbose, muestra más detalles (errores, problemas con paquetes).
- `-?`: Muestra la ayuda.

---

### Qué debes hacer para aprobar el proyecto `ft_ping`

**1. Requisitos obligatorios:**
- **Nombre del ejecutable:** `ft_ping`.
- **Referencia:** Comportamiento similar a `ping` de `inetutils-2.0`.
- **Opciones obligatorias:**  
  - `-v`: Verbose (muestra errores sin detener el programa).  
  - `-?`: Muestra ayuda (usage).
- **Parámetros:**  
  - Aceptar dirección IPv4 o nombre de dominio (FQDN).  
  - No hacer resolución DNS inversa en la respuesta (pero sí en la inicial).
- **Manejo de señales:**  
  - Al recibir `SIGINT` (Ctrl+C), mostrar estadísticas y salir.
- **Cálculo de RTT:**  
  - Mostrar el tiempo de ida y vuelta para cada paquete.
- **Estadísticas finales:**  
  - Paquetes enviados/recibidos, % de pérdida, RTT mínimo/promedio/máximo.
- **Indentación:**  
  - La salida debe ser idéntica a `inetutils-2.0`, excepto en la línea de RTT y resolución DNS inversa.

---

**2. Restricciones técnicas:**
- **Lenguaje:** C.
- **Funciones permitidas:** Todas las de `libc` y `printf`.
- **Prohibido:**  
  - Usar el `ping` del sistema o sus fuentes.  
  - Llamar a un `ping` real desde tu código.
- **Manejo de errores:**  
  - Sin segfaults, double free, etc.  
  - Salida controlada ante errores.

---

**3. Consejos para la implementación:**
- Usar **sockets raw** con `SOCK_RAW` e `IPPROTO_ICMP`.
- Permisos necesarios de **superusuario** (o capacidades `CAP_NET_RAW`) para ejecutarlo.
- Calcula el **checksum ICMP** correctamente.
- Usa `gettimeofday()` para los timestamps.
- Maneja correctamente la **estructura del paquete ICMP** y **cabecera IP**.

---

**4. Bonús (opcional, solo si el obligatorio es perfecto):**
- Implementar opciones como:  
  `-f` (flood), `-l` (preload), `-n` (no resolver DNS), `-w` (deadline), `-W` (timeout), `-s` (tamaño de paquete), `-t` (TTL), etc.

---

**Resumen final:**
Crear un clon de `ping` que envíe paquetes ICMP ECHO_REQUEST, reciba las respuestas, calcule el RTT y muestre estadísticas, todo ello con un formato y comportamiento similares al `ping` de referencia, manejando correctamente los casos de error y las opciones requeridas.
