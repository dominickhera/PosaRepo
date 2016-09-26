#include "newton.h"

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
    //  recursiveAnswer
  }
}