#include "ft_ping.h"

volatile sig_atomic_t g_sigint_received = 0;
volatile sig_atomic_t g_child_status_changed = 0;

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        printf("❌ Use: %s must have PROG [ARGS] ❌\n", argv[0]);
        return (1);
    }
    init_signal();
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