#include "tree.h"

int balanceHeight(TreeNode * node)
{
    int rHeight = 0;
    int lHeight = 0;

    int tempReturn = 0;

    if(node->right != NULL)
    {
        rHeight = getHeight(node->right);
    }
    if(node->left != NULL)
    {
        lHeight = getHeight(node->left);
    }

    // if(rHeight > lHeight)
    // {
    //     rHeight++;
    //     tempReturn = rHeight;
    // }
    // else
    // {
    //     lHeight++;
    //     tempReturn = lHeight;
    // }


    return rHeight > lHeight ? ++rHeight : ++lHeight;
}

int getHeight(TreeNode *node)
{
    // printf("lol\n");

    int tempInt = 0;

    if(node->right != NULL)
    {
        tempInt = tempInt + balanceHeight(node->right);
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
    // printf("20\n");
    TreeNode *temp = NULL;
    // int heightCheck = 0;
    // printf("21\n");
    if(node->right != NULL)
    {
        // printf("23\n");
        node->right = balanceTreeNode(node->right);
        // printf("23.b\n");
    }

    if(node->left != NULL)
    {
        // printf("24\n");
        node->left = balanceTreeNode(node->left);
        // printf("24.b\n");
    }

    // printf("25.a\n");

    int heightCheck = getHeight(node);

    // printf("heightCheck: %d\n", heightCheck);


    if(heightCheck >= 2)
    {
        printf("28\n");
        printf("buuuuut");
        // printf("h: %d\n", getHeight(node->left));
        if(getHeight(node->left) <= -1)
        {
            printf("29\n");
            temp = leftRightRotation(node);
        }
        else
        {
            printf("30\n");
            temp = leftRotation(node);
        }
    }
    else if(heightCheck <= -2)
    {
        printf("25\n");
        if(getHeight(node->right) >= 1)
        {
            printf("26\n");
            temp = rightLeftRotation(node);
        }
        else
        {
            printf("27\n");
            temp = rightRotation(node);
        }

    }
    else
    {
        printf("31\n");
        temp = node;
    }

    // printf("tempF Data: %s\n", temp->data);

    return temp;
}


void balanceTree(Tree *theTree)
{

    // printf("15\n");
    TreeNode *temp = NULL;
    // printf("16\n");
    temp = balanceTreeNode(theTree->root);
    // printf("root: %s, temp: %s\n", theTree->root->data, temp->data);
    // printf("17\n");
    if(temp != theTree->root)
    {
        // printf("18\n");
        theTree->root = temp;
        // printf("buuttttt\n");
        // printf("temp is: %s\n", theTree->root->data);
    }
    // printf("19\n");
}


TreeNode * leftRotation(TreeNode * node)
{
    printf("l\n");

    TreeNode *pivot = node;
    TreeNode *temp = pivot->right;

    pivot->right = temp->left;
    temp->left = pivot;

    // pivot->height = getHeight(pivot);
    // temp->height = getHeight(temp);

    // printf("pivotH: %d, tempH: %d\n", pivot->height, temp->height);

    return temp;

}

TreeNode * rightRotation(TreeNode * node)
{
    printf("r\n");

    TreeNode *pivot = node;
    TreeNode *temp = pivot->left;

    pivot->left = temp->right;
    temp->right = pivot;

    // pivot->height = getHeight(pivot);
    // temp->height = getHeight(temp);

    // printf("pivotH: %d, tempH: %d\n", pivot->height, temp->height);

    return temp;	

}

TreeNode * leftRightRotation(TreeNode * node)
{
    printf("lr\n");

    TreeNode *a = node;
    TreeNode *b = a->left;
    TreeNode *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    // a->height = getHeight(a);
    // b->height = getHeight(b);
    // c->height = getHeight(c);

    // printf("aH: %d, bH: %d, cH: %d\n", a->height, b->height, c->height);

    return c;

}

TreeNode * rightLeftRotation(TreeNode * node)
{
    printf("rl\n");
    TreeNode *a = node;
    TreeNode *b = a->right;
    TreeNode *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    // printf("aH: %d, bH: %d, cH: %d\n", a->height, b->height, c->height);


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
