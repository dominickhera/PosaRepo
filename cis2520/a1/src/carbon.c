#include "carbon.h"


void carbonInit ()
{
  char str[] = "Carbon";
  int string = strlen(str);
  
  switcharoni(str, 0, string-1);
}

void swaparoni(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

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