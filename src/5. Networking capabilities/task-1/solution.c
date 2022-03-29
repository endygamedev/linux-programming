#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 2)
        exit(EXIT_FAILURE);

    struct hostent *h;
    h = gethostbyname(argv[1]);

    if (h == NULL) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;

    while (h->h_addr_list[i] != 0) {
        struct in_addr *a = (struct in_addr*) h->h_addr_list[i];
        printf("%s\n", inet_ntoa(*a));
        i++;
    }

    return 0;
}
