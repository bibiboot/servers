#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void conn(int sec);

struct sigaction ACT;
int BROKE = 0;

int main(int argc, char *argv[]){
    conn(5);
}

void timeout_handler(){
    BROKE = 1;
    printf("TIME OUT HANDLER\n");
}

void conn(int sec){

    struct sigaction OLD_ACT;
    ACT.sa_handler = timeout_handler;

    sigaction(SIGALRM, &ACT, &OLD_ACT);
    alarm(10);

    while(1){
        sleep(10);
        if(BROKE==1) break;
    }

    sigaction(SIGALRM, &OLD_ACT, NULL);
}
