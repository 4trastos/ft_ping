#include "ft_ping.h"

volatile sig_atomic_t g_sigint_received = 0;
volatile sig_atomic_t g_child_status_changed = 0;

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        printf("❌ Use: %s must have PROG [ARGS] ❌\n", argv[0]);
        return (1);
    }
    init_signal();
    return (0);
}