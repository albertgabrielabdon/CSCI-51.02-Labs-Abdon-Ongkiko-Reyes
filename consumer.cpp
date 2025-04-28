#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <sys/shm.h>   

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Wrong" << endl;
        return 1;
    }

    fstream out;
    out.open(argv[1], ios::out | ios::binary);

    if (!out.is_open()) {
        cerr << "Failed" << endl;
        return 1;
    }

    int shmSize = atoi(argv[2]);

    int semId;
    key_t semKey = 1234;
    int semFlag = IPC_CREAT | 0666;
    int nSems = 1;

    semId = semget(semKey, nSems, semFlag);
    if (semId == -1) {
        perror("semget failed");
        exit(1);
    }

    int shmId;
    key_t shmKey = 4567;
    int shmFlags = IPC_CREAT | 0666;
    char* sharedMem;

    shmId = shmget(shmKey, shmSize, shmFlags);
    if (shmId == -1) {
        perror("shmget failed");
        exit(1);
    }

    sharedMem = (char*)shmat(shmId, NULL, 0);
    if (sharedMem == (char*)(-1)) {
        perror("shmat failed");
        exit(1);
    }

    int shmStatusId;
    key_t shmStatusKey = 6969;
    int shmStatusFlags = IPC_CREAT | 0666;
    char* sharedStatusMem;

    shmStatusId = shmget(shmStatusKey, 2, shmStatusFlags);
    if (shmStatusId == -1) {
        perror("shmget (status) failed");
        exit(1);
    }

    sharedStatusMem = (char*)shmat(shmStatusId, NULL, 0);
    if (sharedStatusMem == (char*)(-1)) {
        perror("shmat (status) failed");
        exit(1);
    }

    struct sembuf sema[2];

    while (true) {
       
        sema[0].sem_num = 0;
        sema[0].sem_op = 0; 
        sema[0].sem_flg = SEM_UNDO;
        
        sema[1].sem_num = 0;
        sema[1].sem_op = 1; 
        sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

        int opResult = semop(semId, sema, 2);
        if (opResult == -1) {
            perror("semop wait failed");
            continue;
        }


        if (strcmp(sharedStatusMem, "done") == 0) {
            printf("Producer signaled done.\n");
            break; 
        }

        if (strcmp(sharedStatusMem, "written") == 0) {
            printf("Consumer reading...\n");

            for (int i = 0; i < shmSize; i++) {
                char c = sharedMem[i];

                if (c == '\0') {
                    break; 
                }

                out.put(c);

            }


            strcpy(sharedStatusMem, "read");
            memset(sharedMem, 0, shmSize);
        }

        sema[0].sem_num = 0;
        sema[0].sem_op = -1; 
        sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;
        

        opResult = semop(semId, sema, 1);
        if (opResult == -1) {
            perror("semop release failed");
        } else {
            printf("Consumer cycle done.\n");
        }
        sleep(2);
    }

    out.close();
    shmdt(sharedMem);
    shmdt(sharedStatusMem);

    return 0;
}
