#include "tree.h"
#include "balancedTreeAPI.h"

int main()
{

    int userInput = 0;
    char keyRemove[25];
    char keyInsert[25];

    // Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);

    
    printf("Case 1: Inserting 7 numbers into binary tree and deleting them after\n\n");

    char * data[] = {"5", "3", "6", "12", "2", "20", "11"};

    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0])); 
    for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
    {
        printf("1\n");
        treeInsertNode(tree, data[i]);
    }
    printf("\n\n");
 printf("2\n");
    treePreOrderPrint(tree, &printData);
    printf("\n");
     printf("3\n");
    treeInOrderPrint(tree, &printData);
    printf("\n");
     printf("4\n");
    treePostOrderPrint(tree, &printData);
    printf("\n\n");
     printf("5\n");
    destroyBalancedBinTree(tree);
    printf("\n------------------------------\n\n");

    // while(userInput != 6)
    // {
    //     printf("1. Insert\n2. Remove\n3. pre order\n4. inorder\n5. postorder\n6. exit\n\ntree/> ");
    //     scanf("%d", &userInput);
    //     switch(userInput)
    //     { 
    //         case 1:
    //             printf("insert key: ");
    //             scanf("%s", keyInsert);
    //             treeInsertNode(tree, keyInsert);
    //             // printf("root is now: %s\n", tree->root->data);
    //             break;
    //         case 2:
    //             printf("remove key: ");
    //             scanf("%s", keyRemove);
    //             treeDeleteNode(tree, keyRemove);
    //             // printf("root is now: %s\n", tree->root->data);
    //             break;
    //         case 3:
    //             // printf("idk yet\n");
    //             treePreOrderPrint(tree, &printData);
    //             printf("\n");
    //             break;
    //         case 4:
    //             // printf("idk yet: ");
    //             treeInOrderPrint(tree, &printData);
    //             // scanf("%d", &frequencyCompare);
    //             printf("\n");
    //             break;
    //         case 5:
    //             treePostOrderPrint(tree, &printData);
    //             printf("\n");
    //             break;
    //         case 6:
    //             printf("goodbye!\n"); 
    //             exit(1);
    //             break;
    //     }
    // }
    return 0;
}
