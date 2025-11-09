#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <time.h>
# include <limits.h>
# include <poll.h>
# include <fcntl.h>
# include <threads.h>
# include <sys/socket.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <sys/time.h>

struct ping_packet {
    struct icmphdr   icmp_hdr;
    struct timeval   timestamp;
    char             data[48];
};

struct config
{
    bool            verbose_mode;
    bool            show_help;
    bool            is_valid;
    char            *hostname;
    struct in_addr  ip_address;
};

extern volatile sig_atomic_t g_sigint_received;
extern volatile sig_atomic_t g_sigalrm_received;

//*** Init Functions ***/

int     main(int argc, char **argv);

//*** Parser Logic***/

int     ft_parser(struct config *conf, char **argv, int argc);
void    init_struct(struct config *conf);

//*** Signal Handler ***/

void    sigint_handler(int signum);
void    sigalrm_handler(int signum);
void    init_signal(void);

//*** Ping Logic ***/


//*** Statistics ***/

void    ft_statistics(void);

#endif