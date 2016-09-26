#include "newton.h"

//initiates the newton function, figures ou the difference in time while calling the two different functions both recursive and iterative
// and then prints the difference in time between the two and the faster version.
void newtonInit()
{
	int x;
	struct timeval startTime;
	struct timeval endTime;
	unsigned long long int startMicros;
	unsigned long long int endMicros;
	unsigned long long int deltaMicros;
	unsigned long long int deltaMicros2;
	unsigned long long int differenceMicros;

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

	printf("the iterative function took %llu nanoseconds\nthe recursive function took %llu nanoseconds\n", deltaMicros, deltaMicros2);

	if (deltaMicros > deltaMicros2)
	{
		differenceMicros = deltaMicros - deltaMicros2;
		printf("iterative was faster by %llu nanoseconds\n", differenceMicros);
	}
	if (deltaMicros2 > deltaMicros)
	{
		differenceMicros = deltaMicros2 - deltaMicros;
		printf("recursive was faster by %llu nanoseconds\n", differenceMicros);
	}
}

//iteratively finds the square root of the number given
double newtonIterative(double x)
{
  double answer = 1;
  while (fabs((answer * answer) / x - 1.0) >= 0.0000001)
  {
    answer = ((x/answer) + answer)/2;
  }
  return answer;
}
//recusively finds the square root of the number given
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