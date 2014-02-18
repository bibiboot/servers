#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    setenv("scp_dan", "Value", 0);
    char *s = getenv("scp_dan");
    if(s==NULL) printf("No variable\n");
    else printf("%s\n", s);
    return 0;

}
