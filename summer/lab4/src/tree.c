#include "tree.h"

int balanceHeight(TreeNode * node)
{
    int rHeight = 0;
    int lHeight = 0;

    int tempReturn = 0;

    if(node->right != NULL)
    {
        rHeight = balanceHeight(node->right);
    }
    if(node->left != NULL)
    {
        lHeight = balanceHeight(node->left);
    }

    if(rHeight > lHeight)
    {
        rHeight++;
        tempReturn = rHeight;
    }
    else
    {
        lHeight++;
        tempReturn = lHeight;
    }


    return tempReturn;

}

int getHeight(TreeNode *node)
{
    // printf("lol\n");

    int tempInt = 0;

    if(node->right != NULL)
    {
        tempInt = tempInt - balanceHeight(node->right);
    }

    if(node->left != NULL)
    {
        tempInt = tempInt + balanceHeight(node->left);
    }
    // printf("tempint: %d\n", tempInt);

    return tempInt;
}


TreeNode * balanceTreeNode(TreeNode * node)
{

    TreeNode *temp = NULL;

    if(node->left != NULL)
    {
        node->left = balanceTreeNode(node->left);
    }

    if(node->right != NULL)
    {
        node->right = balanceTreeNode(node->right);
    }

    int heightCheck = getHeight(node);

    if(heightCheck >= 2)
    {
        // printf("28\n");
        if(getHeight(node->left) <= -1)
        {
            temp = leftRightRotation(node);
        }
        else
        {
            temp = rightRotation(node);
        }
    }
    else if(heightCheck <= -2)
    {
        if(getHeight(node->right) >= 1)
        {
            temp = rightLeftRotation(node);
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

    TreeNode *temp = balanceTreeNode(theTree->root);

    if(temp != theTree->root)
    {
        theTree->root = temp;
    }
}


TreeNode * leftRotation(TreeNode * node)
{
    // printf("l\n");

    TreeNode *pivot = node;
    TreeNode *temp = pivot->right;

    pivot->right = temp->left;
    temp->left = pivot;

   
    return temp;

}

TreeNode * rightRotation(TreeNode * node)
{
    // printf("r\n");

    TreeNode *pivot = node;
    TreeNode *temp = pivot->left;

    pivot->left = temp->right;
    temp->right = pivot;

   
    return temp;	

}

TreeNode * leftRightRotation(TreeNode * node)
{
    // printf("lr\n");

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
    // printf("rl\n");
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

void inorder(TreeNode *node)
{

	if(node != NULL)
       {
           inorder(node->left);
           printf("%s ", node->data);
           inorder(node->right);
       }

}

void preorder(TreeNode *node)
{

		if(node != NULL)
       {
       	   printf("%s ", node->data);
           preorder(node->left);
           preorder(node->right);
       }

}

void postorder(TreeNode *node)
{

		if(node != NULL)
       {
           postorder(node->left);
           postorder(node->right);
           printf("%s ", node->data);
       }

}
