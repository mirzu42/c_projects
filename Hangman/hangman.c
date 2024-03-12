#include <stdio.h>
#include <stdlib.h>
#include "../functions.h"
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAXWORDSIZE 130
#define FILENAME "wordlist.txt"
static char** readWordsFromFile(char *filename, int *numOfWords);
static char* storeWord(int choice);
static void gamelogic(char *word);

void hangman(){
    srand(time(NULL));
    printf("Welcome to hangman game!\nThis game can be played as a single player game or multiplayer game.\n");
    printf("1) Guess a computer generated word\n2) Enter a word and another player guesses the word\n");

    int choice, correctInput = 1;
    char word [MAXWORDSIZE];
    choice = read_integer();
    while (getchar() != '\n');

    while (correctInput !=0){
        switch (choice) {
            case 1:
                strcpy(word, storeWord(choice));
                correctInput = 0;
                break;
            case 2:
                strcpy(word, storeWord(choice));
                correctInput = 0;
                break;
        }


    }
    printf("%s\n", word);
    gamelogic(word);

}
static void gamelogic(char *word){
    char guess;
    int correctGuesses = 0;
    int incorrectGuesses = 0;
    int progresslen = strlen(word) * 2;
    char guessedCharacters[15] = "";
    int guessedCharactersIndex = 0;
    char progress[progresslen + 1];

    for (int i = 0; i < progresslen; i++) {
        if (i % 2 == 0){
            progress[i] = '_';
        }
        else {
            progress[i] = ' ';
        }

    }
    progress[progresslen] = '\0'; // Add the null terminator

    printf("%s\n", progress);
    printf("The rules are as follows:\n");
    printf("1. You have to guess the correct word.\n");
    printf("You need to guess which characters the word contains.\n");
    printf("2. You can guess characters incorrectly only five times and after that the game is over.\n");
    printf("If you guess all the characters of a word correctly you win. If you fail to guess all the characters within the guess limit you lose.\n\n");
    while (correctGuesses < strlen(word) && incorrectGuesses < 5){
        printf("%s\n", progress);
        printf("Characters you have already guessed: ");
        if (guessedCharacters[0] != '\0') {
            printf("%c", guessedCharacters[0]); // Print the first character without a leading comma
            for (int i = 1; i < strlen(guessedCharacters); i++) {
                printf(", %c", guessedCharacters[i]); // Print subsequent characters with a leading comma
            }
        }
        printf("\n");
        printf("Enter a character: ");
        while (1){
            if (scanf(" %c", &guess) != 1 || getchar()!='\n'){
                while (getchar()!='\n');
                printf("Invalid input! Please enter a single character only!\n");
            }
            else{
                break;
            }
        }
        guess = tolower(guess); // Ensures that uppercase/lowercase doesn't matter
        int included = 0;
        for (int i = 0;i < strlen(guessedCharacters);i++){ // See if the character has already been guessed.
            if (guessedCharacters[i] == guess){
                included = 1;
                break;
            }
        }
        if (included == 0){ // Add the character to the guessed characters list
            guessedCharacters[guessedCharactersIndex] = guess;
            guessedCharactersIndex++;
        }

        int correctGuess = 0;
        for (int j = 0;j<strlen(word);j++){
            if (tolower(word[j]) == guess){ // Ensures that uppercase/lowercase doesn't matter
                if (included == 0){
                    correctGuesses+=1;
                }
                correctGuess = 1;
                progress[j * 2] = guess;
            }

        }

        if (correctGuess != 1 && included==0){ // If the guess was incorrect and was not already guessed
            incorrectGuesses++;
        }
    }
    if (correctGuesses == strlen(word)){
        printf("You won! The word was %s\n", word);
    }
    else {
        printf("You lost! The correct word was %s", word);
    }



}

static char** readWordsFromFile(char *filename, int *numOfWords){
    char **words = NULL;
    int wordcount = 0;
    char word[MAXWORDSIZE];
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL){
        fprintf(stderr, "Unable to open file %s\n", filename);
        return NULL;
    }
    words = (char **) malloc(sizeof (char*));
    if (words == NULL){
        // Memory allocation failed, free previously allocated memory
        free(words);
        fclose(file);
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    while (!feof(file) && fscanf(file, "%s", word) == 1){
        words[wordcount] = (char *) malloc(strlen(word)+1);
        if (words[wordcount] == NULL) {
            // Memory allocation failed, free previously allocated memory
            for (int i = 0; i < wordcount; i++) {
                free(words[i]);
            }
            free(words);
            fclose(file);
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(1);
        }
        strcpy(words[wordcount], word);
        wordcount++;

        words = (char **) realloc(words, (wordcount + 1) * sizeof(char *));
    }

    fclose(file);
    *numOfWords = wordcount;

    return words;
}

static char* storeWord(int choice){
    char *word= NULL;
    char **words;
    int numOfWords;
    if (choice == 1){
        words = readWordsFromFile(FILENAME, &numOfWords);
        int randomNumber = rand() % numOfWords;
        word = malloc(strlen(words[randomNumber]) + 1);
        strcpy(word, words[randomNumber]);
        for (int i = 0;i<numOfWords;i++){
            free(words[i]);
        }
        free(words);
    }
    else {
        printf("Enter a word: ");
        word = malloc(MAXWORDSIZE);
        fgets(word, sizeof (word), stdin);
        clearEmptyLine(word);
    }
    return word;
}