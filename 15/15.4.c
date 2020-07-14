#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <stdbool.h>

int run(const char *command)
{
    int pid;
    switch(pid = fork())
    {
    case -1:"Fail"
        ;
        puts("failed to fork");
        exit(1);
        break;
    case 0:"Slave"
        ;
        const char *args[] = {command, NULL};
        execvp(command, args);
        puts("!!!!!!!!!shalll not happen");
        break;
    default:"Master"
        ;
        int exitCode;
        waitpid(pid, &exitCode, 0);
        return exitCode;
    }
}

int main(int argc, const char **args){
    if(argc<=4)
    {
        puts("using fallback args");
        const char ** newArgs = calloc(sizeof(char*), 5);
        newArgs[0] = args[0];

        if(argc < 2)newArgs[1] = "ls";
        if(argc < 3)newArgs[2] = "grep";
        if(argc < 4)newArgs[3] = "15.4.txt";

        args = newArgs;
        argc=4;
    }

    const char *cmd1 = args[1], *cmd2=args[2], *fName = args[3];

    int exit1 = run(cmd1), exit2 = run(cmd2);

    printf("Exit codes: %d, %d\n", exit1, exit2);

    if(exit1!=0) {
        puts("Bad exit code of first program");
    }

    FILE *file = fopen(fName, "w");
    if(!file)puts("failed to open for write"), exit(1);

    if(exit1 == 0){
        fwrite(cmd1, sizeof(char), strlen(cmd1), file);
    }

    fclose(file);

    return exit1;
}
