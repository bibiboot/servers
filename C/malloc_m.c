#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  int *i1, *i2, *i3;

  printf("sbrk(0) before malloc(4): 0x%x\n", sbrk(0));
  i1 = (int *) malloc(4);
  printf("sbrk(0) after `i1 = (int *) malloc(4)': 0x%x\n", sbrk(0));
  i2 = (int *) malloc(4);
  printf("sbrk(0) after `i2 = (int *) malloc(4)': 0x%x\n", sbrk(0));
  printf("i1 = 0x%x, i2 = 0x%x, sbrk(0)-i2 = %d\n", i1, i2, 
             (char *) sbrk(0)- (char *) i2);
  i3 = (int *) malloc(8164);
  printf("sbrk(0) after `i3 = (int *) malloc(8164)': 0x%x\n", sbrk(0));
  printf("i3 = 0x%x\n", i3);
  return 0;
}
