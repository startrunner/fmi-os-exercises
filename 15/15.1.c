#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <stdbool.h>

void write_hello(FILE *file)
{
    int pid;
    switch(pid = fork())
    {
    case -1: "Error"
        ;
        puts("Error: could not start process");
        exit(1);
        break;
    case 0: "Slave"
        ;
        //FILE *file = fopen("abc.txt", isAppend ? "a" : "w");
        if(!file)puts("failed to open for write"), exit(0);
        char buffer[10] = "hello\n";
        fwrite(buffer, sizeof(char), strlen(buffer), file);
        fclose(file);
        exit(0);
        break;
    default: "Master"
        ;
        int exitCode = 0;
        if(!waitpid(pid, &exitCode, 0)) puts("failed to wait"), exit(1);

        if(!WIFEXITED(exitCode) || WEXITSTATUS(exitCode)!=0)
        {
            puts("error in process");
            exit(1);
        }
    }
}

int main()
{
    FILE *file = fopen("abc.txt", "w");
    if(!file)puts("failed to open for write"), exit(1);
    write_hello(file);
    write_hello(file);
}
