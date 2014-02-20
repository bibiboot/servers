#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    close(1);
    int fd = open("sample2.txt", O_RDWR | O_CREAT);
    fprintf(stdout, "%d\n", fd);
    if(printf("Hello Danish")<=0){
        perror("Error");
    } 
    return 0;
}
