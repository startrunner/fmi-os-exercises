#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <math.h>
#include <string.h>

int mini(int x, int y){ return (y<x)?y:x; }

int main(int argc, const char **args){
    const char *source;
    const char *destination;
    if(argc!=3){
        source = "11.5.c";
        destination = "11.5.txt";
        puts("using fallback filenames");
    }
    else{
        source = args[1];
        destination = args[2];
    }

    const int BUFFER_MAX = 100;
    char buffer[BUFFER_MAX];

    FILE *fSource = fopen(source, "r");
    if(!fSource)puts("Can't open for read"), exit(1);
    FILE *fDestination = fopen(destination, "a");
    if(!fDestination)puts("Can't open for write"), exit(1);

    int column = 0;
    for(int bufferSize; bufferSize = fread(buffer, sizeof(char), BUFFER_MAX, fSource);){
        for(int i=0;i<bufferSize;i++){
            if(buffer[i]=='\n'){
                column = 0;
                puts("");
            }
            else {
                column++;
                if(column <=3 ){
                    fwrite(buffer + i, sizeof(char), 1, fDestination);
                    printf("%c", buffer[i]);
                }
            }
        }
    }

    puts("done");
}
