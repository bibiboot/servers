#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAXLINE 500000

int main(int argc, char *argv[]){
    char buff[MAXLINE];

    int towrite = read(STDIN_FILENO, buff, sizeof(buff)+1);
    fprintf(stderr, "READ %d bytes\n", towrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);

    char *ptr = buff;
    while(towrite>0){
        errno = 0;
        int wrote =write(STDOUT_FILENO, ptr, towrite);
        fprintf(stderr, "NWRITE: %d, errno: %d, WROTE: %d\n", towrite, errno, wrote);
        if(wrote>0){
            ptr += towrite;
            towrite -= wrote;
        }

    }
}
