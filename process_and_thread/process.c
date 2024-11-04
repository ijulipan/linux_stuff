#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
    pid_t child_pid;
    child_pid = fork(); // Creates new child process, 0 is child PID
    if (child_pid < 0){
        printf("Fork failed\n");
        return 1;
    }
    else if (child_pid == 0){
        printf("Child process successfully created!\n");
        printf("Child PID = %d, Parent PID = %d \n", getpid(), getppid()); // Use getpid() to get the child process's PID and getppid() to get the parent's PID
    }
    else{
        wait(NULL); // NULL is used to indicate that we are not interested in receiving information about the exit status of the child process 
        printf("Parent Process Successfully Created!\n");
        printf("Child PID = %d, Parent PID = %d \n", getpid(), getppid()); 
        /*
            Child PID output will be similar to the Parent PID in the child process because the child in this process
            is the Parent process and it's parent is the terminal or shell process from where we ran the program
        */
    }

    return 0;

}