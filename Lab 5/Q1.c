#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
       
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {
        
        printf("This is the child process!\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        
        printf("This is the parent process!\n");
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        wait(NULL); 
    }

    return 0;
}
