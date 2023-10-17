#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"


#define BUFFER_SIZE 256


char *priorityString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


int getPriority(const char* letter) {
  // TODO: This isn't checking for faults ... pretty bad
  return strcspn(priorityString, letter) + 1;
}

void firstpart(FILE *file) {
  int priority_count = 0;

  // Read line by line with a buffer size defined at the top
  char line[BUFFER_SIZE];
  while (fgets(line, BUFFER_SIZE, file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    size_t rugsack_size = strlen(line);
    size_t compartment_size = rugsack_size / 2;

    // Setup the arrays with the right size
    char compartment_a[compartment_size + 1];
    char compartment_b[compartment_size + 1];

    // Fill the compartment array with the write strings
    strncpy(compartment_a, line, compartment_size);
    strncpy(compartment_b, line + compartment_size, compartment_size);
    compartment_a[compartment_size] = '\0';
    compartment_b[compartment_size] = '\0';

    // Find the character in common and calculate the priority
    char pri_letter[2] = {'\0'};
    pri_letter[0] = *strpbrk(compartment_a, compartment_b);
    int letter_location = strcspn(priorityString, pri_letter) + 1;

    priority_count += letter_location;
  }

  printf("Total priority: %d\n", priority_count);
}

void secondpart(FILE *file)
{
  int priority_count = 0;
  int index = 0;
  char letters[100] = {'\0'};
  char rugsack1[100] = {'\0'};;

  // Read line by line with a buffer size defined at the top
  char line[BUFFER_SIZE];
  while (fgets(line, BUFFER_SIZE, file) != NULL) {
    if (index == 2)
    {
      // This is the third rugsack
      char *pch = strpbrk(letters, line);
      char temp_letter[2] = {*pch, '\0'};

      int priority = getPriority(temp_letter);
      priority_count += priority;

      memset(letters, 0, sizeof(letters));
      memset(rugsack1, 0, sizeof(rugsack1));
      index = 0;
    }
    else if (index == 1)
    {
      // This is the second rugsack
      char *pch = strpbrk(rugsack1, line);
      while (pch != NULL)
      {
        char temp_letter[2] = {*pch, '\0'};
        if (strpbrk(letters, temp_letter) == NULL) {
          letters[strlen(letters)] = *pch;
        }
        pch = strpbrk(pch + 1, line);
      }
      index++;
    }
    else
    {
      // This is the first rugsack
      strncpy(rugsack1, line, strlen(line));
      index++;
    }
  }

  printf("Total priority: %d\n", priority_count);
}

int main(int argc, char **argv) {
  // Check if there is enough arguments given in
  if (argc < 2) {
    printf("[USAGE]: %s <input_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Open file in read-mode
  char *filepath = argv[1];
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Error while opening file %s, %s\n", filepath, strerror(errno));
    return EXIT_FAILURE;
  }

  //firstpart(file);
  secondpart(file);

  fclose(file);
  return 0;
}
