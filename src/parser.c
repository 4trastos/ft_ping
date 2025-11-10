#include "ft_ping.h"

// FLUJO DE EJEMPLO: ./ft_ping -v google.com

void    init_struct(struct config *conf)
{
    conf->verbose_mode = false;
    conf->show_help = false;
    conf->is_valid = false;
    conf->hostname = NULL;
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


#include "ft_ping.h"

void    show_help(void)
{
    printf("Usage: ft_ping [options] <destination>\n\n");
    printf("Options:\n");
    printf("  -v              verbose output\n");
    printf("  -?              show this help\n\n");
    printf("Arguments:\n");
    printf("  <destination>   dns name or ip address\n\n");
    printf("Examples:\n");
    printf("  ft_ping google.com\n");
    printf("  ft_ping -v 192.168.1.1\n");
    printf("  ft_ping -?\n\n");
    printf("ft_ping - a ping implementation for 42 project\n");
}