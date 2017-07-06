void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int compareFunction(const void *first,const void *second)
{
	int tempVal = 0;

	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
	{
		return *(int *)first;
	}
	else
	{
		tempVal = *(int *)first;
		*(int *)first = *(int *)second;
		*(int *)second = tempVal;
		return *(int *)first;
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

	Node * swapVar = newNode;
	Node * tempParent = newNode->parent;


	while(newNode->data > tempParent->data)
	{

		swapVar = newNode;
		newNode = tempParent;
		tempParent = swapVar;
		tempParent = newNode->parent;

	}
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
