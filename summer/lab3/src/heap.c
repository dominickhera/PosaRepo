#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{

    Heap * temp = malloc(sizeof(Heap) * initialSize);
    if(temp == NULL)
    {
        return NULL;
    }

    temp->type = htype;
    temp->lastPosition = NULL;
    temp->initialSize = initialSize;
    temp->destroyDataFP = destroyDataFP;
    temp->printNodeFP = printNodeFP;
    temp->compareFP = compareFP;

    return temp;

}

Node *createHeapNode(void *data)
{
    // create a pointer to a new Node
    //     set new nodes left, right and parent pointers to NULL
    //     set the node's data to the parameter data value
    //     return the pointer to the new Node

    // printf("1\n");
    Node * temp = malloc(sizeof(Node));
    // printf("2\n");
    temp->data = malloc(sizeof(data));
    // printf("3\n");
    if(temp == NULL)
    {
        return NULL;
    }
    // printf("4\n");
    temp->left = NULL;
    // printf("5\n");
    temp->right = NULL;
    // printf("6\n");
    temp->parent = NULL;
    // printf("7\n");
    temp->data = data;
    // printf("8\n");
    // strcpy(temp->data, data);
    // printf("8\n");
    return temp;
}

void insertHeapNode(Heap *heap, void *data)
{
    // create a node from the data
    // locate the next position in the heap (the left most position with no node)
    // add the new node to the located position
    // reheapify the heap to maintain the heap property

    // printf("9\n");
    // printf("10\n");
    

    Node * temp = createHeapNode(data);

    if(heap->lastPosition == NULL)
    {

        temp->parent = temp;
        heap->lastPosition = temp;
        printf("parent: %s\n", temp->parent->data);
    }
    else
    {
        Node * tempParent = heap->lastPosition;
        if(tempParent->left == NULL)
        {
            tempParent->left = temp;
            printf("leftShit: %s\n", tempParent->left->data);
        }
        else if(tempParent->right == NULL)
        {
            tempParent->right = temp;
            printf("rightShit: %s\n", tempParent->right->data);
        }
        else if(tempParent->right != NULL && tempParent->left != NULL)
        {
            tempParent->parent = tempParent->left;
            insertHeapNode(tempParent->parent, data);
            // if(tempParent->left->left == NULL)
            // {
            //     printf("sicko\n");
            // }
        }
        // printf("previous shit is %s\n", tempParent->parent->data);
        // insertHeapNode(tempParent->left, data);
        heap->lastPosition = tempParent;
    }
    // if(heap->lastPosition != NULL)
    // {
    //     Node * tempParent = heap->lastPosition;
    //     printf("previous shit is %s\n", tempParent->data);
    //     temp->parent = tempParent;
    // }
   
    // if(temp->parent == NULL)
    // {
        // temp->parent = temp;
    // }
    // if(tempParent->left == NULL)
    // {
    //     temp->left = temp-;
    //     // printf("lel: %s\n", temp->left->data);
    // }
    // heap->lastPosition = temp;
    // printf("lol: %s\n", temp->parent->data);
    // printf("lel: %s\n", temp->data);
    // heap->initialSize++;
    // printf("11\n");
    // printf("12\n");
    // int tempSize = (heap->initialSize)++;

    // printf("data: %s\n", (char *)temp->data);
    // if(heap->type == 1)
    // {
    // 	printf("13\n");
    //     printf("t1: %d, t2: %d\n", tempSize, getParent(tempSize));
    //     printf("15b\n");
    //     if(heap->heapTable[getParent(tempSize)]->data == NULL)
    //     {
    //         printf("butts\n");
    //         // exit(1);
    //     }
    //     else
    //     {
    //         printf("not butt\n");
    //     }
    //     printf("b1: %s, b2: %s\n", temp->data, heap->heapTable[getParent(tempSize)]->data);
    //     while(strcmp(temp->data, heap->heapTable[getParent(tempSize)]->data) > 0)
    //     {
    //         printf("14b\n");
    //         heap->heapTable[tempSize] = heap->heapTable[getParent(tempSize)];
    //         printf("15\n");
    //         tempSize = getParent(tempSize);
    //         printf("16\n");
    //     }
    //     heap->heapTable[tempSize] = temp;
    //     printf("17\n");
    // //     reheapifyMax(heap, temp);
    // }
    // else
    // {
    // 	printf("14\n");
    // //     reheapifyMin(heap, temp);
    // }
}

void deleteMinOrMax(Heap *heap)
{
    // tempNode = heap->rootNode
    //   heap->rootNode = the node in the "last" position in the tree //the leftmost, bottom node
    //   outOfPlacePtr = heap->rootNode  // keep track of the node that you're moving into place
    //   remove the node in the last position //after copying it into the root
    //   while ( outOfPlacePtr->data is less than either left or right child)  //or greater than for a min heap
    //   {
    //       swap outOfPlacePtr and child with greatest value
    //   }
    //   return tempNode->data

    // Node * temp = heap->

}

// void *getMinOrMax(Heap *heap)
// {

// }

void changeHeapType(Heap *heap)
{

    printf("23\n");
    if(heap->type == 1)
    {
        printf("24\n");
        heap->type = 0;
        printf("25\n");
        reheapifyMin(heap, heap->heapTable[0]);
        printf("26\n");
    }
    else
    {
        printf("27\n");
        heap->type = 1;
        printf("28\n");
        reheapifyMax(heap, heap->heapTable[heap->initialSize]);
    }
    printf("29\n");
}

void deleteHeap(Heap *heap)
{
    for(int i = 0; i < heap->initialSize; i++)
    {
        // deleteMinOrMax(heap->heapTable[i]);
    }
}

void reheapifyMax(Heap * heap, Node * newNode)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }
    printf("15\n");
    Node * swapVar = newNode;
    printf("16\n");
    Node * tempParent = newNode->parent;
    printf("17\n");

    while(strcmp(newNode->data, tempParent->data) > 0)
    {
        printf("18\n");
        swapVar = newNode;
        printf("19\n");
        newNode = tempParent;
        printf("20\n");
        tempParent = swapVar;
        printf("21\n");
        tempParent = newNode->parent;
        printf("22\n");
    }
    printf("23\n");
}

void reheapifyMin(Heap * heap, Node * newNode)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }

    Node * swapVar = newNode;
    Node * tempParent = newNode->parent;


    while(newNode->data < tempParent->data)
    {

        swapVar = newNode;
        newNode = tempParent;
        tempParent = swapVar;
        tempParent = newNode->parent;

    }
}

int getParent(int tempInt)
{

    return ((tempInt - 1)/2);

}

int getLeftChild(int tempInt)
{

    return ((tempInt * 2) + 1);

}

int getRightChild(int tempInt)
{

    return ((tempInt * 2) + 2);

}

