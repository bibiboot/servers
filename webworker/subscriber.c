#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

char *HOST = "127.0.0.1";
char PORT[100];

void read_input(int argc, char *argv[]){
  int i;
  printf("%d\n", argc);
  for(i=1; i<argc; i++){
      if(strcmp("-p", argv[i++])==0){
          strcpy(PORT, argv[i]);
      }
  }
  printf("%s\n", PORT);
}

int main(int argc, char *argv[]){

    read_input(argc, argv);
    struct addrinfo hints, *res;
    char buff[1000];

    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    printf("PORT: %s\n", PORT);
    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);
    
    if(connect(sock, res->ai_addr, res->ai_addrlen)==-1){
        perror("CONNECT");
        exit(0);
    }

    send(sock, "Start", 1000, 0);

    while(1){
    memset(buff, 0, 1000);
    if(recv(sock, buff, 1000, 0)==-1){
        perror("RECV");
        exit(0);
    }
    
    printf("Recieved %s\n", buff);
    }
}
