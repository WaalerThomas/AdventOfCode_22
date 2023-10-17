#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "errno.h"


#define BUFFER_LINE 256


typedef struct assigments {
    int max;
    int min;
} ElfAssig;


void ElfAssig_Copy(ElfAssig *dst, ElfAssig *src)
{
    dst->max = src->max;
    dst->min = src->min;
}


void strToElf(char *line, ElfAssig *elf1, ElfAssig *elf2)
{
    char elf1_str[50] = {'\0'};
    char elf2_str[50] = {'\0'};

    // Just going to get two tokens per line. So no loop
    char *pch = strtok(line, ",");
    strcpy(elf1_str, pch);
    pch = strtok(NULL, ",");
    strcpy(elf2_str, pch);
    elf2_str[strcspn(elf2_str, "\n")] = '\0';

    // Split each elves' assigment into max and min values
    pch = strtok(elf1_str, "-");
    elf1->min = atoi(pch);
    pch = strtok(NULL, "-");
    elf1->max = atoi(pch);

    pch = strtok(elf2_str, "-");
    elf2->min = atoi(pch);
    pch = strtok(NULL, "-");
    elf2->max = atoi(pch);
}


void firstPart(FILE *file)
{
    int pair_count = 0;

    // Read line for line
    char line[BUFFER_LINE];
    while (fgets(line, BUFFER_LINE, file) != NULL)
    {
        ElfAssig elf1, elf2;
        strToElf(line, &elf1, &elf2);

        // Change so that Elf1 will always be the biggest
        int elf1_size = elf1.max - elf1.min;
        int elf2_size = elf2.max - elf2.min;
        if (elf1_size > elf2_size)
        {
            ElfAssig temp;
            ElfAssig_Copy(&temp, &elf1);
            ElfAssig_Copy(&elf1, &elf2);
            ElfAssig_Copy(&elf2, &temp);
        }

        // Ignore lines where efl1 lays outside of elf2
        if (elf1.min < elf2.min || elf1.max > elf2.max)
            continue;

        pair_count++;

        printf("Elf1 - Max: %d Min: %d\n", elf1.max, elf1.min);
        printf("Elf2 - Max: %d Min: %d\n", elf2.max, elf2.min);
    }

    printf("Total pair-count: %d\n", pair_count);
}


void secondPart(FILE *file)
{
    int pair_count = 0;

    // Read line for line
    char line[BUFFER_LINE];
    while (fgets(line, BUFFER_LINE, file) != NULL)
    {
        ElfAssig elf1, elf2;
        strToElf(line, &elf1, &elf2);

        // Change so that elf1 will always be the biggest
        int elf1_size = elf1.max - elf1.min;
        int elf2_size = elf2.max - elf2.min;
        if (elf1_size > elf2_size)
        {
            ElfAssig temp;
            ElfAssig_Copy(&temp, &elf1);
            ElfAssig_Copy(&elf1, &elf2);
            ElfAssig_Copy(&elf2, &temp);
        }

        // Ignore lines where elf1.min is bigger than elf2.min, because then inside
        if (elf1.max < elf2.min || elf1.min > elf2.max)
            continue;

        pair_count++;

        printf("Elf1 - Max: %d Min: %d\n", elf1.max, elf1.min);
        printf("Elf2 - Max: %d Min: %d\n", elf2.max, elf2.min);
    }

    printf("Total pair-count: %d\n", pair_count);
}


int main(int argc, char **argv)
{
    // Check for the right amount of arguments
    if (argc < 2)
    {
        printf("[USAGE] %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Load the file
    char *filepath = argv[1];
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Failed to read file %s, %s\n", filepath, strerror(errno));
        return EXIT_FAILURE;
    }

    //firstPart(file);
    secondPart(file);

    fclose(file);
    return EXIT_SUCCESS;
}
