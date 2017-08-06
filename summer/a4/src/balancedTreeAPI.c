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

        int deleteFlag = 0;
        TreeNode *tempDeleteNodeParent = NULL;
        TreeNode *tempDeleteNode = NULL;

        if(tempNode->right != NULL && tempNode->left != NULL)
        {
            tempDeleteNodeParent = tempNode;
            tempDeleteNode = tempNode->right;
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
            deleteFlag++;

        }
        

        if(tempNode->right == NULL && tempNode->left == NULL)
        {

            if(deleteFlag == 0)
            {
                tempDeleteNode = theTree->root;

                while(tempDeleteNode != tempNode)
                {
                    if(strcmp(tempNode->prodName, tempDeleteNode->prodName) > 0)
                    {
                        tempDeleteNodeParent = tempDeleteNode;
                        tempDeleteNode = tempDeleteNode->right;
                    }
                    else if(strcmp(tempNode->prodName, tempDeleteNode->prodName) < 0)
                    {
                        tempDeleteNodeParent = tempDeleteNode;
                        tempDeleteNode = tempDeleteNode->left;
                    }
                    else if(strcmp(tempNode->prodName, tempDeleteNode->prodName) == 0)
                    {
                        break;
                    }
                }
            }

            if(tempDeleteNodeParent->right == tempNode)
            {
                tempDeleteNodeParent->right = tempNode->right;
            }
            else
            {
                tempDeleteNodeParent->left = tempDeleteNode->right;
            }

            free(tempNode);

            balanceTree(theTree);
            // printf("10\n");
            return;
        }

        if(tempNode->right == NULL && tempNode->left != NULL)
        {
         
            //right is null, left is NOT
             if(deleteFlag == 0)
            {
                tempDeleteNode = theTree->root;

                while(tempDeleteNode != tempNode)
                {
                    if(strcmp(tempNode->prodName, tempDeleteNode->prodName) > 0)
                    {
                        tempDeleteNodeParent = tempDeleteNode;
                        tempDeleteNode = tempDeleteNode->right;
                    }
                    else if(strcmp(tempNode->prodName, tempDeleteNode->prodName) < 0)
                    {
                        tempDeleteNodeParent = tempDeleteNode;
                        tempDeleteNode = tempDeleteNode->left;
                    }
                    else if(strcmp(tempNode->prodName, tempDeleteNode->prodName) == 0)
                    {
                        break;
                    }
                }
            }

            if(tempDeleteNodeParent->left == tempNode)
            {
                tempDeleteNodeParent->left = tempNode->left;
            }
            else
            {
                tempDeleteNodeParent->right = tempNode->left;
            }

            free(tempNode);
            balanceTree(theTree);
            return;


        }
        if(tempNode->right != NULL && tempNode->left == NULL)
        {
            //left is null, Right is NOT

             if(deleteFlag == 0)
            {
                tempDeleteNode = theTree->root;

                while(tempDeleteNode != tempNode)
                {
                    if(strcmp(tempNode->prodName, tempDeleteNode->prodName) > 0)
                    {
                        tempDeleteNodeParent = tempDeleteNode;
                        tempDeleteNode = tempDeleteNode->right;
                    }
                    else if(strcmp(tempNode->prodName, tempDeleteNode->prodName) < 0)
                    {
                        tempDeleteNodeParent = tempDeleteNode;
                        tempDeleteNode = tempDeleteNode->left;
                    }
                    else if(strcmp(tempNode->prodName, tempDeleteNode->prodName) == 0)
                    {
                        break;
                    }
                }
            }

            if(tempDeleteNodeParent->left == tempNode)
            {
                tempDeleteNodeParent->left = tempNode->right;
            }
            else
            {
                tempDeleteNodeParent->right = tempNode->right;
            }

            free(tempNode);
            balanceTree(theTree);
            return;

        }

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


