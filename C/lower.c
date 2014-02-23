#include <stdio.h>

int main(int argc, char *argv[]){
    char given[5] = "ABCef";
    char final[5];
    int i;

    for(i=0; i<=4; i++){
        if(given[i] >= 'A' && given[i] <= 'Z'){
            final[i] = given[i] + 'a' -'A';
        }
        else{
            final[i] = given[i];
        }
    }
    final[i] = '\0';

    printf("Lowe case: %s\n", final);


}
