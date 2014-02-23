#include <stdio.h>
#include <string.h>

void reverse(char *line, int N){
    int i=0;
    while(i<=(N-1)/2){
        char temp = line[i];
        line[i] = line[(N-1)-i];
        line[(N-1)-i] = temp;
        i++;
    }
}

int max_line(char *line, int *i){
    char ch;
    *i=0;

    while(1){
        ch = getchar();
        if(ch=='\n'){
            line[*i] = '\0';
            reverse(line, (*i));
            return 0;
        }
        else if(ch==EOF){
            line[*i] = '\0';
            reverse(line, (*i));
            return -1;
        }
        line[*i] = ch;
        (*i)++;
    }
}

int main(int argc, char *agrv[]){

    char line[1000];
    char cpy_line[1000];
    int max=0;
    int count;


    enum BOOLEAN { YES, NO };
    printf("%d\n", YES);


    while(1){
        int l=max_line(line, &count);
        if(count>max){
            max = count;
            strcpy(cpy_line, line);
        }
        if(l==-1) break;
    }

    printf("Maxline is : %s\n", cpy_line);
    return 0;
}
