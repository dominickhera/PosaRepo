#include "tree.h"

int getHeight(TreeNode *node)
{
	// printf("lol\n");

	int tempReturn = 0;

	TreeNode *tempA = node;
	TreeNode *tempB = node;

	while(tempA->right != NULL)
	{
		tempReturn++;
		tempA->right = tempA->right->right; 
	}

	while(tempB->left != NULL)
	{
		tempReturn--;
		tempB->left = tempB->left->left;
	}

	return tempReturn;

}


TreeNode * balanceTreeNode(TreeNode * node)
{

	TreeNode *temp = NULL;

	if(node->right != NULL)
	{
		node->right = balanceTreeNode(node->right);
	}

	if(node->left != NULL)
	{
		node->left = balanceTreeNode(node->right);
	}


	if(getHeight(node) <= -2)
	{
		if(getHeight(node->left) >= 1)
		{
			temp = rightLeftRotation(node);
		}
		else
		{
			temp = rightRotation(node);
		}
	}
	else if(getHeight(node) >= 2)
	{
		if(getHeight(node->right) >= -1)
		{
			temp = leftRotation(node);
		}
		else
		{
			temp = leftRotation(node);
		}
	}
	else
	{
		temp = node;
	}

	return temp;

}

void balanceTree(Tree *theTree)
{
	TreeNode *temp = NULL;

	temp = balanceTreeNode(theTree->root);

	if(temp != theTree->root)
	{
		theTree->root = temp;
	}
}


TreeNode * leftRotation(TreeNode * node)
{

	TreeNode *pivot = node;
	TreeNode *temp = pivot->right;

	pivot->right = temp->left;
	temp->left = pivot;
	pivot = temp;

	return pivot;

}

TreeNode * rightRotation(TreeNode * node)
{

	TreeNode *pivot = node;
	TreeNode *temp = pivot->left;

	pivot->left = temp->right;
	temp->right = pivot;
	pivot = temp;

	return pivot;	

}

TreeNode * leftRightRotation(TreeNode * node)
{

	TreeNode *a = node;
	TreeNode *b = a->left;
	TreeNode *c = b->right;

	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;

	return c;

}

TreeNode * rightLeftRotation(TreeNode * node)
{

	TreeNode *a = node;
	TreeNode *b = a->right;
	TreeNode *c = b->left;

	a->right = c->left;
	b->left = c->right;
	c->right = b;
	c->left = a;

	return c;

}

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
