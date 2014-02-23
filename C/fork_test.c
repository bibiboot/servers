#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

struct sigaction ACT;

void interrupt_main(int signum){
    int st;
    printf("Child exited\n");
    //waitpid(-1, &st, WNOHANG);
    wait(&st);
    printf("Child exited ended\n");
}

int main(int argc, char *argv[]){
    int p;    
    int status;

    ACT.sa_handler = interrupt_main;
    sigaction(SIGCHLD, &ACT, NULL);

    int i;
    for(i=0; i<=3; i++){
    if((p=fork())==0){
        printf("Inside the child\n");
        exit(0);
    }
    }

    while(1){
        printf("Parent owrking\n");
        sleep(10);
    }

    //waitpid(-1, &status, 0);
    return 0;
}
