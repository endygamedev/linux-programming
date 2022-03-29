#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>


#define BUF_SIZE 256


int main(void) {
    char buffer[BUF_SIZE];

    int f1 = open("in1", O_RDONLY, O_NONBLOCK);
    int f2 = open("in2", O_RDONLY, O_NONBLOCK);
    
    int stop1 = 0;
    int stop2 = 0;

    int sum = 0;
    
    fd_set read_set;
    
    while(1) {

        FD_ZERO(&read_set);
        
        FD_SET(f1, &read_set);
        FD_SET(f2, &read_set);
        
        int max = f1 > f2 ? f1 : f2;

        select(max + 1, &read_set, NULL, NULL, NULL);
        
        if (FD_ISSET(f1, &read_set)) {
            int res = read(f1, buffer, sizeof(buffer));
            
            if (res > 0 && buffer[0] != '\n') {
                int t;
                sscanf(buffer, "%d", &t);
                sum += t;
            } else if (res == 0) {
                stop1 = 1;
            }
        }
        

        if (FD_ISSET(f2, &read_set)) {
            int res = read(f2, buffer, sizeof(buffer));
            
            if (res > 0 && buffer[0] != '\n') {
                int t;
                sscanf(buffer, "%d", &t);
                sum += t;
            } else if (res == 0) {
                stop2 = 1;
            }
        }

        if (stop1 == 1 && stop2 == 1) break;
    }

    printf("%d\n", sum);

    return 0;
}
