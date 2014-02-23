#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

char *HOST = "127.0.0.1";
char PORT[100];
char *CONFIG="httpd.conf";

struct request {
    int sock;
    char buff[100];
};

void read_input(int argc, char *argv[]){
    int i;
    for(i=1;i<argc;i++){
        if(strcmp(argv[i++], "-p")==0){
            strcpy(PORT, argv[i]);
        }
    }
}

void start(){
    struct addrinfo hints, *res;
    char buff[1000];

    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    connect(sock, res->ai_addr, res->ai_addrlen);

    strcpy(buff, "Hello Server Danish\nCookie: Text\n");
    printf("Sending %s\n", buff);
    send(sock, buff, strlen(buff), 0);

    printf("Recieving\n");
    char buff2[100];
    //recv(sock, buff, strlen(buff), 0);
    send(sock, "XXX YY", 100, 0);
    printf("End\n");

}


int main(int argc, char *argv[]){
    read_input(argc, argv);
    start();    
}
