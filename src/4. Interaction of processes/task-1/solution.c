#include <stdio.h>

#define BUF_SIZE 256


int main(int argc, char** argv) {
    char command[BUF_SIZE];
    sprintf(command, "%s %s", argv[1], argv[2]);
    FILE* channel = popen(command, "r");
    char c;
    int count = 0;
    do {
        c = fgetc(channel);
        if (c == '0') count++;
    } while (c != EOF);
    pclose(channel);
    printf("%d\n", count);
    return 0;
}
