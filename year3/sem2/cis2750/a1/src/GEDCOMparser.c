#include "GEDCOMparser.h"
#include "LinkedListAPI"
#include "BinarySearchTreeAPI.h"

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

}

char* printGEDCOM(const GEDCOMobject* obj)
{

}

void deleteGEDCOM(GEDCOMobject* obj)
{

}

char* printError(GEDCOMerror err)
{

}

Individual* findPerson(const GEDCOMobject* familyRecord, bool (*compare)(const void* first, const void* second), const void* person)
{

}

List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{

}


//************************************************************************************************************

//****************************************** List helper functions *******************************************
void deleteEvent(void* toBeDeleted)
{

}

int compareEvents(const void* first,const void* second)
{

}

char* printEvent(void* toBePrinted)
{

}

void deleteIndividual(void* toBeDeleted)
{

}

int compareIndividuals(const void* first,const void* second)
{

}

char* printIndividual(void* toBePrinted)
{

}

void deleteFamily(void* toBeDeleted)
{

}

int compareFamilies(const void* first,const void* second)
{

}

char* printFamily(void* toBePrinted)
{

}

void deleteField(void* toBeDeleted)
{

}

int compareFields(const void* first,const void* second)
{

}

char* printField(void* toBePrinted)
{

}