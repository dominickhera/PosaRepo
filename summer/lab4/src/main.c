#include "tree.h"
#include "balancedTreeAPI.h"

int main()
{
	
    int userInput = 0;
    char fileName[256];
    int frequencyCompare = 0;
    char keyRemove[25];
    char keyInsert[25];
    // char keySearch[25];
    
    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);
    // insert(tree, "");

    while(userInput != 7)
    {
        printf("1. Initialization\n2. Find\n3. Insert\n4. Remove\n5. Check Height and Size\n6. Find All (above a given frequency)\n7. Exit\n\navl/> ");
        scanf("%d", &userInput);
        switch(userInput)
        { 
            case 1:

                printf("filename: ");
                scanf("%s", fileName); 
               	
                break;
            case 2:
                printf("find key: ");
                
                break;
            case 3:
                printf("insert key: ");
                scanf("%s", keyInsert);
                treeInsertNode(tree, keyInsert);
                break;
            case 4:
                printf("remove key: ");
                scanf("%s", keyRemove);
                treeDeleteNode(tree, keyRemove);
                // delete(tree, keyRemove);
                break;
            case 5:
                printf("could not figure out how to implement in time.\n");
                break;
            case 6:
                printf("frequency: ");
                scanf("%d", &frequencyCompare);
                
                break;
            case 7:
                printf("goodbye!\n"); 
                exit(1);
                break;
        }
    }
    return 0;
}
