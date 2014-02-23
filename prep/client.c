#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

char *HOST = "127.0.0.1";
char PORT[100];

struct sigaction ACT;

void start(){
    struct addrinfo hints, *res;
    char buff[1000];
    char buff2[1000];

    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    connect(sock, res->ai_addr,res->ai_addrlen);
   
    while((fgets(buff, 100, stdin))!=NULL){
        send(sock, buff, strlen(buff), 0);
        sleep(1);
        send(sock, buff, strlen(buff), 0);

        int s = recv(sock, buff2, 1000, 0);
    
        printf("%s %d\n", buff2, s);
    }
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
    sigaction(SIGINT, &ACT, NULL);

    read_input(argc, argv);
    start();

}
