#include <stdio.h>
#include <stdlib.h>

void getChoice(int *choice);

int main(void) 
{
    int choice;
    getChoice(&choice);
    return 0;
}

void getChoice(int *choice)
{
    int reads;
    char c;
    printf("Please Enter an integer >");
    while(((reads = scanf("%d%c", choice, &c)) != 2 && reads != EOF) || c != '\n')
    {
        printf("Please enter an integer only : ");
        /* read at least one character until the next newline */
        do {
            reads = scanf("%c", &c);
        }while(reads != EOF && c != '\n');
    }
}

