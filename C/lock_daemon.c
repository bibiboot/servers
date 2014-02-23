#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define LOCKFILE (S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP )

int main(int argc, char *argv[]){
    int fd = open("test.pid", O_RDWR | O_CREAT, LOCKFILE); 
    if(fd<0){
        printf("One daemon is already runnin\n");
        perror("OPEN");
        exit(0);
    }

    char buff[16];
    sprintf(buff, "%d", (int)getpid());
    printf("%d\n", sizeof(buff));
    write(fd, buff, 16);
    return 0;
}
