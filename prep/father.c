#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <time.h>
#include <arpa/inet.h>
#include <errno.h>

char *HOST = "127.0.0.1";
char PORT[100];
pid_t pid;

struct sigaction ACT, ACT2;

void child_die(int signum){
    int st;
    waitpid(-1, &st, 0);
    printf("Removed child\n");
}



void start(){
    struct addrinfo hints, *res;
    char buff[1000];
    time_t t;
  
    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    getaddrinfo(HOST, PORT, &hints, &res);
    
    int sock = socket(res->ai_family, res->ai_socktype, 0);

    bind(sock, res->ai_addr, res->ai_addrlen);

    listen(sock, 10);

    int i;
    for(i=0;i<=10;i++){
    //while(1){
        printf("Waiting %d\n", i); 
        struct sockaddr cliaddr;
        int len = sizeof(cliaddr);
        char human_client[100];
        int new_sock = accept(sock, &cliaddr, &len);
        if(errno==EINTR)continue;

        if((pid=fork())==0){
            close(sock);
            inet_ntop(AF_INET, &cliaddr, human_client, 100);
            //printf("Connected %s\n", human_client); 
            int n = 100;
            struct sockaddr resultaddr;
            int len1 = sizeof(resultaddr);
            getsockname(new_sock, &resultaddr, &len1); 
            inet_ntop(AF_INET, &resultaddr, human_client, 100);
            printf("Forked Connected %s\n", human_client); 
       
            printf("Wating to read\n");
            n = read(new_sock, buff, 100);
            printf("Recieved: %s %d\n", buff, n);

            close(new_sock);
            exit(0);
        }
        close(new_sock);
    }
    while(1);
}

void read_input(int argc, char *argv[]){
    int i;
    for(i=1; i<argc;i++){
        if(strcmp(argv[i++], "-p")==0){
            strcpy(PORT, argv[i]);
        }
    }

}

void interrupt_main(){
   printf("System Shutting down\n");
   exit(0);
}

int main(int argc, char *argv[]){

    ACT.sa_handler = interrupt_main;
    ACT2.sa_handler = child_die;
    sigaction(SIGINT, &ACT, NULL);
    sigaction(SIGCHLD, &ACT2, NULL);

    read_input(argc, argv);
    start();
 
}
