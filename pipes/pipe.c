#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
    Pipe syntax:
    int pipe(int fds[2]);

    fds stand for file descriptors and used to declare who is the reader and writer.

    fd[0] is used to read
    fd[1] is used to write

*/

#define MSGSIZE 20

char * msg1 = "This is message 1";
char * msg2 = "This is message 2";
char * msg3 = "This is message 3";

int main(){

    char inbuf[MSGSIZE];
    int p[2], pid, nbytes;

    // Initialize a pipe, p
    if (pipe(p) < 0){
        printf("Pipe failed to initialise\n");
        exit(1);
    }

    if ((pid = fork()) > 0){
        // Parent process
        // Write to the pipe
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);

        close(p[1]);
        wait(NULL);
    }

    else{

        // Close the writing end of the pipe
        close(p[1]);

        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0){
            printf("%s\n", inbuf);
        }
        printf("Finished reading\n");
    }
  
    return 0;
}
