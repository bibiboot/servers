#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>


#define max(a,b) (((a)>(b))?(a):(b))
#define MAXLINE 100

char *HOST = "127.0.0.1";
char PORT[100];
//char PORT[100] = "8012";

struct sigaction ACT;
int SOCKFD;
FILE *FP;

void *copyto(void *attr){
    /*Child thread read from the stdin and write to sockfd*/
    char sendline[MAXLINE];

    printf("Waiting for input...\n");
    while(fgets(sendline, MAXLINE, FP)>0){
        write(SOCKFD, sendline, MAXLINE);
    }

    /* EOF on stdin */
    /* Terminate the thread */
    shutdown(SOCKFD, SHUT_WR);
    pthread_exit(0);

}

void str_cli(FILE *fp_args, int sockfd_args){
    //Main Thread
    SOCKFD = sockfd_args;
    FP = fp_args;
    char recvline[MAXLINE];

    pthread_t th;

    pthread_create(&th, NULL, copyto, NULL);
    
    // Read from the socket and write to the stdout
    while(read(SOCKFD, recvline, MAXLINE)>0){
        printf("SERVER: %s\n", recvline);
    }

   //Main thread exiting
   exit(0);
}



void start(){
    struct addrinfo hints, *res;
    char buff[1000];
    char buff2[1000];
    int sock[10];

    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);
   
    int i;
    for(i=0; i<1; i++){
        sock[i] = socket(res->ai_family, res->ai_socktype, 0);
        connect(sock[i], res->ai_addr,res->ai_addrlen);
    }

   printf("Sending\n");
   str_cli(stdin, sock[0]);
   exit(0); 
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
