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

	char * errorCodeReturn = malloc(sizeof(char) * 256);
    if(err == INV_FILE)
    {
        strcpy(errorCodeReturn, "INV_FILE: there’s a problem with file argument - its null, it;’s a empty string, file doesn't exist or - cannot be opened,file doesn't have the.ics extension\n");
    }
    else if(err == INV_GEDCOM)
    {

        strcpy(errorCodeReturn, "INV_VER: the calendar version property is present but malformed\n");
    }
    else if(err == INV_HEADER)
    {

        strcpy(errorCodeReturn, "INV_PRODID: the product ID property is present but malformed\n");
    }
    else if(err == INV_RECORD)
    {

        strcpy(errorCodeReturn, "INV_CAL: the calendar itself is invalid (missing required properties or components, invalid opening - closingtags,etc.)\n");
    }
    else if (err == OTHER)
    {
         strcpy(errorCodeReturn, "OTHER_ERROR: Some other error has happened\n");
    }
    else if(err == OK)
    {
        strcpy(errorCodeReturn, "OK: File parsed successfully.\n");
    }
    else
    {
        strcpy(errorCodeReturn, "error code not found\n");
    }

    return errorCodeReturn;

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
