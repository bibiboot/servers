#include <stdio.h>
#include <string.h>

int  main(int argc, char *argv[]){
    int i=0;
    int j=0;
    char buff[100];

    strcpy(buff, "dahddefe   ");
       char *start = buff;
       while(buff[i]!='\0' ){
           if(buff[i]!=' '){
               j=i;
           }
           i++;
       }
       buff[++j] = '\0';
       printf("Trimmed: %s %dXXXX\n", start, j);
    return 0;
}
