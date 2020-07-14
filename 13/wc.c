#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

int main(int argc, const char **args){
    if(argc!=2){
        printf("Expected args: FILE. Given: %d\n", argc);
        exit(1);
    }

    const char *path = args[1];

    FILE *file = fopen(path, "r");
    if(!file){
        printf("Could not open file %s\n", path);
        exit(1);
    }

    const int BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];

    int lastChar = ' ';
    int wordCount = 0;

    for(int currentSize; currentSize = fread(buffer, sizeof(char), BUFFER_SIZE, file);){
        for(int i=0;i<currentSize;i++){
            if(isspace(lastChar) && !isspace(buffer[i])){
                wordCount++;
            }

            lastChar = buffer[i];
        }
    }

    printf("%d\n", wordCount);
}
//kur
