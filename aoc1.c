#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void insertIntoArray(int *list, const int value, const int index)
{
	size_t arraySize = 3;
	for (int i = arraySize - 1; i >= index; i--) {
		if (i + 1 >= arraySize)
			continue;

		list[i + 1] = list[i];
	}

	list[index] = value;
}

void checkForTopThree(int *list, const int currentCal)
{
	for (int i = 0; i < 3; i++) {
		if (list[i] < currentCal)
		{
			insertIntoArray(list, currentCal, i);
			return;
		}
	}
}

int main(int argc, char **argv)
{
	// Check for input file in the arguments
	if (argc < 2)
	{
		printf("Usage: %s [input file]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Open the file
	char *filename = argv[1];
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Could not open %s, %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Variables
	// int highestCal = 0;
	int currentElfCal = 0;
	int topThreeCal[3] = {0, 0, 0};
	int totalCal = 0;

	// Go through each line
	char line[256];
	while (fgets(line, sizeof(line), file) != NULL)
	{
		// Detect end of elf
		if (strcmp(line, "\n") == 0)
		{
			checkForTopThree(topThreeCal, currentElfCal);
			currentElfCal = 0;
			continue;
		}

		int cal = atoi(line);
		if (cal == 0)
		{
			printf("Cannot convert '%s' to an integer\n", line);
			fclose(file);
			exit(EXIT_FAILURE);
		}

		currentElfCal += cal;
	}

	printf("Top 3 Elves:\n[1]: %d\n[2]: %d\n[3]: %d\n", topThreeCal[0], topThreeCal[1], topThreeCal[2]);
	for (int i = 0; i < 3; i++)
	{
		totalCal += topThreeCal[i];
	}
	printf("Total calories of top 3: %d\n", totalCal);

	// Cleaning up
	fclose(file);
	return 0;
}
