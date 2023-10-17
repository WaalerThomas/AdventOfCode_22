#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>


#define BUFFER_LINE_SIZE 256


void find_packet_start(char *stream, size_t *prosessed_count, const size_t window_size)
{
    while (true)
    {
        char window[window_size + 1];
        memset(window, '\0', window_size + 1);
        strncpy(window, stream + *prosessed_count, window_size);

        bool foundEqual = false;
        char compare_str[2] = {'\0'};
        for (int i = 0; i < window_size; i++)
        {
            compare_str[0] = window[i];
            char *window_ptr = window + 1 + i;
            size_t position_test = strcspn(window_ptr, compare_str);
            if (position_test == strlen(window_ptr))
                continue;

            *prosessed_count += (i + 1);
            foundEqual = true;
            break;
        }

        if (!foundEqual) {
            // YAY! None of them are equal
            *prosessed_count += window_size;
            return;
        }
    }
}

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

    size_t stream_size = 0;
    char *stream = malloc(stream_size);
    size_t char_prosessed_count = 0;

    char line[BUFFER_LINE_SIZE];
    while (fgets(line, BUFFER_LINE_SIZE, file) != NULL)
    {
        // Check the first four character.
        // If two characters are equal, move the "window" to the character one
        // after the first accorance of those two characters.
        // Repeat until the four characters are different.

        // Go through the while input file and save the text in an array before going
        // through the data.
        // NOTE: Would be faster if I didn't first save it to an array and instead
        //       just work on each batch.
        size_t line_len = strlen(line);
        if (line_len + strlen(stream) > stream_size)
        {
            stream_size = stream_size + (BUFFER_LINE_SIZE + 1) * sizeof(char);
            stream = realloc(stream, stream_size);
        }
        strncat(stream, line, line_len);

        #if 0
        #endif
    }

    find_packet_start(stream, &char_prosessed_count, 14);

    printf("Stream: %s\n", stream);
    printf("Last character: %c\n", stream[strlen(stream) - 2]);
    printf("Stream length: %zu\n", strlen(stream));
    printf("Stream size: %zu bytes\n", stream_size);

    printf("Char Processed Count: %zu\n", char_prosessed_count);

    free(stream);
    fclose(file);
    return EXIT_SUCCESS;
}
