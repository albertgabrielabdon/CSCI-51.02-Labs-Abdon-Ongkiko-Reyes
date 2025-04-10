#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int num;
int* arr;
pthread_t* parr;

void* someThreadRun(void* idx) {
  int* index = (int*) idx;
  int indexVal = *index;
  int oldVal;
  int newVal;
  oldVal = *(arr + indexVal);
  if (indexVal % 2 == 0) { // if index is even, then cube
    *(arr + indexVal) = pow(*(arr + indexVal), 3);
  }
  else { // if index is odd, then negate
    *(arr + indexVal) = -*(arr + indexVal);
  }
  newVal = *(arr + indexVal);
  printf("arr[%d]: %d has been replaced with %d\n", indexVal, oldVal, newVal);
  void* test;
  return test;
}

int main(int argc, const char * argv[]) {

  if (argc == 1) {
    printf("No argument given. Aborting...\n");
    return 0;
  }
  
  num = argc - 1;
 
  arr = malloc(sizeof(int)*num);
  parr = malloc(sizeof(pthread_t)*num);

  int i;

  for (i = 0; i < num; i++) {
    *(arr + i) =  strtol(argv[i+1], NULL, 0);
  }

  for (i = 0; i < num; i++) {
    pthread_t someThread;
    *(parr + i) = pthread_create(&someThread, NULL, someThreadRun, (void*) &i);
    pthread_join(someThread, NULL);
  }
  
  return 0;

}
