#include "tree.h"
#include "balancedTreeAPI.h"

int main(int argc, char ** argv)
{

    FILE * fp;

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("could not find file\n");
        return 0;
    }
    
    // char * data[] = {"5", "3", "6", "12", "2", "20", "11"};

    // Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);

    // for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
    // {
    //     treeInsertNode(tree, data[i]);
    // }
    // printf("\n\n");
    // treePreOrderPrint(tree, &printData);
    // printf("\n");
    // treeInOrderPrint(tree, &printData);
    // printf("\n");
    // treePostOrderPrint(tree, &printData);
    // printf("\n\n");
    // destroyBalancedBinTree(tree);

    return 0;
}
