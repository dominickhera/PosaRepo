#include "balancedTreeAPI.h"
#include "tree.h"

/*-----------------------------
  CHANGE NOTHING IN THIS FILE!!!!
  -------------------------------*/

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{

    Tree * temp = NULL;

    if((temp = malloc(sizeof(Tree)*500)) == NULL)
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

    TreeNode * temp = NULL;


    if((temp = malloc(sizeof(TreeNode))) == NULL)
    {
        return NULL;
    }

    temp->proID = malloc(sizeof(proID) * 100);
    temp->prodName = malloc(sizeof(prodName) * 100);
    temp->publisher = malloc(sizeof(publisher) * 100);
    temp->genre = malloc(sizeof(genre) * 100);
    temp->price = malloc(sizeof(price) * 100);

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

        TreeNode *tempNode = NULL;
        TreeNode *next = NULL;

        if(treeIsEmpty(theTree) == 1)
        {
            tempNode = createBalancedBinNode(proID, prodName, publisher, genre, taxType, price, quantity);
            theTree->root = tempNode;

        }
        else
        {
                TreeNode *end = NULL;
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
                        next->quantity += quantity;
                        return;
                    }		
                }

                tempNode = createBalancedBinNode(proID, prodName, publisher, genre, taxType, price, quantity);

                if(strcmp(prodName, end->prodName) > 0)
                {
                    end->right = tempNode;
                }
                else if(strcmp(prodName, end->prodName) < 0)
                {
                    end->left = tempNode;
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



