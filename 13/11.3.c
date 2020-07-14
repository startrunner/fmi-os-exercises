#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

int main(){
    srand(time(NULL));

    char content[26];
    for(int i=0;i<25;i++){
        content[i] = 'a' + abs(rand())%26;
    }
    content[25] = '\0';

    printf("conent: %s\n", content);

    const char *fileName = "tmp.txt";

    //WRITE
    {
        FILE *file = fopen(fileName, "w");
        if(!file)puts("Could not open for write"), exit(1);
        fwrite(content, sizeof(char), 25, file);
        fclose(file);
    }

    //READ
    {
        const int BUFFER_SIZE = 10;
        char buffer[BUFFER_SIZE+1];

        FILE *file = fopen(fileName, "r");
        if(!file)puts("Can't open for read"), exit(1);

        for(int currentSize; currentSize = fread(buffer, sizeof(char), BUFFER_SIZE, file);){
            buffer[currentSize] = '\0';
            printf("returned: %d\n", currentSize);
            printf("read: %s\n", buffer);
        }
    }

    return EXIT_SUCCESS;
}
