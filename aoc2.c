#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum HandChoice
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

enum EndState
{
    LOST = 0,
    DRAW = 3,
    WON = 6
};

void getTokens(char *string, const char *delimiter, char *return_array)
{
    int index = 0;
    char *choices = strtok(string, delimiter);
    while (choices != NULL)
    {
        return_array[index] = choices[0];
        choices = strtok(NULL, delimiter);
        index++;
    }
}

int getOutcomeScore(const enum HandChoice opponent, const enum HandChoice choice)
{
    if (opponent == choice) return DRAW;

    if (opponent == ROCK && choice == SCISSORS) return LOST;
    if (opponent == ROCK && choice == PAPER)    return WON;

    if (opponent == PAPER && choice == ROCK)     return LOST;
    if (opponent == PAPER && choice == SCISSORS) return WON;

    if (opponent == SCISSORS && choice == PAPER) return LOST;
    if (opponent == SCISSORS && choice == ROCK)  return WON;
}

int main(int argc, char **argv)
{
    // Check that the input file has been given
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

    int totalScore = 0;

    // Read each line of the file
    char line[256];
    while (fgets(line, 256, file) != NULL)
    {
        // Find each character in the line
        char hands[2];
        getTokens(line, " ", hands);

        // Translate character to enum value
        enum HandChoice hand_opponent = SCISSORS;
        enum HandChoice hand_me = SCISSORS;
        enum EndState endState = WON;

        if (hands[0] == 'A')        hand_opponent = ROCK;
        else if (hands[0] == 'B')   hand_opponent = PAPER;

        // Figure out the endstate of the game
        if (hands[1] == 'X') endState = LOST;
        else if (hands[1] == 'Y') endState = DRAW;

        // Get the correct hand to fulfill that endstate
        if (endState == DRAW) hand_me = hand_opponent;
        else if (endState == LOST)
        {
            if (hand_opponent == ROCK) hand_me = SCISSORS;
            else if (hand_opponent == PAPER) hand_me = ROCK;
            else hand_me = PAPER;
        }
        else if (endState == WON)
        {
            if (hand_opponent == ROCK) hand_me = PAPER;
            else if (hand_opponent == PAPER) hand_me = SCISSORS;
            else hand_me = ROCK;
        }

        totalScore += (endState + hand_me);
    }

    printf("Total Score: %d\n", totalScore);

    // Cleanup
    fclose(file);
    exit(EXIT_SUCCESS);
}