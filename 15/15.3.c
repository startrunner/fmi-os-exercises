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

int main(int argc, char const **args)
{
    if(argc==1)
    {
        puts("using fallback args");
        const char ** newArgs = calloc(sizeof(char*), 32);
        newArgs[0] = args[0];
        newArgs[1] = "grep";
        newArgs[2] = "ls";
        newArgs[3] = "cp";

        args = newArgs;

        argc=0;
        while(args[argc])argc++;
    }

    int successCount = 0, failCount = 0;
    for(int i=1;i<argc;i++){
        int exitCode = run(args[i]);
        successCount += (exitCode == 0);
        failCount += (exitCode !=0);
        printf("exit code of %s: %d\n", args[i], exitCode);
    }

    printf("Success count: %d\n", successCount);
    printf("Fail count: %d\n", failCount);
}
