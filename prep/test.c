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
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

struct sigaction ACT, ACT2;
char *HOST = "127.0.0.1";
char PORT[100];
pid_t pid;

int isReadable(int fd){
    fd_set rset; 
    FD_ZERO(&rset);
    FD_SET(fd, &rset);

    printf("Waiting......\n");
    // Return greater then zero in case of readable descriptor
    return select(fd+1, &rset, NULL, NULL, NULL);
}

void start(){
    struct addrinfo hints, *res;
    char buff[1000];
    int maxfd, maxi, i, nready;
    int client[FD_SETSIZE];
    fd_set rset;

    FD_ZERO(&rset);
  
    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    getaddrinfo(HOST, PORT, &hints, &res);
    
    int listenfd = socket(res->ai_family, res->ai_socktype, 0);

    bind(listenfd, res->ai_addr, res->ai_addrlen);

    listen(listenfd, 10);
    FD_SET(listenfd, &rset);

    while(isReadable(listenfd)){
        struct sockaddr cliaddr;
        int len = sizeof(cliaddr);
        int new_fd = accept(listenfd, &cliaddr, &len);
        int num = recv(new_fd, buff, 100, MSG_PEEK);
        printf("counr: %d\n", num);
        char buff2[100];
        recv(new_fd, buff2, 100, 0);
        printf("READ: %s\n", buff2);
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

void child_die(int signum){
    int st;
    // Calling of the wait will not take care
    // of the simultaneous SIGCHILD call.
    // As the unix calls are not queed so
    // we will have zombie in the system.
    //waitpid(-1, &st, 0);
    while(waitpid(-1, 0, WNOHANG)>0){
        printf("CHILD REAPED\n");
    }
}

int main(int argc, char *argv[]){

    ACT.sa_handler = interrupt_main;
    ACT2.sa_handler = child_die;
    sigaction(SIGINT, &ACT, NULL);
    sigaction(SIGCHLD, &ACT2, NULL);

    read_input(argc, argv);
    start();
}
