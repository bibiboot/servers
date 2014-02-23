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
#include <pthread.h>

#define MAXLINE 10

struct sigaction ACT, ACT2;
char *HOST = "127.0.0.1";
char PORT[100];

int readn(int fd, void *vptr, int n){
    /* THis is used as the standard is buggy and cannpt be debugged*/
    int nleft;
    int nread;
    char *ptr;

    ptr=vptr;
    nleft = n;
    while(nleft>0){
        if((nread=read(fd, ptr, nleft))<0){
            printf("ERROR CLIENT\n");
            if(errno==EINTR){
                /*Interrupted system call*/
                nread = 0;
            }
            else{
                printf("ERORR\n");
                return -1;
            }
        }
        else if(nread==0){
            /*EOF*/
            printf("EOF\n");
            break; 
        }
       //printf("Nleft: %d, Nread: %d\n", nleft, nread);
       nleft-=nread;
       ptr+=nread;
       //printf("Nleft: %d, Nread: %d\n", nleft, nread);
    }

    return (n-nleft);
}

void str_echo(int sockfd){
    char buf[MAXLINE];
    int n;

    again:
        //while((n=read(sockfd, buf, MAXLINE))>0){
        while((n=readn(sockfd, buf, MAXLINE))>0){
            printf("%s", buf);
            if(write(sockfd, buf, MAXLINE)<0){
                perror("WRITE");
            }
        }

    if(n<0 && errno == EINTR){
        printf("Err");
        /* System cal was interrupted by a signal */
       goto again; 
    }
    if(n<0){
        printf("READ ERROR\n");
    }
}

void *doit(void *arg){
    /* Thread function */
    pthread_detach(pthread_self());
    str_echo((int)arg);
    close((int)arg);
    printf("Thread Exiting\n");
    return NULL;
}

void start(){
    struct addrinfo hints, *res;
    pthread_t th;
    char buff[1000];
    time_t t;
  
    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    getaddrinfo(HOST, PORT, &hints, &res);
    
    int listenfd = socket(res->ai_family, res->ai_socktype, 0);

    bind(listenfd, res->ai_addr, res->ai_addrlen);

    listen(listenfd, 10);

    while(1){
        printf("Waiting\n"); 
        struct sockaddr cliaddr;
        int len = sizeof(cliaddr);
        char human_client[100];
        int connfd = accept(listenfd, &cliaddr, &len);
        if(connfd<0){
            /*System call interrupted*/
            if(errno==EINTR) {
                continue;
            }
            perror("ERROR ACCEPT");
            exit(0);
        }
       printf("Connected\n");
       pthread_create(&th, NULL, doit, (void *)connfd);
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
