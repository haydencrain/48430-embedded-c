/*******************************************************************************
List of header files - do NOT use any other header files. Note that string.h is
included in case you want to use any of the functions in there. However the task
can be achieved with stdio.h and stdlib.h only.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*******************************************************************************
List preprocessing directives - you may define your own.
*******************************************************************************/
/*number that will be used to exit the program*/
#define EXIT 5
/* maximum length of the input string that is needed to check if int or not */
#define MAX_INPUT_LENGTH 100


/*******************************************************************************
List structs - you may define struct date and struct student only. Each struct
definition should have only the fields mentioned in the assignment description.
*******************************************************************************/



/*******************************************************************************
Function prototypes - do NOT change the given prototypes. However you
may define your own functions if required.
*******************************************************************************/
void printMenu(void);
int getIntPrompt();
void printLinkedList(/* pass only ONE parameter here */);
int delHead(/* pass only ONE parameter here */);
int delVowels();
int isEmpty(/* pass only ONE parameter here */);


/*******************************************************************************
Main
*******************************************************************************/
int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		printf("Parse a sentence");
		return 1;
	}

	int choice;	/* used to decide which task will occur */

	do /* post-while loop which will loop until EXIT is entered by the user */
	{
		choice = getIntPrompt(); 
		/* ensures that the choice is only int */

		switch (choice) /*chooses an option based on what number was chosen*/
		{
			case 1: printLinkedList();
					break;  /* Add a Student to the List */

			case 2: delHead();
					break; 	/* Remove the last Student */

			case 3: delVowels();
					break;	/* Print the Students in the List */
				
			case 4: if(isEmpty())
						printf("Not empty.\n");
					else
						printf("Empty list.\n");
					break;	/* Save the Students to a database */

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
	"Enter your choice>");
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
int getIntPrompt()
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

/*******************************************************************************
printLinkedList
This function prints the linked list.
inputs:
- 
outputs:
- 
*******************************************************************************/
void printLinkedList()
{

}

/*******************************************************************************
delHead
This function will remove the first character of the linked list.
inputs:
- 
outputs:
- int num
*******************************************************************************/
int delHead()
{
	return 0;
}

/*******************************************************************************
delHead
This function will remove the vowels of the linked list.
inputs:
- 
outputs:
- int num
*******************************************************************************/
int delVowels()
{
	return 0;
}

/*******************************************************************************
isEmpty
This function will check whether the linked list is empty or not
- 
outputs:
- int num
*******************************************************************************/
int isEmpty()
{
	return 0;
}
