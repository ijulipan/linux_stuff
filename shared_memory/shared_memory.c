/* This is an example code to implement shared memory IPC using Parent-Child process */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MEM_SIZE 1024

int main(){
    /* Creates a shared memory segment, returns an FD*/
    int shm_id = shmget(IPC_PRIVATE, MEM_SIZE, IPC_CREAT | 0666);
    if(shm_id < 0){
        perror("shmget");
        exit(1);
    }

    /* Attach the shared memory segment to parent process */
    char* shared_memory;
    shared_memory = shmat(shm_id, NULL, 0);
    if (shared_memory == -1)
    {
        perror("shmat");
        exit(1);
    }

    /* Fork the process */
    pid_t pid = fork();

    if(pid == 0){
        sleep(1);

        /* Reattach the shared memory */
        char* child_shared_memory = shmat(shm_id, NULL, 0);
         if (child_shared_memory == (char*) -1){
            perror("shmat");
            exit(1);
        }

        /* Write the data */
        snprintf(child_shared_memory, MEM_SIZE, "Hello from Child!");
        printf("Child wrote: %s\n", child_shared_memory);

        /* Detach the shared memory */
        shmdt(child_shared_memory);

        /* Mark for deletion */
        shmctl(shm_id, IPC_RMID, NULL);
    } else{
        /* Wait for child process to finish writing*/
        wait(NULL);
        printf("Parent read: %s\n", shared_memory);

        /* Detach after writing */
        shmdt(shared_memory);
        
    }
    
}