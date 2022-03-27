#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUF_SIZE 256


int main(void) {
    FILE* file = fopen("/proc/self/stat", "rb");
    char buffer[BUF_SIZE];
    fread(&buffer, sizeof(char), BUF_SIZE, file);
    fclose(file);
    
    int i = 0;
    char* token = strtok(buffer, " ");
    for (i = 0; i < 2; i++)
        token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    printf("%s\n", token);
    return 0;
}
