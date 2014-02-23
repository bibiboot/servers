#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define PERMS 0777

char getchar_m(){
    char c; 
    return read(0, &c, 1)?c:EOF;
}

int copy_m(char *dest, char *src){
    char buff[100];
    int dfd = creat(dest, PERMS);
    if(dfd<0){
        perror("DEST");
        exit(0);
    }

    int sfd = open(src, O_RDONLY);
    if(sfd<0){
        perror("SRC");
        exit(0);
    }
    int n; 
    while((n=read(sfd, buff, 100))>0){
        if(write(dfd, buff, 100)!=100){
            perror("WRITE");
            exit(0);
        };
    }
    return 0;
}

long get_time(){
    struct timeval t;
    if(gettimeofday(&t, NULL)<0){
        perror("GETTIME");
        exit(0);
    }
    return (long)t.tv_usec;
}


int main(int argc, char *argv[]){
    char c;
    char buff[] = "Hello I am orage boy";
    /*
    while((c=getchar_m())!=EOF){
        printf("%c",c);
    }
    */
    /*
    long stime = get_time();
    copy_m(argv[1], argv[2]);
    long etime = get_time();
    printf("%ld\n", etime-stime);
    */

    //printf("Get processid: %d\n", (int)getpid());

    //printf("%ld\n", sysconf(_SC_PAGESIZE));

    write(STDOUT_FILENO, buff, sizeof(buff)-1);
    sleep(10);
    printf("Before fork\n");
    if(fork()==0){

    }
    else{
        sleep(2);
    }
    
    waitpid(-1, NULL, NULL);
    printf("Ending\n");
    return 0;
}
