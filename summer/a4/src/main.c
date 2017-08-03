#include "tree.h"
#include "balancedTreeAPI.h"

int main(int argc, char ** argv)
{

    FILE * fp;
    char * items[6];

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("could not find file\n");
        return 0;
    }

    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        int index = 0;
        char * word;

        if(line[strlen(line) - 1] == '\n')
        {
            line[strlent(line) - 1] = '\0';
        }

        word = strtok(line, ",");

        items[index++] = word;

        while((word = strtok(NULL, ",")) != NULL)
        {
            items[index++] = word;
        }

        treeInsertNode(tree, items[0],items[1],items[2],items[3],items[4],items[5], items[6]);


    }

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
