#include "balancedTreeAPI.h"
#include "tree.h"

/*-----------------------------
  CHANGE NOTHING IN THIS FILE!!!!
  -------------------------------*/

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{

    Tree * temp = malloc(sizeof(Tree)*500);

    if(temp == NULL)
    {
        return NULL;
    }

    temp->root = NULL;
    temp->compareFP = compareFP;
    temp->destroyFP = destroyFP;
    temp->copyFP = copyFP;

    printf("Binary Tree successfully created\n\n");

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

    printf("Binary Tree Node successfully created with data: %s\n", (char *)temp->data);

    return temp;

}

void destroyBalancedBinTree(Tree *toBeDeleted)
{

    free(toBeDeleted);

}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{

    if(theTree != NULL)
    {

        TreeNode *tempNode = createBalancedBinNode(toBeInserted);;
        TreeNode *next = NULL;
        TreeNode *end = NULL;

        if(treeIsEmpty(theTree) == 1)
        {
            theTree->root = tempNode;

        }
        else
        {
            if(treeFindNode(theTree, toBeInserted) == NULL)
            {
                next = theTree->root;
                while(next != NULL)
                {
                    end = next;
                    if(strcmp(toBeInserted, next->data) > 0)
                    {
                        next = next->right;
                    }
                    else if(strcmp(toBeInserted, next->data) < 0)
                    {
                        next = next->left;
                    }		
                }

                if(strcmp(toBeInserted, end->data) > 0)
                {
                    end->right = tempNode;
                }
                else if(strcmp(toBeInserted, end->data) < 0)
                {
                    end->left = tempNode;
                }

                balanceTree(theTree);
            }
            else
            {
                printf("node already exists...\n");
            }
        }
    }
    else
    {
        printf("Tree does not exist\n");
    }

}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
    TreeNode *tempNode = treeFindNode(theTree, toBeDeleted);

    if(tempNode != NULL)
    {
        // free(&tempNode->height);
        free(tempNode->data);
        free(tempNode);
        printf("Node %s successfully deleted\n", (char *)toBeDeleted);
    }
    else
    {
        printf("node doesnt exist...\n");
    }

    balanceTree(theTree);

}

int treeIsEmpty(Tree *theTree)
{
    if(theTree->root == NULL)
    {
        printf("Tree is currently empty\n");
        return 1;
    }
    else
    {
        printf("Tree is not currently empty\n");
        return 0;
    }
}

int treeHasTwoChildren(TreeNode *root)
{

    if(root->left != NULL && root->right != NULL)
    {
        printf("Node has both a left and a right child\n");
        return 0;
    }

    printf("Node does not have two children\n");
    return 1;

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
            printf("Found Node %s!\n", (char *)tempSearch->data);
            return tempSearch;
        }
    }

    // printf("Could not find Node %s :c\n", (char *)data);
    return NULL;

}

void *treeFindMin(Tree *theTree)
{

    TreeNode *tempSearch = theTree->root;

    while(tempSearch != NULL)
    {
        tempSearch = tempSearch->left;
    }

    printf("Minimum Node Value: %s\n", (char *)tempSearch->data);

    return tempSearch;

}

void *treeFindMax(Tree *theTree)
{

    TreeNode *tempSearch = theTree->root;

    while(tempSearch != NULL)
    {
        tempSearch = tempSearch->right;
    }

    printf("Maxmium Node Value: %s\n", (char *)tempSearch->data);

    return tempSearch;

}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if(theTree != NULL)
    {
        printf("InOrder: ");
        inorder(theTree->root);
    }
}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if(theTree != NULL)
    {
        printf("PreOrder: ");
        preorder(theTree->root);
    }
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if(theTree != NULL)
    {
        printf("PostOrder: ");
        postorder(theTree->root);
    }
}


