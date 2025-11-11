#include "ft_ping.h"

int     socket_creation(struct config *conf)
{
    struct timeval  timeout = {9, 0};
    int             ttl = 64;

    conf->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (conf->sockfd == -1)
    {
        if (errno == EPERM)
            printf("ft_ping: socket: Operation not permitted. Must be root.\n");
        else
            printf("ft_ping: socket: ( %s )\n", strerror(errno));
        return (-1);
    }
    if (setsockopt(conf->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
    {
        printf("ft_ping: setsockopt: %s\n", strerror(errno));
        close(conf->sockfd);
        return (-1);
    }
    if (setsockopt(conf->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    {
        printf("ft_ping: setsockopt: %s\n", strerror(errno));
        close(conf->sockfd);
        return (-1);
    }
    return (0);
}
