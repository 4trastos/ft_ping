#include "ft_ping.h"

int     socket_creation(struct config *conf)
{
    int ttl = 64;

    conf->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (conf->sockfd == -1)
    {
        return (-1);
    }
    if (setsockopt(conf->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
    {
        return (-1);
    }
    return (0);
}


// ====================================================================
//  crear socket:       raw_socket = socket(AF_INET, SOCK_RAW, int protocol);
//  crear endpoint:     int socket(int domain, int type, int protocol);
//  enviar:             ssize_t sendto(int sockfd, const void buf[.len], size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
//                      ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
//  recibir:            ssize_t recvfrom(int sockfd, void buf[restrict .len], size_t len, int flags, struct sockaddr *_Nullable restrict src_addr, socklen_t *_Nullable restrict addrlen);
//                      ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags); **** Más potente, permite acceder a información adicional (TTL, etc.) ****
//  leer:               int getsockopt(int sockfd, int level, int optname, void optval[restrict *.optlen], socklen_t *restrict optlen);
// =====================================================================


// =====================================================================
// Funciones que podría añadir:

//     gettimeofday() - Para timestamps y calcular RTT

//     inet_pton() - Para convertir direcciones IP

//     gethostbyname() - Para resolución DNS de nombres

//     signal() - Para manejar Ctrl+C (SIGINT) y mostrar estadísticas

// Puntos importantes:

//     Privilegios: Necesitarás ejecutar como root (por el socket raw)

//     Checksum ICMP: Debes calcularlo manualmente

//     Estructuras: Necesitarás definir estructuras para IP header + ICMP header

//     Timeouts: Configurar timeout en recepción para no bloquearse indefinidamente
// =====================================================================


