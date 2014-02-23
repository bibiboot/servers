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

struct sigaction ACT, ACT2;
char *HOST = "127.0.0.1";
char PORT[100];
pid_t pid;

void start(){
    struct addrinfo hints, *res;
    char buff[1000];
    int maxfd, maxi, i, nready;
    int client[FD_SETSIZE];
    fd_set allset, rset;
  
    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    getaddrinfo(HOST, PORT, &hints, &res);
    
    int listenfd = socket(res->ai_family, res->ai_socktype, 0);

    bind(listenfd, res->ai_addr, res->ai_addrlen);

    listen(listenfd, 10);

    maxfd = listenfd;
    maxi = -1;
    for(i=0; i<FD_SETSIZE; i++) client[i] = -1;
    

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    // Infinite Loop
    while(1){
        rset = allset;
        printf("Waiting........\n");
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &rset)){
            // Handle for new connection
            struct sockaddr *cliaddr; 
            int len = sizeof(cliaddr);
            printf("Connected.....\n");
            int connfd = accept(listenfd, cliaddr, &len);

            for(i=0; i<FD_SETSIZE; i++){
                if(client[i]<0){
                    client[i] = connfd;
                    break;
                }
            }


            if(i==FD_SETSIZE){
                printf("Too many clients\n");
                exit(0);
            }

            // Add the new socked it to the allset;
            FD_SET(connfd, &allset);

            // Check if the new file descriptor increaeses the maxfd count
            if(connfd > maxfd){
                maxfd = connfd;
            }

            if(i>maxi){
                maxi=i;
            }

            // No more readable file descriptors. 
            if(--nready<=0) continue;
        }

        int sockfd;
        // Check all the clients for the which file descriptor is readable now
        for(i=0; i<FD_SETSIZE; i++){
            // Not allocated socket
            if((sockfd=client[i])<0) continue;
             
            if(FD_ISSET(sockfd, &rset)){
                // Read from the file descriptr
                if((read(sockfd, buff, 100))==0){
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i]= -1;
                    printf("Closing client %d\n", sockfd);
                }else{
                    printf("READ: %s\n", buff);
                    write(sockfd, buff, 100);
                }

                if(--nready<=0) break;
            }
        }
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
