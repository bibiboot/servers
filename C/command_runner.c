#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 100

struct sigaction ACT;

void call(){
    printf("DO NOTING\n");
}

int main(int argc, char *argv[]){
    char cmd[100];
    ACT.sa_handler = call;
    sigaction(SIGINT, &ACT, NULL);

    while(fgets(cmd, MAXLINE, stdin)!=NULL){
       char *last = strchr(cmd, '\n'); 
       *last = '\0';
       if(fork()==0){
           //Only child runs here
           //Execute the command
           while(1);
           if(execlp(cmd, cmd, NULL)<0){
               perror("EXECLP");
               exit(0);
           }
       }
       //printf("%s", cmd);
       waitpid(-1, NULL, NULL);
       printf("Exiting\n");
    }
    return 0;
}
