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
# include <netinet/in.h>

typedef struct s_ipheader
{

}   t_ipheader;

typedef struct s_icmpheader
{

}   t_icmpheader;

extern volatile sig_atomic_t g_sigint_received;
extern volatile sig_atomic_t g_child_status_changed;


//*** Init Functions ***/

int main(int argc, char **argv);

//*** Signal Handler ***/

void    sigint_handler(int signum);
void    sigchld_handler(int signum);
void    init_signal(void);

//*** Ping logic ***/


//*** Comunicatoin logic ***/



#endif