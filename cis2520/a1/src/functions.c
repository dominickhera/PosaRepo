#include "functions.h"


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
          swaparoni((c+x), (c+i)); //backtrack
       }
   }
}

int ackermanns(int x, int y)
{
  if (x<0 || y<0)
  {
    printf("-1\n");
  }
  else if(x == 0)
  {
    y = y + 1;
  }
  else if(y == 0)
  {
    ackermanns(x-1, 1);
  }
  else if(x>0 && y>0)
  {
    ackermanns(x - 1, ackermanns(x, y - 1));
  }

  printf("A(%d, %d)\n", x, y);
}