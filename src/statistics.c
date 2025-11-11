#include "ft_ping.h"

void    show_statistics(struct config *conf)
{
    struct timeval  end_time;
    double          total_time;
    double          avg_rtt;
    int             packet_loss;

    gettimeofday(&end_time, NULL);
    packet_loss = 0;
    avg_rtt = 0;
    total_time = (end_time.tv_sec - conf->stats.start_time.tv_sec) * 1000.0 +
                (end_time.tv_usec - conf->stats.start_time.tv_usec) / 1000.0;

    if (conf->stats.packets_sent > 0)
        packet_loss = (int)((conf->stats.packets_sent - conf->stats.packets_received) * 1000.0 / conf->stats.packets_sent);
    if (conf->stats.packets_received > 0)
        avg_rtt = conf->stats.total_rtt / conf->stats.packets_received;

    printf("\n--- %s ping statistics ---\n", conf->hostname);
    printf("%d packets transmitted, %d received, %d%% packet loss, time %.0fms\n", 
            conf->stats.packets_sent, conf->stats.packets_received, packet_loss, total_time);
    
    if (conf->stats.packets_received > 0)
        printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", conf->stats.min_rtt, avg_rtt, conf->stats.max_rtt, 0.0);
    return;
}