#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUF_SIZE 256


int main(int argc, char** argv) {
    int pid;
    sscanf(argv[1], "%d", &pid);
    printf("%d\n", pid);
    while(pid != 1) {
        char filename[BUF_SIZE];
        sprintf(filename, "/proc/%d/stat", pid);
        FILE* file = fopen(filename, "rb");
        char buffer[BUF_SIZE];
        fread(&buffer, sizeof(char), BUF_SIZE, file);
        fclose(file);
        
        int i = 0;
        char* token = strtok(buffer, " ");;
        for (i = 0; i < 2; i++)
            token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        printf("%s\n", token);
        pid = atoi(token);
    }
    return 0;
}
