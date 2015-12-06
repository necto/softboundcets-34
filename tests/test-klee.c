#include<stdio.h>
#include<stdlib.h>

#include<klee/klee.h>

int main(int argc, char** argv){

  int arr[100];
  int num, i;

  size_t result = 0;

  for(i = 0; i < 100; i++){
    arr[i] = rand();
  }

  // Replace user inp.ut with a symbolic variable
  num = klee_int("num");

  
  for(i = 0; i< num; i++){
    result = result + arr[i];
  }
 
  printf("the result is %zd\n", result);

  return 0;
}
