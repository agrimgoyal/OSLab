// producer.c
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_message_queue"
#define MAX_SIZE 1024
#define MSG_STOP "exit"

int main() {
    mqd_t mq;
    char message[MAX_SIZE];

    // Open or create the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, NULL);
    if (mq == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Enter your message: ");
    fgets(message, MAX_SIZE, stdin);

    // Send the message to the queue
    if (mq_send(mq, message, strlen(message), 0) == -1) {
        perror("mq_send");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the queue: %s\n", message);

    // Close the queue
    mq_close(mq);

    return 0;
}
