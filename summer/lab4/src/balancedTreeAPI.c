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

    return temp;

}

void destroyBalancedBinTree(Tree *toBeDeleted)
{

}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{

    TreeNode *tempNode = createBalancedBinNode(toBeInserted);
    TreeNode *next = NULL;

    if(theTree->root != NULL)
    {
        next = theTree->root;

        while(next != NULL)
        {
            if(strcmp(toBeInserted, next->data) > 0)
            {
                next = next->right;
            }
            else if(strcmp(toBeInserted, next->data) < 0)
            {
                next = next->left;
            }		
        }

        if(strcmp(toBeInserted, next->data) > 0)
        {
            next->right = tempNode;
        }
        else if(strcmp(toBeInserted, next->data) < 0)
        {
            next->left = tempNode;
        }

    }
    else
    {
        theTree->root = tempNode;
    }

}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{

	TreeNode *tempNode = treeFindNode(theTree, toBeDeleted);

	free(&tempNode->height);
	free(&tempNode->data);
	free(tempNode);

	//balancetree

}

int treeIsEmpty(Tree *theTree)
{
    if(theTree->root == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int treeHasTwoChildren(TreeNode *root)
{

    if(root->left != NULL && root->right != NULL)
    {
        return 0;
    }
    else if(root->left != NULL || root->right != NULL)
    {
        return 1;
    }

    return 3;

}

void *treeFindNode(Tree *theTree, void *data)
{

    TreeNode *tempSearch = theTree->root;

    while(tempSearch != NULL)
    {
        if(strcmp(data, tempSearch->data) > 0)
        {
            tempSearch = tempSearch->right;
        }
        else if(strcmp(data, tempSearch->data) < 0)
        {
            tempSearch = tempSearch->left;
        }
        else if(strcmp(data, tempSearch->data) == 0)
        {
            return tempSearch;
        }
    }

    return NULL;

}

void *treeFindMin(Tree *theTree)
{

	TreeNode *tempSearch = theTree->root;

    while(tempSearch != NULL)
    {
        tempSearch = tempSearch->left;
    }

    return tempSearch;

}

void *treeFindMax(Tree *theTree)
{

	TreeNode *tempSearch = theTree->root;

     while(tempSearch != NULL)
    {
        tempSearch = tempSearch->right;
    }

    return tempSearch;

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


