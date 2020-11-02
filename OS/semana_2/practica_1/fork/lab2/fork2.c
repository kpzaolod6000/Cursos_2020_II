#include <stdio.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>   // For wait and related macros.

int main() {
    pid_t pid = fork(); // Fork a child process.
    if (pid < 0) { // Error occurred.
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) { // Child process.
        printf("[CHILD]: About to load command.\n");
        execlp("ls", "-la", (char*) NULL);//SI
	//execlp("usr/var","ls", "-la", (char*) NULL);NO
	//execlp("gcc fork0.c -o p","./p", (char*) NULL);NO
	//execlp("./fork0", (char*) NULL); SI
	      printf("[CHILD]: Great! It worked!\n");
    } else { // Parent process.
        printf("[PARENT]: Waiting on child.\n");
        wait(NULL);
        printf("[PARENT]: Child finished.\n");
    }
    return 0;
}
