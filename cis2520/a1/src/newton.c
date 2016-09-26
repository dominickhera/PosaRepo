#include "newton.h"

void newtonInit()
{
	int x;
	struct timeval startTime;
	struct timeval endTime;
	unsigned long long int startMicros;
	unsigned long long int endMicros;
	unsigned long long int deltaMicros;
	unsigned long long int deltaMicros2;

	printf("enter number to find the square root of: \n");
	scanf("%d", &x);

	gettimeofday(&startTime, NULL);
	printf("the iterative answer is %f\n", newtonIterative(x));
	gettimeofday(&endTime, NULL);
	
	startMicros = (1000000 * startTime.tv_sec) + startTime.tv_usec;
	endMicros = (1000000 * endTime.tv_sec) + endTime.tv_usec;

	deltaMicros = endMicros - startMicros;

	gettimeofday(&startTime, NULL);
	printf("the recursive answer is %f\n", newtonRecursive(1,x,1));
	gettimeofday(&endTime, NULL);

	startMicros = (1000000 * startTime.tv_sec) + startTime.tv_usec;
	endMicros = (1000000 * endTime.tv_sec) + endTime.tv_usec;

	deltaMicros2 = endMicros - startMicros;

	printf("the iterative function took %llu nano seconds\nthe recursive function took %llu nano seconds\n", deltaMicros, deltaMicros2);
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