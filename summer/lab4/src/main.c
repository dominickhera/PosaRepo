#include "tree.h"
#include "balancedTreeAPI.h"

int main()
{
	
    int userInput = 0;
    // char fileName[256];
    // int frequencyCompare = 0;
    char keyRemove[25];
    char keyInsert[25];
    // char keySearch[25];
    
    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);
    // insert(tree, "");

    while(userInput != 6)
    {
        printf("1. Insert\n2. Remove\n3. pre order\n4. inorder\n5. postorder\n6. exit\n\ntree/> ");
        scanf("%d", &userInput);
        switch(userInput)
        { 
            case 1:
                printf("insert key: ");
                scanf("%s", keyInsert);
                treeInsertNode(tree, keyInsert);
                // printf("root is now: %s\n", tree->root->data);
                break;
            case 2:
                printf("remove key: ");
                scanf("%s", keyRemove);
                treeDeleteNode(tree, keyRemove);
                // printf("root is now: %s\n", tree->root->data);
                break;
            case 3:
                // printf("idk yet\n");
                treePreOrderPrint(tree, &printData);
                printf("\n");
                break;
            case 4:
                // printf("idk yet: ");
                treeInOrderPrint(tree, &printData);
                // scanf("%d", &frequencyCompare);
                printf("\n");
                break;
            case 5:
                treePostOrderPrint(tree, &printData);
                printf("\n");
                break;
            case 6:
                printf("goodbye!\n"); 
                exit(1);
                break;
        }
    }
    return 0;
}
