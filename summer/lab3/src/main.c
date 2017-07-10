#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "functions.h"

int main()
{


    printf("Case 1: Inserting 7 numbers into max heap and deleting them after\n\n");

    char * data[] = {"23", "40", "48", "55", "42", "60", "99"};

    Heap * heapThing = createHeap(7, MAX_HEAP, &free, &printData, &compareFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0]));	
    for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
    {
        insertHeapNode(heapThing, data[i]);
    }
    printf("\n\n");

    printHeap(heapThing);
    printf("\n\n");
    deleteHeap(heapThing);
    printf("\n------------------------------\n\n");

    printf("Case 2: Inserting 7 numbers into min heap and deleting them after\n\n");

    char * data2[] = {"23", "40", "48", "55", "42", "60", "99"};

    Heap * heapThing2 = createHeap(7, MIN_HEAP, &free, &printData, &compareFunction);

    for(int i = 0; i < (sizeof(data2)/sizeof(data2[0])); i++)
    {
        insertHeapNode(heapThing2, data2[i]);
    }
    printf("\n\n");

    printHeap(heapThing2);
    printf("\n\n");
    deleteHeap(heapThing2);
    printf("\n\n------------------------------\n\n");

    printf("Case 3: Inserting 7 numbers into max heap, changing the heap to min heap and deleting them after\n\n");

    char * data3[] = {"23", "40", "48", "55", "42", "60", "99"};

    Heap * heapThing3 = createHeap(7, MAX_HEAP, &free, &printData, &compareFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0]));	
    for(int i = 0; i < (sizeof(data3)/sizeof(data3[0])); i++)
    {
        insertHeapNode(heapThing3, data3[i]);
    }
    printf("\n\n");
    changeHeapType(heapThing3);
    printHeap(heapThing3);
    printf("\n\n");
    // deleteMinOrMax(heapThing);
    deleteHeap(heapThing3);
    printf("\n------------------------------\n\n");


    printf("Case 4: Inserting 7 numbers into a null max heap\n\n");

    char * data4[] = {"23", "40", "48", "55", "42", "60", "99"};

    Heap * heapThing4 = NULL;
    // createHeap(7, MAX_HEAP, &free, &printData, &compareFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0]));	
    for(int i = 0; i < (sizeof(data4)/sizeof(data4[0])); i++)
    {
        insertHeapNode(heapThing4, data4[i]);
    }
    printf("\n\n");
    changeHeapType(heapThing4);
    printHeap(heapThing4);
    printf("\n\n");
    // deleteMinOrMax(heapThing);
    deleteHeap(heapThing4);
    printf("\n------------------------------\n\n");

    printf("Case 5: Inserting 0 numbers into a null max heap\n\n");

    char * data5[] = {" "};

    Heap * heapThing5 = NULL;
    // createHeap(7, MAX_HEAP, &free, &printData, &compareFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0]));	
    for(int i = 0; i < (sizeof(data5)/sizeof(data5[0])); i++)
    {
        insertHeapNode(heapThing4, data5[i]);
    }
    printf("\n\n");
    changeHeapType(heapThing5);
    printHeap(heapThing5);
    printf("\n\n");
    // deleteMinOrMax(heapThing);
    deleteHeap(heapThing5);
    printf("\n------------------------------\n\n");

    printf("Case 6: Inserting letters and numbers into a max heap\n\n");

    char * data6[] = {"23", "A", "48", "55", "C", "60", "99"};

    Heap * heapThing6 = createHeap(7, MAX_HEAP, &free, &printData, &compareFunction);

    // printf("size: %lu\n", sizeof(data)/sizeof(data[0]));	
    for(int i = 0; i < (sizeof(data6)/sizeof(data6[0])); i++)
    {
        insertHeapNode(heapThing6, data6[i]);
    }
    printf("\n\n");
    changeHeapType(heapThing6);
    printHeap(heapThing6);
    printf("\n\n");
    // deleteMinOrMax(heapThing);
    deleteHeap(heapThing6);
    printf("\n------------------------------\n\n");



    // printf("butts\n");
    // printShit(heapThing);
    // changeHeapType(heapThing);


    return 0;

}
