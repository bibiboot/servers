#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char given[100];
    strcpy(given, "Danisha");
    char c = 'a';

    int i = 0;
    int j = 0;
    while(given[i]!='\0'){
       if(given[i]==c){
           i++;
       } 
       given[j++] = given[i++];
    } 

    given[j] = '\0';

    printf("Given: %s\n", given);

}
