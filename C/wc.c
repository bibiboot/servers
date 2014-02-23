#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    if(argc==1){
        fp = stdin;  
    }
    else if(argc==2){
        fp = fopen(argv[1], "r");
        if(fp==NULL){
             perror("FILE");
             exit(0);
        }
    }
    else{
        printf("In correct format\n");
        exit(0);
    }

    char ch;
    long nl, wc, word, size;
    int prev_char = 1;
    nl = 0;
    wc = 0;
    word = 0;
    size = 0;

    while((ch=fgetc(fp))!=EOF){
        size++;
        if(ch=='\n') nl++;

        if((ch==' ' || ch=='\n' || ch=='\t') && prev_char == 0){
            prev_char = 1;
            word++; 
        }
        else if((ch==' ' || ch=='\n' || ch=='\t')){
            continue;
        }
        else {
            prev_char = 0;
        }
    }    

    printf("Lines: %ld\n", nl);
    printf("Words: %ld\n", word);
    printf("Size: %ld\n", size);

    return 0;
}
