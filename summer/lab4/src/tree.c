#include "tree.h"

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
