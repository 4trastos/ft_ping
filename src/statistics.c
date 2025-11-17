#include "ft_ping.h"

void    show_statistics(struct config *conf)
{
    double          avg_rtt;
    double          stddev;
    int             packet_loss;
    int             packets_received;

    packet_loss = 0;
    avg_rtt = 0.0;
    stddev = 0.0;
    packets_received= conf->stats.packets_received;

    if (conf->stats.packets_sent > 0)
        packet_loss = (int)((conf->stats.packets_sent - conf->stats.packets_received) * 100.0 /conf->stats.packets_sent);

    
    if (packets_received > 0)
        avg_rtt = conf->stats.total_rtt / packets_received;
    
    if (packets_received > 0)
    {
        double mean = avg_rtt;
        double mean_sq = conf->stats.total_rtt_sq / packets_received;
        double variance = mean_sq - (mean * mean);
        if (variance < 0 && variance > -1e-12) /* evitar -0 por errores numéricos */
            variance = 0;
        if (variance < 0)
            variance = 0; /* defensa adicional */
        stddev = sqrt(variance);
    }

    printf("\n--- %s ping statistics ---\n", conf->hostname ? conf->hostname : "host");
    printf("%d packets transmitted, %d received, %d%% packet loss\n", 
            conf->stats.packets_sent, conf->stats.packets_received, packet_loss);
    
    if (conf->stats.packets_received > 0)
        printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", conf->stats.min_rtt, avg_rtt, conf->stats.max_rtt, stddev);
    return;
}