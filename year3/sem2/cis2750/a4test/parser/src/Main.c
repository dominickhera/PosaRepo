#include "GEDCOMparser.h"
#include "LinkedListAPI.h"
// #include "BinarySearchTreeAPI.h"
#include <ctype.h>

// GEDCOMobject * createObject();

int main() 
{
	GEDCOMobject * testObject;
	 // = createObject();

	// enum eCode errorCodeTest;
	GEDCOMerror errorCodeTest;

	errorCodeTest = createGEDCOM("./uploads/simpleValid.ged", &testObject);


	char * str = printError(errorCodeTest);

	printf("%s\n", str);
	free(str);

	// char * obj = printGEDCOM(testObject);

	// printf("%s\n", obj);
	// free(obj);
	// free(testObject);
	 // deleteGEDCOM(testObject);


	return 0;

}

// GEDCOMobject * createObject()
// {
//         GEDCOMobject* tempObject = malloc(sizeof(GEDCOMobject));

//         tempObject->families = initializeList(printFamily, deleteFamily, compareFamilies);
//         tempObject->individuals = initializeList(printIndividual, deleteIndividual, compareIndividuals);

//         return tempObject;

// }
