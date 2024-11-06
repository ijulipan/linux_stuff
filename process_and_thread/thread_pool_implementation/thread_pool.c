#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 4
typedef struct Task {
    int a, b;
} Task;

Task taskQueue[256];
int taskCount = 0;

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void submitTask(Task task){
    /* Function to submit a task onto the Queue */
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

void executeTask(Task* task){
    /* Function to execute a task*/
    int result = task->a + task->b;
    printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}

void* start_thread(void* arg){
    /* Function to wait and get a task from the Queue */
    while (1){
        Task task;
        int found = 0;
        /* lock the mutex first to assign one thread to check & fetch a task in the Queue*/
        pthread_mutex_lock(&mutexQueue);
        while (taskCount == 0){
            pthread_cond_wait(&condQueue, &mutexQueue);
        }
        
        found = 1;
        task = taskQueue[0];
        for (int i = 0; i < taskCount - 1; i++){
            taskQueue[i] = taskQueue[i + 1];
        }
        taskCount--;
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);
        
    }
}

int main(){
    /* Testing the execute task function
    Task t1 = {.a = 10, .b = 20};

    executeTask(&t1);
    */

   pthread_t thread[THREAD_NUM];
   int i;

   pthread_mutex_init(&mutexQueue, NULL);
   pthread_cond_init(&condQueue, NULL);

   /* Create the threads */
   for(i = 0; i < THREAD_NUM; i++){
    if((pthread_create(&thread[i], NULL, &start_thread, NULL)) != 0){
        perror("Failed to create the thread.");
    }

    srand(time(NULL));

    /* Create 100 tasks with random numbers and submit it to the task Queue */
    for(i = 0; i < 100; i++){
        Task t = { .a = rand() % 100, .b = rand() % 100};
        submitTask(t);
    }

    /* Join the threads */
    if((pthread_join(&thread[i], NULL)) != 0){
        perror("Failed to join the thread.");
    }
   }

   pthread_mutex_destroy(&mutexQueue);
   pthread_cond_destroy(&condQueue);

    return 0;
}