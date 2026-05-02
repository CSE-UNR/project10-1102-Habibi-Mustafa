//Autor Mustafa Habibi
//Project 10

#include <stdio.h>
#include <stdbool.h>

#define SIZE 5
#define MAX_GUESSES 6
#define MAX_LEN 100

void loadWord(char word[]);
int length(char str[]);
void makeLower(char str[]);
bool isLetter(char c);
bool validGuess(char guess[]);
bool sameWord(char guess[], char word[]);
bool letterWrongPlace(char guess[], char word[], int index);
void makeResult(char guess[], char word[], char shown[], char arrows[]);
void copyString(char to[], char from[]);
void showGuesses(char guesses[][MAX_LEN], char arrows[][MAX_LEN], int count);

int main(void) {
    char word[MAX_LEN];
    char guess[MAX_LEN];
    char shown[MAX_LEN];
    char arrows[MAX_LEN];

    char guesses[MAX_GUESSES][MAX_LEN];
    char allArrows[MAX_GUESSES][MAX_LEN];

    int guessCount = 0;
    bool won = false;

    loadWord(word);

    while (guessCount < MAX_GUESSES && won == false) {
        if (guessCount == MAX_GUESSES - 1) {
            printf("\nFINAL GUESS : ");
        } else {
            printf("\nGUESS %d! Enter your guess: ", guessCount + 1);
        }

        scanf("%s", guess);
        makeLower(guess);

        while (validGuess(guess) == false) {
            printf("Your guess must be 5 letters long.\n");
            printf("Please try again: ");
            scanf("%s", guess);
            makeLower(guess);
        }

        makeResult(guess, word, shown, arrows);

        copyString(guesses[guessCount], shown);
        copyString(allArrows[guessCount], arrows);

        guessCount++;

        printf("====================================\n");
        showGuesses(guesses, allArrows, guessCount);

        if (sameWord(guess, word)) {
            won = true;
        }
    }

    if (won) {
        printf("\nYou won!\n");
    } else {
        printf("\nYou lost, better luck next time!\n");
    }

    return 0;
}

void loadWord(char word[]) {
    FILE *file = fopen("mystery.txt", "r");

    if (file == NULL) {
        word[0] = '\0';
        return;
    }

    fscanf(file, "%s", word);
    fclose(file);

    makeLower(word);
}

int length(char str[]) {
    int count = 0;

    while (str[count] != '\0') {
        count++;
    }

    return count;
}

void makeLower(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool validGuess(char guess[]) {
    if (length(guess) != SIZE) {
        return false;
    }

    for (int i = 0; i < SIZE; i++) {
        if (!isLetter(guess[i])) {
            return false;
        }
    }

    return true;
}

bool sameWord(char guess[], char word[]) {
    for (int i = 0; i < SIZE; i++) {
        if (guess[i] != word[i]) {
            return false;
        }
    }

    return true;
}

bool letterWrongPlace(char guess[], char word[], int index) {
    for (int i = 0; i < SIZE; i++) {
        if (guess[index] == word[i] && index != i && guess[i] != word[i]) {
            return true;
        }
    }

    return false;
}

void makeResult(char guess[], char word[], char shown[], char arrows[]) {
    for (int i = 0; i < SIZE; i++) {
        shown[i] = guess[i];
        arrows[i] = ' ';
    }

    shown[SIZE] = '\0';
    arrows[SIZE] = '\0';

    for (int i = 0; i < SIZE; i++) {
        if (guess[i] == word[i]) {
            shown[i] = guess[i] - 32;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (guess[i] != word[i] && letterWrongPlace(guess, word, i)) {
            arrows[i] = '^';
        }
    }
}

void copyString(char to[], char from[]) {
    int i = 0;

    while (from[i] != '\0') {
        to[i] = from[i];
        i++;
    }

    to[i] = '\0';
}

void showGuesses(char guesses[][MAX_LEN], char arrows[][MAX_LEN], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n\n", arrows[i]);
    }
}
