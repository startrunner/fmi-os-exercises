#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>

void dowrite(const char *fileName, const char *buffer, int bufferSize, int isAppend)
{
    //printf("\nwriting %d\n", isAppend);
    if(bufferSize == 0)return;

    FILE *file = fopen(fileName, isAppend ? "a" : "w");
    if(!file)puts("can't open for write"), exit(1);

    fwrite(buffer, sizeof(char), bufferSize, file);
    fclose(file);
}

int main(int argc, const char **args){
    const char *fileName;
    if(argc!=2){
        printf("Expected arguments: DEST Given: %d\n", argc);
        //exit(1);
        fileName = "f.txt";
    }
    else fileName = args[1];

    const int BUFFER_MAX = 100;
    char buffer[BUFFER_MAX];

    puts("Enter input and then do ctrl+d");

    //Read, replace with tabs
    {
        int bufferSize = 0;
        int writeCount = 0;
        for(int current; (current = fgetc(stdin))!=EOF; )
        {
            //printf("%d\n", current);
            char text[5];
            if(current == '\t'){
                strcpy(text, ">>>");
            }
            else{
                text[0] = (char)current;
                text[1] = '\0';
            }

            for(int i=0;text[i]!='\0';i++){
                buffer[bufferSize++] = text[i];
                if(bufferSize == BUFFER_MAX){
                    dowrite(fileName, buffer, bufferSize, (++writeCount) != 1);
                    bufferSize = 0;
                }
            }
        }

        dowrite(fileName, buffer, bufferSize, (++writeCount) != 1);
    }

    //Write to console
    {
        FILE *file = fopen("f.txt", "r");
        if(!file)puts("can't open for read"), exit(1);
        for(int bufferSize; bufferSize = fread(buffer, sizeof(char), BUFFER_MAX, file);){
            for(int i=0;i<bufferSize;i++)putc(buffer[i], stdout);
        }
    }

    puts("done");

    return EXIT_SUCCESS;
}
