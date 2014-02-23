#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>

char *HOST = "127.0.0.1";
char PORT[100];

sigset_t SET;
struct sigaction ACT;

struct request {
    int sock;
};

struct node {
    int data;
    struct node *next;
};

struct node *HEAD;
struct node *TAIL;

struct node *create_node(int data){
    struct node *temp = (struct node *)malloc(sizeof(*temp));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void interrupt_main(){
    printf("Exiting the Program\n");
    exit(0);
}

void block_signal(){
    sigemptyset(&SET);
    sigaddset(&SET, SIGINT);
    pthread_sigmask(SIG_BLOCK, &SET, NULL);
}

void unblock_signal(){
    sigemptyset(&SET);
    sigaddset(&SET, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &SET, NULL);

    ACT.sa_handler = interrupt_main;
    sigaction(SIGINT, &ACT, NULL);
}



void add(int data){
    if(HEAD==NULL){
        HEAD = create_node(data);
        TAIL = HEAD;
        return;
    }

    struct node *temp = create_node(data);
    TAIL->next = temp;
    TAIL = temp;
}

void read_input(int argc, char *argv[]){

    int i;
    for(i=1; i<argc; i++){
        if(strcmp(argv[i++], "-p")==0){
            strcpy(PORT, argv[i]);
        }
    }
    printf("PORT : %s\n", PORT);

}

void *run(void *attr){

    block_signal();
    struct request *r = (struct request *)attr;
    struct node *temp = HEAD;

    while(1){
        while(temp->next!=NULL){
             char buff[100];
             sprintf(buff, "%d", temp->data);
             printf("Sending %s\n", buff);
             send(r->sock, buff, 100, 0);
             temp=temp->next;
             sleep(2);
        }
    }

}

void start(){
    struct addrinfo hints, *res;
    
    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    bind(sock, res->ai_addr, res->ai_addrlen);

    listen(sock, 10);

    while(1){
        char buff[100];
        printf(".....WAITING\n"); 
        int new_sock = accept(sock, res->ai_addr, &(res->ai_addrlen));
        printf(".....ACCEPTED\n"); 
  
        recv(new_sock, buff, 100, 0);
                
        struct request *r = (struct request *)malloc(sizeof(*r));
        r->sock = new_sock;
        
        pthread_t th;
        pthread_create(&th, NULL, run, (void*)r);
    }

}

void *build(void *attr){
    int i;
    for(i=0; i<=100; i++){
        add(i);
        printf("Publishing %d\n", i);
        sleep(10);
    }
}

int main(int argc, char *argv[]){

    unblock_signal();
    read_input(argc, argv);

    pthread_t th;
    pthread_create(&th, NULL, build, NULL);

    start();

}
