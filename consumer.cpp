#include <sys/types.h> //for key pid
#include <sys/ipc.h> //ipc
#include <sys/sem.h> // sema
#include <sys/shm.h> //shared mem

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h> 

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Wrong input!" << endl;
        return 1;
    }

    fstream out;
    out.open(argv[1]);

    if (!out.is_open()) {
        exit(1);
    }

    int shmSize = atoi(argv[2]);

    int semId;
    key_t semKey = 1234; //one sema set
    // IPC_CREAT - If no existing semaphore set is associated with the key, create one
    // 0666 - Remember chmod? The 0 in front specifies that the number is in octal
    int semFlag = IPC_CREAT | 0666;
    int nSems = 1; 

    semId = semget(semKey, nSems, semFlag);
    if (semId == -1) {
        error( "semget" );
        exit(1);
    }

    // sharedmem part
    int shmId;
    key_t shmKey = 4567; 
    int shmFlags = IPC_CREAT | 0666;
    char* sharedMem;

    shmId = shmget(shmKey, shmSize, shmFlags);
    sharedMem = (char*) shmat(shmId, NULL, 0);

    // status part
    int shmStatusId;
    key_t shmStatusKey = 6969; //for chesca to revise, idk if these mean anyth or if i can just pick any num
    int shmStatusFlags = IPC_CREAT | 0666;
    char* sharedStatusMem;

    shmStatusId = shmget(shmStatusKey, 2, shmStatusFlags);  
    sharedStatusMem = (char*) shmat(shmStatusId, NULL, 0);

    // my opps
    int nOperations = 2;
    struct sembuf sema[nOperations];

    //wait if prod done writing
    sema[0].sem_num = 0;
    sema[0].sem_op = 0;  
    sema[0].sem_flg = SEM_UNDO;
    //SEM_UNDO: Allocates space for an undo operation if the process 
    //terminates abnormally. Prevents semaphores from accidentally 
    //being locked forever, or until a system reboot.

    //then allow consumer to write
    sema[1].sem_num = 0;
    sema[1].sem_op = 1;  
    sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;
    //IPC_NOWAIT: Force error if operation must wait.

    //sema ops
    int opResult = semop(semId, sema, nOperations);
    if (opResult != -1) {
            printf("Reading...\n");

            //https://www.programiz.com/c-programming/library-function/string.h/strcmp
            if (strcmp(sharedStatusMem, "done") == 0) {
                printf("Producer is done!\n");
                return 0;  
            }

            if (strcmp(sharedStatusMem, "written") == 0) {
                out.write(sharedMem, shmSize);
                printf("Written!\n");

                strcpy(sharedStatusMem, "read");
                memset(sharedMem, 0, shmSize);  
            }

            nOperations = 1;
            sema[0].sem_num = 0;
            sema[0].sem_op = -1;  
            sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

            opResult = semop(semId, sema, nOperations);
            if (opResult != -1) {
                perror("semop (decrement)");
            } else {
                printf( "Successfully decremented semaphore!\n" );
            }

    } else {
        perror( "semop (increment)" );
        sleep(1);
    }

    //close for memo leaks potentially
    out.close();
    //https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-shmdt-shared-memory-detach-operation
    shmdt(sharedMem);
    shmdt(sharedStatusMem);

    return 0;
}
