#include "GEDCOMparser.h"
#include "LinkedListAPI.h"
#include "BinarySearchTreeAPI.h"


Header * initializeHeader(char* source, char* gedcVersion, char* encodingType, char* submitterName, char* address);
// GEDCOMobject * initializeGEDCOMobject();
Submitter * initializeSubmitter(char* submitterName, char* address);
Field * initializeOtherField(char* tag, char* value);
Event * initializeEvent(char* type, char* date, char* place);

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

    FILE *fp;
    char line[256];
    char lineStorage[256][500];
    char *tempFieldStorage = malloc(sizeof(char) * 1000);
    char *tempDataStorage = malloc(sizeof(char) * 1000);
    char eventOtherFieldTagStorage[256][500];
    char eventOtherFieldValueStorage[256][500];
    char submitterOtherFieldTagStorage[256][500];
    char submitterOtherFieldValueStorage[256][500];
    char headerOtherFieldTagStorage[256][500];
    char headerOtherFieldValueStorage[256][500];
    char individualOtherFieldTagStorage[256][500];
    char individualOtherFieldValueStorage[256][500];
    char familyOtherFieldTagStorage[256][500];
    char familyOtherFieldValueStorage[256][500];
    char gedcomObjectOtherFieldTagStorage[256][500];
    char gedcomObjectOtherFieldValueStorage[256][500];
    char individualGivenNameStorage[256][500];
    char individualSurNameStorage[256][500];
    char sourceStore[256];
    char gedcVersionStore[64];
    char encodingTypeStore[64];
    char submitterNameStore[61];
    char submitterAddress[256];
    int totalIndividualOtherFieldArray[500];
    int totalEventOtherFieldArray[500];
    int totalFamilyOtherFieldArray[500];
    int totalIndividaulCount = 0;
    int individualOtherFieldCount = 0;
    int eventOtherFieldCount = 0;
    int familyOtherFieldCount = 0;
    int headerOtherFieldCount = 0;
    int tempSize = 0;
    int tempSizeTwo = 0;
    int headFlag = 0;
    int indiFlag = 0;
    int submFlag = 0;
    int famFlag = 0;
    int endFlag = 0;

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

        //start of thing
        if(lineStorage[i][0] == '0')
        {
            if(strcasestr(lineStorage[i], 'HEAD'))
            {
                headFlag = 1;
            }
            else if(strcasestr(lineStorage[i], 'INDI'))
            {
                indiFlag = 1;
            }
            else if(strcasestr(lineStorage[i], 'FAM'))
            {
                famFlag = 1;
            }
            else if(strcasestr(lineStorage[i], 'SUBM'))
            {
                submFlag = 1;
            }
            else if(strcasestr(lineStorage[i], 'TRLR'))
            {
                endFlag = 1;
            }
        }
        //stuff in thing
        else
        {
            if(headFlag == 1)
            {
                while(lineStorage[i+1][0] != '0')
                {
                    if(strcasestr(lineStorage[i], 'SOUR'))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {

                                // while(lineStorage[i][j+1] != '\0')
                                // {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                    // j++;
                                // }
                        }


                        strcpy(sourceStore, tempFieldStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        tempSize = 0;
                    }
                    else if(strcasestr(lineStorage[i], 'GEDC'))
                    {
                        i++;
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;   
                        }

                        strcpy(gedcVersionStore, tempFieldStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        tempSize = 0;

                    }
                    else if(strcasestr(lineStorage[i], 'CHAR'))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;   
                        }

                        strcpy(encodingTypeStore, tempFieldStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        tempSize = 0;
                    }
                    else
                    {

                        for(int j = 1; j < strlen(lineStorage[i]); j++)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            if(lineStorage[i][j+1] == ' ')
                            {
                                while(lineStorage[i][j+1] != '\0')
                                {
                                    tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                    tempSizeTwo++;
                                }
                            }
                        }

                        strcpy(headerOtherFieldTagStorage[headerOtherFieldCount], tempFieldStorage);
                        strcpy(headerOtherFieldValueStorage[headerOtherFieldCount], tempDataStorage);
                        headerOtherFieldCount++;
                        memset(tempFieldStorage, '\0', 1000);
                        memset(tempDataStorage, '\0', 1000);
                        tempSize = 0;
                        tempSizeTwo = 0;

                    }

                    i++;
                }

                headFlag = 0;
            }
            else if(indiFlag == 1)
            {
                while(lineStorage[i+1][0] != '0')
                {
                    
                    if(strcasestr(lineStorage[i], 'NAME'))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]) ; j++)
                        {
                            while(lineStorage[i][j+1] != ' ')
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                                j++;
                            }

                            j++;
                            while(lineStorage[i][j+1] != '/')
                            {
                                tempDataStorage[tempSizeTwo] lineStorage[i][j];
                                tempSizeTwo++;
                                j++;
                            }
                        }

                        strcpy(individualGivenNameStorage[totalIndividaulCount], tempFieldStorage);
                        strcpy(individualSurNameStorage[totalIndividaulCount], tempDataStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        memset(tempDataStorage, '\0', 1000);
                        tempSize = 0;
                        tempSizeTwo = 0;
                    }
                    // else if(strcasestr(lineStorage[i], ''))
                    i++;
                }

                indiFlag = 0;

            }
            else if(famFlag == 1)
            {
                while(lineStorage[i+1][0] != '0')
                {
                    
                    
                    i++;
                }

                famFlag = 0;

            }
            else if(submFlag == 1)
            {
              
                while(lineStorage[i+1][0] != '0')
                {
                    

                    i++;
                }

                submFlag = 0;

            }

        }

    }

    GEDCOMerror err;
    err.type = OK;
    err.line = count;
    return err;



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

Individual * initializeIndividual(char* givenName, char* surname)
{
    Individual* tempIndividual;

    tempIndividual->givenName = malloc(sizeof(givenName));
    strcpy(tempIndividual->givenName, givenName);
    tempIndividual->surname = malloc(sizeof(surname));
    strcpy(tempIndividual->surname, surname);

    return tempIndividual;

}

// Family * initializeFamily()
// {
//     Family* tempFamily;

// }

Header * initializeHeader(char* source, char* gedcVersion, char* encodingType, char* submitterName, char* address)
{
    Header* tempHeader;

    strcpy(tempHeader->source, source);
    tempHeader->gedcVersion = atof(gedcVersion);
    tempHeader->submitter = initializeSubmitter(submitterName, address);

    return tempHeader;

}

// GEDCOMobject * initializeGEDCOMobject()
// {
//     GEDCOMobject* tempObject;

// }

Submitter * initializeSubmitter(char* submitterName, char* address)
{
    Submitter* tempSubmitter;

    tempSubmitter = malloc(sizeof(submitterName) + (sizeof(char)*(strlen(address)+1)));
    strcpy(tempSubmitter->submitterName, submitterName);
    strcpy(tempSubmitter->address, address);

    return tempSubmitter;


}

Field * initializeOtherField(char* tag, char* value)
{
    Field* tempField;

    tempField->tag = malloc(sizeof(tag));
    strcpy(tempField->tag, tag);
    tempField->value = malloc(sizeof(value));
    strcpy(tempField->value, value);

    return tempField;

}

Event * initializeEvent(char* type, char* date, char* place)
{
    Event* tempEvent;

    strcpy(tempEvent->type, type);
    tempEvent->date = malloc(sizeof(date));
    tempEvent->place = malloc(sizeof(place));

    return tempEvent;

}





