#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <sys/devpoll.h>
#include <unistd.h>

#define max(a,b) (((a)>(b))?(a):(b))
#define MAXLINE 1000

char *HOST = "127.0.0.1";
char PORT[100];
//char PORT[100] = "8012";

struct sigaction ACT;

void str_cli(FILE *fp, int sockfd){
    int stdineof;
    char buff[MAXLINE];
    int n;
    int wfd;

    struct pollfd pollfd[2];
    struct dvpoll dopoll;
    int i;
    int result;

    wfd = open("/dev/poll", O_RDWR, 0);

    pollfd[0].fd = fileno(fp);
    pollfd[0].events = POLLIN;
    pollfd[0].revents = 0;

    pollfd[1].fd = sockfd;
    pollfd[1].events = POLLIN;
    pollfd[1].revents = 0;
  
    write(wfd, pollfd, sizeof(struct pollfd)*2);

   stdlineof = 0;
   while(1){
       //Block untils anything is ready
       dopoll.dp_timeout = -1;
       dopoll.dp_nfds = 2;
       dopoll.dp_fds = pollfd;
       result = ioctl(wfd, DP_POLL, &dopoll);

       /*Loop through ready file descriptors*/
       for(i=0; i<result; i++){
           if(dopoll.dp_fds[i].fd == sockfd){
               /*Socket is readable*/
               if((n=read(sockfd, buff, MAXLINE))==0){
                   if(stdlineof==1)
                       return ;/* Normal termination */
                   else
                       exit(0); /*Server terminated prematurely*/
               }
               /*Write back to the server*/
               write(fileno(stdout), buff, n);
           }
           else{
               /*Input is readable*/
               if((n=read(fileno(fp), buff, MAXLINE))==0){
                   stdlineof = 1;
                   shutdown(sockfd, SHUT_WR); /*Send FIN*/
                   continue;
               }
               /*Write to the socket to the server*/
               write(sockfd, buff, n);
           }
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
