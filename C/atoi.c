#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    char given[3] = "123";
    int sum = 0;
    int i;

    for(i=2; i>=0; i--){
        int val = given[i] - '0';
        sum += val*pow((double)10, (double)2-i);
    }

    printf("Value : %d\n", sum);
    return 0;
}
