#include "ackermann.h"

void ackermannInit()
{

int x, y;

printf("please enter first number\n");
scanf("%d", &x);
printf("please enter second number\n");
scanf("%d", &y);
printf("the answer is %d\n", ackermanns(x,y));


}


int ackermanns(int x, int y)
{
  if (x<0 || y<0)
  {
    printf("-1\n");
    return -1;
  }
  if(x == 0)
  {
    return y + 1;
  }
  if(y == 0)
  {
     return ackermanns(x - 1, 1);
  }
  if(x>0 && y>0)
  {

    return ackermanns(x - 1, ackermanns(x, y - 1));
  }
}