#include "tree.h"
#include "balancedTreeAPI.h"

int main()
{
	
    int userInput = 0;
    // char fileName[256];
    int frequencyCompare = 0;
    char keyRemove[25];
    char keyInsert[25];
    // char keySearch[25];
    
    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);
    // insert(tree, "");

    while(userInput != 5)
    {
        printf("1. Insert\n2. Remove\n3. idk yet\n4. idk yet\n5. Exit\n\ntree/> ");
        scanf("%d", &userInput);
        switch(userInput)
        { 
            case 1:
                printf("insert key: ");
                scanf("%s", keyInsert);
                treeInsertNode(tree, keyInsert);
                printf("root is now: %s\n", tree->root->data);
                break;
            case 2:
                printf("remove key: ");
                scanf("%s", keyRemove);
                treeDeleteNode(tree, keyRemove);
                // printf("root is now: %s\n", tree->root->data);
                break;
            case 3:
                printf("idk yet\n");
                break;
            case 4:
                printf("idk yet: ");
                scanf("%d", &frequencyCompare);
                
                break;
            case 5:
                printf("goodbye!\n"); 
                exit(1);
                break;
        }
    }
    return 0;
}
