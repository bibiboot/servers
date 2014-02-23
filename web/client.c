#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

char *HOST = "127.0.0.1";
char PORT[100];

void read_input(int argc, char *argv[]){

    int i;
    for(i=1; i<argc; i++){
        if(strcmp(argv[i++], "-p")==0){
            strcpy(PORT, argv[i]);
        }
    }
}

int main(int argc, char *argv[]){

    read_input(argc, argv);
    struct addrinfo hints, *res;
    char buff[1000];

    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);


    while(1){
        connect(sock, res->ai_addr, res->ai_addrlen);
        send(sock, "GET /index.html HTTP/1.1\r\n", 1000, 0);

        recv(sock, buff, 1000, 0);

        printf("Recieved %s\n", buff);

        sleep(5);
    }

}
