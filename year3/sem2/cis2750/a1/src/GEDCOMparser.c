#include "GEDCOMparser.h"
#include "LinkedListAPI.h"
#include "BinarySearchTreeAPI.h"
#include <ctype.h>


Header * initializeHeader(char* source, char* gedcVersion, char* encodingType);
GEDCOMobject * initializeGEDCOMobject();
Family * initializeFamily();
Submitter * initializeSubmitter(char* submitterName, char* address);
Field * initializeOtherField(char* tag, char* value);
Event * initializeEvent(char* type, char* date, char* place);
Individual * initializeIndividual(char* givenName, char* surname);

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

    FILE *fp;
    char line[256];
    char lineStorage[256][500];
    char *tempFieldStorage = malloc(sizeof(char) * 1000);
    char *tempDataStorage = malloc(sizeof(char) * 1000);

    // handles other fields in each event
    // char eventOtherFieldTagStorage[256][500];
    // char eventOtherFieldValueStorage[256][500];

    //handles submitter struct and other fields for submitter struct
    char submitterNameStore[61];
    char submitterAddress[256];
    char submitterOtherFieldTagStorage[256][500];
    char submitterOtherFieldValueStorage[256][500];


    //handles other fields for header file, and other header parts
    char headerOtherFieldTagStorage[256][500];
    char headerOtherFieldValueStorage[256][500];
    char sourceStore[256];
    char gedcVersionStore[64];
    char encodingTypeStore[64];

    //handles inital individual name parts
    char individualGivenNameStorage[256][500];
    char individualSurNameStorage[256][500];

    //handles individual other field structs
    char individualOtherFieldTagStorage[256][500];
    char individualOtherFieldValueStorage[256][500];

    //handles individual event parts including the other field structs
    char individualEventTypeStorage[256][5];
    char individualEventDateStorage[256][500];
    char individualEventPlaceStorage[256][500];
    char individualEventOtherFieldTagStorage[256][500];
    char individualEventOtherFieldValueStorage[256][500];

    //handles family event struct
    char familyEventTypeStorage[256][5];
    char familyEventDateStorage[256][500];
    char familyEventPlaceStorage[256][500];
    char familyEventOtherFieldTagStorage[256][500];
    char familyEventOtherFieldValueStorage[256][500];

    //handles other fields in family struct
    char familyOtherFieldTagStorage[256][500];
    char familyOtherFieldValueStorage[256][500];

    //handles other fields in gedcome object struct
    char gedcomObjectOtherFieldTagStorage[256][500];
    char gedcomObjectOtherFieldValueStorage[256][500];


    int totalIndividualOtherFieldArray[500];
    int totalIndividualEventArray[500];
    int totalIndividualEventOtherFieldArray[500];
    // int totalEventOtherFieldArray[500];
    int totalFamilyOtherFieldArray[500];
    int totalFamilyEventArray[500];
    int totalFamilyEventOtherFieldArray[500];

    int familyHusbandFindArray[500];
    int familyWifeFindArray[500];
    //finds amount of children per family, uses family count to store number
    int familyChildFindCountArray[500];
    //single list that contains all children count numbers in individuals 
    int familyChildFindArray[500];
    int totalIndividualCount = 0;
    // int totalEventCount = 0;
    int totalIndividualOtherFieldCount = 0;
    int totalFamilyOtherFieldCount = 0;
    int totalIndividualEventCount = 0;
    int totalFamilyEventCount = 0;
    int totalIndividualEventOtherFieldCount = 0;
    int totalFamilyEventOtherFieldCount = 0;

    int totalFamilyCount = 0;
    int familyChildCount = 0;

    int individualOtherFieldCount = 0;
    int eventOtherFieldCount = 0;
    int familyOtherFieldCount = 0;
    int headerOtherFieldCount = 0;
    int submitterOtherFieldCount = 0;

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
            if(strcasestr(lineStorage[i], "HEAD"))
            {
                headFlag = 1;
            }
            else if(strcasestr(lineStorage[i], "INDI"))
            {
                indiFlag = 1;
            }
            else if(strcasestr(lineStorage[i], "FAM"))
            {
                famFlag = 1;
            }
            else if(strcasestr(lineStorage[i], "SUBM"))
            {
                submFlag = 1;
            }
            else if(strcasestr(lineStorage[i], "TRLR"))
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
                    if(strcasestr(lineStorage[i], "SOUR"))
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
                    else if(strcasestr(lineStorage[i], "GEDC"))
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
                    else if(strcasestr(lineStorage[i], "CHAR"))
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

                    if(strcasestr(lineStorage[i], "NAME"))
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
                                tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                tempSizeTwo++;
                                j++;
                            }
                        }

                        strcpy(individualGivenNameStorage[totalIndividualCount], tempFieldStorage);
                        strcpy(individualSurNameStorage[totalIndividualCount], tempDataStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        memset(tempDataStorage, '\0', 1000);
                        tempSize = 0;
                        tempSizeTwo = 0;
                    }
                    // else if(strcasestr(lineStorage[i], 'FAMS'))
                    // {

                    // }
                    // else if(strcasestr(lineStorage[i], 'FAMC'))
                    // {

                    // }
                    else
                    {
                        if(strcasestr(lineStorage[i+1], "DATE"))
                        {
                            for(int j = 1; j < strlen(lineStorage[i]); j++)
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                            }

                            strcpy(individualEventTypeStorage[totalIndividualEventCount], tempFieldStorage);
                            memset(tempFieldStorage, '\0', 1000);
                            tempSize = 0;
                            i++;
                            for(int j = 7; j < strlen(lineStorage[i]); j++)
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                            }

                            strcpy(individualEventDateStorage[totalIndividualEventCount], tempFieldStorage);
                            memset(tempFieldStorage, '\0', 1000);
                            tempSize = 0;

                            if(strcasestr(lineStorage[i + 1], "PLAC"))
                            {
                                i++;
                                for(int j = 7; j < strlen(lineStorage[i]); j++)
                                {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                }

                                strcpy(individualEventPlaceStorage[totalIndividualEventCount], tempFieldStorage);
                                memset(tempFieldStorage, '\0', 1000);
                                tempSize = 0;
                            }
                            else
                            {
                                strcpy(individualEventPlaceStorage[totalIndividualEventCount], "");
                            }

                            while(lineStorage[i+1][0] != '1')
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

                                strcpy(individualEventOtherFieldValueStorage[totalIndividualEventOtherFieldCount], tempFieldStorage);
                                strcpy(individualOtherFieldTagStorage[totalIndividualEventOtherFieldCount], tempDataStorage);
                                totalIndividualEventOtherFieldCount++;
                                memset(tempFieldStorage, '\0', 1000);
                                memset(tempDataStorage, '\0', 1000);
                                tempSize = 0;
                                tempSizeTwo = 0;
                                i++;

                            }

                            totalIndividualEventOtherFieldArray[totalIndividualEventCount] = totalIndividualEventOtherFieldCount;
                            totalIndividualEventArray[totalIndividualCount] = totalIndividualEventCount;
                            // eventOtherFieldCount = 0;
                            totalIndividualEventCount++;

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

                            strcpy(individualOtherFieldValueStorage[totalIndividualOtherFieldCount], tempFieldStorage);
                            strcpy(individualOtherFieldTagStorage[totalIndividualOtherFieldCount], tempDataStorage);
                            totalIndividualOtherFieldCount++;
                            memset(tempFieldStorage, '\0', 1000);
                            memset(tempDataStorage, '\0', 1000);
                            tempSize = 0;
                            tempSizeTwo = 0;

                            totalIndividualOtherFieldArray[totalIndividualCount] = totalIndividualOtherFieldCount;
                            // individualOtherFieldCount = 0;
                        }
                    }

                    i++;
                }
                totalIndividualEventArray[totalIndividualCount] = totalIndividualEventCount;
                totalIndividualCount++;
                indiFlag = 0;

            }
            else if(famFlag == 1)
            {
                while(lineStorage[i+1][0] != '0')
                {
                    if(strcasestr(lineStorage[i], "HUSB"))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            while(lineStorage[i][j+1] != '@')
                            {
                                if(isdigit(lineStorage[i][j]))
                                {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                }
                                j++;
                            }
                        }
                        familyHusbandFindArray[totalFamilyCount] = atoi(tempFieldStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        tempSize = 0;
                    }
                    else if(strcasestr(lineStorage[i], "WIFE"))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            while(lineStorage[i][j+1] != '@')
                            {
                                if(isdigit(lineStorage[i][j]))
                                {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                }
                                j++;
                            }
                        }
                        familyWifeFindArray[totalFamilyCount] = atoi(tempFieldStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        tempSize = 0;
                    }
                    else if(strcasestr(lineStorage[i], "CHIL"))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            while(lineStorage[i][j+1] != '@')
                            {
                                if(isdigit(lineStorage[i][j]))
                                {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                }
                                j++;
                            }
                        }
                        familyChildFindArray[familyChildCount] = atoi(tempFieldStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        tempSize = 0;
                        familyChildCount++;
                    }
                    else
                    {
                        if(strcasestr(lineStorage[i+1], "DATE"))
                        {
                            for(int j = 1; j < strlen(lineStorage[i]); j++)
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                            }

                            strcpy(familyEventTypeStorage[totalFamilyEventCount], tempFieldStorage);
                            memset(tempFieldStorage, '\0', 1000);
                            tempSize = 0;
                            i++;
                            for(int j = 7; j < strlen(lineStorage[i]); j++)
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                            }

                            strcpy(familyEventDateStorage[totalFamilyEventCount], tempFieldStorage);
                            memset(tempFieldStorage, '\0', 1000);
                            tempSize = 0;

                            if(strcasestr(lineStorage[i + 1], "PLAC"))
                            {
                                i++;
                                for(int j = 7; j < strlen(lineStorage[i]); j++)
                                {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                }

                                strcpy(familyEventPlaceStorage[totalFamilyEventCount], tempFieldStorage);
                                memset(tempFieldStorage, '\0', 1000);
                                tempSize = 0;
                            }
                            else
                            {
                                strcpy(familyEventPlaceStorage[totalFamilyEventCount], "");
                            }

                            while(lineStorage[i+1][0] != '1')
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

                                strcpy(familyEventOtherFieldValueStorage[totalFamilyEventOtherFieldCount], tempFieldStorage);
                                strcpy(familyEventOtherFieldTagStorage[totalFamilyEventOtherFieldCount], tempDataStorage);
                                totalFamilyEventOtherFieldCount++;
                                memset(tempFieldStorage, '\0', 1000);
                                memset(tempDataStorage, '\0', 1000);
                                tempSize = 0;
                                tempSizeTwo = 0;
                                i++;

                            }
                            totalFamilyEventOtherFieldArray[totalFamilyEventCount] = totalFamilyEventOtherFieldCount;
                            // eventOtherFieldCount = 0;
                            totalFamilyEventCount++;
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

                            strcpy(familyOtherFieldValueStorage[totalFamilyOtherFieldCount], tempFieldStorage);
                            strcpy(familyOtherFieldTagStorage[totalFamilyOtherFieldCount], tempDataStorage);
                            totalFamilyOtherFieldCount++;
                            memset(tempFieldStorage, '\0', 1000);
                            memset(tempDataStorage, '\0', 1000);
                            tempSize = 0;
                            tempSizeTwo = 0;

                            totalFamilyOtherFieldArray[totalFamilyCount] = totalFamilyOtherFieldCount;
                            // individualOtherFieldCount = 0;
                        }
                    }

                    i++;
                }
                familyChildFindCountArray[totalFamilyCount] = familyChildCount;
                totalFamilyCount++;
                // familyChildCount = 0;
                famFlag = 0;

            }
            else if(submFlag == 1)
            {
                while(lineStorage[i+1][0] != '0')
                {
                    if(strcasestr(lineStorage[i], "NAME"))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]) ; j++)
                        {
                            // while(lineStorage[i][j+1] != ' ')
                            // {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            // j++;

                        }

                        strcpy(submitterNameStore, tempFieldStorage);
                        // strcpy(individualSurNameStorage[totalIndividualCount], tempDataStorage);
                        memset(tempFieldStorage, '\0', 1000);
                        // memset(tempDataStorage, '\0', 1000);
                        tempSize = 0;
                        // tempSizeTwo = 0;
                        }
                        else
                        {
                            if(strcasestr(lineStorage[i+1], "PLAC"))
                            {
                                i++;
                                for(int j = 7; j < strlen(lineStorage[i]); j++)
                                {
                                    tempFieldStorage[tempSize] = lineStorage[i][j];
                                    tempSize++;
                                }

                                strcpy(submitterAddress, tempFieldStorage);
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

                                strcpy(submitterOtherFieldValueStorage[submitterOtherFieldCount], tempFieldStorage);
                                strcpy(submitterOtherFieldTagStorage[submitterOtherFieldCount], tempDataStorage);
                                submitterOtherFieldCount++;
                                memset(tempFieldStorage, '\0', 1000);
                                memset(tempDataStorage, '\0', 1000);
                                tempSize = 0;
                                tempSizeTwo = 0;
                            }

                        }

                        i++;
                    }

                    submFlag = 0;

                }
                //where all the creation and insertion happens
                else if(endFlag == 1)
                {

                    GEDCOMobject * tempObject;
                    Individual * tempIndividual;
                    Family * tempFamily;
                    Header * tempHeader;
                    Field * tempOtherField;
                    Event * tempEvent;
                    Submitter * tempSubm;

                    // initializeHeader(char* source, char* gedcVersion, char* encodingType, char* submitterName, char* address)
                    // {
                    // tempObject->submitter = initializeHeader(char* source, char* gedcVersionStore, char* encodingTypeStore, char* submitterNameStore, char* submitterAddress);

                    tempSubm = initializeSubmitter(submitterNameStore, submitterAddress);
                    if(submitterOtherFieldCount != 0)
                    {
                        for(int j = 0; j < submitterOtherFieldCount; j++)
                        {

                            // (char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second));
                            tempOtherField = initializeOtherField(submitterOtherFieldTagStorage[j], submitterOtherFieldValueStorage[j]);
                            insertBack(&tempSubm->otherFields, (void*)tempOtherField);
                            // tempSubm->otherFields = initializeList(printField, deleteField, compareFields);
                        }
                    }

                    tempHeader = initializeHeader(sourceStore, gedcVersionStore, encodingTypeStore);
                    if(headerOtherFieldCount != 0)
                    {
                        for(int j = 0; j < headerOtherFieldCount; j++)
                        {
                            tempOtherField = initializeOtherField(headerOtherFieldTagStorage[j], (void*)headerOtherFieldValueStorage[j]);
                            insertBack(&tempHeader->otherFields, (void*)tempOtherField);
                        }
                    }

                    tempHeader->submitter = tempSubm;
                    tempObject->submitter = tempSubm;

                    if(totalIndividualCount != 0)
                    {

                        for(int j = 0; j < totalIndividualCount; j++)
                        {

                            tempIndividual = initializeIndividual(individualGivenNameStorage[j], individualSurNameStorage[j]);
                            if(totalIndividualEventArray[j] != 0)
                            {
                                if(j == 0)
                                {
                                    for(int k = 0; k < totalIndividualEventArray[j]; k++)
                                    {

                                        // Event * initializeEvent(char* type, char* date, char* place)
                                        tempEvent = initializeEvent(individualEventTypeStorage[k], individualEventDateStorage[k], individualEventPlaceStorage[k]);
                                        if(totalIndividualEventOtherFieldArray[k] != 0)
                                        {
                                            if(k == 0)
                                            {
                                                for(int m = 0; m < totalIndividualEventOtherFieldArray[k]; m++)
                                                {
                                                    tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                                    insertBack(&tempEvent->otherFields, (void*)tempOtherField);
                                                }
                                            }
                                            else
                                            {
                                                for(int m = totalIndividualEventOtherFieldArray[k - 1]; m < totalIndividualEventOtherFieldArray[k] + 1; m++)
                                                {
                                                    tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                                    insertBack(&tempEvent->otherFields, (void*)tempOtherField);   
                                                }
                                            }
                                        }

                                        insertBack(&tempIndividual->events, tempEvent);
                                    }

                                }
                                else
                                {
                                    for(int k = totalIndividualEventArray[j - 1]; k < totalIndividualEventArray[j]+1; k++)
                                    {
                                        tempEvent = initializeEvent(individualEventTypeStorage[k], individualEventDateStorage[k], individualEventPlaceStorage[k]);
                                        if(totalIndividualEventOtherFieldArray[k] != 0)
                                        {
                                            if(k == 0)
                                            {
                                                for(int m = 0; m < totalIndividualEventOtherFieldArray[k]; m++)
                                                {
                                                    tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                                    insertBack(&tempEvent->otherFields, (void*)tempOtherField);
                                                }
                                            }
                                            else
                                            {
                                                for(int m = totalIndividualEventOtherFieldArray[k - 1]; m < totalIndividualEventOtherFieldArray[k] + 1; m++)
                                                {
                                                    tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                                    insertBack(&tempEvent->otherFields, (void*)tempOtherField);   
                                                }
                                            }
                                        }

                                        insertBack(&tempIndividual->events, tempEvent);

                                    }

                                }
                            }


                            if(totalIndividualOtherFieldArray[j] != 0)
                            {
                                if(j == 0)
                                {
                                    for(int k = 0; k < totalIndividualOtherFieldArray[j]; k++)
                                    {

                                        // Event * initializeEvent(char* type, char* date, char* place)
                                        tempOtherField = initializeOtherField(individualOtherFieldTagStorage[k], individualOtherFieldValueStorage[k]);
                                        insertBack(&tempIndividual->otherFields, (void*)tempOtherField);
                                    }
                                }
                                else
                                {
                                    for(int k = totalIndividualOtherFieldArray[j - 1]; k < totalIndividualOtherFieldArray[j] + 1; k++)
                                    {

                                        // Event * initializeEvent(char* type, char* date, char* place)
                                        tempOtherField = initializeOtherField(individualOtherFieldTagStorage[k], individualOtherFieldValueStorage[k]);
                                        insertBack(&tempIndividual->otherFields, (void*)tempOtherField);
                                    }
                                }
                            }
                        }

                    }


                }

                // }

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
        tempIndividual->events = initializeList(printEvent, deleteEvent, compareEvents);
        tempIndividual->families = initializeList(printFamily, deleteFamily, compareFamilies);
        tempIndividual->otherFields = initializeList(printField, deleteField, compareFields);

        return tempIndividual;

    }

    Family * initializeFamily()
    {
        Family* tempFamily;
        tempFamily->children = initializeList(printIndividual, deleteIndividual, compareIndividuals);
        tempFamily->events = initializeList(printEvent, deleteEvent, compareEvents);
        tempFamily->otherFields = initializeList(printField, deleteField, compareFields);

        return tempFamily;

    }

    Header * initializeHeader(char* source, char* gedcVersion, char* encodingType)
    {
        Header* tempHeader;

        strcpy(tempHeader->source, source);
        tempHeader->gedcVersion = atof(gedcVersion);
        tempHeader->otherFields = initializeList(printField, deleteField, compareFields);
        // tempHeader->submitter = initializeSubmitter(submitterName, address);

        return tempHeader;

    }

    GEDCOMobject * initializeGEDCOMobject()
    {
        GEDCOMobject* tempObject;

        tempObject->families = initializeList(printFamily, deleteFamily, compareFamilies);
        tempObject->individuals = initializeList(printIndividual, deleteIndividual, compareIndividuals);

        return tempObject;

    }

    Submitter * initializeSubmitter(char* submitterName, char* address)
    {
        Submitter* tempSubmitter;

        tempSubmitter = malloc(sizeof(submitterName) + (sizeof(char)*(strlen(address)+1)));
        strcpy(tempSubmitter->submitterName, submitterName);
        strcpy(tempSubmitter->address, address);
        tempSubmitter->otherFields = initializeList(printField, deleteField, compareFields);

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
        tempEvent->otherFields = initializeList(printField, deleteField, compareFields);

        return tempEvent;

    }
