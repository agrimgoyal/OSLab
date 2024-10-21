// consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_KEY 1234

typedef struct msgbuf {
    long mtype;
    char mtext[200];
} message_buf;

int main() {
    int msgid;
    message_buf rbuf;

    // Access the message queue
    msgid = msgget(QUEUE_KEY, 0666);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    // Receive the message
    if (msgrcv(msgid, &rbuf, sizeof(rbuf.mtext), 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received Message: %s\n", rbuf.mtext);
    
    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
