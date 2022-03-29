#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


struct sockaddr_in local;


void server(void) {
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;

    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss, 5);

    cs = accept(ss, NULL, NULL);

    char buf[BUFSIZ];
    read(cs, buf, BUFSIZ);
    printf("%s\n", buf);
    close(cs);
}


void client(void) {
    int s = socket(AF_INET, SOCK_STREAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;
    
    connect(s, (struct sockaddr*) &local, sizeof(local));
    
    char buf[BUFSIZ] = "Hello\n";
    write(s, buf, strlen(buf) + 1);
    close(s);
}


int main(int argc, char** argv) {
    if (argc != 2)
        return printf("Use: %s [s|c]\n", argv[0]);

    struct sockaddr_in local;

    if (argv[1][0] == 's')
        server();

    if (argv[1][0] == 'c')
        client();
}
