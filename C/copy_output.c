#include <stdio.h>

int main(int argc, char *argv[]){

    char c;
    while((c=getchar())!=EOF){
        printf("Inside\n");
        putchar(c);
     }
     return 0;
}
