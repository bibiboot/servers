#include <stdio.h>
#include <stdlib.h>

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

void add(int data){
    if(HEAD==NULL){
        HEAD = create_node(data);
        TAIL = HEAD;
        return;
    }

    struct node *temp = create_node(data);
    TAIL->next = temp;
}


int main(int argc, char *argv[]){

    add(1);
    add(2);

    struct node *temp = HEAD;
    while(temp!=NULL){
        printf("%d\n", temp->data);
        temp = temp->next;
    }

}
