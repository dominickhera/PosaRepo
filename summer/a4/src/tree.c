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
    int tempInt = 0;

    if(node->right != NULL)
    {
        tempInt = tempInt - balanceHeight(node->right);
    }

    if(node->left != NULL)
    {
        tempInt = tempInt + balanceHeight(node->left);
    }

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

    TreeNode *a = node->right;
    TreeNode *b = a->left;

    a->left = node;
    node->right = b;


    return a;

}

TreeNode * rightRotation(TreeNode * node)
{

    TreeNode *a = node->left;
    TreeNode *b = a->right;

    a->right = node;
    node->left = b;


    return a;	

}

TreeNode * leftRightRotation(TreeNode * node)
{

    node->left = leftRotation(node->left);

    return rightRotation(node);

}

TreeNode * rightLeftRotation(TreeNode * node)
{

    node->right = rightRotation(node->right);

    return leftRotation(node);
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

    return toBeCopy;
}

int hashData(size_t hashSize, char * dataKey)
{

    int tempKey = 0;

    while(*dataKey != '\0')
    {
        tempKey = tempKey + *dataKey;
        dataKey++;
    }


    // printf("%lu\n", tempKey % hashSize);
    return tempKey % hashSize;
}

void stockCheck(TreeNode *node)
{

    if(node != NULL)
    {
        // printf("tits\n");
        // if(node->left != NULL)
        // {
        stockCheck(node->left);
        printf("%s, Quantity: %d\n", (char *)node->prodName, node->quantity);
        stockCheck(node->right);
        // }

        // if(node->right != NULL)
        // {
             // stockCheck(node->left);
        // printf("%s, Quantity: %d\n", (char *)node->prodName, node->quantity);
        // stockCheck(node->right);
        // }
    }

}


void inorder(TreeNode *node)
{

    if(node != NULL)
    {
        // printf("butt\n");
        inorder(node->left);
        printf("%s\n", (char *)node->prodName);
        inorder(node->right);
    }

}

void preorder(TreeNode *node)
{

    if(node != NULL)
    {
        printf("%s\n", (char *)node->proID);
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
        printf("%s ", (char *)node->proID);
    }

}

