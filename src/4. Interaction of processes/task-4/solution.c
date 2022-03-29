#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>


void mysignal_handler(int signalno) { exit(EXIT_SUCCESS); }


int main(void) {

    pid_t pid = fork();

    if (pid != 0) exit(EXIT_SUCCESS);

    chdir("/");

    setsid();

    signal(SIGURG, mysignal_handler);
    printf("%d\n", getpid());

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    while(1) {
        sleep(30);
    }

    return 0;
}
