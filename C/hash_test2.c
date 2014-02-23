#include <stdio.h>
#include <search.h>

int main(int argc, char *argv[]){
    hcreate(30);

    ENTRY ep, *e;
    ep.key = "data";
    ep.data = (void*)100;
    hsearch(ep, ENTER);

    e = hsearch(ep, FIND);
    printf("%d\n", (int)e->data);
    return 0;
}
