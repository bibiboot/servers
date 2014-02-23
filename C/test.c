#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    //int fd = open("test.txt", O_RDWR|O_CREAT);
    //FILE *fp = fdopen(fd, "a+");
    FILE *fp = fopen("te", "a+");
    char ch;
    
    while((ch=getchar())!=EOF){
        printf("%c\n", ch);
        fputc(ch, fp);
        fflush(fp);
    }

    close(fp);

    return 0;
}
