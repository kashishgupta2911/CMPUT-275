#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *const GREEN = "\x1b[32m";
const char *const YELLOW = "\x1b[33m";
const char *const WHITE = "\x1b[0m";
const char *current = WHITE;

void setColour(const char *colour)
{
    if (current == colour)
        return;
    printf("%s", colour);
    current = colour;
}

void printResult(char *correct_word, char *input_word, int correct_len)
{
    for (int i = 0; i < correct_len; i++)
    {
        if (correct_word[i] == input_word[i])
        {
            setColour(GREEN); // green for correct characters
            printf("%c", input_word[i]);
        }
        //correct word, but in the wrong position
        else if (strchr(correct_word, input_word[i]) && strchr(input_word, input_word[i]) == &input_word[i])
        {
            setColour(YELLOW);
            printf("%c", input_word[i]);
        }
        else
        { // Incorrect word remains as it is
            setColour(WHITE);
            printf("%c", input_word[i]);
        }
    }
    printf("\n");
    setColour(WHITE); //reset the color to white so that next line does not turn to that color
}

int main(int argc, char *argv[])
{ 
    //checks if the correct number of cml arg is provided
    if (argc != 2)
    {
        printf("Invalid number of command line arguments\n");
        return 1;
    }
    //takes correct word from the cml arg
    char *correct_word = argv[1];
    int correct_len = strlen(correct_word);

    //6 max tries
    for (int counter = 0; counter < 6; ++counter)
    {
        char input_word[13]; // Limit input to 12 characters
        printf("Enter guess: ");
        scanf("%12s", input_word);

        if (strcmp(input_word, "q") == 0)
            break;

        int input_len = strlen(input_word);

        //if the guessed word len matches the correct word len
        if (input_len != correct_len)
        {
            printf("Invalid guess, guess length must match word length\n");
            continue; // Restart the loop for a new guess
        }

        printResult(correct_word, input_word, correct_len);

        if (strcmp(input_word, correct_word) == 0)
        {
            printf("Finished in %d guesses\n", counter + 1);
            break;
        }
        else if (counter == 5)
            printf("Failed to guess the word: %s\n", correct_word);
    }

    return 0;
}
