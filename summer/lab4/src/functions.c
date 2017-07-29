#include "functions.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int compareFunction(void *first, void *second)
{
	

	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
	{
		return *(int *)first;
	}
	else
	{
		int tempVal = 0;
		tempVal = *(int *)first;
		*(int *)first = *(int *)second;
		*(int *)second = tempVal;
		return *(int *)first;
	}
}

void *copyFunction(void *toBeCopy)
{
	printf("this is supposed to copy stuff i think\n");

	return toBeCopy;
}

treeNode * leftRotation(treeNode * node)
{


}

treeNode * rightRotation(treeNode * node)
{

}

treeNode * leftRightRotation(treeNode * node)
{

	treeNode *a = node;
	treeNode *b = a->left;
	treeNode *c = b->right;

	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;

}

treeNode * rightLeftRotation(treeNode * node)
{

}
