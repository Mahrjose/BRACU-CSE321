#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg {
    long int type;
    char txt[50];
};

int main() {
    int msgid;
    key_t key = IPC_PRIVATE;
    struct msg message;

    // Create message queue
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {

        if (msgrcv(msgid, &message, sizeof(message.txt), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("OTP generator received workspace name from log in: %s\n", message.txt);
        int otp = getpid();

        message.type = 2;
        sprintf(message.txt, "%d", otp);
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to log in from OTP generator: %d\n", otp);

        message.type = 3;
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("OTP sent to mail from OTP generator: %d\n", otp);

        exit(EXIT_SUCCESS);
    } else {
        printf("Please enter the workspace name:\n");
        char workspace[50];
        scanf("%s", workspace);

        if (strcmp(workspace, "cse321") != 0) {
            printf("Invalid workspace name\n");
            exit(EXIT_FAILURE);
        }

        message.type = 1;
        strcpy(message.txt, workspace);
        msgsnd(msgid, &message, sizeof(message.txt), 0);
        printf("Workspace name sent to otp generator from log in: %s\n", workspace);

        // Read OTP from otp generator
        if (msgrcv(msgid, &message, sizeof(message.txt), 2, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Log in received OTP from OTP generator: %s\n", message.txt);

        // Read OTP from mail
        if (msgrcv(msgid, &message, sizeof(message.txt), 3, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Log in received OTP from mail: %s\n", message.txt);

        // Verify OTP
        if (strcmp(message.txt, message.txt) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        // Remove message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(1);
        }

        exit(EXIT_SUCCESS);
    }

    return 0;
}
