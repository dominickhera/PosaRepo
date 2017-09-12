/* 
 * Slightly more complex example - list contents are a simple struct
 */
#include <stdio.h>
#include <string.h>
#include "LinkedListAPI.h"

typedef struct name {
	char* firstName;
	char* lastName;
	unsigned int age;
}Name;

//printFunc will return a string that contains a humanly readable copy of the list contents
char* printFunc(void *toBePrinted){
	
	char* tmpStr;
	Name* tmpName;
	int len;
	
	if (toBePrinted == NULL){
		return NULL;
	}
	
	tmpName = (Name*)toBePrinted;
	
	
	/*
	Length of the string is:
	length of the first and last names+3 spaces+4 chars for "Age:"+1 character for '\0'+20 digits to represent the age
	While we only need 3 digits to represent the human age, if the age is uninitialised, it can be any int value
	An int is 8 bytes on 64-bit system, and needs up to 20 chars to represent it
	If we don't do this, our code will crash if age is uninitialized	
	*/
	len = strlen(tmpName->firstName)+strlen(tmpName->lastName)+28;
	tmpStr = (char*)malloc(sizeof(char)*len);
	
	sprintf(tmpStr, "%s %s Age: %d", tmpName->firstName, tmpName->lastName, tmpName->age);
	
	return tmpStr;
}

//We compare names by last name
int compareFunc(const void *first, const void *second){
	
	Name* tmpName1;
	Name* tmpName2;
	
	if (first == NULL || second == NULL){
		return 0;
	}
	
	tmpName1 = (Name*)first;
	tmpName2 = (Name*)second;
	
	return strcmp((char*)tmpName1->lastName, (char*)tmpName2->lastName);
}

//We need to free the first and last names, and then the Name struct itself
void deleteFunc(void *toBeDeleted){
	
	Name* tmpName;
	
	if (toBeDeleted == NULL){
		return;
	}
	
	tmpName = (Name*)toBeDeleted;
	
	free(tmpName->firstName);
	free(tmpName->lastName);
	free(tmpName);
}

int main(void){
	
	printf("1\n");
	Name* tmpName;
	printf("2\n");
	char tmpStr[100];
	printf("3\n");
	int memLen;
	printf("4\n");
	/* 
	Create the list.  The list is allocated on the stack, and initializeList returns the list struct.
	*/
	List list = initializeList(&printFunc, &deleteFunc, &compareFunc);
	printf("5\n");
	//Populate the list
	for (int i = 0; i < 4; i++){
		printf("6\n");
		tmpName = (Name*)malloc(sizeof(Name));
		printf("7\n");
		tmpName->age = (i+1)*10;
		printf("8\n");
		sprintf(tmpStr, "Name%d", i);
		printf("9\n");	
		memLen = strlen(tmpStr)+2;
		printf("10\n");
		tmpName->firstName = (char*)malloc(sizeof(char)*memLen);
		printf("11\n");
		strcpy(tmpName->firstName, tmpStr);
		printf("12\n");
		
		sprintf(tmpStr, "Lastname%d", i);
		printf("13\n");
		memLen = strlen(tmpStr)+2;
		printf("14\n");
		tmpName->lastName = (char*)malloc(sizeof(char)*memLen);
		printf("15\n");
		strcpy(tmpName->lastName, tmpStr);
		printf("16\n");

	
		insertBack(&list, (void*)tmpName);
		printf("17\n");
		printf("%p\n", tmpName);
		printf("18\n");
	}
		printf("19\n");
	void* elem;
	printf("20\n");
	//Create an iterator - again, the iterator is allocated on the stack
	ListIterator iter = createIterator(list);
printf("21\n");
	/*
	Traverse the list using an iterator.  
	nextElement() returns NULL ones we reach the end of the list
	*/
	while ((elem = nextElement(&iter)) != NULL){
		printf("22\n");
		Name* tmpName = (Name*)elem;
		printf("23\n");
		/*
		We use the printData function that we created to return a string representation 
		of the data associated with the current node
		*/
		char* str = list.printData(tmpName);
		printf("24\n");
		printf("%s\n", str);
		printf("25\n");
		//Since list.printData dynamically allocates the string, we must free it
		free(str);
		printf("26\n");
	}
	printf("27\n");
	printf("28\n");
	
	/*
	Crear list contents - free each node, including its contents
	Since the list is created in the stack, we don't need to free it. 
	*/
	clearList(&list);	
	printf("29\n");
	return 0;		
}











