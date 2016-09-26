#ifndef __DHERA__NEWTON__
#define __DHERA__NEWTON__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void newtonInit();
double newtonIterative(double x);
double newtonRecursive(double e,  double x, double recursiveAnswer);

#endif