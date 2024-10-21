// producer.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define QUEUE_KEY 1234

typedef struct msgbuf {
    long mtype;
    char mtext[200];
} message_buf;

int main() {
    int msgid;
    message_buf sbuf;
    size_t buflen;

    // Create the message queue
    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    sbuf.mtype = 1;  // Message type
    printf("Enter a message to add to queue: ");
    fgets(sbuf.mtext, sizeof(sbuf.mtext), stdin);

    buflen = strlen(sbuf.mtext);
    if (sbuf.mtext[buflen-1] == '\n') sbuf.mtext[buflen-1] = '\0';

    // Send the message
    if (msgsnd(msgid, &sbuf, buflen, IPC_NOWAIT) < 0) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message Sent: %s\n", sbuf.mtext);
    return 0;
}
