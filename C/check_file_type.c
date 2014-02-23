#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i;
    for(i=1; i<argc; i++){
        struct stat buff;
        if(stat(argv[i], &buff)<0){
            perror("Stat");
            exit(0);
        } 
        if(S_ISREG(buff.st_mode))
            printf("Regular file\t%s\n", argv[i]);
        else if(S_ISSOCK(buff.st_mode))
            printf("Socket file\t%s\n", argv[i]);
        else
            printf("Not known\t%s\n", argv[i]);
    }
    return 0;
}

