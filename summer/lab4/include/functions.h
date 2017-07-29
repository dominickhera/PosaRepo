#ifndef _DHERA_FUNCTIONS_
#define _DHERA_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "balancedTreeAPI.h"

void printData(void * data);
int compareFunction(void *first,void *second);
void *copyFunction(void *toBeCopy);
treeNode * leftRotation(treeNode * node);
treeNode * rightRotation(treeNode * node);
treeNode * leftRightRotation(treeNode * node);
treeNode * rightLeftRotation(treeNode * node);



#endif
