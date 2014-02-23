#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

char *HOST = "127.0.0.1";
char PORT[100];

struct node {
    int data;
    struct node *next;
};

struct node *HEAD;
struct node *TAIL;


struct request {
    int sock;
};

void *run(void *attr){
    
    struct request *r = (struct request *)attr;
    struct node *temp = HEAD;

    while(1){
    while(temp->next!=NULL){
        
        char buff[1000];
        sprintf(buff, "%d", temp->data);
        send(r->sock, buff , 1000, 0);
        temp = temp->next;
        sleep(2);
    }
    }

}

struct node *newnode(int data){
    struct node *temp = (struct node*)malloc(sizeof(*temp));
    temp->data = data;
    temp->next = NULL;
    return temp;
}


void read_list(){
    struct node *temp = HEAD;

    while(temp!=NULL){
        printf("%d\n", temp->data);
        temp=temp->next;
    }
}

void add(int data){
    if(HEAD==NULL) {
        HEAD = newnode(data);
        TAIL = HEAD;
        return ;
    }

    struct node *temp  = newnode(data);
    TAIL->next = temp;
    TAIL = temp;
}

void start_pub(){
    
    struct addrinfo hints, *res;
    memset(&hints, 0, 1000);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(HOST, PORT, &hints, &res)!=0){
        perror("ADDR\n");
        exit(0);
    }

    int sock = socket(res->ai_family, res->ai_socktype, 0);
    if(sock==-1){
        perror("SOCK");
        exit(0);
    }

    if(bind(sock, res->ai_addr, (res->ai_addrlen))==-1){
        perror("BIND");
        exit(0);
    }

    if(listen(sock, 10)==-1){
        perror("LISTEN");
        exit(0);
    }

    char buff[1000];
    while(1){
        printf(".........WAITING......\n");
        int new_sock = accept(sock, res->ai_addr, &(res->ai_addrlen));
        printf(".........CONNECTED......\n");

        recv(new_sock, buff, 1000, 0);
        printf("%s\n", buff);

        struct request *r = (struct request *)malloc(sizeof(*r));
        r->sock = new_sock;

        pthread_t th;
        pthread_create(&th, NULL, run, (void *)r);
    }
}

void *build(void *atr){
    int i;
    for(i=0;i<=100;i++){
        printf("Publishing %d\n", i);
        add(i);    
        sleep(10);
    }
}

void read_input(int argc, char *argv[]){

    int i;
    for(i=1;i<argc;i++){
        if(strcmp("-p", argv[i++])==0){
            strcpy(PORT, argv[i]);
        }
    }
}

int main(int argc, char *argv[]){

    read_input(argc, argv);
    pthread_t th;
    pthread_create(&th, NULL, build, NULL);
    start_pub();

}
