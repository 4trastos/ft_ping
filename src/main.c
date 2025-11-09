#include "ft_ping.h"

volatile sig_atomic_t g_sigint_received = 0;
volatile sig_atomic_t g_sigalrm_received = 0;

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        printf("❌ Use: %s must have PROG [ARGS] ❌\n", argv[0]);
        return (1);
    }
    
    init_signal();
    // 1. **Parser** (-v, -?)
    // 2. **Resolución DNS** 
    // 3. **Socket creation** (sin enviar todavía)
    // 4. **Signal handlers**
    // 5. **Creación paquete ICMP** + checksum
    // 6. **Envío** (sin recepción)
    // 7. **Recepción** y cálculo RTT
    // 8. **Bucle principal** completo
    // 9. **Estadísticas** finales
    // 10. **Testing** y ajustes de formato
    while(!g_sigint_received)
    {
        printf("bucle principal\n");     
    };
    return (0);
}

// ====================================================
//         Estructura típica de uso:
// ====================================================
//              1. Crear socket
//
//      int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
//
//              2. Configurar opciones (TTL, timeout)
//
//      int ttl = 64;
//      setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
//
//              3. Construir paquete ICMP
//
//      struct icmp_packet packet;
//          ... llenar con ECHO_REQUEST
//
//              4. Enviar
//
//      sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
//
//              5. Recibir respuesta
//
//      recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&src_addr, &addrlen);
// ====================================================