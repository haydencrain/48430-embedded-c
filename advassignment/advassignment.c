/*******************************************************************************
48430 Embedded C - Advanced Assignment
Name: Hayden Crain
Student ID: 98105873
Date of submission: 2/10/2016
A brief statement on what you could achieve (less than 50 words):
- Add the inputs into a linked list
- print the linked list
- delete the header appropriately
- delete the vowels and re link the list appropriately
- check if the list is empty

A brief statement on what you could NOT achieve (less than 50 words):


NOTE:: My code has been formatted to fit the 80 limit using a tab width of 4.

*******************************************************************************/

/*******************************************************************************
List of header files - do NOT use any other header files. Note that string.h is
included in case you want to use any of the functions in there. However the task
can be achieved with stdio.h and stdlib.h only.
*******************************************************************************/
#include <stdio.h> /* printf etc. */
#include <stdlib.h> /* free, malloc functions for linked list manipulation */
#include <string.h>

/*******************************************************************************
List preprocessing directives - you may define your own.
*******************************************************************************/
/*number that will be used to exit the program*/
#define EXIT 5
/* maximum length of the input string that is needed to check if int or not */
#define MAX_INPUT_LENGTH 100
/* vowels needed for checking if the character is a vowel */
#define VOWELS "AEIOUaeiou"

/*******************************************************************************
List structs - you may define struct date and struct student only. Each struct
definition should have only the fields mentioned in the assignment description.
*******************************************************************************/
typedef struct node{
	char c;
	struct node* next;
} node_t;

/*******************************************************************************
Function prototypes - do NOT change the given prototypes. However you
may define your own functions if required.
*******************************************************************************/
/* PRINTERS */
void printMenu(void);
void printLinkedList(node_t *head);

/* DELETERS */
int delHead(node_t **head);
int delVowels(node_t **head);

/* CHECKER */
int isEmpty(node_t **head);
int isVowel(char c);

/* SETTER */
void insertNode(node_t **head, char character);

/* GETTER */
int getIntPrompt(void);

/*******************************************************************************
Main
*******************************************************************************/
int main(int argc, char* argv[])
{
	node_t *head = NULL; 
	head = malloc(sizeof(node_t));

	int choice;	/* used to decide which task will occur */
	int i, j; /* used to count through the argv array */

	if(argc == 1) /* if there isnt any input */
	{
		printf("Parse a sentence");
		return 1; /* end the program */
	}
    
    for(i = 1; i < argc; i++) /* loop through argv[] */
    {
        for(j = 0; argv[i][j] != '\0'; j++) /* loop through each character */
        {
            char character = argv[i][j]; /* get the character */
            insertNode(&head, character); /* place into linked list */
        }
    }

    head = head->next; /* point the head to the first position */

    do /* post-while loop which will loop until EXIT is entered by the user */
	{
		choice = getIntPrompt(); 
		/* ensures that the choice is only int */

		switch (choice) /*chooses an option based on what number was chosen*/
		{
			case 1: printLinkedList(head);
					break;  /* print the linkedlist */

			case 2: if(!delHead(&head))
						printf("FAIL: Empty list.\n");
					break; 	/* delete the first character in the linked list */

			case 3: if(!delVowels(&head))
						printf("FAIL: Empty list.\n");
					break;	/* delete all vowels in the list */
				
			case 4: if(isEmpty(&head))
						printf("Empty list.\n");
					else
						printf("Not empty.\n");
					break;	/* check if the linkedlist is empty */

			case EXIT: break; 	/* number used to exit the program */
			
			default: printf("Invalid choice.\n"); 
			/* other numbers are not used */
		}

	} while(choice != EXIT); /* program will exit */

    return 0;
}

/*******************************************************************************
printMenu
This function prints the initial menu with all instructions on how to use this
program.
inputs:
- none
outputs:
- none
*******************************************************************************/
void printMenu(void)
{
	printf("\n\n"
	"1. print input arguments (no spaces)\n"
	"2. remove first character\n"
	"3. remove vowels\n"
	"4. is the linked list empty?\n"
	"5. exit program\n"
	"Enter your choice>"); /* print initial menu */
}

/*******************************************************************************
printLinkedList
This function prints the linked list.
inputs:
- 
outputs:
- 
*******************************************************************************/
void printLinkedList(node_t *head)
{
	if(head != NULL) /* if there is a node available */
	{
		printf("%c", head->c); /* print the character */
		printLinkedList(head->next); /* move on to the next character */
	} else
		printf("\n");
}

/*******************************************************************************
delHead
This function will remove the first character of the linked list.
inputs:
- 
outputs:
- int num
*******************************************************************************/
int delHead(node_t **head)
{
	if(isEmpty(head))	/* if the list is empty */	
		return 0;   /* return error */

	node_t *temp_head = *head; /* create temp pointer */
	*head = (*head)->next; /* tell head pointer to point to next pos */
	free(temp_head); /* release the original head memory */

	return 1;
}

/*******************************************************************************
delVowels
This function will remove the vowels of the linked list.
inputs:
- 
outputs:
- int num
*******************************************************************************/
int delVowels(node_t **head)
{
	if(isEmpty(head))	 /* if the list is empty */	
		return 0;  	/* return error */

	node_t *current_p, *previous_p; /* previous and current nodes */
	previous_p = NULL; /* the first spot is NULL */
	
	for(current_p = *head; current_p != NULL; current_p=current_p->next)
		/* loop through the list */
	{
		char character = current_p->c; /* get the current character */
		if(isVowel(character)) /* if the character is a vowel */
		{
			if(previous_p == NULL) /* if it is at the head node */
				*head = current_p->next; /* change the head pointer */
			else /* otherwise */
				previous_p->next = current_p->next; /* link over the current */
			free(current_p); /* remove the current */
		} else {
			/* if there is no vowel, move the previous pointer to the current 
			pointer location. (If there is a vowel, we don't to do this line,
			because otherwise the pointer will point to a garbage memory 
			location) */
			previous_p = current_p; 
		}
	}
	return 1;

}

/*******************************************************************************
isEmpty
This function will check whether the linked list is empty or not
- 
outputs:
- int num
*******************************************************************************/
int isEmpty(node_t **head)
{
	if(*head == NULL) /* if the list is empty */
		return 1; /* return true */
	return 0; /* return false */
}

/*******************************************************************************
isVowel
This function will check whether the character is a vowel
- 
outputs:
- int num
*******************************************************************************/
int isVowel(char c)
{
	char vowels[] = VOWELS; /* array of vowels */
	int i; /* counter to count through array of vowels */

	for(i=0; i < sizeof(vowels); i++)
	{
		if(c==vowels[i]) /* if the character is a vowel */
			return 1; /* return true */
	}

	return	0; /* return false */
}

/*******************************************************************************
insertNode
This function will get the char from a position in argv[] and place it into a 
linked list
- header node, char c
outputs:
- 
*******************************************************************************/
void insertNode(node_t **head, char character)
{
	node_t *current_node = *head; /* initialise a curent node pointer */

	while (current_node->next != NULL) /*if we are not at the end of the list*/
		current_node = current_node->next; /* go to next node */

	current_node->next = malloc(sizeof(node_t)); /* allocate a new node */
	current_node->next->c = character; /* set c to the character */
	current_node->next->next = NULL; /* set the next node to NULL */
}

/*******************************************************************************
getIntPrompt
This function handles the user prompt for entering the choice the birth day, 
month & year. 
The function will loop until only an integer has been scanned. It 
will then return the integer. This prevents hostile entries.
inputs:
- 
outputs:
- int num
*******************************************************************************/
int getIntPrompt(void)
{
    char *ptr, input[MAX_INPUT_LENGTH]; /* used to store the input */
    int num; /* used to store the integer */

	printMenu(); /* print the menu */

    /* gets the whole line and stores it into a string */
    while (fgets(input, sizeof(input), stdin)) 
    {
    	input[strcspn(input, " ")] = 0; /* remove any spaces */
        num = strtol(input, &ptr, 10); /* convert into long int */
        if (ptr == input || *ptr != '\n')
        /* if the input contains anything else other than a number */
        {
        	/* prompt is printed again */
        	printf("Invalid choice.\n"); /* error */
        	printMenu(); /* print initial menu */
        } else break;
    }

    return num; /* return the integer */
}
