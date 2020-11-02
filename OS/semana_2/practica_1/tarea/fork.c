#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 0;

int main()
{
    int local = 0;
    pid_t pid;
    /* fork a child process */
    pid = fork ();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        global++;
        local++;
        //exit(1); termina un proceso inmeditamente
        //while (1){}
        
        //execlp("/bin/ls","ls",NULL);//este proceso invoca otro pero acaba con el proceso hijo
        //global++;
        //local++;
    }
    else { /* parent process */
    /* parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete\n");
    }

    printf("%d <-> %d\n",global,local);
    return 0;
}

/* #include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    
    pid_t pid;
    // fork a child process 
    pid = fork ();
    if (pid < 0) { // error occurred 
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { // child process 
        sleep(10);
        printf("aun no muero csmr");
        
    }
    else { //parent process 
        printf("soy el padre y voy a morir me vale un mrda mi hijo\n");
    }
    return 0;
} */