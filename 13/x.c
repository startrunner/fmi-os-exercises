#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

int main(int argc, char const **args)
{
    if (argc != 3)
    {
        printf("expected args: SOURCE, DEST. Given %d \n", argc);
        exit(1);
    }

    printf("copying %s -> %s\n", args[0], args[1]);

    const char *source = args[1], *dest = args[2];

    {
        const int BUFFER_SIZE = 100;
        char buffer[BUFFER_SIZE];

        int bytesCopied = 0;

        FILE *sourceFile = fopen(source, "r");
        if (!sourceFile)
            puts("failed to open source file"), exit(1);
        FILE *destFile = fopen(dest, "w");
        if (!destFile)
            puts("failed to open dest file"), exit(1);

        for (int size; size = fread(buffer, sizeof(char), BUFFER_SIZE, sourceFile);)
        {
            fwrite(buffer, sizeof(char), size, destFile);
            bytesCopied += size;

            printf("copied %d bytes\n", bytesCopied);
        }

        fclose(sourceFile);
        fclose(destFile);
    }

    return EXIT_SUCCESS;
}
