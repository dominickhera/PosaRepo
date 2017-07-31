#include "tree.h"
#include "balancedTreeAPI.h"

int main()
{

    printf("Case 1: Inserting 7 numbers into binary tree and deleting them after\n\n");

    char * data[] = {"5", "3", "6", "12", "2", "20", "11"};

    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);

    for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
    {
        treeInsertNode(tree, data[i]);
    }
    printf("\n\n");
    treePreOrderPrint(tree, &printData);
    printf("\n");
    treeInOrderPrint(tree, &printData);
    printf("\n");
    treePostOrderPrint(tree, &printData);
    printf("\n\n");
    destroyBalancedBinTree(tree);
    printf("\n------------------------------\n\n");

    printf("Case 2: Inserting 7 numbers into binary tree, deleting several nodes and deleting the tree after\n\n");

    char * data2[] = {"5", "3", "6", "12", "2", "20", "11"};

    Tree *tree2 = createBalancedBinTree(compareFunction, &free, &copyFunction);

    for(int i = 0; i < (sizeof(data2)/sizeof(data2[0])); i++)
    {
        treeInsertNode(tree2, data2[i]);
    }

    treeDeleteNode(tree2, data2[2]);
    // treeDeleteNode(tree2, data2[1]);
    // // treeDeleteNode(tree2, data2[5]);
    printf("\n\n");
    treePreOrderPrint(tree2, &printData);
    printf("\n");
    treeInOrderPrint(tree2, &printData);
    printf("\n");
    treePostOrderPrint(tree2, &printData);
    printf("\n\n");
    destroyBalancedBinTree(tree2);
    printf("\n------------------------------\n\n");


    printf("Case 3: Inserting 7 numbers into a null binary tree\n\n");

    char * data3[] = {"5", "3", "6", "12", "2", "20", "11"};

    Tree *tree3 = NULL;

    for(int i = 0; i < (sizeof(data3)/sizeof(data3[0])); i++)
    {
        treeInsertNode(tree3, data3[i]);
    }
    printf("\n\n");
    treePreOrderPrint(tree3, &printData);
    printf("\n");
    treeInOrderPrint(tree3, &printData);
    printf("\n");
    treePostOrderPrint(tree3, &printData);
    printf("\n\n");
    destroyBalancedBinTree(tree3);
    printf("\n------------------------------\n\n");

    printf("Case 4: Inserting 0 numbers into a null binary tree\n\n");

    char * data4[] = {" "};

    Tree *tree4 = NULL;

    for(int i = 0; i < (sizeof(data4)/sizeof(data4[0])); i++)
    {
        treeInsertNode(tree4, data4[i]);
    }
    printf("\n\n");
    treePreOrderPrint(tree4, &printData);
    printf("\n");
    treeInOrderPrint(tree4, &printData);
    printf("\n");
    treePostOrderPrint(tree4, &printData);
    printf("\n\n");
    destroyBalancedBinTree(tree4);
    printf("\n------------------------------\n\n");

    printf("Case 5: Inserting letters and numbers into a binary tree\n\n");

    char * data5[] = {"23", "A", "48", "55", "C", "60", "99"};

    Tree *tree5 = createBalancedBinTree(compareFunction, &free, &copyFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0])); 
    for(int i = 0; i < (sizeof(data5)/sizeof(data5[0])); i++)
    {
        treeInsertNode(tree5, data5[i]);
    }
    printf("\n\n");
    treePreOrderPrint(tree5, &printData);
    printf("\n");
    treeInOrderPrint(tree5, &printData);
    printf("\n");
    treePostOrderPrint(tree5, &printData);
    printf("\n\n");
    destroyBalancedBinTree(tree5);
    printf("\n------------------------------\n\n");

    return 0;
}
