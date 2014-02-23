#include <stdio.h>
#include <pthread.h>
#include <signal.h>

pthread_key_t A_KEY;

struct sigaction ACT;

void run(){
    int val = (int)pthread_getspecific(A_KEY);
    printf("%d\n", val);
}

void *fn1(void *attr){
    pthread_setspecific(A_KEY, (void*)100);
    while(1);
}

void *fn2(void *attr){
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &s, NULL);
    ACT.sa_handler = run;
    sigaction(SIGINT, &ACT, NULL);
    pthread_setspecific(A_KEY, (void*)200);
    while(1);
}

int main(int argc, char *argv[]){
    //Block the signal
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    pthread_sigmask(SIG_BLOCK, &s, NULL);

    pthread_key_create(&A_KEY, NULL);

    pthread_t th1, th2;

    pthread_create(&th1, NULL, fn1, NULL);
    pthread_create(&th2, NULL, fn2, NULL);
    

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}
