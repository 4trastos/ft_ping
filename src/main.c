#include "ft_ping.h"

volatile sig_atomic_t g_sigint_received = 0;
volatile sig_atomic_t g_sigalrm_received = 0;

void    cleanup(struct config *conf)
{
    if (conf->sockfd != -1)
        close(conf->sockfd);
    if (conf->packet != NULL)
        free(conf->packet);
    free(conf);
}

int main(int argc, char **argv)
{
    struct config   *conf;
    int             exit = 0;
    unsigned char   *bytes;

    if (argc < 2)
    {
        printf("%s: usage error: Destination address required \n", argv[0]);
        return (1);
    }
    
    conf = malloc(sizeof(struct config));
    if (!conf)
        return (1);
    init_signal();
    init_struct(conf);
    if (ft_parser(conf, argv, argc) == -1)
        exit = 1;
    else if (conf->show_help == true)
    {
        show_help();
        exit = 0;
    }
    else if (dns_resolution(conf) == -1)
        exit = 1;
    else if (socket_creation(conf) == -1)
        exit = 1;
    else if (icmp_creation(conf) == -1)
        exit = 1;
    // 6. **Envío** (sin recepción)
    // 7. **Recepción** y cálculo RTT
    // 8. **Bucle principal** completo
    else
    {
        bytes = (unsigned char *)&conf->ip_address;
        while(!g_sigint_received)
        {
            if (icmp_creation(conf) == -1)
            {
                exit = 1;
                break;
            }

            printf("[DEBUG:] bucle principal - sequence: ( %d )\n", conf->packet->icmp_hdr.un.echo.sequence);
            printf("[DEBUG:] Verbose: ( %d ) · Help: ( %d ) · Valid: ( %d ) · Hostname: ( %s )\n", conf->verbose_mode, conf->show_help, conf->is_valid, conf->hostname);
            printf("[DEBUG:] IP ADDRESS: ( %d.%d.%d.%d )\n", bytes[0], bytes[1], bytes[2], bytes[3]);
            printf("[DEBUG:] SOCKET -> socket fd: ( %d )\n", conf->sockfd);
            printf("[DEBUG:] CHECKSUM: ( %d )\n", conf->packet->icmp_hdr.checksum);
            printf("[DEBUG HEX:] ICMP data: ( %02x.%02x.%02x.%02x )\n", conf->packet->icmp_hdr.type, conf->packet->icmp_hdr.checksum, conf->packet->icmp_hdr.un.echo.id, conf->packet->icmp_hdr.un.echo.sequence);
            sleep(2);
        };   
    }

    // 9. **Estadísticas** finales
    // 10. **Testing** y ajustes de formato

    cleanup(conf);
    return (exit);
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



// H23&&mwub-JCha&7asg??!!-kuzfih

// Himwub-vixzi9-kuzfih