#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


#define BUF_SIZE 256


int isnumber(const char* str) {
    while (*str != '\0') {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}


int main(void) {
    int count = 0;
    struct dirent **namelist;

    int n = scandir("/proc", &namelist, NULL, alphasort);

    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }


    char pidname[BUF_SIZE];
    while (n--) {
        if (isnumber(namelist[n]->d_name)) {
            sprintf(pidname, "/proc/%s/comm", namelist[n]->d_name);
            FILE* file = fopen(pidname, "rb");
            char buffer[BUF_SIZE];
            fread(&buffer, sizeof(char), BUF_SIZE, file);
            fclose(file);
            if (strstr(buffer, "genenv"))
                count++;
        }
        free(namelist[n]);
    }
    free(namelist);
    printf("%d\n", count);
    exit(EXIT_SUCCESS);
}
