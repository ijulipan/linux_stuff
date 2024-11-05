/* Producer-Consumer Problem */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAXBUF 10
// Declaring the thread IDs
pthread_t thread_id[2];

// Declare a mutex
pthread_mutex_t lock;
pthread_cond_t cond;

int buffer[MAXBUF];
int counter;

void* producer(void* arg){
    for(int i = 0; i < 20; i++){
        // lock the mutex first
        pthread_mutex_lock(&lock);
        while (counter == MAXBUF){
            /* If the buffer is full, send the wait signal to the consumer that it is waiting for it to consume a product */
            pthread_cond_wait(&cond, &lock);
        }
        /* Add an item to the buffer array */
        buffer[counter++] = i; // Add the item
        printf("Produced item: %d\n", i);
        pthread_cond_broadcast(&cond); // Signal the consumer
        pthread_mutex_unlock(&lock); 
    }
    return NULL;
}

void* consumer(void* arg){
    for(int i = 0; i < 20; i++){
        /* Lock the mutex */
        pthread_mutex_lock(&lock);

        while(counter == 0){
            /* Check if the buffer is empty, send wait signal to wait for producer item */
            pthread_cond_wait(&cond, &lock);
        }

        int item = buffer[--counter];
        printf("Consumed item: %d\n", item);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
}

int main(){
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    int thread1 = pthread_create(&thread_id[0], NULL, &producer, NULL);
    int thread2 = pthread_create(&thread_id[1], NULL, &consumer, NULL);

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;

}
