#include "ackermann.h"

//initiates the ackerman function, asking for the two variables and calling the main ackermann function
void ackermannInit()
{

int x, y;

printf("please enter first number\n");
scanf("%d", &x);
printf("please enter second number\n");
scanf("%d", &y);
printf("the answer is %d\n", ackermanns(x,y));


}


//main ackermann function that will spit out an answer based on the two numbers given, it currently only goes up to 4,1
int ackermanns(int x, int y)
{
  if (x<0 || y<0)
  {
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