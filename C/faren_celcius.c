#include <stdio.h>

int main(int aargc, char *argv[]){

    int upper, lower, c;

    upper = 300;
    lower = 1;

    while(lower<=upper){
        c = (5*(lower-32))/9;
        printf("%d\t%d\n", lower, c);
        lower+=20;
        if(lower==21) lower = 20;
     }
}
