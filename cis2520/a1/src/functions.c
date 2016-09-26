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
          swaparoni((c+x), (c+i));
       }
   }
}

int ackermanns(int x, int y)
{
  if (x<0 || y<0)
  {
    printf("-1\n");
    return -1;
  }
  else if(x == 0)
  {
    y = y + 1;
    printf("A(%d, %d)\n", x, y);

    return y + 1;
  }
  else if(y == 0)
  {
    x = x - 1;
    ackermanns(x, 1);
  }
  else if(x>0 && y>0)
  {
    // x = x - 1;
    y = y - 1;
    // ackermanns(x, y - 1);
    // ackermanns(x - 1, y);
    ackermanns(x - 1, ackermanns(x, y));
  }

  // printf("A(%d, %d)\n", x, y);
}

float newtonIterative(float x)
{
  float answer = 1;
  while (fabs((answer * answer) / x - 1.0) >= 0.0000)
  {
    answer = ((x/answer) + answer)/2;
  }
  return answer;
}

float newtonRecursive(float x)
{
  float recursiveAnswer = 1;

  if (fabs(recursiveAnswer * recursiveAnswer)/ x - 1.0 >= 0.0000)
  {
    recursiveAnswer
  }
}

