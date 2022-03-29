#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int s1 = 0, s2 = 0, stop = 0;

void mysignal_handler1(int signalno) { s1++; }
void mysignal_handler2(int signalno) { s2++; }
void mysignal_handler3(int signalno) { stop = 1; }


int main(void) {
    signal(SIGUSR1, mysignal_handler1);
    signal(SIGUSR2, mysignal_handler2);
    signal(SIGTERM, mysignal_handler3);

    while (!stop) { usleep(100000); }
    printf("%d %d\n", s1, s2);
    return 0;
}
