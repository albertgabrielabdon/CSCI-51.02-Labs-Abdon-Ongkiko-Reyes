#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

// from https://www.w3schools.com/cpp/cpp_files.asp
#include <iostream>
#include <fstream>

// from https://en.cppreference.com/w/cpp/thread/sleep_for
#include <thread>

using namespace std;

int main( int argc, char* argv[] ) {

  fstream file;
  file.open(argv[1]);

  // from https://www.programiz.com/cpp-programming/examples/binary-decimal-convert
  int shmSize = atoi(argv[2]);
  // int shmSizeDec = shmSize;
  // int dec = 0, i = 0, rem;
  // while (shmSizeDec != 0) {
  //   rem = shmSizeDec % 10;
  //   shmSizeDec /= 10;
  //   dec += rem * pow(2, i);
  //   ++i;
  // }
  // shmSizeDec = dec;
  printf("shmSize: %d\n", shmSize);

  // insert everything here
  // read contents
  // write contents to shared memory
  // close program

  // ** semaphore + shared memory initialization

  int semId;
  key_t semKey = 1234; // will be used by consumer as well, change if there are problems
  int semFlag = IPC_CREAT | 0666;
  int nSems = 1; // will be used by consumer as well

  semId = semget( semKey, nSems, semFlag );

  if (semId == -1) {
    perror("semget failed");
    exit(1);
  }

  int shmId;
  key_t shmKey = 4567;
  int shmFlags = IPC_CREAT | 0666;
  char* sharedMem;

  shmId = shmget( shmKey, shmSize, shmFlags );

  sharedMem = (char*) shmat(shmId, NULL, 0);

  if ((int*) sharedMem == (int*) -1) {
    perror("shmget failed");
    exit(1);
  }

  // ** semaphore + shared memory accessing

  int nOperations = 2;
  struct sembuf sema[nOperations];

  // FIRST:
  // wait for semaphore to become 0
  sema[0].sem_num = 0;
  sema[0].sem_op = 0;
  sema[0].sem_flg = SEM_UNDO;

  // SECOND:
  // increment semaphore by 1
  sema[1].sem_num = 0;
  sema[1].sem_op = 1;
  sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

  while (true) {
    // check if semaphore is currently being used
    printf("Checking if producer can proceed...\n");
    int opResult = semop( semId, sema, nOperations );

    if (opResult != -1) {
      printf("No one is using the file and the shared memory is okay to use. Making changes...\n");

      // insert stuff here
      // should probably add a check for if file is empty
      while (file.peek() != EOF) {
        char buffer[shmSize];
        file.read(buffer, shmSize);
        strcpy(sharedMem, buffer);
        printf("Written: %s\n", buffer);
      }

      // AFTER
      // decrease semaphore by 1
      nOperations = 1;

      sema[0].sem_num = 0;
      sema[0].sem_op = -1;
      sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

      opResult = semop( semId, sema, nOperations );

      if (opResult != -1) {
        printf("Successfully wrote to shared memory.\n");
      }
      else {
        printf("Could not write to shared memory.\n");
      }

      break;
    }
    else {
      printf("Someone may be using the file. Trying again in 2 seconds...\n");
      this_thread::sleep_for(2000ms);
      continue;
    }

    file.close();
    return 0;
  }
}