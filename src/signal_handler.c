#define _POSIX_C_SOURCE 200809L

#include "ft_ping.h"

void    init_signal(void)
{
    struct sigaction sa_int = {0};
    struct sigaction sa_alrm = {0};

    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    sa_alrm.sa_handler = sigalrm_handler;
    sigemptyset(&sa_alrm.sa_mask);
    sa_alrm.sa_flags = 0;

    sigaction(SIGINT, &sa_int, NULL);
    sigaction(SIGALRM, &sa_alrm, NULL);
}

// Timeout en recvfrom() → reintentar o marcar como packet loss
void    sigalrm_handler(int signum)
{
    (void)signum;
    g_sigalrm_received = 1;
}

void    sigint_handler(int signum)
{
    (void)signum;
    ft_statistics();
    g_sigint_received = 1;
}

