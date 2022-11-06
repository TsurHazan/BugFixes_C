#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

int main_1()
{

	//wrong code:

	/* 1 #include < stdio.h < //wrong syntax
		2 int main() {
		3 int a = 4; b = 7; // ';' between
		4 float c;
		5 scanf("%f", c); // no &
		6 if (5 = c) // = is wrong you need ==
			7 print("%f", c);
		8 // no return in main
	}*/


	//correct code:
	
	//#include <stdio.h>
	//int main() {
	int a = 4, b = 7;
	float c;
	scanf("%f", &c);
	if (c == 5)
	{
		printf("%f", c);
	}
	return 0;
    //}
}


int main_2()
{
	int x=3, y=4,i; // add numbers
	int nums[6];
	int* arrPtr;

	// Section A - Print the variables
	puts("***** Section A *****\n"); 
	printf(" Base = %d\n", x);
	printf(" Height = %d\n", y);
	printf(" Area = %d\n", x * y);

	// Section B - Print the static array "nums".
	puts("***** Section B *****\n"); 

	for (i = 0; i < 6; i++)  //change while to for and created 'i' at start of main 
	{
		nums[i] = i * 2;
		printf(" nums[%d] = %d\n", i, nums[i]);
	}
	
	// Section C - Print allocated array.
	puts("***** Section C *****\n");
	arrPtr =(int*)malloc(sizeof(int) * 6); //added typecast and changed to size of 6
	if (arrPtr) {
		for (i = 0; i < 6; i++) { 
			arrPtr[i] = i * 3;
			printf(" array[%d] = %d\n", i, arrPtr[i]);
		}
		free(arrPtr); //need to free when finishing with memory
	}
	else {
		printf("Error Allocating Memory!\n");
		//Log error-getlasterror()
		exit(1);
	}
	return 0;
}


/* struct to collect counting info about english letters found
in a text file. */

typedef struct letter {
	char small;
	char big;
	int counter;
	struct letter* next; //added next 
	struct letter* prev; //added prev 
}letter;

//Function to free linked list
void freeList(letter* head) {
	letter* releaseItem;
	letter* runItem = head;
	while (runItem != NULL) {
		releaseItem = runItem;
		runItem = runItem->next;
		printf("\nchar small:%c  char big:%c  counter:%d\n", releaseItem->small, releaseItem->big, releaseItem->counter); //print struct before release for check
		free(releaseItem);
	}
}

int main_3()
{
	//Next two string represents all the english alphabets 
	//(small and capital)
	char smallAlpha[26] = "abcdefghijklmnopqrstuvwxyz";
	char bigAlpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int lettersCountArr[26] = { 0 }; //changed to 26
	char readChar; //deleted ch because there is no need

	FILE* f = fopen("myFile.txt", "r");
	if (!f) //added file check
	{
		//log error getlasterror()
		exit(1);
	}

	// Display the content of myFile.txt and count letters
	printf("the content of myFile.txt :\n");
	while ((readChar = fgetc(f)) != EOF) { //changed to EOF because fgetc can read it
		printf("%c", readChar);
		for (int i = 0; i <26; ++i) {
			if (readChar == smallAlpha[i] || readChar == bigAlpha[i])
			{
				lettersCountArr[i]++;
			}
		}
	}
	fclose(f);

	// Build Linked list from file content
	// Every node represent English letter (small and big).
	letter* HEAD = NULL;
	letter* TAIL = NULL;
	for (int j = 0; j < 26; ++j) 
	{
		letter* letterItem = (letter*)malloc(sizeof(letter));
		if (!letterItem) {
			puts("Error Allocating Memory!");
			//log error getlasterror() 
			exit(1);
		}

		//fixed Linked list
		letterItem->next = NULL;
		letterItem->small = 'a' + j;
		letterItem->big = 'A' + j;
		letterItem->counter = lettersCountArr[j];
		if (HEAD == NULL)
		{
			letterItem->prev = NULL;
			HEAD = letterItem;
			TAIL = letterItem;
		}
		else
		{
			TAIL->next = letterItem;
			letterItem->prev = TAIL;
			TAIL = letterItem;
		}
	}
	freeList(HEAD); //free list
	return 0;
}

//another solution with dictionary
/*int main()
{
	//Next two string represents all the english alphabets
	//(small and capital)

	char smallAlpha[26] = "abcdefghijklmnopqrstuvwxyz"; //changed to regular arr
	char bigAlpha[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //changed to regular arr
	char readChar, ch;
	FILE* f = fopen("myFile.txt", "r");
	if (!f)
	{
		//log error getlasterror()
		exit(1);
	}

	// Creating the linked list before reading file
	// Every node represent English letter (small and big).

	letter* HEAD = NULL;
	letter* TAIL = NULL;
	letter* runner;

	for (int j = 0; j < 26; ++j) { //changed loop to 26
		letter* letterItem = (letter*)malloc(sizeof(letter));
		if (!letterItem) {
			puts("Error Allocating Memory!");
			//log error getlasterror()
			exit(1);
		}

		letterItem->next = NULL;
		letterItem->small = 'a' + j;
		letterItem->big = 'A' + j;
		letterItem->counter =0;
		if (HEAD == NULL)
		{
			letterItem->prev = NULL;
			HEAD = letterItem;
			TAIL = letterItem;
		}
		else
		{
			TAIL->next = letterItem;
			letterItem->prev = TAIL;
			TAIL = letterItem;
		}

	}

	// Display the content of myFile.txt and count letters
	printf("the content of myFile.txt :\n");
	while ((readChar = fgetc(f)) != EOF) { //in fgetc you need to use EOF
		runner = HEAD;
		printf("%c", readChar);
			while (runner != NULL) //removed for loop and changed to dictionary
			{
				if (readChar == runner->small || readChar == runner->big)
				{
					runner->counter++;
				}
				runner = runner->next;
			}
	}

	freeList(HEAD);
	fclose(f);
	return 0;
} */