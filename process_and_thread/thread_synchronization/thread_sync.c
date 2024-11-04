#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// Declare thread IDs
pthread_t thread_id[2];

// Declare mutex lock
pthread_mutex_t lock;


int counter;

void * increment_pointer(void* arg){
    // Lock the mutex first
    while (1){
        pthread_mutex_lock(&lock);

        if(counter >= 100){
            // Unlock the mutex if counter reaches 100
            pthread_mutex_unlock(&lock);
            break;
        }

        counter += 1;
        printf("Counter: %d\n", counter);

        //Unlock the mutex to allow each thread access to the counter and increment one by one
        pthread_mutex_unlock(&lock);
    }
    return NULL;
    
}

int main(){
    int i = 0;
    int error;

    if((pthread_mutex_init(&lock, NULL)) != 0){
        printf("Mutex init unsuccessful.\n");
        return 1;
    }

    while(i < 2){
        // create the thread and save as error
        error = pthread_create(&thread_id[i], NULL, &increment_pointer, NULL);

        if(error != 0){
            printf("Thread cannot be created!\n");
            strerror(error);
        }
        i++;
    }

    // Queue the threads to finish first and then destroy the mutex after use
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}