#include "ft_ping.h"

double      calculate_rtt(struct ping_packet *sent_packet)
{
    struct timeval now;
    struct timeval diff;

    gettimeofday(&now, NULL);
    timersub(&now, &sent_packet->timestamp, &diff);

    return ((diff.tv_sec * 1000.0) + (diff.tv_usec / 1000.0));
}

int receive_response(struct config *conf)
{
    struct sockaddr_in  src_adrr;
    struct iphdr        *ip_header;
    struct icmphdr      *icmp_reply;
    socklen_t           addr_len = sizeof(src_adrr);
    char                recv_buffer[1024];
    ssize_t             bytes_received;
    double              rtt;

    bytes_received = recvfrom(conf->sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *)&src_adrr, &addr_len);
    if (bytes_received == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            // Timeout - paquete perdido
            if (conf->verbose_mode)
                printf("Timeout for sequence %d\n", conf->sequence);
            return (-1);
        }
        printf("ft_ping: recvfrom error: %s\n", strerror(errno));
        return (-1);
    }

    ip_header = (struct iphdr *)recv_buffer;
    icmp_reply = (struct icmphdr *)(recv_buffer + (ip_header->ihl * 4));        // El ICMP header está después del IP header

    // Verificar que es respuesta a NUESTRO paquete
    if (icmp_reply->un.echo.id == conf->packet->icmp_hdr.un.echo.id)
    {
        rtt = calculate_rtt(conf->packet);
        conf->stats.packets_received++;
        conf->stats.total_rtt += rtt;

        if (conf->stats.packets_received == 1)
        {
            conf->stats.max_rtt = rtt;
            conf->stats.min_rtt = rtt;
        }
        else
        {
            if (rtt < conf->stats.min_rtt)
                conf->stats.min_rtt = rtt;
            if (rtt > conf->stats.max_rtt)
                conf->stats.max_rtt = rtt;
        }

        printf("%ld bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n",
               bytes_received - (ip_header->ihl * 4),  // Tamaño ICMP
               conf->hostname,                         // Hostname
               inet_ntoa(src_adrr.sin_addr),           // IP origen
               icmp_reply->un.echo.sequence,           // Sequence
               ip_header->ttl,                         // TTL
               calculate_rtt(conf->packet));           // RTT
    }
    return (0);
}

int send_reply(struct config *conf)
{
    struct sockaddr_in  *dest_addr;
    ssize_t             bytes_sent;

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
    conf->stats.packets_sent++;
    free(dest_addr);
    return (0);
}