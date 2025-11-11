#include "ft_ping.h"

int send_reply(struct config *conf)
{
    struct sockaddr_in *dest_addr;
    ssize_t bytes_sent;

    dest_addr = malloc(sizeof(struct sockaddr_in));
    if (!dest_addr)
        return (-1);
    memset(dest_addr, 0, sizeof(struct sockaddr_in));
    dest_addr->sin_family = AF_INET;
    dest_addr->sin_addr = conf->ip_address;

    bytes_sent = sendto(conf->sockfd, conf->packet, sizeof(struct ping_packet), 0, (struct sockaddr*)dest_addr, sizeof(*dest_addr));
    if (bytes_sent == -1)
    {
        printf("ft_ping: sendto: %s\n", strerror(errno));
        free(dest_addr);
        return (-1);
    }
    if (conf->verbose_mode)
        printf("Packet sent successfully - Sequence: %d\n", conf->sequence);
    
    free(dest_addr);
    return (0);
}