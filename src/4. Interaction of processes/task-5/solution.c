#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char** argv) {

    int id1 = shmget(atoi(argv[1]), 1000, 0);
    int *data1 = shmat(id1, (void *)0, SHM_RDONLY);

    int id2 = shmget(atoi(argv[2]), 1000, 0);
    int *data2 = shmat(id2, (void *)0, SHM_RDONLY);

    key_t key = ftok(__FILE__, "R");

    int id = shmget(key, 1000, 0644 | IPC_CREAT);
    int *data = shmat(id, (void *)0, 0);

    int i;
    for (i = 0; i < 100; i++)
        data[i] = data1[i] + data2[i];

    printf("%d\n", key);

    return 0;
}
