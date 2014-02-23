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

struct sigaction ACT, ACT2;
char *HOST = "127.0.0.1";
char PORT[100];
pid_t pid;

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

    while(1){
        printf("Waiting\n"); 
        struct sockaddr cliaddr;
        int len = sizeof(cliaddr);
        char human_client[100];
        int new_sock = accept(sock, &cliaddr, &len);
        if(new_sock<0){
            if(errno==EINTR) {
                //perror("ACEPT");
                continue;
            }
            perror("ERROR ACCEPT");
            exit(0);
        }

        if((pid=fork())==0){
            int n = 100;
            close(sock);

            while(1){
            inet_ntop(AF_INET, &cliaddr, human_client, 100);
            struct sockaddr resultaddr;
            int len1 = sizeof(resultaddr);
            getsockname(new_sock, &resultaddr, &len1); 
            inet_ntop(AF_INET, &resultaddr, human_client, 100);
            printf("Forked Connected %s\n", human_client); 

            printf("WRITE: %s\n", "HELLO");
            send(new_sock, "HELLO FROM SERVER", 100, 0);
            printf("Wating to read %d\n", new_sock);
            n = read(new_sock, buff, 100);
            printf("READ: %s\n", buff);

            }
            close(new_sock);
            exit(0);
        }
        close(new_sock);
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
