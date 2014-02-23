#include <stdio.h>

float power(int a, int b);

int main(int argc, char *argv[]){

   float value = power(-2, -4); 
   printf("%f\n", value);
   return 0;
}

float power(int a, int b){
    if(b==0) return 1.0;
    if(b%2==0) return power(a, b/2)*power(a, b/2);

    if(b>0 && b%2!=0) return a*power(a, (b-1)/2)*power(a, (b-1)/2);
    else return (1.0/a)*power(a, (b+1)/2)*power(a, (b+1)/2);
}
