#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    //Open the write for appending and if do not exist then create
    FILE *fp = fopen("FILE", "a+");
    if(fp==NULL){
        perror("FILE CREATE");
        exit(0);
    }

    //Write character into a file
    char ch = 'X';
    fputc(ch, fp);

    //Get file descriptor from FILE 
    int fd = fileno(fp);

    //Create a file system call
    int cfd;
    if((cfd=creat("hello.txt", O_RDWR))<0){
        perror("CREATE");
        exit(0);
    }
    printf("%d\n", cfd);

    

    return 0;
}

