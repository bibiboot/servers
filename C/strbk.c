#include <stdio.h>

int main(int argc, char *argv[]){

    char s1[7] = "bcbcbcd";
    char s2[5] = "bcbcd";

    int N=6;
    int M=4;

    int i;
    for(i=0; i<=N; i++){
        char *start = s1+i;
        int temp = i;
        int j = 0;
        while(temp<=N && j<=M && s1[temp++] == s2[j++]);

        if(temp==(N+1) && j==(M+1)){
            printf("Matched %s\n", start);
            return 0;
        }
    }

}
