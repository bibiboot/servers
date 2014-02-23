#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>


#define max(a,b) (((a)>(b))?(a):(b))

char *HOST = "127.0.0.1";
char PORT[100];
//char PORT[100] = "8012";

struct sigaction ACT;

void str_cli(FILE *fp, int sockid){
    char buff[100];
    fd_set rset;
    FD_ZERO(&rset);
    while(1){
        FD_SET(fileno(fp), &rset);
        FD_SET(sockid, &rset);
        int maxdp = max(sockid, fileno(fp))+1;
        select(maxdp, &rset, NULL, NULL, NULL);

        if(FD_ISSET(sockid, &rset)){
            // Something is their to read
            if(read(sockid, buff, 100)==0){
                exit(0);
            }
            printf("Read: %s\n", buff);
        }

        if(FD_ISSET(fileno(fp), &rset)){
            char line[100];
            if(fgets(line, 100, fp)==NULL){
                printf("Client closing\n");
                return;
            };
            //strcpy(line, "XXYXXX");
            write(sockid, line, strlen(line));
            sleep(60*10);
        }
    }
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
