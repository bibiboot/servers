#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

void get_time(char *desti){
    struct timeval tv;
    gettimeofday(&tv, NULL);

    char *human_time = ctime(&(tv.tv_sec)) + 11;
    strncpy(desti, human_time, 8);
    desti[8]  = '\0';
    sprintf(desti, "%s.%d", desti,(int)(tv.tv_usec));
}

int main(int argc, char *argv[]){
    char desti[100];
    get_time(desti);
    printf("%s\n", desti);
}

