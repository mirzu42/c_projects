//
// Created by miro on 12.3.2024.
//
#include <stdio.h>
#include <limits.h>
#include <string.h>
int read_integer(void){
    int selection = INT_MAX;
    do {
        if (scanf("%d", &selection) !=1){
            while (getchar()!='\n');
            printf("Invalid input, not a number!\n");
        }

    } while (selection==INT_MAX);
    return selection;
}
void clearEmptyLine(char *str){
    str[strcspn(str, "\n")] = '\0';
}
