//dominick hera//
//cis1500//
//29/10/15//
//assignment 2//
//scrambled words//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//initialising functions before defining them after the main function
int getFileName (char openFile[], int length);
int scrambleWord (char word[], int length);
int processText (char openFile[]);

int main(void)
{
    //declares variables needed
    char fileName[30];
    srand (time(NULL));
    FILE *ifp;

    //calls function to get name of file and opens it
    getFileName(fileName, 30);
    ifp = fopen(fileName, "r");
    
    //terminates the program if the file entered doesnt exist
    if (ifp == NULL) 
    {
        printf("Sorry, file does not exist\n");
        return 0;
    }
	
    //closes the file to prevent memory leaks
    fclose(ifp);
    
    //calls process function
    processText(fileName);

    printf("\n");
    return 0;
}

int getFileName (char openFile[], int length) 
{

    //asks for file name and stores it in a string
    printf("enter file name to scramble\n");
    scanf("%s", openFile);

    return 0;
}

int scrambleWord (char* word, int length) 
{
      
    int i;

    //main scramble function
    //goes back to main function if the the word is 3 or less letters
    if (length <= 3)
    {
        return 0;
    }
    else
    {
	//creates a second array to scramble
	//puts original array with characters through the smaller second array
        //replaces the original letters in the array with spaces
	char letters[length-2];  
        for (i = 1; i < (length - 1); i++)
        {
            letters[i-1] = word[i];
            word[i] = ' ';
        }

	//scrambles letters 5 times
	//declares a temporary variable, as well as a and b to put the letters through
	//if the randomised numbers between a and b are the same then b gets randomised again
        for (i = 0; i < 5; i++) 
        {
            char temp;
            int a,b;
            a = rand() % (length - 2); 	
            b = rand() % (length - 2);
            while (a == b) 
            {
                b = rand() % (length - 2);
            }
            temp = letters[a];
            letters[a] = letters[b];
            letters[b] = temp;
        }
	
	//puts the second array back into the original one starting at
	//the second letter in the word
        for (i = 1; i < (length - 1); i++) 
        {
            word[i] = letters[i-1];
        }
    }
    return 0;
}
int processText (char fileOpen[])
{
    char word[50];
    int length;
    int i;
    FILE *dfp = fopen(fileOpen, "r");

    //sends the text file until the end of the file is reached
    //finds length of each word, and uses that in a for loop
    //checks for punctuation, if there is punctuation, the length
    //is set to the current number and movess on to the next word
    while (fscanf(dfp, "%s", word) != EOF)
    {
        length = strlen(word);
        for (i = 0; i < length; i++)
        {
            if (ispunct(word[i])) 
            {
                length = i;
                break;
            }
        }

	//calls the scramble function from before  with the first 
	//word array and length of each word
	//prints the word in the string and then uses fgetc to grab
	//the next character in line whether it be a space or new line
        scrambleWord(word, length);
        printf("%s%c", word, fgetc(dfp));
    }
    //closes the textfile again to prevent memory leaks
    fclose(dfp);
    return 0;
}
