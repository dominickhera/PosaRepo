#include "carbon.h"

//initiates the carbon function, declares the string to be carbon, calls the switcharoni function
void carbonInit ()
{
  char str[] = "Carbon";
  int string = strlen(str);
  
  switcharoni(str, 0, string-1);
}

//uses the traditional swap method between x and y using temp as a temporary varible to swap whatever is in the two variables
void swaparoni(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

//if x equals y then it just prints the string, otherwise it runs a for loop that swaps the characters in the string in increasingly different locations within the string
// then recursively calling the function over again, and then swapping the characters again until it gets through all the possible answers.
void switcharoni(char *c, int x, int y)
{
   int i;
   if (x == y)
     printf("%s\n", c);
   else
   {
       for (i = x; i <= y; i++)
       {
          swaparoni((c+x), (c+i));
          switcharoni(c, x+1, y);
          swaparoni((c+x), (c+i));
       }
   }
}