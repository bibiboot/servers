#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *HEAD;
struct node *TAIL;

struct node *create_node(int data){
    struct node *temp = (struct node *)malloc(sizeof(*temp));
    temp->next = NULL;
    temp->data = data;
    return temp;
}

int isEmpty(){
    if(HEAD==NULL) return 0;
    return -1;
}

void add(int data){
    if(HEAD==NULL){
        struct node *temp = create_node(data);
        HEAD = temp;
        TAIL = HEAD;
        return ;
    }
   struct node *temp = create_node(data);
   TAIL->next = temp;
   TAIL = temp;
}

struct node *pop(){
   if(isEmpty()==0) return NULL; 

   struct node *temp = HEAD;
   HEAD = HEAD->next;
   return temp;
}

pthread_mutex_t m;
pthread_cond_t cond;

void *run(void *attr){

    int thid = (int)pthread_self();
    struct node *temp = HEAD;
    while(1){
        pthread_mutex_lock(&m);
        if(isEmpty()==0){
            printf("COND WAIT\n");
            pthread_cond_wait(&cond, &m);
            //while(isEmpty()==0);
        }
        printf("%d\t%d\n", thid, temp->data);
        temp=temp->next;
        pthread_mutex_unlock(&m);
    }

}

void init_pool(){
    int i;
    for(i=0;i<10;i++){
        pthread_t th ;
        pthread_create(&th, NULL, run, NULL);
    }
}

void *build(void *attr){
    int i;
    for(i=0; i<=100; i++){
        pthread_mutex_lock(&m);
        add(i);
        printf("BROADCASTING\n");
        pthread_cond_broadcast(&cond); 
        pthread_mutex_unlock(&m);
        sleep(10);
        
    }
}


int main(int argc, char *argv[]){
    pthread_t th;
    pthread_create(&th, NULL, build, NULL);
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);
    init_pool();

    while(1);
}
