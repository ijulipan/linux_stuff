#include <string.h>
#include <sys/msg.h>

int main(){
    int msqid = 0;

    struct message{
        long type;
        char text[20];
    } msg;

    long msgtyp = 0; // Set the msgtyp to 0 to receive any message type

    msgrcv(msqid, (void *)&msg, sizeof(msg.text), msgtyp, MSG_NOERROR | IPC_NOWAIT);
    printf("%s \n", msg.text);

    return 0;
}