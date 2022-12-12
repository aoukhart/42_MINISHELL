#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ctrl_c_handler(int sig)
{
    signal(sig, SIG_IGN);
    printf("Ctrl-C pressed\n");
}

int main()
{
    while (1)
    {
        signal(SIGINT, ctrl_c_handler);
        pause();
    }
}
