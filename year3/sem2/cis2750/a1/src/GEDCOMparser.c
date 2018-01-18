#include "GEDCOMparser.h"
#include "LinkedListAPI.h"
#include "BinarySearchTreeAPI.h"

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

    FILE *fp;
    char line[256];
    char lineStorage[256][500];
    char gedcVersionStore[128];
    char sourceStore[128];
    char encodingStore[64];
    int count = 0;


    if(fileName != NULL && fileName[0] != '\0')
    {
        if(strcasestr(fileName, ".ged"))
        {
            if((fp = fopen(fileName, "r")))
            {
                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    strcpy(lineStorage[count], line);
                    count++;
                }

                fclose(fp);
            }
            else
            {
                GEDCOMerror err;
                err.type = INV_FILE;
                err.line = count;
                return err;
            }
        }
        else
        {
            GEDCOMerror err;
            err.type = INV_FILE;
            err.line = count;
            return err;
        }
    }
    else
    {
        GEDCOMerror err;
        err.type = INV_FILE;
        err.line = count;
        return err;
    }


    for(int i = 0; i < count; i++)
    {

    }



}

char* printGEDCOM(const GEDCOMobject* obj)
{

    char * gedcomReturn = malloc(sizeof(char) * 1000);
    if(obj != NULL)
    {

    }

}

void deleteGEDCOM(GEDCOMobject* obj)
{

}

char* printError(GEDCOMerror err)
{

    char * errorCodeReturn = malloc(sizeof(char) * 256);
    if(err.type == INV_FILE)
    {
        strcpy(errorCodeReturn, "INV_FILE: there’s a problem with file argument - its null, it;’s a empty string, file doesn't exist or - cannot be opened,file doesn't have the.ics extension\n");
    }
    else if(err.type == INV_GEDCOM)
    {

        strcpy(errorCodeReturn, "INV_GEDCOM: the calendar version property is present but malformed\n");
    }
    else if(err.type == INV_HEADER)
    {

        strcpy(errorCodeReturn, "INV_HEADER: the product ID property is present but malformed\n");
    }
    else if(err.type == INV_RECORD)
    {

        strcpy(errorCodeReturn, "INV_Record: the calendar itself is invalid (missing required properties or components, invalid opening - closingtags,etc.)\n");
    }
    else if (err.type == OTHER)
    {
        strcpy(errorCodeReturn, "OTHER: Some other error has happened\n");
    }
    else if(err.type == OK)
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
