#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

// from https://www.w3schools.com/cpp/cpp_files.asp
#include <iostream>
#include <fstream>

// from https://en.cppreference.com/w/cpp/thread/sleep_for
#include <thread>

using namespace std;

int main( int argc, char* argv[] ) {

  if (argc > 3 || argc < 3) {
    perror("wrong input");
    exit(1);
  }

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

  // semaphore
  int semId;
  key_t semKey = 1234; // will be used by consumer as well, change if there are problems
  int semFlag = IPC_CREAT | 0666;
  int nSems = 1; // will be used by consumer as well

  semId = semget( semKey, nSems, semFlag );

  if (semId == -1) {
    perror("semget failed");
    exit(1);
  }

  // shared memory for read/write
  int shmIdRw;
  key_t shmKeyRw = 4567;
  int shmFlagsRw = IPC_CREAT | 0666;
  char* sharedMemRw;

  shmIdRw = shmget( shmKeyRw, shmSize, shmFlagsRw );

  sharedMemRw = (char*) shmat(shmIdRw, NULL, 0);

  if ((int*) sharedMemRw == (int*) -1) {
    perror("shmget for read/write failed");
    exit(1);
  }

  // shared memory for status
  int shmIdStat;
  key_t shmKeyStat = 6969;
  int shmFlagsStat = IPC_CREAT | 0666;
  char* sharedMemStat;

  shmIdStat = shmget( shmKeyStat, 2, shmFlagsStat );

  sharedMemStat = (char*) shmat(shmIdStat, NULL, 0);

  if ((int*) sharedMemStat == (int*) -1) {
    perror("shmget for status failed");
    exit(1);
  }

  // INTIALIZATION, run producer first
  strcpy(sharedMemStat, "done");

  // ** semaphore + shared memory accessing

  while (true) {
    if ((strcmp(sharedMemStat, "read") == 0 || strcmp(sharedMemStat, "done") == 0)) {
        if (file.peek() == EOF) {
            strcpy(sharedMemStat, "done");
            printf("Status: %s\n", sharedMemStat);
            break;
        }
        printf("Proceed...\n");
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

        // check if semaphore is currently being used
        printf("Checking if producer can proceed...\n");
        int opResult = semop( semId, sema, nOperations );

        if (opResult != -1) {
            printf("File has been found and no one is using shared memory. Writing file contents to shared memory...\n");

            // insert stuff here
            // should probably add a check for if file is empty
            char buffer[shmSize];
            file.read(buffer, shmSize);
            strcpy(sharedMemRw, buffer);
            strcpy(sharedMemStat, "written");
            printf("Status: %s\n", sharedMemStat);
            printf("Written: %s\n", sharedMemRw);

            // AFTER
            // decrease semaphore by 1
            nOperations = 1;

            sema[0].sem_num = 0;
            sema[0].sem_op = -1;
            sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

            opResult = semop( semId, sema, nOperations );
        }
        else {
            printf("Someone is using the shared memory. Trying again in 2 seconds...\n");
            sleep(2);
        }
        }
        else {
        printf("Waiting for response from consumer...\n");
        sleep(2);
        }
    }
  file.close();
  shmdt(sharedMemStat); 
  shmdt(sharedMemRw);
  shmctl(shmIdStat, IPC_RMID, NULL);
  shmctl(shmIdRw, IPC_RMID, NULL);
  semctl(semId, 0, IPC_RMID);
  return 0;
}
