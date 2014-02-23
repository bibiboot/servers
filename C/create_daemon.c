#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

struct sigaction ACT;

int main(int argc, char *argv[]){

    int pid=fork();
    if(pid!=0){
        //Parent kill yourself
        exit(0);
     }

     ACT.sa_handler = SIG_IGN;
     sigaction(SIGHUP, &ACT, NULL);
     chdir("/");
     setsid();
     close(0);
     close(1);
     close(2);
     int fd = open("/dev/null", O_RDWR);
     int fd1 = dup(0);
     int fd2 = dup(0);
     
     while(1){
         printf("I am alive\n");
         sleep(1);
     }
     return 0;
}
