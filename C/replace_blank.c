#include <stdio.h>

int main(int argc, char *argv[]){
    char ch;
    int isBlank = 0;

    while((ch=getchar())!=EOF){
        if(isBlank == 1 && ch == ' '){
            continue;
        }
        else if(ch!=' '){
            isBlank = 0;
            putchar(ch);
        }
        else {
            isBlank = 1;
            putchar('\\');
            putchar('t');
        }
    }
    return 0;
}
