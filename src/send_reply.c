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
    uint16_t            seq;
    double              rtt;

    bytes_received = recvfrom(conf->sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *)&src_adrr, &addr_len);
    if (bytes_received == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
            return (-1);
        printf("ft_ping: recvfrom error: %s\n", strerror(errno));
        return (-1);
    }

    ip_header = (struct iphdr *)recv_buffer;
    icmp_reply = (struct icmphdr *)(recv_buffer + (ip_header->ihl * 4));        // El ICMP header está después del IP header

    // Verificar que es respuesta a NUESTRO paquete
    if (icmp_reply->type == ICMP_ECHOREPLY && icmp_reply->un.echo.id == getpid())
    {
        seq = icmp_reply->un.echo.sequence;
        rtt = calculate_rtt(&conf->packets[seq]);
    
        conf->stats.packets_received++;
        conf->stats.total_rtt += rtt;
        conf->stats.total_rtt_sq += rtt * rtt;
    
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
    
        printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
                bytes_received - (ip_header->ihl * 4) - sizeof(struct timeval),
                inet_ntoa(src_adrr.sin_addr),
                icmp_reply->un.echo.sequence,
                ip_header->ttl, 
                rtt);
    }
    else if (icmp_reply->type == ICMP_TIME_EXCEEDED)
    {
        // TTL expirado en algún router intermedio
        printf("%ld bytes from %s: Time to live exceeded\n", 
            bytes_received - (ip_header->ihl * 4) - sizeof(struct timeval),
            inet_ntoa(src_adrr.sin_addr));
    }
    return (0);
}

int send_socket(struct config *conf)
{
    struct sockaddr_in  dest_addr;
    struct ping_packet  *packet;
    ssize_t             bytes_sent;
    int                 seq;

    seq = conf->sequence - 1;
    
    packet = &conf->packets[seq];

    memset(&dest_addr, 0, sizeof(struct sockaddr_in));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr = conf->ip_address;

    bytes_sent = sendto(conf->sockfd, packet, sizeof(struct ping_packet), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    if (bytes_sent == -1)
    {
        printf("ft_ping: sendto: %s\n", strerror(errno));
        return (-1);
    }
    conf->stats.packets_sent++;
    return (0);
}