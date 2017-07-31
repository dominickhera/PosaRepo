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
    // oid free_tree(node* p)
    // {
    //     if ( !p )
    //         return;

    //     free_tree(p -> left);
    //     free_tree(p -> right);
    //     free(p);
    // }


    // TreeNode *temp 
}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{
    // if(treeIsEmpty(theTree) == 1)
    // {
    if(treeFindNode(theTree, toBeInserted) == NULL)
    {
        // printf("1\n");
        TreeNode *tempNode = createBalancedBinNode(toBeInserted);;

        // printf("2\n");
        TreeNode *next = NULL;
        // printf("3\n");
        TreeNode *end = NULL;
        if(treeIsEmpty(theTree) == 1)
        {
            // printf("4\n");
            // tempNode = createBalancedBinNode(toBeInserted);
            theTree->root = tempNode;

        }
        else
        {
            // printf("5\n");
            next = theTree->root;
            // printf("6\n");
            while(next != NULL)
            {
                end = next;
                // printf("7\n");
                if(strcmp(toBeInserted, next->data) > 0)
                {
                    // printf("8\n");
                    next = next->right;
                }
                else if(strcmp(toBeInserted, next->data) < 0)
                {
                    // printf("9\n");
                    next = next->left;
                }		
            }

            // tempNode = createBalancedBinNode(toBeInserted);
            // printf("10\n");
            if(strcmp(toBeInserted, end->data) > 0)
            {
                // printf("11\n");
                end->right = tempNode;
            }
            else if(strcmp(toBeInserted, end->data) < 0)
            {
                end->left = tempNode;
                // printf("12.b\n");
            }

            // printf("13.b\n");
        }
        // printf("14.a\n");
        balanceTree(theTree);
        // printf("14\n");
    }
    else
    {
        printf("node already exists...\n");
    }
    // }
    // else
    // {
    // 	printf("tree is empty\n");
    // }

}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
    TreeNode *tempNode = treeFindNode(theTree, toBeDeleted);

    if(tempNode != NULL)
    {
        // free(&tempNode->height);
        free(tempNode->data);
        free(tempNode);
    }
    else
    {
        printf("node doesnt exist...\n");
    }

    balanceTree(theTree);
    //balancetree

}

int treeIsEmpty(Tree *theTree)
{
    if(theTree->root == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int treeHasTwoChildren(TreeNode *root)
{

    if(root->left != NULL && root->right != NULL)
    {
        return 0;
    }

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

	// if(TreeNode != NULL)
 //    {
 //        treeInOrderPrint(TreeNode->left);
 //        printf("%s ", TreeNode->data);
 //        treeInOrderPrint(TreeNode->right);
 //    }

}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{

	// if(TreeNode != NULL)
 //    {
 //        printf("%s ", TreeNode->data);
 //        treePreOrderPrint(TreeNode->left);
 //        treePreOrderPrint(TreeNode->right);
 //    }

}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{

	// if(TreeNode != NULL)
 //    {
 //        treePostOrderPrint(TreeNode->left);
 //        treePostOrderPrint(TreeNode->right);
 //        printf("%s ", TreeNode->data);
 //    }

}


