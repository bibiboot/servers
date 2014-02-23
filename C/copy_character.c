#include <stdio.h>


int main(int argc, char *argv[]){
    long nc = 0;
    long nl = 0;
    char c;

    while((c=getchar())!=EOF){
        nc++;
        if(c==' ') nl++;
    }

    printf("The enterred length is %ld\n", nc);
    printf("Total new line  is %ld\n", nl);

}
