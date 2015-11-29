#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int getFileName (char openFile[], int length);
int scrambleWord (char word[], int length);
int processText (char openFile[]);

int main(void)
{
    char fileName[30];
    srand (time(NULL));
    FILE *ifp;

    getFileName(fileName, 30);
    ifp = fopen(fileName, "r");

    if (ifp == NULL) 
    {
        printf("Sorry, file does not exist\n");
        return 0;
    }
    fclose(ifp);

    processText(fileName);

    printf("\n");
    return 0;
}

int getFileName (char openFile[], int length) 
{

    printf("enter file name to scramble\n");
    scanf("%s", openFile);

    return 0;
}

int scrambleWord (char* word, int length) 
{
    int i;
    if (length <= 3)
    {
        return 0;
    }
    else
    {
        char letters[length-2];  
        for (i = 1; i < (length - 1); i++)
        {
            letters[i-1] = word[i];
            word[i] = ' ';
        }
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
        scrambleWord(word, length);
        printf("%s%c", word, fgetc(dfp));
    }
    fclose(dfp);
    return 0;
}
