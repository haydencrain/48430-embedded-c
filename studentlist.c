/*******************************************************************************
48430 Embedded C - Assignment 2
Name: Hayden Crain
Student ID: 98105873
Date of submission: 
A brief statement on what you could achieve (less than 50 words):
- adding a student to the list.
- if there are 5 students already, no more students are to be added
- removing a student off the list.
- printing the students, showing all of their information.
- saving the students to a database text file.
- loading the students from a database text file.
- accounted for careless and hostile entries.

A brief statement on what you could NOT achieve (less than 50 words):


NOTE:: My code has been formatted to fit the 80 limit using a tab width of 4.


*******************************************************************************/

/*******************************************************************************
List of header files - do NOT use any other header files. Note that stdlib and
cstring are included in case you want to use any of the functions in there.
However the task can be achieved with stdio only.
*******************************************************************************/
#include <stdio.h> /* printf, scanf, use of FILE functions etc. */
#include <stdlib.h> 
#include <string.h>

/*******************************************************************************
List preprocessing directives - you may define your own.
*******************************************************************************/
/* Maximum number of students in the class */
#define MAX_CLASS_SIZE 5
/* Minimum number of students in the class */
#define MIN_CLASS_SIZE 0
/* Maximum length of the string - student name. Note that all strings in C are
NULL terminated i.e. '\0' at the end of the string. Hence the length of the
actual name can be 10 characters at most*/
#define MAX_NAME_SIZE 11
/*number that will be used to exit the program*/
#define EXIT 6 
/* Static file name of the text file where student list is stored */
#define DB_FILE_NAME "database"
/* maximum number of characters that will appear in the file per line */
#define MAX_LINE_LENGTH 33
/* maximum length of the input string that is needed to check if int or not */
#define MAX_INPUT_LENGTH 100
/* minimum number of days in a month */
#define MIN_DAY 1
/* maximum number of days in a month */
#define MAX_DAY 31
/* minimum number of months in a year */
#define MIN_MONTH 1
/* maximum number of months in a year */
#define MAX_MONTH 12
/* minimum year of birth that can be entered */
#define MIN_YEAR 1800
/* maximum year of birth that can be entered */
#define MAX_YEAR 2016
/* minimum GPA that can be entered */
#define MIN_GPA 0.0
/* maximum GPA that can be entered */
#define MAX_GPA 4.0
/* Maximum length of the string - type. (when entering the user's birthday,
birthmonth or birthyear) */
#define MAX_TYPE_LENGTH 5
/* the following are used for when deciding which prompt will be used when
getting an int from the user */
#define TYPE_MENU "menu"
#define TYPE_DAY "day"
#define TYPE_MONTH "month"
#define TYPE_YEAR "year"


/*******************************************************************************
List structs - you may define struct date and struct student only. Each struct
definition should have only the fields mentioned in the assignment description.
*******************************************************************************/
typedef struct
{
	int day;	/* day from 1-31 */
	int month;	/* month from 1-12 */
	int year;	/* year from 1800-2016 */
}date;

typedef struct
{
	char name[MAX_NAME_SIZE]; /* name of the student */
	date birthday;		  	  /* student's birthday */
	float gpa;				  /* GPA of the student between 0.0-4.0 */
}student;


/*******************************************************************************
Function prototypes - do NOT change the given prototypes. However you
may define your own functions if required.
*******************************************************************************/
/* ADD AND DELETE STUDENTS */
int addStudent(student studentlist[], int *no_students);
int deleteStudent(int *no_students); 

/* GETTERS */
int getIntPrompt(char type[MAX_TYPE_LENGTH]);
float getFloatPrompt();
int getBirthDay();
int getBirthMonth();
int getBirthYear();
float getGPA();

/* PRINT FUNCTIONS */
void printMenu(void);  
int printStudents(const student studentlist[], int no_students);
void printColumnTitles(void);

/* READ AND WRITE FUNCTIONS */
void saveStudents(const student studentlist[], int no_students);
int readStudents(student studentlist[], int *no_students); 

/*******************************************************************************
Main
*******************************************************************************/
int main(void)
{
	student studentlist[MAX_CLASS_SIZE]; /* list of students */

	int no_students = 0, /* initially, the number of students is 0 */
		choice;			 /* used to decide which task will occur */

	do /* post-while loop which will loop until EXIT is entered by the user */
	{
		choice = getIntPrompt(TYPE_MENU); 
		/* ensures that the choice is only int */

		switch (choice) /*chooses an option based on what number was chosen*/
		{
			case 1: addStudent(studentlist, &no_students);
					break;  /* Add a Student to the List */

			case 2: deleteStudent(&no_students);
					break; 	/* Remove the last Student */

			case 3: printStudents(studentlist, no_students);
					break;	/* Print the Students in the List */
				
			case 4: saveStudents(studentlist, no_students);
					break;	/* Save the Students to a database */

			case 5: readStudents(studentlist, &no_students);
					break;	/* load the Students from the database */

			case EXIT: break; 	/* number used to exit the program */
			
			default: printf("Invalid choice.\n"); 
			/* other numbers are not used */
		}

	} while(choice != EXIT); /* program will exit */

	return 0;
} 

/*******************************************************************************
addStudent
This function will ask the user for inputs to be added to a student record, and
the student will be added to the list, which also incrememnt the number of
students.
inputs:
- studentlist, *no_students
outputs:
- int: 0 if successul, 1 if class is full
*******************************************************************************/
int addStudent(student studentlist[], int *no_students)
{
	student student_temp; /* make a new temporary student */

	if (*no_students == MAX_CLASS_SIZE) /*if there are no more spots in class*/
	{
		printf("Class is full\n"); 
		return 1; /* return 1 if unsuccessful */
	}
	
	/* GET STUDENT'S NAME */
	char input_string[MAX_INPUT_LENGTH]; /* used to store the string input */
	printf("Enter name>"); /* ask for student's name */
	fgets(input_string, sizeof(input_string), stdin);
	input_string[strcspn(input_string, "\n")] = 0; /* remove any newlines */
	strncpy(student_temp.name, input_string, (MAX_NAME_SIZE));
	student_temp.name[MAX_NAME_SIZE-1] = '\0'; /* add null character to end */

	student_temp.birthday.day = getBirthDay(); /* get student birthday */
	student_temp.birthday.month = getBirthMonth(); /* get student birthmonth*/
	student_temp.birthday.year = getBirthYear(); /* get student birthyear */
	student_temp.gpa = getGPA(); /* get student gpa */

	studentlist[*no_students] = student_temp; /* append student to array */

	++ *no_students;	  /* increment the number of students */

	return 0; /* return 0 if successful */
}

/*******************************************************************************
deleteStudent
This function removes the last Student in the list by decrementing the number 
of students. The Student is "deleted" (it is still there but hidden from the 
counter).
inputs:
- *no_students
outputs:
- int: 0 if successul, 1 if there aren't any students to delete
*******************************************************************************/
int deleteStudent(int *no_students)
{
	if(*no_students == MIN_CLASS_SIZE) /* if there are no students */
	{
		printf("Class is empty\n");
		return 1; /* return 1 if error occurs (deletion unsuccessful) */
	}
	-- *no_students; /* decrements the number of students */
	return 0; /* return 0 if deletion successful */
}

/*******************************************************************************
getIntPrompt
This function handles the user prompt for entering the choice the birth day, 
month & year. 
The function will loop until only an integer has been scanned. It 
will then return the integer. This prevents hostile entries.
inputs:
- a string type of either "menu" "day", "month" or "year" so that the print 
statements can display the correct message.
outputs:
- int num
*******************************************************************************/
int getIntPrompt(char type[MAX_TYPE_LENGTH])
{
    char *ptr, input[MAX_INPUT_LENGTH]; /* used to store the input */
    int num; /* used to store the integer */

    if(strcmp(type, TYPE_MENU) == 0) /* if menu prompt is needed */
    	printMenu(); /* print the menu */
    else
    	printf("Enter birthday: %s>", type); /* prints the birthday menu */

    /* gets the whole line and stores it into a string */
    while (fgets(input, sizeof(input), stdin)) 
    {
    	input[strcspn(input, " ")] = 0; /* remove any spaces */
        num = strtol(input, &ptr, 10); /* convert into long int */
        if (ptr == input || *ptr != '\n')
        /* if the input contains anything else other than a number */
        {
        	/* prompt is printed again */
            if(strcmp(type, TYPE_MENU) == 0)
            {
            	printf("Invalid choice.\n"); /* error */
            	printMenu(); /* print initial menu */
            } else
            	printf("Invalid %s. Enter birthday: %s>", type, type); 
        } else break;
    }

    return num; /* return the integer */
}

/*******************************************************************************
getFloatPrompt
This function handles the user prompt for entering the GPA of the student. 
The function will loop until only an double has been scanned. It 
will then return the float. This prevents hostile entries.
inputs:
- 
outputs:
- float gpa
*******************************************************************************/
float getFloatPrompt()
{
    char *ptr, input[MAX_INPUT_LENGTH]; /* used to store the input */
    float gpa; /* used to store the float value */

    printf("Enter GPA>"); /* prints the prompt */

    /* get the whole line and store it into a string */
    while (fgets(input, sizeof(input), stdin)) 
    {
        input[strcspn(input, " ")] = 0; /* remove any newlines */
        if(input[0] == '\n') /*if input is only a newline */
        {
        	gpa = 0.0; /* set the gpa to 0.0 and return it */
        	return gpa;
        }
        gpa = strtod(input, &ptr);
        if (ptr == input || *ptr != '\n') 
        {
            printf("Invalid GPA. "); /* error */
			printf("Enter GPA>"); /* prints the prompt again */
        } else break;
    }

    return gpa; /* return the gpa float */
}

/*******************************************************************************
getBirthDay
This function handles the user prompt for entering a correct birthday of the 
student. The function will loop until a correct birthday has been entered.

inputs:
- 
outputs:
- int birthday_num
*******************************************************************************/
int getBirthDay()
{
	int day; /* used to temporarily store the student's birth day */
	/* GET STUDENT'S DAY OF BIRTH */
	while((day = getIntPrompt(TYPE_DAY)) < MIN_DAY || 
		day > MAX_DAY) /* day must be inbetween 1-31 */
	{
		printf("Invalid day. "); /* error */
	}	
	return day; 
	/* return day only once it is deemed acceptable */
}

/*******************************************************************************
getBirthMonth
This function handles the user prompt for entering a correct birthmonth of the 
student. The function will loop until a correct birthday has been entered.

inputs:
- 
outputs:
- int birthday_num
*******************************************************************************/
int getBirthMonth()
{
	int month; /* used to temporarily store the student's birth month */
	/* GET STUDENT'S MONTH OF BIRTH */
	while((month = getIntPrompt(TYPE_MONTH)) < MIN_MONTH || 
		month > MAX_MONTH) /* month must be inbetween 1-12 */
	{
		printf("Invalid month. "); /* error */
	}
	return month;
	/* return month only once it is deemed acceptable */
}

/*******************************************************************************
getBirthYear
This function handles the user prompt for entering a correct birthyear of the 
student. The function will loop until a correct birthday has been entered.

inputs:
- 
outputs:
- int birthday_num
*******************************************************************************/
int getBirthYear()
{
	int year; /* used to temporarily store the student's birth year */
	/* GET STUDENT'S YEAR OF BIRTH */
	while((year = getIntPrompt(TYPE_YEAR)) < MIN_YEAR || 
		year > MAX_YEAR) /* year must be inbetween 1800 and 2016 */
	{
		printf("Invalid year. "); /* error */
	}	
	return year;
	/* return year only once it is deemed acceptable */
}

/*******************************************************************************
getGPA
This function handles the user prompt for entering the correct GPA of the 
student. The function will loop until a correct GPA has been entered.

inputs:
- 
outputs:
- float gpa
*******************************************************************************/
float getGPA()
{
	float gpa; /* used to temporarily store the student's gpa */
	/* GET STUDENT'S GPA */
	while((gpa = getFloatPrompt()) < MIN_GPA || gpa > MAX_GPA)
		/* gpa must be inbetween 0.0 and 4.0 */
	{
		printf("Invalid GPA. ");
	}
	return gpa;
	/* add gpa to student_temp only once it is deemed acceptable */
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
	"1. add student\n"
	"2. delete last student\n"
	"3. display student list\n"
	"4. save the student list to the database\n"
	"5. read the student list from the database\n"
	"6. exit the program\n"
	"Enter your choice>"); /* print initial menu */
}

/*******************************************************************************
printColumnTitles
This function will print the "Name, Birthday and GPA" Titles, along with the 
dashed lines that appear below.
inputs:
- none
outputs:
- none
*******************************************************************************/
void printColumnTitles(void)
{
	printf("%-10s %-10s %s\n", "Name", "Birthday", "GPA");
	printf("---------- ---------- ------\n"); /* print column titles */
}

/*******************************************************************************
printStudents
This function prints the Students in the list with all details (birthday and
GPA)
inputs:
- studentlist, no_students
outputs:
- int 0 or 1 whether the print is successful or not
*******************************************************************************/
int printStudents(const student studentlist[], int no_students)
{
	int i; /* used to locate current student (counting through array) */

	if(no_students == MIN_CLASS_SIZE) /* if there are no students */
	{
		printf("Class is empty\n");
		return 1; /* return 1 if error occurs (deletion unsuccessful) */
	}

	printColumnTitles(); /* prints the titles and -'s */
	
	/* for every student "i", print its details */
	for (i = 0; i < no_students; ++i)
	{
		printf(
			"%-10s %02d-%02d-%04d %.4f\n", 
			studentlist[i].name,
			studentlist[i].birthday.day,
			studentlist[i].birthday.month,
			studentlist[i].birthday.year,
			studentlist[i].gpa 
		); /* print the student */
	}
	return 0; /* print successful */
}

/*******************************************************************************
saveStudents
This function will save the students currently in the list to a file called
"database".
inputs:
- studentlist, no_students
outputs:
- none
*******************************************************************************/
void saveStudents(const student studentlist[], int no_students)
{
	int i = 0; /* used to count through each student */
	FILE *fptr = fopen(DB_FILE_NAME, "w"); /* open the database file */
	/* for every student "i", write its details onto the database */
	for (i = 0; i < no_students; ++i)
	{
		fprintf(fptr,
			"%s\t%d\t%d\t%d\t%.6f\n", 
			studentlist[i].name,
			studentlist[i].birthday.day,
			studentlist[i].birthday.month,
			studentlist[i].birthday.year,
			studentlist[i].gpa 
		); /* write the student onto the line */
	}

	fclose(fptr); /*close the database file */
}

/*******************************************************************************
readStudents
This function will read the students stored in the database and load them into
the current list.
inputs:
- studentlist, *no_students
outputs:
- 0 or 1, dependant on whether the file has been found
*******************************************************************************/
int readStudents(student studentlist[], int *no_students)
{
	int i = 0; /* used to keep track of how many students are in the file */
	char line[MAX_LINE_LENGTH];
	FILE *fptr = fopen(DB_FILE_NAME, "rt");
	
	if(fptr == NULL) /* if there is no file */
	{
		printf("Read error\n"); /* error */
		return 1; /* file could not be found */
	}
	/* for each line in the file, read information and store it in the 
	relevant variables */
	while(fgets(line, MAX_LINE_LENGTH, fptr) != NULL)
	{
		sscanf(line, 
			"%s\t%d\t%d\t%d\t%f\n", 
			studentlist[i].name,
			&studentlist[i].birthday.day,
			&studentlist[i].birthday.month,
			&studentlist[i].birthday.year,
			&studentlist[i].gpa
		); /* read the contents of each student */
		++i; /* increment the no. of students after every line */
	}

	*no_students = i; /* update the number of students */

	fclose(fptr); /* close the file */

	return 0; /* file was read successfully */
}
