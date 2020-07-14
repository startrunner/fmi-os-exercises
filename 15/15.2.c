#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <stdbool.h>

int main(int argc, const char **args){
    const char *fileName;

    if(argc!=2){
        puts("using fallback file name");
        fileName = "15.2.c";
    }
    else{
        fileName = args[1];
    }

    int pid;
    switch(pid = fork())
    {
        case -1:"Error"
        ;
        puts("failed to fork");
        exit(1);
        break;
        case 0:"Slave"
        ;
        const char *args[] = {"grep", "int", fileName, NULL};
        execvp("grep", args);
        puts("done");
        break;
        default: "Master"
        ;
        int exitCode;
        waitpid(pid, &exitCode, 0);
        printf("Exit code: %d\n", WEXITSTATUS(exitCode));
        break;
    }


    return EXIT_SUCCESS;
}
