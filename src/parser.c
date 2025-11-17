#include "ft_ping.h"

// FLUJO DE EJEMPLO: ./ft_ping -v google.com

void    init_struct(struct config *conf)
{
    conf->verbose_mode = false;
    conf->show_help = false;
    conf->is_valid = false;
    conf->hostname = NULL;
    conf->sockfd = -1;
    conf->sequence = 0;
    conf->ttl = 64;

    conf->stats.packets_sent = 0;
    conf->stats.packets_received = 0;
    conf->stats.min_rtt = 0;
    conf->stats.max_rtt = 0;
    conf->stats.total_rtt = 0;
    gettimeofday(&conf->stats.start_time, NULL);
}

int     ft_parser(struct config *conf, char **argv, int argc)
{
    int     i = 1;

    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-v") == 0)
                conf->verbose_mode = true;
            else if (strcmp(argv[i], "-?") == 0)
                conf->show_help = true;
            else if (strcmp(argv[i], "--ttl") == 0)
            {
                i++;
                if (i >= argc)
                {
                    printf("%s: Error: --ttl requires a value\n", argv[0]);
                    return (-1);
                }
                conf->ttl = atoi(argv[i]);
                if (conf->ttl <= 0 || conf->ttl > 255)
                {
                    printf("%s: Error: TTL must be between 1 and 255\n", argv[0]);
                    return (-1);
                }  
            }
            else
            {
                printf("%s: Error: Unknown option %s\n", argv[0], argv[i]);
                return (-1);
            }
        }
        else
        {
            if (conf->hostname != NULL)
            {
                printf("%s: Error: Only one hostname is allowed\n", argv[0]);
                return (-1);
            }
            conf->hostname = argv[i];
        }
        i++;
    }

    if (conf->hostname == NULL && !conf->show_help)
    {
        printf("Error: Destination hostname required\n");
        return (-1);
    }
    conf->is_valid= true;
    return (0);
}

void    show_help(void)
{
    printf("Usage: ft_ping [options] <destination>\n\n");
    printf("Options:\n");
    printf("  -v              verbose output\n");
    printf("  -?              show this help\n");
    printf("  --ttl=N         set the time-to-live value (optional)\n");
    printf("\nArguments:\n");
    printf("  <destination>   dns name or ip address\n\n");
    printf("Examples:\n");
    printf("  ft_ping google.com\n");
    printf("  ft_ping -v 192.168.1.1\n");
    printf("  ft_ping -?\n");
    printf("  ft_ping --ttl 4 google.es\n\n");
    printf("ft_ping - a ping implementation for 42 project\n");
}

void        printf_verbose(struct config *conf)
{
    unsigned char *bytes;

    bytes = (unsigned char *)&conf->ip_address;
    //printf("ft_ping: sock4.fd: %d (socktype: SOCK_RAW), hints.ai_family: AF_INET\n", conf->sockfd);
    //printf("\nai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", conf->hostname);
    printf("PING %s (%d.%d.%d.%d): %d data bytes, id 0x%04x = %d\n", 
        conf->hostname, bytes[0], bytes[1], bytes[2], bytes[3], 
        ICMP_PAYLOAD_SIZE, 
        getpid() & 0xFFFF, getpid());

    return;
}