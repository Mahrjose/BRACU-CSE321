#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

struct shared {
    char sel[100];
    int b;
};

int main() {
    int shmid;
    key_t key = IPC_PRIVATE;
    struct shared *shmptr;

    if ((shmid = shmget(key, sizeof(struct shared), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shmptr = (struct shared *)shmat(shmid, NULL, 0)) == (struct shared *) -1) {
        perror("shmat");
        exit(1);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);
        char buf[BUFFER_SIZE];
        ssize_t bytes_read = read(pipefd[0], buf, BUFFER_SIZE);
        if (bytes_read < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buf[bytes_read] = '\0';
        printf("Received: %s\n", buf);

        if (strcmp(shmptr->sel, "a") == 0) {
            printf("Your selection: a\n\nEnter amount to be added:\n");
            int amount;
            scanf("%d", &amount);
            if (amount > 0) {
                shmptr->b += amount;
                printf("Balance added successfully\nUpdated balance after addition: %d\n", shmptr->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (strcmp(shmptr->sel, "w") == 0) {
            printf("Your selection: w\n\nEnter amount to be withdrawn:\n");
            int amount;
            scanf("%d", &amount);
            if (amount > 0 && amount <= shmptr->b) {
                shmptr->b -= amount;
                printf("Balance withdrawn successfully\nUpdated balance after withdrawal: %d\n", shmptr->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (strcmp(shmptr->sel, "c") == 0) {
            printf("Your selection: c\n\nYour current balance is: %d\n", shmptr->b);
        } else {
            printf("Invalid selection\n");
        }

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
        
    } else {
        close(pipefd[0]);
        printf("Provide Your Input From Given Options:\n1. Type a to Add Money\n2. Type w to Withdraw Money\n3. Type c to Check Balance\n");

        char input[100];
        scanf("%s", input);

        strcpy(shmptr->sel, input);

        shmptr->b = 1000;

        write(pipefd[1], input, strlen(input) + 1);
        close(pipefd[1]);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Thank you for using\n");
        }

        close(pipefd[1]);

        if (shmdt(shmptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }

        exit(EXIT_SUCCESS);
    }

    return 0;
}
