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
    return (0);
}