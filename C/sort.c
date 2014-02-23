#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    int ch1 = (int)a;
    int ch2 = (int)b;

    if(ch1>ch2) return 1;
    else if(ch1<ch2) return -1;
    return 0;
}

int main(int argc, char *argv[]){
    char temp[1000];
    FILE *fp = fopen("sort.c", "r");
    
    while((fgets(temp,  1000, fp))!=NULL){
        temp[0] = 'X';
        qsort(temp, sizeof(temp), sizeof(char), compare);
        printf("%s %d\n", temp, sizeof(temp));
    }
    return 0;
}


