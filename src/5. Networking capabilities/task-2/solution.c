#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


struct sockaddr_in local;


int main(int argc, char** argv) {
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(atoi(argv[1]));
    local.sin_family = AF_INET;

    int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    
    int i = 0;
    while(1) {
        char buf[BUFSIZ];
        for(i = 0; i < BUFSIZ; i++) buf[i] = 0;
        read(s, buf, BUFSIZ);
        if(!strncmp(buf, "OFF\n", 4)) break;
        buf[BUFSIZ] = '\0';
        fprintf(stdout, "%s\n", buf);
    }
    
    return 0;
}
