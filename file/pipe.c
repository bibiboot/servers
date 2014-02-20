#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
Example of file where stdout is closed
and the latest file open is given the file descriptor 
of the stdout
*/

int main(int argc, char *argv[]){
    close(1);
    int fd = open("sample2.txt", O_RDWR | O_CREAT);
    fprintf(stdout, "%d\n", fd);
    if(printf("Hello Danish")<=0){
        perror("Error");
    } 
    return 0;
}
