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

TreeNode *createBalancedBinNode(void *proID, void *prodName, void *publisher, void *genre, TAX_TYPE taxType,void *price, int quantity)
{

    TreeNode * temp = malloc(sizeof(TreeNode));
    temp->proID = malloc(sizeof(proID) * 100);
    temp->prodName = malloc(sizeof(prodName) * 100);
    temp->publisher = malloc(sizeof(publisher) * 100);
    temp->genre = malloc(sizeof(genre) * 100);
    temp->price = malloc(sizeof(price) * 100);


    if(temp == NULL)
    {
        return NULL;
    }

    strcpy(temp->proID, proID);
    strcpy(temp->prodName, prodName);
    strcpy(temp->publisher, publisher);
    strcpy(temp->genre, genre);
    strcpy(temp->price, price);
    temp->quantity = quantity;
    temp->taxType = taxType;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;


    return temp;

}

void destroyBalancedBinTree(Tree *toBeDeleted)
{

    free(toBeDeleted);

}

void treeInsertNode(Tree *theTree, void *proID, void *prodName, void *publisher, void *genre, TAX_TYPE taxType,void *price, int quantity)
{

    if(theTree != NULL)
    {

        TreeNode *tempNode = createBalancedBinNode(proID, prodName, publisher, genre, taxType, price, quantity);
        TreeNode *next = NULL;
        TreeNode *end = NULL;

        if(treeIsEmpty(theTree) == 1)
        {
            theTree->root = tempNode;

        }
        else
        {
            
                next = theTree->root;
                while(next != NULL)
                {
                    end = next;
                    if(strcmp(prodName, next->prodName) > 0)
                    {
                        next = next->right;
                    }
                    else if(strcmp(prodName, next->prodName) < 0)
                    {
                        next = next->left;
                    }
                    else if(strcmp(prodName, next->prodName) == 0)
                    {
                        next->quantity++;
                        return;
                    }		
                }

                if(strcmp(prodName, end->prodName) > 0)
                {
                    end->right = tempNode;
                }
                else if(strcmp(prodName, end->prodName) < 0)
                {
                    end->left = tempNode;
                }
                else if(strcmp(prodName, end->prodName) == 0)
                {
                    end->quantity++;
                    return;
                }

                balanceTree(theTree);
        }
    }
    else
    {
        printf("Tree does not exist\n");
    }

}

void treeDeleteNode(Tree *theTree, void *prodName)
{

    TreeNode *tempNode = NULL;
    if((tempNode = treeFindNode(theTree, prodName)) != NULL)
    {

        TreeNode *tempDeleteNodeParent = NULL;
        TreeNode *tempDeleteNode = NULL;
        // printf("tempnode exists\n");
        if(treeHasTwoChildren(tempNode) == 0)
        {
            printf("butthole\n");
            tempDeleteNodeParent = tempNode;
            tempDeleteNode = tempNode->left;
            //left and right are BOTH NOT NULL

            while(tempDeleteNode->left != NULL)
            {
                tempDeleteNodeParent = tempDeleteNode;
                tempDeleteNode = tempDeleteNode->left;
            }

            strcpy(tempNode->proID, tempDeleteNode->proID);
            strcpy(tempNode->prodName, tempDeleteNode->prodName);
            strcpy(tempNode->price, tempDeleteNode->price);
            strcpy(tempNode->genre, tempDeleteNode->genre);
            strcpy(tempNode->publisher, tempDeleteNode->publisher);
            tempNode->taxType = tempDeleteNode->taxType;
            tempNode->quantity = tempDeleteNode->quantity;

            tempNode = tempDeleteNode;
            // free(tempDeleteNode);
            // return ;

        }
        

        if(treeHasTwoChildren(tempNode) == 3)
        {
            printf("lolol\n");
            // tempNode->right = NULL;
            // tempNode->left = NULL;
            // tempNode = NULL;
            // if(tempDeleteNodeParent->right == tempNode)
            // {
                // printf("shit's the same nigga\n");
                // tempDeleteNodeParent->right = NULL;
            // }
            // else
            // {
                // printf("shit aint the same\n");
                // tempDeleteNodeParent->left = NULL;
            // }
            printf("1\n");
            // free(tempNode->proID);
            printf("2\n");
            // free(tempNode->prodName);
            printf("3\n");
            // free(tempNode->price);
            printf("4\n");
            // free(tempNode->genre);
            printf("5\n");
            // free(tempNode->publisher);
            printf("6\n");
            // free(&tempNode->taxType);
            // printf("7\n");
            // free(&tempNode->quantity);
            // printf("8\n");
            free(tempNode);
            // printf("8\n");
            // tempNode = NULL;
            // printf("8\n");
            // tempNode->proID = NULL;
            // printf("8\n");
            // tempNode->prodName = NULL;
            // printf("8\n");
            // tempNode->price = NULL;
            // printf("8\n");
            // tempNode->genre = NULL;
            // printf("8\n");
            // tempNode->publisher = NULL;
            // printf("8\n");
            // balanceTree(theTree);
            // printf("10\n");
            return;
        }
        // else 

        if(treeHasTwoChildren(tempNode) == 2)
        {
         
            //right is null, left is NOT

            printf("suck a b00ty\n");
            // tempDeleteNode = treeFindMin(tempNode);

            if(tempDeleteNodeParent->left == tempNode)
            {
                printf("shit's the same nigga\n");
                tempDeleteNodeParent->left = tempNode->left;
            }
            else
            {
                printf("shit aint the same\n");
                tempDeleteNodeParent->right = tempNode->left;
            }

            free(tempNode);
            return;


        }
        if(treeHasTwoChildren(tempNode) == 1)
        {
            //left is null, Right is NOT

            printf("left null tithole\n");
            // tempDeleteNodeParent = tempNode;
            // tempDeleteNode = tempNode->right;
            // strcpy(tempNode->proID, tempDeleteNode->proID);
            // strcpy(tempNode->prodName, tempDeleteNode->prodName);
            // strcpy(tempNode->price, tempDeleteNode->price);
            // strcpy(tempNode->genre, tempDeleteNode->genre);
            // strcpy(tempNode->publisher, tempDeleteNode->publisher);
            // tempNode->taxType = tempDeleteNode->taxType;
            // tempNode->quantity = tempDeleteNode->quantity;

        //     // tempNode->right = tempDeleteNode->left;

            // tempNode = tempDeleteNode;
            // free(tempDeleteNode);

            if(tempDeleteNodeParent->left == tempNode)
            {
                printf("shit's the same nigga\n");
                tempDeleteNodeParent->left = tempNode->right;
            }
            else
            {
                printf("shit aint the same\n");
                tempDeleteNodeParent->right = tempNode->right;
            }

            free(tempNode);
            return;
            
        }
        // free(tempDeleteNode);


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
    else if(root->left == NULL && root->right != NULL)
    {
        return 1;
    }
    else if(root->left != NULL && root->right == NULL)
    {
        return 2;
    }
    else if(root->left == NULL && root->right == NULL)
    {
        return 3;
    }

    return 4;

}

void *treeFindNode(Tree *theTree, void *data)
{

    if(theTree != NULL)
    {
        TreeNode *tempSearch = theTree->root;

        while(tempSearch != NULL)
        {
            if(strcmp(data, tempSearch->prodName) > 0)
            {
                tempSearch = tempSearch->right;
            }
            else if(strcmp(data, tempSearch->prodName) < 0)
            {
                tempSearch = tempSearch->left;
            }
            else if(strcmp(data, tempSearch->prodName) == 0)
            {
                return tempSearch;
            }
        }
    }

    return NULL;

}

void *treeFindMin(TreeNode *tempNode)
{

    TreeNode *tempSearch = tempNode;

    while(tempSearch != NULL)
    {
        tempSearch = tempSearch->left;
    }

    return tempSearch;

}

void *treeFindMax(TreeNode *tempNode)
{

    TreeNode *tempSearch = tempNode;

    while(tempSearch != NULL)
    {
        tempSearch = tempSearch->right;
    }

    return tempSearch;

}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if(theTree != NULL)
    {
        // printf("InOrder: ");
        inorder(theTree->root);
    }
}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if(theTree != NULL)
    {
        // printf("PreOrder: ");
        preorder(theTree->root);
    }
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if(theTree != NULL)
    {
        // printf("PostOrder: ");
        postorder(theTree->root);
    }
}


