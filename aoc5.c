#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>


#define BUFFER_LINE_SIZE 265
#define PART_TWO


struct Stacks_s {
    size_t count;
    char stacks[50][100];
} Stacks_default = { 0 };

typedef struct Stacks_s Stacks;


void add_to_stack(Stacks *stacks, const char character, const int stack_index)
{
    char *stack = stacks->stacks[stack_index];
    stack[strlen(stack)] = character;
}


void move_between_stacks(Stacks *stacks, const int from_index, const int to_index)
{
    // TODO: Should check that the given index is correct
    char *from_stack = stacks->stacks[from_index];
    char *to_stack = stacks->stacks[to_index];

    char cargo = from_stack[strlen(from_stack) - 1];
    to_stack[strlen(to_stack)] = cargo;

    from_stack[strlen(from_stack) - 1] = '\0';
}


void multimove_between_stacks(Stacks *stacks, const int amount, const int from_index, const int to_index)
{
    char *from_stack = stacks->stacks[from_index];
    char *to_stack = stacks->stacks[to_index];

    size_t startIndex = strlen(from_stack) - amount;
    strncpy(to_stack + strlen(to_stack), from_stack + startIndex, amount);

    memset(from_stack + startIndex, '\0', amount);
}


void firstPart(FILE *file)
{
    bool readingStack = true;
    char stack_lines[50][100];
    size_t stack_lines_size = 0;
    Stacks stacks;

    // Fill the stack lines with NULL-characters
    for (int i = 0; i < 50; i++) {
        memset(stack_lines[i], '\0', 100);
        memset(stacks.stacks[i], '\0', 100);
    }

    char line[BUFFER_LINE_SIZE];
    while (fgets(line, BUFFER_LINE_SIZE, file) != NULL)
    {
        if (readingStack) {
            if (strcmp(line, "\n") == 0)
            {
                // End of reading the stack
                // This is where we go through stack_lines
                char *last_stackline = stack_lines[stack_lines_size - 1];
                stacks.count = atoi(last_stackline + strlen(last_stackline) - 3); // NOTE: Don't know how reliable this method is

                for (int i = stack_lines_size - 2; i >= 0; i--) {
                    for (int j = 0; j < stacks.count; j++)
                    {
                        char cargo[2] = {stack_lines[i][1 + j * 4], '\0'};
                        if (strcmp(cargo, " ") == 0 || (int)cargo[0] == 0)
                            continue;

                        printf("Cargo Letter: %s\n", cargo);
                        add_to_stack(&stacks, cargo[0], j);
                    }
                }
                printf("Stacks count: %zu\n", stacks.count);

                readingStack = false;
                continue;
            }

            // Add the line to stack_lines and remove newline
            strcpy(stack_lines[stack_lines_size], line);
            size_t newline_location = strcspn(stack_lines[stack_lines_size], "\n");
            stack_lines[stack_lines_size][newline_location] = '\0';
            stack_lines_size++;
            continue;
        }

        // Now it is time to go through all the move lines
        int amount = 0;
        int stack_from = 0;
        int stack_to = 0;

        // TODO: Feel like you could have done this part prettier
        char *pch = strtok(line, " ");
        pch = strtok(NULL, " ");
        amount = atoi(pch);
        pch = strtok(NULL, " ");
        pch = strtok(NULL, " ");
        stack_from = atoi(pch) - 1;
        pch = strtok(NULL, " ");
        pch = strtok(NULL, " ");
        stack_to = atoi(pch) - 1;

        printf("%d: %d -> %d\n", amount, stack_from, stack_to);

        #ifdef PART_ONE
        for (int i = 0; i < amount; i++) {
            move_between_stacks(&stacks, stack_from, stack_to);
        }
        #endif

        #ifdef PART_TWO
        multimove_between_stacks(&stacks, amount, stack_from, stack_to);
        #endif
    }

    for (int i = 0; i < stacks.count; i++) {
        printf("Stack %d: %s\n", i, stacks.stacks[i]);
    }

    // Get the top of each stack
    for (int i = 0; i < stacks.count; i++) {
        size_t lastCargo_index = strlen(stacks.stacks[i]) - 1;
        printf("%c", stacks.stacks[i][lastCargo_index]);
    }
    printf("\n");
}


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("[USAGE] %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filepath = argv[1];
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Failed to open file %s, %s", filepath, strerror(errno));
        return EXIT_FAILURE;
    }

    firstPart(file);

    fclose(file);
    return EXIT_SUCCESS;
}
