#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>

// from https://www.w3schools.com/cpp/cpp_files.asp
#include <iostream>
#include <fstream>

using namespace std;

int main( int argc, char* argv[] ) {

  fstream file;
  file.open(argv[1]);

  int shmSize = (int) argv[2];

  // insert everything here
  // read contents
  // write contents to shared memory
  // close program

  // semaphore + shm initialization

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

  // semaphore accessing

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

  // THIS IS FOR THE CONSUMER
  // decrement semaphore by 1
  // sema[1].sem_num = 0;
  // sema[1].sem_op = -1;
  // sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

  // semaphore operation

  // check if semaphore is currently being used
  int opResult = semop( semId, sema, nOperations );

  if (opResult != -1) {
    printf("No one is using the file. Making changes...");

    // insert stuff here
    while (file.peek() != EOF) {
      file.read(shm, shmSize);
    }

    // after
    nOperations = 1;

    sema[0].sem_num = 0;
    sema[0].sem_op = -1;
    sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

    opResult = semop( semId, sema, nOperations );

    if (opResult != -1) {
      printf("Successfully wrote to file.\n");
    }
    else {
      printf("Could not write to file.\n");
    }    
  }
  else {
    printf("Someone may be using the file. Aborting...");
  }

  file.close();

  return 0;
}