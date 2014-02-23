#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *agrv[]){

    char ch;
    int ndigits[256];

    int i;
    for(i=0;i<256;i++) ndigits[i] = 0;
    
    while((ch=getchar())!=EOF){
       // Is digit
          ndigits[ch]+=1; 
    }

    for(i=0;i<256;i++) printf("%d", ndigits[i]);
    printf("\n");

    return 0;
}
