#include "tree.h"

treeNode * leftRotation(treeNode * node)
{

	treeNode *b = node;
	treeNode *c = b->right;
	
	c = b;
	b = c->left;

}

treeNode * rightRotation(treeNode * node)
{

	treeNode *b = node;
	treeNode *c = b->left;
	
	c = b;
	b = c->right;

}

treeNode * leftRightRotation(treeNode * node)
{

}

treeNode * rightLeftRotation(treeNode * node)
{


}
