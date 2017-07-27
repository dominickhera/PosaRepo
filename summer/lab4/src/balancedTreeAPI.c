#include "balancedTreeAPI.h"
#include "tree.h"

/*-----------------------------
  CHANGE NOTHING IN THIS FILE!!!!
  -------------------------------*/

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{

    Tree * temp = malloc(sizeof(Tree));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->root = NULL;
    temp->compareFP = compareFP;
    temp->destroyFP = destroyFP;
    temp->copyFP = copyFP;

    return temp;

}

TreeNode *createBalancedBinNode(void *data)
{

    TreeNode * temp = malloc(sizeof(TreeNode));
    temp->data = malloc(sizeof(data));

    if(temp == NULL)
    {
        return NULL;
    }

    strcpy(temp->data, data);
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    temp->frequency = 1;

    return temp;

}

void destroyBalancedBinTree(Tree *toBeDeleted)
{

}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{

	Tree *theTree = createBalancedBinNode(toBeInserted);
	Tree *next = NULL;
	Tree *last = NULL;

	// if(theTree->root != NULL)
	// {
	// 	next = theTree->root;

	// 	while(next != NULL)
	// 	{
	// 		last = next;
			
	// 	}

	// }



}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{

}

int treeIsEmpty(Tree *theTree)
{

}

int treeHasTwoChildren(TreeNode *root)
{

}

void *treeFindNode(Tree *theTree, void *data)
{

}

void *treeFindMin(Tree *theTree)
{

}

void *treeFindMax(Tree *theTree)
{

}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{

}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{

}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{

}


