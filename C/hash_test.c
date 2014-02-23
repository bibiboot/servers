#include <stdio.h>
#include <search.h>

int N=2;
char *data[2] = { "cat", "apple" };
char *data2[2] = { "cat", "say" };

int main(int argc, char *argv[]){
    ENTRY e, *ep;
    int i;
    hcreate(10);

    for(i=0; i<N; i++){
        e.key = data[i];
        e.data = (void*)i;
        printf("Added %s\n", data[i]);
        hsearch(e, ENTER);
    }

    for(i=0; i<N; i++){
        e.key = data2[i];
        ep = hsearch(e, FIND);
        if(ep!=NULL) printf("Matched %s\n", data2[i]);
    }
}
