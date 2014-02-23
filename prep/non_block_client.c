#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

/*
Using Nonblocking
*/


#define max(a,b) (((a)>(b))?(a):(b))
#define MAXLINE 1000

char *HOST = "127.0.0.1";
char PORT[100];

struct sigaction ACT;

void str_cli(FILE *fp, int sockfd){
    int maxdpl, val, stdlineof;
    int nwritten;
    fd_set rset, wset;
    char to[MAXLINE], fr[MAXLINE];
    char *tooptr, *toiptr, *froptr, *friptr;

    /*STDIN_FILENO and STDOUT_FILENO are constants*/

    val = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);

    val = fcntl(STDOUT_FILENO, F_GETFL, 0);
    fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);

    val = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

    tooptr = toiptr = to;
    froptr = friptr = fr;
    stdlineof = 0;

    maxdpl = max( max(STDOUT_FILENO, STDIN_FILENO), sockfd);

    while(1){
        FD_ZERO(&rset);
        FD_ZERO(&wset);

        if(stdlineof==0 && toiptr< &to[MAXLINE]){
            /* Read from stdin */ 
            FD_SET(STDIN_FILENO, &rset);
        }
        if(tooptr < toiptr){
            /* Write into the socket */
            FD_SET(sockfd, &wset);
        } 
        if(friptr < &fr[MAXLINE]){
            /*Read from socket*/
            FD_SET(sockfd, &rset);
        }
        if(froptr < friptr){
            /*Write to stdut*/
            FD_SET(STDOUT_FILENO, &wset);
        }

        // Wait
        select(maxdpl, &rset, &wset, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &rset)){
            // Read from the socket 
           if((n=read(sockfd, toiptr, &to[MAXLINE] - toiptr))<0){
               
           }
           else if(n==0){

           }
           else{
               // Alert the read of stdout

           }
        }
        if(FD_ISSET(STDIN_FILENO, &rset)){
            // Read from the stdin
        }

    }
}

void start(){
    struct addrinfo hints, *res;
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
