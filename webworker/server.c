#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

struct node {
    int data;
    int sock;
    struct node *next;
};

struct node *HEAD;
struct node *TAIL;

char *HOST = "127.0.0.1";
char PORT[100];

pthread_mutex_t m;
pthread_cond_t cond;

int isEmpty(){
    if(HEAD==NULL) return 0;
    return -1;
}

struct node *create_node(int data, int sock){
    struct node *temp = (struct node *)malloc(sizeof(*temp));
    temp->data = data;
    temp->sock = sock;
    temp->next = NULL;
    return temp;
}

void add(int data, int sock){
    if(HEAD==NULL){
        HEAD = create_node(data, sock);
        TAIL = HEAD;
        return; 
    }

    struct node *temp = create_node(data, sock);
    TAIL->next = temp;
    TAIL = temp;
}

struct node *pop(){
    if(isEmpty()==0) return NULL;

    struct node *temp = HEAD;
    HEAD = HEAD->next;
    return temp; 
}

void read_input(int argc, char *argv[]){
    int i;
    for(i=1; i<argc; i++){
        if(strcmp(argv[i++], "-p")==0){
            strcpy(PORT, argv[i]);
        }
    }
}

void *run(void *attr){

    int curr = (int)pthread_self();
    while(1){
        pthread_mutex_lock(&m);
        if(isEmpty()==0){
            pthread_cond_wait(&cond, &m);
        }
        struct node *temp = pop();
        if(temp!=NULL){
        printf("%d Working\n", curr);
        printf("%d\n", temp->data);
        
        char *test = "Hello";
        send(temp->sock, test, strlen(test), 0);
        }
        sleep(5);

        pthread_mutex_unlock(&m);

    }

}

void init_pool(){
    int i;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);

    for(i=0; i<10; i++){
        pthread_t th;
        pthread_create(&th, NULL, run, NULL);
    }
}

void start(){
    struct addrinfo hints, *res;

    memset(&hints, 0, 100);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(HOST, PORT, &hints, &res);

    int sock = socket(res->ai_family, res->ai_socktype, 0);

    bind(sock, res->ai_addr, res->ai_addrlen);

    listen(sock, 10);

    char buff[100];
    int i=0;
    while(1){
        int sockid = accept(sock, res->ai_addr, &(res->ai_addrlen));

        recv(sockid, buff, strlen(buff), 0);
         
        //Add to the Queue 
        add(i++, sockid);
        //Broadcast
        pthread_mutex_lock(&m);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&m);
        sleep(10);
    }
}

int main(int argc, char *argv[]){
    read_input(argc, argv);
    init_pool();
    start();
}
