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
    unsigned char   verbose_mode;
    unsigned char   hostname;
    unsigned char   ip_address;
};


extern volatile sig_atomic_t g_sigint_received;
extern volatile sig_atomic_t g_sigalrm_received;


//*** Init Functions ***/

int main(int argc, char **argv);

//*** Signal Handler ***/

void    sigint_handler(int signum);
void    sigalrm_handler(int signum);
void    init_signal(void);

//*** Ping logic ***/


//*** Statistics ***/

void    ft_statistics(void);

#endif