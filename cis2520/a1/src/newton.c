#include "newton.h"

void newtonInit()
{
	int x;

	printf("enter number to find the square root of: \n");
	scanf("%d", &x);
	printf("the iterative answer is %f\n", newtonIterative(x));
	printf("the recursive answer is %f\n", newtonRecursive(1,x,1));

}


double newtonIterative(double x)
{
  double answer = 1;
  while (fabs((answer * answer) / x - 1.0) >= 0.0000001)
  {
    answer = ((x/answer) + answer)/2;
  }
  return answer;
}

double newtonRecursive(double e,  double x, double recursiveAnswer)
{

  if (fabs(recursiveAnswer * recursiveAnswer - x) <= e)
  {
  	return recursiveAnswer;
  }
  else
  {
    recursiveAnswer = (recursiveAnswer * recursiveAnswer + x) / (2 * recursiveAnswer);
    return 1.0 * (newtonRecursive(recursiveAnswer ,x, e));
  }

}