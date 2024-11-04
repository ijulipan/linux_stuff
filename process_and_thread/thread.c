#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function for thread to perform tasks
void * thread_function(void *arg){
    printf("Hello from thread!\n");
    return NULL;
}

int main(){

    // Declare thread ID
    pthread_t thread_id;

    printf("Before thread executed function.\n");
    // Create a thread
    pthread_create(&thread_id, NULL, thread_function, NULL);
    pthread_join(thread_id, NULL);

    printf("After thread finished processing.\n");

    return 0;

}