#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define BUFFER_LINE_SIZE 256


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("[USAGE]: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filepath = argv[1];
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Failed to open file %s, %s\n", filepath, strerror(errno));
        return EXIT_FAILURE;
    }

    char line[BUFFER_LINE_SIZE];
    while (fgets(line, BUFFER_LINE_SIZE, file) != NULL)
    {
        printf("%s", line);

        // If the line starts with a $, then that line is a command
        char *chp = strtok(line, " ");
    }

    fclose(file);
    return EXIT_SUCCESS;
}
