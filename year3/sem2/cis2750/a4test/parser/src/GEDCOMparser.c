#include "GEDCOMparser.h"
#include "LinkedListAPI.h"
// #include "BinarySearchTreeAPI.h"
#include <ctype.h>


Header * initializeHeader(char* source, char* gedcVersion, char* encodingType);
GEDCOMobject * initializeGEDCOMobject();
Family * initializeFamily();
Submitter * initializeSubmitter(char* submitterName, char* address);
Field * initializeOtherField(char* tag, char* value);
Event * initializeEvent(char* type, char* date, char* place);
Individual * initializeIndividual(char* givenName, char* surname);
bool customIndividualCompareFunction(const void* first, const void* second);
List getChild(const GEDCOMobject* familyRecord, const Individual* person, List list);
char* initFilesToJSON(char* fileName);
char* grabIndList(char* fileName);
void addIndividualWrapper(char* fileName, char* IndJSON);
void createGEDCOMWrapper(char* str, char * fileName);

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

    FILE *fp;
    char line[256];
    char lineStorage[1000][256];
    char *tempFieldStorage;
    tempFieldStorage = (char*)malloc(sizeof(char) * 256);
    char *tempDataStorage;
    tempDataStorage = (char*)malloc(sizeof(char) * 256);

    // handles other fields in each event
    // char eventOtherFieldTagStorage[256][500];
    // char eventOtherFieldValueStorage[256][500];

    //handles submitter struct and other fields for submitter struct
    char submitterNameStore[61];
    char submitterAddress[256];
    char submitterOtherFieldTagStorage[500][500];
    char submitterOtherFieldValueStorage[500][500];


    //handles other fields for header file, and other header parts
    char headerOtherFieldTagStorage[1000][500];
    char headerOtherFieldValueStorage[1000][500];
    char sourceStore[249];
    char gedcVersionStore[64];
    char encodingTypeStore[64];

    //handles inital individual name parts
    char individualGivenNameStorage[500][500];
    char individualSurNameStorage[500][500];

    //handles individual other field structs
    char individualOtherFieldTagStorage[500][500];
    char individualOtherFieldValueStorage[500][500];

    //handles individual event parts including the other field structs
    char individualEventTypeStorage[500][500];
    char individualEventDateStorage[500][500];
    char individualEventPlaceStorage[500][500];
    char individualEventOtherFieldTagStorage[500][500];
    char individualEventOtherFieldValueStorage[500][500];

    //handles family event struct
    char familyEventTypeStorage[500][5];
    char familyEventDateStorage[500][500];
    char familyEventPlaceStorage[500][500];
    char familyEventOtherFieldTagStorage[500][500];
    char familyEventOtherFieldValueStorage[500][500];

    //handles other fields in family struct
    char familyOtherFieldTagStorage[500][500];
    char familyOtherFieldValueStorage[500][500];

    //handles other fields in gedcome object struct
    // char gedcomObjectOtherFieldTagStorage[256][500];
    // char gedcomObjectOtherFieldValueStorage[256][500];


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

    // int individualOtherFieldCount = 0;
    // int eventOtherFieldCount = 0;
    // int familyOtherFieldCount = 0;
    int headerOtherFieldCount = 0;
    int submitterOtherFieldCount = 0;

    int tempSize = 0;
    int tempSizeTwo = 0;
    // int 
    int headFlag = 0;
    // int indiFlag = 0;
    int submFlag = 0;
    int sourceFlag = 0;
    int versionFlag = 0;
    int encordingFlag = 0;
    int subRefFlag = 0;
    // int testFlag = 0;
    // int famFlag = 0;
    // int endFlag = 0;
    // int printCount = 0;
    // int subPrintCount = 0;
    int count = 0;


    if(fileName != NULL && fileName[0] != '\0')
    {
        if(strcasestr(fileName, ".ged"))
        {
            if((fp = fopen(fileName, "r")) != NULL)
            {
                // printf("filename is %s\n", fileName);
                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    if(line[strlen(line) - 1] == '\n')
                    {
                        line[strlen(line) - 1] = '\0';
                    }
                    // if(line[strcspn(line, "\r\n")])
                    // {
                    //     // if(line[strlen(line) - 1] == '\r')
                    //     // {
                    //     line[strcspn(line, "\r\n")] = 0;
                    // }
                    // // }
                    // else if(line[strcspn(line, "\n\r")])
                    // {
                    //     //     // if(line[strlen(line) - 1] == '\n')
                    //     //     // {
                    //     line[strcspn(line, "\n\r")] = 0;
                    // }
                    // // }
                    // else if(line[strcspn(line, "\n")])
                    // {
                    //     line[strlen(line) - 1] = '\n';
                    // }
                    // else if(line[strcspn(line, "\r")])
                    // {
                    //     // printf("line: %s\n", line);
                    //     // testFlag = 1;
                    //     line[strcspn(line, "\r")] = 0;
                    //     // printf("line: %s\n", line);
                    //     // line[strlen(line) - 2] = '\0';
                    //     // line[strlen(line) - 1] = '\n';

                    // }

                    if(strlen(line) > 255)
                    {
                        GEDCOMerror err;
                        err.type = INV_RECORD;
                        err.line = -1;
                        return err;
                    }
                    strcpy(lineStorage[count], line);

                    count++;
                }

                fclose(fp);
            }
            else
            {
                free(tempFieldStorage);
                free(tempDataStorage);

                GEDCOMerror err;
                err.type = INV_FILE;
                err.line = -1;
                return err;
            }
        }
        else
        {
            free(tempFieldStorage);
            free(tempDataStorage);

            GEDCOMerror err;
            err.type = INV_FILE;
            err.line = -1;
            return err;
        }
    }
    else
    {
        free(tempFieldStorage);
        free(tempDataStorage);

        GEDCOMerror err;
        err.type = INV_FILE;
        err.line = -1;
        return err;
    }
    // }
    // else
    //     {
    //         GEDCOMerror err;
    //         err.type = INV_FILE;
    //         err.line = count;
    //         return err;
    //     }

for(int i = 0; i < 500; i++)
{
    familyHusbandFindArray[i] = -1;
    familyWifeFindArray[i] = -1;
}
*obj = initializeGEDCOMobject();
GEDCOMobject * tempObject = *obj;
// GEDCOMobject * tempObject = initializeGEDCOMobject();

if(lineStorage[0][0] != '0')
{
    GEDCOMerror err;
    err.type = INV_HEADER;
    err.line = -1;
    return err;
}

for(int i = 0; i < count; i++)
{
    // printf("count is %d\n", count);
    // printf("line[%d]: <%s>\n", i, lineStorage[i]);
    //start of thing
    // if(lineStorage[i][0] != '0')
    // {
    // GEDCOMerror err;
    // err.type = INV_HEADER;
    // err.line = -1;
    // return err;
    // }
    if(lineStorage[i][0] == '0')
    {
        // printf("line[%d]: <%s>\n", i, lineStorage[i]);
        if(strcasestr(lineStorage[i], "HEAD"))
        {
            // printf("head found\n");
            headFlag = 1;
            // i++;
            while(lineStorage[i+1][0] != '0')
            {
                if((i+1) >= count)
                {
                    GEDCOMerror err;
                    err.type = INV_GEDCOM;
                    err.line = -1;
                    return err;
                }
                // if(lineStorage[i][0] = '0')
                // if(testFlag == 1)
                // {
                    // printf("line[%d]: %s\n", i, lineStorage[i]);
                // }
                // if(atoi(&lineStorage[i+1][0]) > atoi(&lineStorage[i][0]) + 1 && atoi(&lineStorage[i+1][0]) != atoi(&lineStorage[i][0]) && atoi(&lineStorage[i+1][0]) != 0)
                // {
                //     GEDCOMerror err;
                //     err.type = INV_RECORD;
                //     err.line = -1;
                //     return err;
                // }
                i++;

                // printf("line[%d]<%s>\n",i, lineStorage[i]);
                // printf("first item of line is <%c>\n", lineStorage[i][0]);
                if(strcasestr(lineStorage[i], "SOUR"))
                {
                    sourceFlag = 1;
                    for(int j = 7; j < strlen(lineStorage[i]); j++)
                    {
                        // if(lineStorage[i][j] == 'R')
                        // {
                        // j+=2;
                        // while(isalpha(lineStorage[i][j]) != 0)
                        // while(lineStorage[i][j] != lineStorage[i][strlen(lineStorage[i])])
                        //{
                        printf("lineStorage char: %c\n", lineStorage[i][j]);
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        //    j++;
                        //}
                        //}
                    }

                    if(strlen(tempFieldStorage) == 0 )
                    {
                        GEDCOMerror err;
                        err.type = INV_HEADER;
                        err.line = -1;
                        return err;
                    }
                    strcpy(sourceStore, tempFieldStorage);
                    printf("sourceStore: <%s>\n", tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;
                }
                else if(strcasestr(lineStorage[i], "GEDC"))
                {
                    versionFlag = 1;
                    // i++;
                    // printf("line next starts with %c\n", lineStorage[i+1][0]);
                    if(lineStorage[i+1][0] != '2')
                    {
                        // printf("line should return error\n");
                        GEDCOMerror err;
                        err.type = INV_RECORD;
                        err.line = -1;
                        return err;
                    }
                    i++;
                    for(int j = 7; j < strlen(lineStorage[i]); j++)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;   
                    }
                    // printf("gedc: <%s>\n", tempFieldStorage);
                    strcpy(gedcVersionStore, tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;

                }
                else if(strcasestr(lineStorage[i], "CHAR"))
                {
                    encordingFlag = 1;
                    for(int j = 7; j < strlen(lineStorage[i]); j++)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;   
                    }
                    if(strlen(tempFieldStorage) == 0 )
                    {
                        GEDCOMerror err;
                        err.type = INV_HEADER;
                        err.line = -1;
                        return err;
                    }
                    // printf("char: <%s>\n", tempFieldStorage);
                    strcpy(encodingTypeStore, tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;
                }
                else if(lineStorage[i][0] == '1')
                {

                    if(strcasestr(lineStorage[i], "SUBM"))
                    {
                        subRefFlag = 1;
                    }

                    for(int j = 0; j < strlen(lineStorage[i]); j++)
                    {
                        // printf("char1[%d]: %c\n", j, lineStorage[i][j]);
                        if(isalpha(lineStorage[i][j+1]) != 0)
                        {
                            // printf("b00ty j is %d\n",j);
                            while(isalpha(lineStorage[i][j]) != 0)
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                                j++;
                                // printf("char2[%d]: %c\n", j, lineStorage[i][j]);
                                // printf(";\n");
                                // }
                                // printf("lolcooooo j is %d\n",j);
                                if(lineStorage[i][j] == ' ')
                                {
                                    j++;
                                    // printf("ay lmao\n");
                                    // printf("now j is %d\n", j);
                                    // printf("char3[%d]: %c\n", j, lineStorage[i][j]);
                                    //     j+=2;
                                    while(j < strlen(lineStorage[i]))
                                        // while(lineStorage[i][j+1] != '\0')
                                    {
                                        // printf("char4[%d]: %c\n", j, lineStorage[i][j]);
                                        tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                        tempSizeTwo++;
                                        j++;
                                    }
                                }
                        }
                    }
                }

                if(strlen(tempFieldStorage) == 0 || strlen(tempDataStorage) == 0)
                {
                    // printf("header tag: <%s>, value: <%s>\n", tempFieldStorage, tempDataStorage);
                    GEDCOMerror err;
                    err.type = INV_HEADER;
                    err.line = -1;
                    return err;
                }
                else if(strlen(tempDataStorage) > 255)
                {
                    GEDCOMerror err;
                    err.type = INV_HEADER;
                    err.line = -1;
                    return err;
                }
                // if(testFlag == 1)
                // {
                    // printf("header tag: <%s>, value: <%s>\n", tempFieldStorage, tempDataStorage);
                // }
                strcpy(headerOtherFieldTagStorage[headerOtherFieldCount], tempFieldStorage);
                strcpy(headerOtherFieldValueStorage[headerOtherFieldCount], tempDataStorage);
                headerOtherFieldCount++;
                memset(tempFieldStorage, '\0', 256);
                memset(tempDataStorage, '\0', 256);
                tempSize = 0;
                tempSizeTwo = 0;

            }

            // i++;
        }
    }
    else if(strcasestr(lineStorage[i], "INDI"))
    {
        // printf("indi found\n");
        // indiFlag = 1;
        // i++;
        // printf("indi found %s\n", lineStorage[i]);
        while(lineStorage[i + 1][0] != '0')
        {


            // if(lineStorage[i][0] == '0')
            // {


            i++;
            // if((i+1) >= count)
            // {
            //     GEDCOMerror err;
            //     err.type = INV_GEDCOM;
            //     err.line = -1;
            //     return err;
            // }
            // if(atoi(&lineStorage[i+1][0]) >= atoi(&lineStorage[i][0]) + 2 && atoi(&lineStorage[i+1][0]) != atoi(&lineStorage[i][0]) && atoi(&lineStorage[i+1][0]) != 0)
            // {
            //     GEDCOMerror err;
            //     err.type = INV_RECORD;
            //     err.line = -1;
            //     return err;
            // }

            if(strcasestr(lineStorage[i], "NAME"))
            {

                for(int j = 0; j < strlen(lineStorage[i]); j++)
                {
                    // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                    if(lineStorage[i][j] == 'E')
                    {
                        // printf("end of name\n");
                        j+=2;
                        while(isalpha(lineStorage[i][j]) != 0)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                            // printf(";\n");



                            if(lineStorage[i][j] == ' ')
                            {
                                j+=2;
                                while(lineStorage[i][j] != '/')
                                {
                                    tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                    tempSizeTwo++;
                                    j++;
                                }
                            }

                        }
                    }
                }



                // printf("given name: <%s>\nsurname: <%s>\n", tempFieldStorage, tempDataStorage);

                strcpy(individualGivenNameStorage[totalIndividualCount], tempFieldStorage);
                strcpy(individualSurNameStorage[totalIndividualCount], tempDataStorage);
                memset(tempFieldStorage, '\0', 256);
                memset(tempDataStorage, '\0', 256);
                tempSize = 0;
                tempSizeTwo = 0;
            }
            else
            {
                // printf("other field for indi in %s\n", fileName);
                if((strcasestr(lineStorage[i+1], "DATE")))
                {
                    // printf("(bawe111r)\n" );
                    for(int j = 0; j < strlen(lineStorage[i]); j++)
                    {
                        if(isalpha(lineStorage[i][j]) != 0)
                        {
                            while(lineStorage[i][j] != '\0')
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                                j++;
                            }
                        }
                    }
                    // printf("Event type: <%s>\n", tempFieldStorage);
                    strcpy(individualEventTypeStorage[totalIndividualEventCount], tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;
                    i++;
                    for(int j = 0; j < strlen(lineStorage[i]); j++)
                    {
                        if(lineStorage[i][j] == 'E')
                        {
                            j+=2;
                            while(lineStorage[i][j] != lineStorage[i][strlen(lineStorage[i])])
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
                                j++;
                            }
                        }
                    }
                    // printf("event date: <%s>\n", tempFieldStorage);
                    strcpy(individualEventDateStorage[totalIndividualEventCount], tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;

                    if(strcasestr(lineStorage[i + 1], "PLAC"))
                    {
                        // printf("lol\n");
                        i++;
                        int j = 7;
                        while(lineStorage[i][j] != '\0')
                            // for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            // printf("char %c\n", lineStorage[i][j]);
                            tempSize++;
                            j++;
                        }

                        strcpy(individualEventPlaceStorage[totalIndividualEventCount], tempFieldStorage);
                        memset(tempFieldStorage, '\0', 256);
                        tempSize = 0;
                    }
                    else
                    {
                        strcpy(individualEventPlaceStorage[totalIndividualEventCount], "");
                    }

                    while(atoi(&lineStorage[i][0]) < 0)
                    {

                        for(int j = 2; j < strlen(lineStorage[i]); j++)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            if(lineStorage[i][j+1] == ' ')
                            {
                                while(j < strlen(lineStorage[i]))
                                {
                                    tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                    tempSizeTwo++;
                                    j++;
                                }
                            }
                        }

                        strcpy(individualEventOtherFieldValueStorage[totalIndividualEventOtherFieldCount], tempFieldStorage);
                        strcpy(individualOtherFieldTagStorage[totalIndividualEventOtherFieldCount], tempDataStorage);
                        totalIndividualEventOtherFieldCount++;
                        memset(tempFieldStorage, '\0', 256);
                        memset(tempDataStorage, '\0', 256);
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
                    if(!(strcasestr(lineStorage[i], "FAMC")))
                    {
                        if(!(strcasestr(lineStorage[i], "FAMS")))
                        {




                            for(int j = 0; j < strlen(lineStorage[i]); j++)
                            {
                                // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                                if(isalpha(lineStorage[i][j+1]) != 0)
                                {
                                    // printf("b00ty j is %d\n",j);
                                    while(isalpha(lineStorage[i][j]) != 0)
                                    {
                                        // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                                        tempFieldStorage[tempSize] = lineStorage[i][j];
                                        tempSize++;
                                        j++;
                                        // printf(";\n");
                                        // }
                                        // printf("lolcooooo j is %d\n",j);
                                        if(lineStorage[i][j] == ' ')
                                        {
                                            j++;
                                            // printf("ay lmao\n");
                                            // printf("now j is %d\n", j);
                                            // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                                            //     j+=2;
                                            // while(lineStorage[i][j] != '\0')
                                            while(j != strlen(lineStorage[i]))
                                            {
                                                // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                                                tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                                tempSizeTwo++;
                                                j++;
                                            }
                                        }
                                }
                            }
                        }
                        // if(strlen(tempFieldStorage) == 0 || strlen(tempDataStorage) == 0)
                        // {
                        //     GEDCOMerror err;
                        //     err.type = INV_RECORD;
                        //     err.line = i;
                        //     return err;
                        // }

                        // printf("indi tag: <%s> indi field <%s>\n", tempFieldStorage, tempDataStorage);
                        strcpy(individualOtherFieldValueStorage[totalIndividualOtherFieldCount], tempDataStorage);
                        strcpy(individualOtherFieldTagStorage[totalIndividualOtherFieldCount], tempFieldStorage);
                        totalIndividualOtherFieldCount++;
                        memset(tempFieldStorage, '\0', 256);
                        memset(tempDataStorage, '\0', 256);
                        tempSize = 0;
                        tempSizeTwo = 0;

                        totalIndividualOtherFieldArray[totalIndividualCount] = totalIndividualOtherFieldCount;
                        // individualOtherFieldCount = 0;
                    }
                }
            }
        }

        // i++;

        }
        totalIndividualEventArray[totalIndividualCount] = totalIndividualEventCount;
        totalIndividualCount++;
        // }
}
else if(strcasestr(lineStorage[i], "FAM"))
{
    // printf("fam found\n");
    // printf("family starts on line: %s\n", lineStorage[i]);
    // famFlag = 1;
    // i++;
    while(lineStorage[i+1][0] != '0')
    {
        // printf("family starts on line: %s\n", lineStorage[i]);
        // if((i+1) >= count)
        // {
        //     GEDCOMerror err;
        //     err.type = INV_GEDCOM;
        //     err.line = -1;
        //     return err;
        // }
        // if(atoi(&lineStorage[i+1][0]) > atoi(&lineStorage[i][0]) + 1 && atoi(&lineStorage[i+1][0]) != atoi(&lineStorage[i][0]) && atoi(&lineStorage[i+1][0]) != 0)
        // {
        //     GEDCOMerror err;
        //     err.type = INV_RECORD;
        //     err.line = -1;
        //     return err;
        // }
        i++;
        if(strcasestr(lineStorage[i], "HUSB"))
        {
            for(int j = 7; j < strlen(lineStorage[i]); j++)
            {
                while(lineStorage[i][j] != '@' && j < strlen(lineStorage[i]))
                {
                    if((isalpha(lineStorage[i][j])) == 0)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                    }
                    j++;
                }
            }

            // printf("line[%d]:%s\nhus num is <%s>\n",i, lineStorage[i], tempFieldStorage);
            familyHusbandFindArray[totalFamilyCount] = atoi(tempFieldStorage) - 1;
            memset(tempFieldStorage, '\0', 256);
            tempSize = 0;
        }
        else if(strcasestr(lineStorage[i], "WIFE"))
        {
            for(int j = 7; j < strlen(lineStorage[i]); j++)
            {
                while(lineStorage[i][j] != '@' && j < strlen(lineStorage[i]))
                {
                    if((isalpha(lineStorage[i][j])) == 0)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                    }
                    j++;
                }
            }
            // printf("wife num is <%s>\n", tempFieldStorage);
            familyWifeFindArray[totalFamilyCount] = atoi(tempFieldStorage) - 1;
            memset(tempFieldStorage, '\0', 256);
            tempSize = 0;
        }
        else if(strcasestr(lineStorage[i], "CHIL"))
        {
            // printf("hiya\n");
            // printf("1\n");
            // printf("line is <%s>\n", lineStorage[i]);
            for(int j = 7; j < strlen(lineStorage[i]); j++)
            {
                while(lineStorage[i][j] != '@' && j < strlen(lineStorage[i]) )
                {
                    if((isalpha(lineStorage[i][j])) == 0)
                    {
                        // printf("lineStorage char is currently <%c>\n", lineStorage[i][j]);
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                    }
                    j++;
                }
            }
            // printf("child num is <%d>\n", atoi(tempFieldStorage));
            // familyChildCount++;
            familyChildFindArray[familyChildCount] = (atoi(tempFieldStorage) - 1);
            memset(tempFieldStorage, '\0', 256);
            // printf("3\n");
            tempSize = 0;
            // printf("4\n");
            familyChildCount++;
            // printf("5\n");

        }
        else
        {

            if((strcasestr(lineStorage[i+1], "DATE")))
            {
                // printf("lolcats\n");
                for(int j = 2; j < strlen(lineStorage[i]) ; j++)
                {
                    tempFieldStorage[tempSize] = lineStorage[i][j];
                    tempSize++;
                }
                // printf("date storage thing: <%s>\n", tempFieldStorage);
                strcpy(familyEventTypeStorage[totalFamilyEventCount], tempFieldStorage);
                memset(tempFieldStorage, '\0', 256);
                tempSize = 0;
                i++;
                for(int j = 7; j < strlen(lineStorage[i]) ; j++)
                {
                    tempFieldStorage[tempSize] = lineStorage[i][j];
                    tempSize++;
                }
                // printf("next storage thing: <%s>\n", tempFieldStorage);
                strcpy(familyEventDateStorage[totalFamilyEventCount], tempFieldStorage);
                memset(tempFieldStorage, '\0', 256);
                tempSize = 0;

                if(strcasestr(lineStorage[i + 1], "PLAC"))
                {
                    i++;
                    for(int j = 7; j < strlen(lineStorage[i]); j++)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                    }
                    // printf("third storage thing: <%s>\n", tempFieldStorage);
                    strcpy(familyEventPlaceStorage[totalFamilyEventCount], tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;
                }
                else
                {
                    strcpy(familyEventPlaceStorage[totalFamilyEventCount], "");
                }

                while(atoi(&lineStorage[i][0]) < 0)
                {
                    // printf("f00l line: %d\n", i);
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
                                j++;
                            }
                        }
                    }
                    // if(strlen(tempFieldStorage) == 0 || strlen(tempDataStorage) == 0)
                    // {
                    //     GEDCOMerror err;
                    //     err.type = INV_RECORD;
                    //     err.line = i;
                    //     return err;
                    // }

                    strcpy(familyEventOtherFieldValueStorage[totalFamilyEventOtherFieldCount], tempFieldStorage);
                    strcpy(familyEventOtherFieldTagStorage[totalFamilyEventOtherFieldCount], tempDataStorage);
                    totalFamilyEventOtherFieldCount++;
                    memset(tempFieldStorage, '\0', 256);
                    memset(tempDataStorage, '\0', 256);
                    tempSize = 0;
                    tempSizeTwo = 0;


                }

                // printf("currently at line %d\n", i);

                totalFamilyEventOtherFieldArray[totalFamilyEventCount] = totalFamilyEventOtherFieldCount;
                // printf("event count is %d\n", totalFamilyEventCount);
                // eventOtherFieldCount = 0;
                totalFamilyEventCount++;
                // printf("event count is %d\n", totalFamilyEventCount);
            }
            else if((strcasestr(lineStorage[i+1], "PLAC")))
            {
                for(int j = 2; j < strlen(lineStorage[i]) ; j++)
                {
                    tempFieldStorage[tempSize] = lineStorage[i][j];
                    tempSize++;
                }
                // printf("date storage thing: <%s>\n", tempFieldStorage);
                strcpy(familyEventTypeStorage[totalFamilyEventCount], tempFieldStorage);
                memset(tempFieldStorage, '\0', 256);
                tempSize = 0;
                i++;
                // for(int j = 7; j < strlen(lineStorage[i]) - 1; j++)
                // {
                //     tempFieldStorage[tempSize] = lineStorage[i][j];
                //     tempSize++;
                // }
                // // printf("next storage thing: <%s>\n", tempFieldStorage);
                // strcpy(familyEventDateStorage[totalFamilyEventCount], tempFieldStorage);
                // memset(tempFieldStorage, '\0', 256);
                // tempSize = 0;

                // if(strcasestr(lineStorage[i + 1], "PLAC"))
                // {
                // i++;
                for(int j = 7; j < strlen(lineStorage[i]); j++)
                {
                    tempFieldStorage[tempSize] = lineStorage[i][j];
                    tempSize++;
                }
                // printf("third storage thing: <%s>\n", tempFieldStorage);
                strcpy(familyEventPlaceStorage[totalFamilyEventCount], tempFieldStorage);
                memset(tempFieldStorage, '\0', 256);
                tempSize = 0;
                // }
                // else
                // {
                // strcpy(familyEventPlaceStorage[totalFamilyEventCount], "");
                // }
            }
            else
            {
                //     if(strcasestr(lineStorage[i+1], "DATE"))
                // {
                // printf("other at line %d\n", i);
                // printf("else line is <%s>\n", lineStorage[i]);
                // }
                // printf("i+1 %s\n", lineStorage[i+1]);

                for(int j = 0; j < strlen(lineStorage[i]); j++)
                {
                    // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                    if(isalpha(lineStorage[i][j+1]) != 0)
                    {
                        // printf("b00ty j is %d\n",j);
                        while(isalpha(lineStorage[i][j]) != 0)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                            // printf(";\n");
                            // }
                            // printf("lolcooooo j is %d\n",j);
                            if(lineStorage[i][j] == ' ')
                            {
                                j++;
                                // printf("ay lmao\n");
                                // printf("now j is %d\n", j);
                                // printf("char[%d]: %c\n", j, lineStorage[i][j]);
                                //     j+=2;
                                while(j < strlen(lineStorage[i])-1)
                                {
                                    tempDataStorage[tempSizeTwo] = lineStorage[i][j];
                                    tempSizeTwo++;
                                    j++;
                                }
                            }
                    }
                }
            }
            // if(strlen(tempFieldStorage) == 0 || strlen(tempDataStorage) == 0)
            // {
            //     GEDCOMerror err;
            //     err.type = INV_RECORD;
            //     err.line = -1;
            //     return err;
            // }
            // printf("family other tag: <%s> value: <%s>\n", tempFieldStorage, tempDataStorage);
            strcpy(familyOtherFieldValueStorage[totalFamilyOtherFieldCount], tempFieldStorage);
            strcpy(familyOtherFieldTagStorage[totalFamilyOtherFieldCount], tempDataStorage);
            totalFamilyOtherFieldCount++;
            memset(tempFieldStorage, '\0', 256);
            memset(tempDataStorage, '\0', 256);
            tempSize = 0;
            tempSizeTwo = 0;

            totalFamilyOtherFieldArray[totalFamilyCount] = totalFamilyOtherFieldCount;
            // individualOtherFieldCount = 0;
        }
        // i++;
    }
    // printf("hello %s\n", lineStorage[i]);
    // i++;
}
totalFamilyEventArray[totalFamilyCount] = totalFamilyEventCount;
familyChildFindCountArray[totalFamilyCount] = familyChildCount;
totalFamilyCount++;
}
else if(strcasestr(lineStorage[i], "SUBM"))
{
    // printf("subm found on line %d\n", i);
    submFlag = 1;
    // if(strcasestr(lineStorage[i+1], "NAME"))
    // { 
    // printf("next line has name\n");
    i++;
    // printf("subm starts with this line: <%s>\n", lineStorage[i]);


    while(lineStorage[i][0] != '0')
    {
        // if(atoi(&lineStorage[i+1][0]) > atoi(&lineStorage[i][0]) + 1 && atoi(&lineStorage[i+1][0]) != atoi(&lineStorage[i][0]) && atoi(&lineStorage[i+1][0]) != 0)
        // {
        //     GEDCOMerror err;
        //     err.type = INV_RECORD;
        //     err.line = -1;
        //     return err;
        // }
        // if((i+1) >= count)
        // {
        //     GEDCOMerror err;
        //     err.type = INV_GEDCOM;
        //     err.line = -1;
        //     return err;
        // }
        // printf("line[%d]: <%s>\n", i, lineStorage[i]);
        // printf("this line\n");
        // i++;
        if(strcasestr(lineStorage[i], "NAME"))
        {
            // i++;
            // printf("hellfadjsklfasdfo\n");
            for(int j = 7; j < strlen(lineStorage[i]) ; j++)
            {
                // while(lineStorage[i][j+1] != ' ')
                // {
                tempFieldStorage[tempSize] = lineStorage[i][j];
                tempSize++;
                // j++;

            }

            strcpy(submitterNameStore, tempFieldStorage);
            // printf("tempFieldStorage sub name is %s\n", tempFieldStorage);
            // strcpy(individualSurNameStorage[totalIndividualCount], tempDataStorage);
            memset(tempFieldStorage, '\0', 256);
            // memset(tempDataStorage, '\0', 1000);
            tempSize = 0;
            // tempSizeTwo = 0;
            }
            else if(strcasestr(lineStorage[i], "ADDR"))
            {
                for(int j = 7; j < strlen(lineStorage[i]) ; j++)
                {
                    // while(lineStorage[i][j+1] != ' ')
                    // {
                    tempFieldStorage[tempSize] = lineStorage[i][j];
                    tempSize++;
                    // j++;

                }

                strcpy(submitterAddress, tempFieldStorage);
                // printf("tempFieldStorage sub name is %s\n", tempFieldStorage);
                // strcpy(individualSurNameStorage[totalIndividualCount], tempDataStorage);
                memset(tempFieldStorage, '\0', 256);
                // memset(tempDataStorage, '\0', 1000);
                tempSize = 0;   
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

                        memset(tempFieldStorage, '\0', 256);
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
                                    j++;
                                }
                            }
                        }
                        // if(strlen(tempFieldStorage) == 0 || strlen(tempDataStorage) == 0)
                        // {
                        //     GEDCOMerror err;
                        //     err.type = INV_GEDCOM;
                        //     err.line = -1;
                        //     return err;
                        // }
                        strcpy(submitterOtherFieldValueStorage[submitterOtherFieldCount], tempFieldStorage);
                        strcpy(submitterOtherFieldTagStorage[submitterOtherFieldCount], tempDataStorage);
                        submitterOtherFieldCount++;
                        memset(tempFieldStorage, '\0', 256);
                        memset(tempDataStorage, '\0', 256);
                        tempSize = 0;
                        tempSizeTwo = 0;
                    }
                    // i++;
                }

                i++;
                // }
        }
    }
    else if(strcasestr(lineStorage[i], "TRLR"))
    {
        // printf("end found\n");
        // endFlag = 1;
    }
}
}
if(!((strcasestr(lineStorage[count - 1],"TRLR"))))
{
    GEDCOMerror err;
    err.type = INV_GEDCOM;
    err.line = -1;
    return err;
}
// // // // }
if(headFlag != 1)
{
    GEDCOMerror err;
    err.type = INV_GEDCOM;
    err.line = -1;
    return err;
}
if(submFlag == 0)
{
    GEDCOMerror err;
    err.type = INV_GEDCOM;
    err.line = -1;
    return err;
}

if(versionFlag != 1 || sourceFlag != 1 || encordingFlag != 1 || submFlag != 1 || subRefFlag != 1)
{
    GEDCOMerror err;
    err.type = INV_HEADER;
    err.line = -1;
    return err;
}
else if(submFlag != 1)
{
    GEDCOMerror err;
    err.type = INV_GEDCOM;
    err.line = -1;
    return err;
}

// GEDCOMobject * tempObject;   
Individual * tempIndividual;
Family * tempFamily;
Header * tempHeader;
Field * tempOtherField;
Event * tempEvent;
Submitter * tempSubm;

tempSubm = initializeSubmitter(submitterNameStore, submitterAddress);
if(submitterOtherFieldCount != 0)
{
    for(int j = 0; j < submitterOtherFieldCount; j++)
    {

        // (char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second));
        tempOtherField = initializeOtherField(submitterOtherFieldTagStorage[j], submitterOtherFieldValueStorage[j]);
        insertBack(&tempSubm->otherFields, tempOtherField);
        // deleteField((void*)tempOtherField);
        // tempSubm->otherFields = initializeList(printField, deleteField, compareFields);
    }
}

tempHeader = initializeHeader(sourceStore, gedcVersionStore, encodingTypeStore);
if(headerOtherFieldCount != 0)
{
    for(int j = 0; j < headerOtherFieldCount; j++)
    {
        // printf("other val: <%s>\n", headerOtherFieldValueStorage[j]);
        tempOtherField = initializeOtherField(headerOtherFieldTagStorage[j], headerOtherFieldValueStorage[j]);
        insertBack(&tempHeader->otherFields, tempOtherField);
        // deleteField((void*)tempOtherField);
    }
}

tempHeader->submitter = tempSubm;
tempObject->header = tempHeader;
tempObject->submitter = tempSubm;
// printf("total ind count is %d\n", totalIndividualCount);
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
                                insertBack(&tempEvent->otherFields, tempOtherField);
                                // deleteField((void*)tempOtherField);
                            }
                        }
                        else
                        {
                            for(int m = totalIndividualEventOtherFieldArray[k - 1]; m < totalIndividualEventOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);   
                                // deleteField((void*)tempOtherField);
                            }
                        }
                    }

                    insertBack(&tempIndividual->events, tempEvent);
                    // deleteEvent((void*)tempEvent);
                }

            }
            else
            {
                for(int k = totalIndividualEventArray[j - 1]; k < totalIndividualEventArray[j]; k++)
                {
                    tempEvent = initializeEvent(individualEventTypeStorage[k], individualEventDateStorage[k], individualEventPlaceStorage[k]);
                    if(totalIndividualEventOtherFieldArray[k] != 0)
                    {
                        if(k == 0)
                        {
                            for(int m = 0; m < totalIndividualEventOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);
                                // deleteField((void*)tempOtherField);
                            }
                        }
                        else
                        {
                            for(int m = totalIndividualEventOtherFieldArray[k - 1]; m < totalIndividualEventOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(individualEventOtherFieldTagStorage[m], individualEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);   
                                // deleteField((void*)tempOtherField);
                            }
                        }
                    }

                    insertBack(&tempIndividual->events, tempEvent);
                    // deleteEvent((void*)tempEvent);
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
                    insertBack(&tempIndividual->otherFields, tempOtherField);
                    // deleteField((void*)tempOtherField);
                }
            }
            else
            {
                for(int k = totalIndividualOtherFieldArray[j - 1]; k < totalIndividualOtherFieldArray[j]; k++)
                {

                    // Event * initializeEvent(char* type, char* date, char* place)
                    tempOtherField = initializeOtherField(individualOtherFieldTagStorage[k], individualOtherFieldValueStorage[k]);
                    insertBack(&tempIndividual->otherFields, tempOtherField);
                    // deleteField((void*)tempOtherField);
                }
            }
        }
        // else
        // {
        // printf("shit at field array is %d\n", totalIndividualOtherFieldArray[j+1]);
        // }

        insertBack(&tempObject->individuals, tempIndividual);
        // deleteIndividual((void*)tempIndividual);
    }

}


//DO FAMILIES NOWWWWWWW
// printf("total family is %d\n", totalFamilyCount);
//there are more than 0 families
if(totalFamilyCount != 0)
{
    //cycle through all the families starting at 0
    for(int j = 0; j < totalFamilyCount; j++)
    {

        //initialize the first family , which is all just lists
        tempFamily = initializeFamily();
        // printf("insert stuff is %d\n", totalFamilyEventArray[j]);

        //check to see if there are any events for this family
        if(totalFamilyEventArray[j] != 0)
        {
            // printf("hello\n");
            //cycle through 
            if(j == 0)
            {
                for(int k = 0; k < totalFamilyEventArray[j]; k++)
                {
                    tempEvent = initializeEvent(familyEventTypeStorage[k], familyEventDateStorage[k], familyEventPlaceStorage[k]);
                    if(k == 0)
                    {
                        if(totalFamilyEventOtherFieldArray[k] != 0)
                        {
                            for(int m = 0; m < totalFamilyOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(familyEventOtherFieldTagStorage[m], familyEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);
                                // deleteField((void*)tempOtherField);
                            }
                        }   
                    }
                    else
                    {
                        if(totalFamilyEventOtherFieldArray[k] != 0)
                        {
                            for(int m = totalFamilyOtherFieldArray[k-1]; m < totalFamilyOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(familyEventOtherFieldTagStorage[m], familyEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);
                                // deleteField((void*)tempOtherField);
                            }
                        } 
                    }
                    insertBack(&tempFamily->events, tempEvent);
                    // deleteEvent((void*)tempEvent);
                }
            }
            else
            {
                for(int k = totalFamilyEventArray[j - 1]; k < totalFamilyEventArray[j]; k++)
                {
                    tempEvent = initializeEvent(familyEventTypeStorage[k], familyEventDateStorage[k], familyEventPlaceStorage[k]);
                    if(k == 0)
                    {
                        if(totalFamilyEventOtherFieldArray[k] != 0)
                        {
                            for(int m = 0; m < totalFamilyOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(familyEventOtherFieldTagStorage[m], familyEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);
                                // deleteField((void*)tempOtherField);
                            }
                        }   
                    }
                    else
                    {
                        if(totalFamilyEventOtherFieldArray[k] != 0)
                        {
                            for(int m = totalFamilyOtherFieldArray[k-1]; m < totalFamilyOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(familyEventOtherFieldTagStorage[m], familyEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, tempOtherField);
                                // deleteField((void*)tempOtherField);
                            }
                        } 
                    }
                    insertBack(&tempFamily->events, tempEvent);
                    // deleteEvent((void*)tempEvent);
                }

            }
        }

        if(totalFamilyOtherFieldArray[j] != 0)
        {
            if(j == 0)
            {

                for(int k = 0; k < totalFamilyOtherFieldArray[j]; k++)
                {

                    tempOtherField = initializeOtherField(familyOtherFieldTagStorage[k], familyEventOtherFieldValueStorage[k]);
                    insertBack(&tempFamily->otherFields, tempOtherField);
                    // deleteField((void*)tempOtherField);

                }

            }
            else
            {
                for(int k = totalFamilyOtherFieldArray[j-1]; k < totalFamilyOtherFieldArray[j]; k++)
                {
                    tempOtherField = initializeOtherField(familyOtherFieldTagStorage[k], familyEventOtherFieldValueStorage[k]);
                    insertBack(&tempFamily->otherFields, tempOtherField);
                    // deleteField((void*)tempOtherField);
                }
            }
        }


        if(familyHusbandFindArray[j] != -1)
        {
            void *individualElem;
            ListIterator individualElemIter = createIterator(tempObject->individuals);
            while((individualElem = nextElement(&individualElemIter)) != NULL)
            {
                Individual * tempIndividualFind = (Individual*)individualElem;
                if(strcmp(tempIndividualFind->surname, individualSurNameStorage[familyHusbandFindArray[j]]) == 0 && strcmp(tempIndividualFind->givenName, individualGivenNameStorage[familyHusbandFindArray[j]]) == 0)
                {
                    tempFamily->husband = tempIndividualFind;
                    insertBack(&tempIndividualFind->families, tempFamily);
                    // deleteFamily((void*)tempFamily);
                }
            }
        }
        else
        {
            tempFamily->husband = NULL;
        }

        if(familyWifeFindArray[j] != -1)
        {
            void *individualElem;
            ListIterator individualElemIter = createIterator(tempObject->individuals);
            while((individualElem = nextElement(&individualElemIter)) != NULL)
            {
                Individual * tempIndividualFind = (Individual*)individualElem;
                if(strcmp(tempIndividualFind->surname, individualSurNameStorage[familyWifeFindArray[j]]) == 0 && strcmp(tempIndividualFind->givenName, individualGivenNameStorage[familyWifeFindArray[j]]) == 0)
                {
                    tempFamily->wife = tempIndividualFind;
                    insertBack(&tempIndividualFind->families, tempFamily);
                    // deleteFamily((void*)tempFamily);
                }
            }
        }
        else
        {
            tempFamily->wife = NULL;
        }

        if(familyChildFindCountArray[j] != 0)
        {
            // printf("family child count at %d is %d kids, also %d\n", j, familyChildFindCountArray[j], familyChildFindArray[j]);

            // for(int m = 0; m < familyChildFindArray[j]; m++)
            // {
            // printf("m is now %d, find count is %d\n" familyChildFindCountArray[j]);
            // }


            if(j == 0)
            {
                // printf("is 0\n");
                for(int k = 0; k < familyChildFindCountArray[j]; k++)
                {
                    // printf("dfaslkdfj\n");
                    void *individualElem;
                    ListIterator individualElemIter = createIterator(tempObject->individuals);
                    while((individualElem = nextElement(&individualElemIter)) != NULL)
                    {
                        Individual * tempIndividualFind = (Individual*)individualElem;
                        if(strcmp(tempIndividualFind->surname, individualSurNameStorage[familyChildFindArray[k]]) == 0 && strcmp(tempIndividualFind->givenName, individualGivenNameStorage[familyChildFindArray[k]]) == 0)
                        {
                            insertBack(&tempFamily->children, tempIndividualFind);
                            insertBack(&tempIndividualFind->families, tempFamily);
                            // deleteIndividual((void*)tempIndividualFind);
                            // deleteFamily((void*)tempFamily);
                            // printf("surnam is <%s>\n",individualGivenNameStorage[familyChildFindArray[k]]);
                            // tempFamily->wife = tempIndividualFind;
                        }
                    }
                }
            }
            else
            {
                // printf("not 0\n");
                for(int k = familyChildFindCountArray[j]; k < familyChildFindCountArray[j]+1; k++)
                {
                    // printf("k is %d\n", k);
                    void *individualElem;
                    ListIterator individualElemIter = createIterator(tempObject->individuals);
                    while((individualElem = nextElement(&individualElemIter)) != NULL)
                    {
                        Individual * tempIndividualFind = (Individual*)individualElem;
                        if(strcmp(tempIndividualFind->surname, individualSurNameStorage[familyChildFindArray[k]]) == 0 && strcmp(tempIndividualFind->givenName, individualGivenNameStorage[familyChildFindArray[k]]) == 0)
                        {
                            // void *individualElemDupeCheck;
                            // ListIterator individualElemDupeCheckIter = createIterator(tempFamily->children);
                            // while((individualElemDupeCheck = nextElement(&individualElemDupeCheckIter)) != NULL)
                            // {
                            //     Individual * tempIndividualFindDupeCheck = (Individual*)individualElemDupeCheck;
                            //     if(strcmp(tempIndividualFind->surname, tempIndividualFindDupeCheck->surname) == 0 && strcmp(tempIndividualFind->givenName, tempIndividualFindDupeCheck->givenName) == 0)
                            //     {

                            //         insertBack(&tempFamily->children, tempIndividualFind);
                            //         insertBack(&tempIndividualFind->families, tempFamily);

                            //         // tempFamily->wife = tempIndividualFind;
                            //     }
                            // }
                            // printf("fuck\n");
                            insertBack(&tempFamily->children, tempIndividualFind);
                            insertBack(&tempIndividualFind->families, tempFamily);
                            // deleteIndividual((void*)tempIndividualFind);
                            // deleteFamily((void*)tempFamily);
                            // break;
                            // tempFamily->wife = tempIndividualFind;
                        }
                        // printf("hell\n");
                    }
                    // printf("dkfajsdklfa\n");
                }
                // printf("where\n");
            }
            // printf("afd\n");
        }
        else
        {
            printf("family aint got no children\n");
        }
        // printf("hello\n");
        insertBack(&tempObject->families, tempFamily);
        // deleteFamily((void*)tempFamily);
        // }
        // *obj = tempObject;
        // }
        // *obj = tempObject;

        // }

        }
}
*obj = tempObject;
// deleteGEDCOM(tempObject);
// char * str = printGEDCOM(tempObject);
// printf("temp idea\n%s\n", str);

// }
// char * str = printGEDCOM(tempObject);
// printf("temp idea\n%s\n", str);
// *obj = tempObject;
GEDCOMerror err;
err.type = OK;
err.line = count;
return err;



}



GEDCOMerror writeGEDCOM(char* fileName, const GEDCOMobject* obj)
{

    // if(obj == NULL)
    // {
    // GEDCOMerror err;
    // err.type = INV_GEDCOM;
    // err.line = -1;
    // return err;
    // }
    if(obj != NULL)
    {

        if(fileName != NULL && fileName[0] != '\0')
        {
            if(strcasestr(fileName, ".ged"))
            {
                FILE * fp;
                if((fp = fopen(fileName, "w")) != NULL)
                {
                    // char * str = printGEDCOM(obj);
                    // printf("ref obj is %s\n", str);
                    char * writeReturn = malloc(sizeof(char) *1000);
                    // GEDCOMerror err;
                    // err.type = validateGEDCOM(obj);
                    // err.line = -1;
                    // if(err.type != 0)
                    // {
                    //     return err;
                    // }
                    if(obj->header != NULL)
                    {
                        Header * tempHeader = (Header*)obj->header;
                        sprintf(writeReturn + strlen(writeReturn), "0 HEAD\n1 SOUR %s\n", tempHeader->source);
                        if(getLength(tempHeader->otherFields)!= 0)
                        {
                            void* tempElem;
                            ListIterator tempElemIter = createIterator(tempHeader->otherFields);
                            while((tempElem = nextElement(&tempElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)tempElem;
                                // printf("fuckk all\n");
                                sprintf(writeReturn + strlen(writeReturn), "2 %s %s\n", tempField->tag, tempField->value);
                            }

                        }
                        // else
                        // {
                        //     printf("mother fuck %d\n", getLength(tempHeader->otherFields));
                        // }
                        sprintf(writeReturn + strlen(writeReturn), "1 GEDC\n2 VERS %.1f\n",tempHeader->gedcVersion); 
                        switch((int)tempHeader->encoding)
                        {
                            case 0:
                                sprintf(writeReturn + strlen(writeReturn), "1 CHAR ANSEL\n1 SUBM @U1@\n");
                                // break;
                            case 1:
                                sprintf(writeReturn + strlen(writeReturn), "1 CHAR UTF-8\n1 SUBM @U1@\n");
                                // break;
                            case 2:
                                sprintf(writeReturn + strlen(writeReturn), "1 CHAR UNICODE\n1 SUBM @U1@\n");
                                // break;
                            case 3:
                                // printf("fucker\n");
                                sprintf(writeReturn + strlen(writeReturn), "1 CHAR ASCII\n1 SUBM @U1@\n");
                                // break;
                            default:
                                break;
                        }

                    }
                    else
                    {
                        free(writeReturn);
                        fclose(fp);
                        GEDCOMerror err;
                        err.type = INV_HEADER;
                        err.line = -1;
                        return err;
                    }
                    // sprintf(writeReturn + strlen(writeReturn), "1 CHAR %u\n1 SUBM @U1@\n",  tempHeader->encoding);

                    if(getLength(obj->individuals) != 0)
                    {
                        int personCount = 1;
                        void* tempPersonElem;
                        ListIterator tempPersonElemIter = createIterator(obj->individuals);
                        while((tempPersonElem = nextElement(&tempPersonElemIter)) != NULL)
                        {
                            Individual * tempIndividual = (Individual*)tempPersonElem;
                            sprintf(writeReturn + strlen(writeReturn), "0 @I%d@ INDI\n1 NAME %s /%s/\n",personCount, tempIndividual->givenName, tempIndividual->surname);
                            if(getLength(tempIndividual->otherFields) != 0)
                            {
                                void* tempElem;
                                ListIterator tempElemIter = createIterator(tempIndividual->otherFields);
                                while((tempElem = nextElement(&tempElemIter)) != NULL)
                                {
                                    Field * tempField = (Field*)tempElem;
                                    sprintf(writeReturn + strlen(writeReturn), "1 %s %s\n", tempField->tag, tempField->value);
                                }
                            }

                            if(getLength(tempIndividual->events) != 0)
                            {
                                void* tempEventElem;
                                ListIterator tempEventElemIter = createIterator(tempIndividual->events);
                                while((tempEventElem = nextElement(&tempEventElemIter)) != NULL)
                                {
                                    Event * tempEvent = (Event*)tempEventElem;
                                    sprintf(writeReturn + strlen(writeReturn), "1 %s\n", tempEvent->type);
                                    if(strlen(tempEvent->date) != 0)
                                    {
                                        sprintf(writeReturn + strlen(writeReturn), "2 %s\n", tempEvent->date);
                                    }
                                    if(strlen(tempEvent->place) != 0)
                                    {
                                        sprintf(writeReturn + strlen(writeReturn), "2 %s\n", tempEvent->place);
                                    }

                                    if(getLength(tempEvent->otherFields) != 0)
                                    {
                                        void* tempElem;
                                        ListIterator tempElemIter = createIterator(tempEvent->otherFields);
                                        while((tempElem = nextElement(&tempElemIter)) != NULL)
                                        {
                                            Field * tempField = (Field*)tempElem;
                                            sprintf(writeReturn + strlen(writeReturn), "2 %s %s\n", tempField->tag, tempField->value);
                                        }
                                    }

                                }
                            }

                            if(getLength(tempIndividual->families) != 0)
                            {
                                int familyCount = 1;
                                void* tempFamilyElem;
                                ListIterator tempFamilyElemIter = createIterator(tempIndividual->families);
                                while((tempFamilyElem = nextElement(&tempFamilyElemIter)) != NULL)
                                {

                                    Family * tempFamily = (Family*)tempFamilyElem;
                                    Individual * tempHubby = (Individual*)tempFamily->husband;
                                    Individual * tempWifey = (Individual*)tempFamily->wife;
                                    if ((tempHubby->givenName != NULL && tempIndividual->givenName != NULL && (strcmp(tempIndividual->givenName, tempHubby->givenName ) == 0)) || (tempWifey->givenName != NULL && tempIndividual->givenName != NULL && (strcmp(tempIndividual->givenName, tempWifey->givenName ) == 0)))
                                    {
                                        // printf("given names are fucked, test is <%s> ref is <%s>\n", testInd->givenName, refInd->givenName);
                                        // printf("sur names are fucked, test is <%s> ref is <%s>\n", testInd->surname, refInd->surname);

                                        if ((tempHubby->surname != NULL && tempIndividual->surname != NULL && (strcmp(tempIndividual->surname, tempHubby->surname ) == 0)) || (tempWifey->surname != NULL && tempIndividual->surname != NULL && (strcmp(tempIndividual->surname, tempWifey->surname ) == 0)))
                                        {
                                            void* objFamilyListElem;
                                            ListIterator objFamilyListElemIter = createIterator(obj->families);
                                            while((objFamilyListElem = nextElement(&objFamilyListElemIter)) != NULL)
                                            {
                                                Family * tempCompFamily = (Family*)objFamilyListElem;
                                                if(tempFamily == tempCompFamily)
                                                {
                                                    sprintf(writeReturn + strlen(writeReturn), "1 FAMS @F%d@\n", familyCount);
                                                }
                                                familyCount++;
                                            }

                                        }
                                        familyCount = 1;
                                    }

                                    else
                                    {

                                        void* objFamilyListElem;
                                        ListIterator objFamilyListElemIter = createIterator(obj->families);
                                        while((objFamilyListElem = nextElement(&objFamilyListElemIter)) != NULL)
                                        {
                                            Family * tempCompFamily = (Family*)objFamilyListElem;
                                            if(tempFamily == tempCompFamily)
                                            {
                                                sprintf(writeReturn + strlen(writeReturn), "1 FAMC @F%d@\n", familyCount);
                                            }
                                            familyCount++;
                                        }
                                        // sprintf(writeReturn + strlen(writeReturn), "1 FAMC @F%d@\n", familyCount);
                                        familyCount = 1;

                                    }
                                    // familyCount++;

                                }
                            }
                            personCount++;
                        }
                    }

                    if(getLength(obj->families) != 0)
                    {
                        int familyCount = 1;
                        void* tempFamilyElem;
                        ListIterator tempFamilyElemIter = createIterator(obj->families);
                        while((tempFamilyElem = nextElement(&tempFamilyElemIter)) != NULL)
                        {
                            Family * tempFamily = (Family*)tempFamilyElem;
                            sprintf(writeReturn + strlen(writeReturn), "0 @F%d@ FAM\n", familyCount);
                            if(tempFamily->husband != NULL)
                            {
                                int personCount = 1;
                                void* tempPersonFindElem;
                                ListIterator tempPersonFindElemIter = createIterator(obj->individuals);
                                while((tempPersonFindElem = nextElement(&tempPersonFindElemIter))!= NULL)
                                {
                                    Individual * tempIndividual = (Individual*)tempPersonFindElem;
                                    if(tempIndividual == tempFamily->husband)
                                    {
                                        sprintf(writeReturn + strlen(writeReturn), "1 HUSB @I%d@\n", personCount);
                                    }
                                    personCount++;
                                }

                            }

                            if(tempFamily->wife != NULL)
                            {
                                int personCount = 1;
                                void* tempPersonFindElem;
                                ListIterator tempPersonFindElemIter = createIterator(obj->individuals);
                                while((tempPersonFindElem = nextElement(&tempPersonFindElemIter))!= NULL)
                                {
                                    Individual * tempIndividual = (Individual*)tempPersonFindElem;
                                    if(tempIndividual == tempFamily->wife)
                                    {
                                        sprintf(writeReturn + strlen(writeReturn), "1 WIFE @I%d@\n", personCount);
                                    }
                                    personCount++;
                                }

                            }

                            if(getLength(tempFamily->events) != 0)
                            {
                                void *tempEventElem;
                                ListIterator tempEventElemIter = createIterator(tempFamily->events);
                                while((tempEventElem = nextElement(&tempEventElemIter)) != NULL)
                                {

                                    Event * tempEvent = (Event*)tempEventElem;
                                    sprintf(writeReturn + strlen(writeReturn), "1 %s\n", tempEvent->type);
                                    if(strlen(tempEvent->date) != 0)
                                    {
                                        sprintf(writeReturn + strlen(writeReturn), "2 %s\n", tempEvent->date);
                                    }
                                    if(strlen(tempEvent->place) != 0)
                                    {
                                        sprintf(writeReturn + strlen(writeReturn), "2 %s\n", tempEvent->place);
                                    }

                                    if(getLength(tempEvent->otherFields) != 0)
                                    {
                                        void* tempElem;
                                        ListIterator tempElemIter = createIterator(tempEvent->otherFields);
                                        while((tempElem = nextElement(&tempElemIter)) != NULL)
                                        {
                                            Field * tempField = (Field*)tempElem;
                                            sprintf(writeReturn + strlen(writeReturn), "2 %s %s\n", tempField->tag, tempField->value);
                                        }
                                    }

                                }

                            }

                            if(getLength(tempFamily->children) != 0)
                            {
                                int personCount = 1;
                                void* tempChildElem;
                                ListIterator tempChildElemIter = createIterator(tempFamily->children);
                                while((tempChildElem = nextElement(&tempChildElemIter)) != NULL)
                                {
                                    Individual * tempChild = (Individual*)tempChildElem;
                                    void* tempPersonFindElem;
                                    ListIterator tempPersonFindElemIter = createIterator(obj->individuals);
                                    while((tempPersonFindElem = nextElement(&tempPersonFindElemIter))!= NULL)
                                    {
                                        Individual * tempIndividual = (Individual*)tempPersonFindElem;
                                        if(tempIndividual == tempChild)
                                        {
                                            sprintf(writeReturn + strlen(writeReturn), "1 CHIL @I%d@\n", personCount);
                                        }
                                        personCount++;
                                    }
                                    personCount = 1;
                                }
                            }

                            familyCount++;
                        }
                    }

                    if(obj->submitter != NULL)
                    {
                        sprintf(writeReturn + strlen(writeReturn), "0 @U1@ SUBM\n");
                        Submitter * tempSubm = (Submitter*)obj->submitter;
                        if(strlen(tempSubm->submitterName) != 0)
                        {
                            sprintf(writeReturn + strlen(writeReturn), "1 NAME %s\n", tempSubm->submitterName);
                        }

                        if(strlen(tempSubm->address) != 0)
                        {
                            sprintf(writeReturn + strlen(writeReturn), "1 ADDR %s\n", tempSubm->address);
                        }

                        if(getLength(tempSubm->otherFields) != 0)
                        {
                            void* tempElem;
                            ListIterator tempElemIter = createIterator(tempSubm->otherFields);
                            while((tempElem = nextElement(&tempElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)tempElem;
                                if(!(strcasestr(tempField->tag, "SUBM")))
                                {
                                    sprintf(writeReturn + strlen(writeReturn), "1 %s %s\n", tempField->tag, tempField->value);
                                }
                            }
                        }
                    }
                    else
                    {
                        GEDCOMerror err;
                        err.type = INV_RECORD;
                        err.line = -1;
                        return err;
                    }

                    sprintf(writeReturn + strlen(writeReturn), "0 TRLR\n");

                    // printf("write return returns this \n%s\n", writeReturn);
                    fputs(writeReturn, fp);
                    free(writeReturn);
                    fclose(fp);
                }
                else
                {
                    GEDCOMerror err;
                    err.type = INV_FILE;
                    err.line = -1;
                    return err;
                }
            }
            else
            {
                GEDCOMerror err;
                err.type = INV_FILE;
                err.line = -1;
                return err;
            }
        }
        else
        {
            GEDCOMerror err;
            err.type = INV_FILE;
            err.line = -1;
            return err;
        }

    }


    GEDCOMerror err;
    err.type = OK;
    err.line = -1;
    return err;

}

ErrorCode validateGEDCOM(const GEDCOMobject* obj)
{

    if(obj != NULL)
    {
        if(obj->header == NULL)
        {
            return INV_GEDCOM;
        }
        else
        {
            Header * tempHeader = (Header*)obj->header;
            if(strlen(tempHeader->source) == 0)
            {
                return INV_HEADER;
            }

            if(tempHeader->gedcVersion == 0)
            {
                return INV_HEADER;
            }

            if(tempHeader->submitter == NULL)
            {
                return INV_HEADER;
            }

            if(tempHeader->encoding != ANSEL && tempHeader->encoding != UTF8 && tempHeader->encoding != UNICODE && tempHeader->encoding != ASCII)
            {
                return INV_HEADER;
            }

            if(getLength(tempHeader->otherFields) != 0)
            {
                void* tempElem;
                ListIterator tempElemIter = createIterator(tempHeader->otherFields);
                while((tempElem = nextElement(&tempElemIter)) != NULL)
                {
                    Field * tempField = (Field*)tempElem;
                    if(strlen(tempField->tag) == 0 || strlen(tempField->value) == 0)
                    {
                        return INV_HEADER;
                    }
                }
            }
        }

        if(obj->submitter == NULL)
        {
            return INV_GEDCOM;
        }
        else
        {
            Submitter * tempSubm = (Submitter*)obj->submitter;
            if(strlen(tempSubm->submitterName) == 0)
            {
                return INV_RECORD;
            }
            if(getLength(tempSubm->otherFields) != 0)
            {
                void* tempElem;
                ListIterator tempElemIter = createIterator(tempSubm->otherFields);
                while((tempElem = nextElement(&tempElemIter)) != NULL)
                {
                    Field * tempField = (Field*)tempElem;
                    if(strlen(tempField->tag) == 0 || strlen(tempField->value) == 0)
                    {
                        return INV_GEDCOM;
                    }
                }
            }
        }

        // if(getLength)
        // {
        if(getLength(obj->families) != 0)
        {  

            void* tempFamilyElem;
            ListIterator tempElemIter = createIterator(obj->families);
            while((tempFamilyElem = nextElement(&tempElemIter)) != NULL)
            {
                Family * tempFamily = (Family*)tempFamilyElem;
                // if(tempFamily->wife != NULL)
                // {

                // }

                // if(tempFamily->husband != NULL)
                // {

                // }

                // if(getLength(tempFamily->children) != 0)
                // {

                // }
                if(getLength(tempFamily->events) != 0)
                {

                    void* eventElem;
                    ListIterator tempEventElem = createIterator(tempFamily->events);
                    while((eventElem = nextElement(&tempEventElem)) != NULL)
                    {
                        Event * tempEvent = (Event*)eventElem;
                        if(getLength(tempEvent->otherFields) != 0)
                        {
                            void* tempElem;
                            ListIterator tempElemIter = createIterator(tempEvent->otherFields);
                            while((tempElem = nextElement(&tempElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)tempElem;
                                if(strlen(tempField->tag) == 0 || strlen(tempField->value) == 0)
                                {
                                    return INV_GEDCOM;
                                }
                            }
                        }
                    }
                }

                if(getLength(tempFamily->otherFields) != 0)
                {
                    void* tempElem;
                    ListIterator tempElemIter = createIterator(tempFamily->otherFields);
                    while((tempElem = nextElement(&tempElemIter)) != NULL)
                    {
                        Field * tempField = (Field*)tempElem;
                        if(strlen(tempField->tag) == 0 || strlen(tempField->value) == 0)
                        {
                            return INV_GEDCOM;
                        }
                    }
                }
            }

        }
        // }

        // if(obj->individuals != NULL)
        // {
        if(getLength(obj->individuals) != 0)
        {
            void* personElem;
            ListIterator personElemIter = createIterator(obj->individuals);
            while((personElem = nextElement(&personElemIter)) != NULL)
            {
                Individual * tempIndividual = (Individual*)personElem;
                if(getLength(tempIndividual->events) != 0)
                {

                    void* eventElem;
                    ListIterator tempEventElem = createIterator(tempIndividual->events);
                    while((eventElem = nextElement(&tempEventElem)) != NULL)
                    {
                        Event * tempEvent = (Event*)eventElem;
                        if(getLength(tempEvent->otherFields) != 0)
                        {
                            void* tempElem;
                            ListIterator tempElemIter = createIterator(tempEvent->otherFields);
                            while((tempElem = nextElement(&tempElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)tempElem;
                                if(strlen(tempField->tag) == 0 || strlen(tempField->value) == 0)
                                {
                                    return INV_GEDCOM;
                                }
                            }
                        }
                    }
                }

                if(getLength(tempIndividual->otherFields) != 0)
                {
                    void* tempElem;
                    ListIterator tempElemIter = createIterator(tempIndividual->otherFields);
                    while((tempElem = nextElement(&tempElemIter)) != NULL)
                    {
                        Field * tempField = (Field*)tempElem;
                        if(strlen(tempField->tag) == 0 || strlen(tempField->value) == 0)
                        {
                            return INV_GEDCOM;
                        }
                    }
                }
            }
        }
        // }

        return OK;
    }
    else
    {
        return INV_GEDCOM;
    }

    return OK;


}


//FINISH THIS
List getDescendantListN(const GEDCOMobject* familyRecord, const Individual* person, unsigned int maxGen)
{

    List individualDescendantsN = initializeList(printIndividual, deleteIndividual, compareIndividuals);

    if(familyRecord != NULL)
    {
        // if(person != NULL)
        // {

        // }
    }

    return individualDescendantsN;

}


//FINISH THIS
List getAncestorListN(const GEDCOMobject* familyRecord, const Individual* person, int maxGen)
{

    List individualAncestorsN = initializeList(printIndividual, deleteIndividual, compareIndividuals);

    if(familyRecord != NULL && person != NULL)
    {
        if(person != NULL)
        {

        }
    }

    return individualAncestorsN;
}

char* indToJSON(const Individual* ind)
{
    char * jsonReturn = malloc(sizeof(char) * 1000);
    if(ind != NULL)
    {
        int genderFlag = 0;
        int familyCount = getLength(ind->families);
        void* elem;
        ListIterator elemIter = createIterator(ind->otherFields);
        while((elem = nextElement(&elemIter)) != NULL)
        {
            Field* tempField = (Field*)elem;
            if(strcmp(tempField->tag, "SEX") == 0)
            {
                if(strcmp(tempField->value , "M") == 0)
                {
                    genderFlag = 1;
                }
                else
                {
                    genderFlag = 2;
                }
            }
        }
        // char * jsonReturn = malloc(sizeof(char) * 1000);

        if(ind->givenName != NULL)
        {
            sprintf(jsonReturn + strlen(jsonReturn), "{\"givenName\":\"%s\"", ind->givenName);

        }
        else
        {
            sprintf(jsonReturn + strlen(jsonReturn), "{\"givenName\":\"\"");  
        }

        if(ind->surname != NULL)
        {
            sprintf(jsonReturn + strlen(jsonReturn), ",\"surname\":\"%s\"", ind->surname);

        }
        else
        {
            sprintf(jsonReturn + strlen(jsonReturn), ",\"surname\":\"\"");  
        }

        if(genderFlag != 0)
        {
            if(genderFlag == 1)
            {
                sprintf(jsonReturn + strlen(jsonReturn), ",\"gender\":\"Male\"");
            }
            else
            {
                sprintf(jsonReturn + strlen(jsonReturn), ",\"gender\":\"Female\"");   
            }
        }
        else
        {
            sprintf(jsonReturn + strlen(jsonReturn), ",\"gender\":\"\""); 
        }

        sprintf(jsonReturn + strlen(jsonReturn), ",\"familyCount\":\"%d\"}", familyCount);

        // return jsonReturn;
    }
    return jsonReturn;
}

Individual* JSONtoInd(const char* str)
{

    if(str != NULL)
    {
        if(strlen(str) != 0)
        {
            char *tempFieldStorage = malloc(sizeof(char) * 256);
            char *tempDataStorage = malloc(sizeof(char) * 256);
            int tempCount = 0;
            int secondTempCount = 0;

            int nameCount = 0;
            for(int i = 0; i < strlen(str); i++)
            {
                if(str[i] == ':')
                {
                    i+=2;
                    if(nameCount == 0)
                    {
                        nameCount++;
                        while(str[i] != '"')
                        {
                            tempFieldStorage[tempCount] = str[i];
                            tempCount++;
                            i++;
                        }
                    }
                    else
                    {
                        while(str[i] != '"')
                        {
                            tempDataStorage[secondTempCount] = str[i];
                            secondTempCount++;
                            i++;
                        }
                    }

                }
            }
            if(secondTempCount != 0 || tempCount != 0)
            {

                Individual * tempIndividual = initializeIndividual(tempFieldStorage, tempDataStorage);
                tempCount = 0;
                secondTempCount = 0;
                memset(tempFieldStorage, '\0', 256);
                memset(tempDataStorage, '\0', 256);

                free(tempFieldStorage);
                free(tempDataStorage);
                return tempIndividual;
            }
            free(tempFieldStorage);
            free(tempDataStorage);
        }
    }
    return NULL;


}

void createGEDCOMWrapper(char* str, char * fileName)
{
    GEDCOMobject * tempObject = JSONtoGEDCOM(str);

    writeGEDCOM(fileName, tempObject);

}


GEDCOMobject* JSONtoGEDCOM(const char* str)
{


    if(str != NULL)
    {
        if(strlen(str) != 0)
        {
            GEDCOMobject * tempObject = initializeGEDCOMobject();

            char *tempFieldStorage = malloc(sizeof(char) * 256);
            char *tempDataStorage = malloc(sizeof(char) * 256);
            char *tempThreeStorage = malloc(sizeof(char) *256);
            char *tempFourStorage = malloc(sizeof(char) *256);
            char *tempFiveStorage = malloc(sizeof(char) *256);
            int tempCount = 0;
            int secondTempCount = 0;
            int countThree = 0;
            int countFour = 0;
            int countFive = 0;

            int categoryFind = 0;
            for(int i = 0; i < strlen(str); i++)
            {
                if(str[i] == ':')
                {
                    i+=2;
                    switch(categoryFind)
                    {
                        case 0:
                            categoryFind++;
                            while(str[i] != '"')
                            {
                                tempFieldStorage[tempCount] = str[i];
                                tempCount++;
                                i++;
                            }
                            // printf("case 1: <%s>\n", tempFieldStorage);
                            break;
                        case 1:
                            categoryFind++;
                            while(str[i] != '"')
                            {
                                tempDataStorage[secondTempCount] = str[i];
                                secondTempCount++;
                                i++;
                            }
                            // printf("case 2: <%s>\n", tempDataStorage);
                            break;
                        case 2:
                            categoryFind++;
                            while(str[i] != '"')
                            {
                                tempThreeStorage[countThree] = str[i];
                                countThree++;
                                i++;
                            }
                            // printf("case 3: <%s>\n", tempThreeStorage);
                            break;
                        case 3:
                            categoryFind++;
                            while(str[i] != '"')
                            {
                                tempFourStorage[countFour] = str[i];
                                countFour++;
                                i++;
                            }
                            // printf("case 4: <%s>\n", tempFourStorage);
                            break;
                        case 4:
                            categoryFind++;
                            while(str[i] != '"')
                            {
                                tempFiveStorage[countFive] = str[i];
                                countFive++;
                                i++;
                            }
                            // printf("case 5: <%s>\n\n", tempFiveStorage);
                            break;
                        default:
                            printf("error\n");
                            break;
                    }

                }
            }

            if(tempCount != 0 && secondTempCount != 0 && countThree != 0 && countFour != 0)
            {
                Submitter * tempSubm = initializeSubmitter(tempFourStorage, tempFiveStorage);
                Header * tempHeader = initializeHeader(tempFieldStorage, tempDataStorage, tempThreeStorage);
                tempObject->submitter = tempSubm;
                tempHeader->submitter = tempSubm;
                tempObject->header = tempHeader;
                // printf("results are %s\n", printGEDCOM(tempObject));
                // Individual * tempIndividual = initializeIndividual(tempFieldStorage, tempDataStorage);
                tempCount = 0;
                secondTempCount = 0;
                countThree = 0;
                countFour = 0;
                countFive = 0;
                memset(tempFieldStorage, '\0', 256);
                memset(tempDataStorage, '\0', 256);
                memset(tempThreeStorage, '\0', 256);
                memset(tempFourStorage, '\0', 256);
                memset(tempFiveStorage, '\0', 256);
                free(tempFieldStorage);
                free(tempDataStorage);
                free(tempThreeStorage);
                free(tempFourStorage);
                free(tempFiveStorage);
                return tempObject;
            }
            free(tempFieldStorage);
            free(tempDataStorage);
            free(tempThreeStorage);
            free(tempFourStorage);
            free(tempFiveStorage);
        }

    }


    return NULL;


}

//creates object for each file and then 
//returns basic information as JSON for the file viewer
char* initFilesToJSON(char* fileName)
{

    // printf("fileName is %s\n", fileName);

    char * jsonReturn = malloc(sizeof(char) * 500);

    if(strlen(fileName) != 0)
    {
        GEDCOMobject * tempObject = initializeGEDCOMobject();

        createGEDCOM(fileName, &tempObject);


        // printf("err is %u\n", err.type);

        //SOURCE/GEDVERSION/ENCODING/SUBMITTERNAME/ADDRESS/NUMIND/NUMFAM
        if(tempObject->header != NULL)
        {
            Header * tempHeader = (Header*)tempObject->header;
            sprintf(jsonReturn, "{\"source\":\"%s\", \"version\":\"%.1f\"", tempHeader->source, tempHeader->gedcVersion);


            if(tempHeader->encoding == ANSEL)
            {
                sprintf(jsonReturn + strlen(jsonReturn), ", \"encoding\":\"ANSEL\"");
            }
            else if (tempHeader->encoding == UTF8)
            {
                sprintf(jsonReturn + strlen(jsonReturn), ", \"encoding\":\"UTF-8\"");
            }
            else if (tempHeader->encoding == ASCII)
            {
                sprintf(jsonReturn + strlen(jsonReturn), ", \"encoding\":\"ASCII\"");
            }
            else if (tempHeader->encoding == UNICODE)
            {
                sprintf(jsonReturn + strlen(jsonReturn), ", \"encoding\":\"UNICODE\"");
            }

        }
        else
        {
            sprintf(jsonReturn + strlen(jsonReturn), "{\"source\":\"\", \"version\":\"\", \"encoding\":\"\"");  
        }

        if(tempObject->submitter != NULL)
        {
            Submitter * tempSubm = (Submitter*)tempObject->submitter;
            sprintf(jsonReturn + strlen(jsonReturn), ",\"submitterName\":\"%s\", \"submitterAddress\":\"%s\"", tempSubm->submitterName, tempSubm->address);

        }
        else
        {
            sprintf(jsonReturn + strlen(jsonReturn), ",\"submitterName\":\"\", \"submitterAddress\":\"\"");  
        }

        sprintf(jsonReturn + strlen(jsonReturn), ",\"totalIndividuals\":\"%d\", \"totalFamilies\":\"%d\"}", getLength(tempObject->individuals), getLength(tempObject->families));

        // free(tempObject);
        deleteGEDCOM(tempObject);
    }

    printf("json before return is %s\n", jsonReturn);
    return jsonReturn;

}

void addIndividualWrapper(char* fileName, char* IndJSON)
{

    GEDCOMobject * tempObject = initializeGEDCOMobject();
    createGEDCOM(fileName, &tempObject);

    Individual * tempIndividual = JSONtoInd(IndJSON);

    addIndividual(tempObject, tempIndividual);

    writeGEDCOM(fileName, tempObject);

    // free(tempObject);

}

void addIndividual(GEDCOMobject* obj, const Individual* toBeAdded)
{
    if(obj != NULL && toBeAdded != NULL)
    {

        insertBack(&obj->individuals, (void*)toBeAdded);
    }

}

char* grabIndList(char* fileName)
{
    GEDCOMobject * tempObject = initializeGEDCOMobject();

    createGEDCOM(fileName, &tempObject);

    char * indList = iListToJSON(tempObject->individuals);

    return indList;
}

char* iListToJSON(List iList)
{
    char * indListReturn = malloc(sizeof(char) * 1000);

    if(getLength(iList) != 0)
    {
        int lengthTrack = 0;
        int realLength = getLength(iList);
        sprintf(indListReturn + strlen(indListReturn), "[");
        void* elem;
        ListIterator elemIter = createIterator(iList);
        while((elem = nextElement(&elemIter)) != NULL)
        {

            Individual * tempIndividual = (Individual*)elem;
            char * indStr = indToJSON(tempIndividual);
            if(lengthTrack + 1 != realLength)
            {
                sprintf(indListReturn + strlen(indListReturn), "%s,", indStr);
            }
            else
            {
                sprintf(indListReturn + strlen(indListReturn), "%s", indStr);
            }

            lengthTrack++;
            free(indStr);
        }
        sprintf(indListReturn + strlen(indListReturn), "]");
    }
    else if(getLength(iList) == 0)
    {
        sprintf(indListReturn + strlen(indListReturn) , "[]");
    }


    return indListReturn;

}

char* gListToJSON(List gList)
{

    char * listReturn = malloc(sizeof(char) * 1000);
    if(getLength(gList) != 0)
    {
        sprintf(listReturn + strlen(listReturn), "[");
        int lengthTrack = 0;
        int realLength = getLength(gList);    
        void* elem;
        ListIterator elemIter = createIterator(gList);
        while((elem = nextElement(&elemIter)) != NULL)
        {
            List * tempList = (List*)elem;
            char * listStr = iListToJSON(*tempList);
            if(lengthTrack + 1 != realLength)
            {
                sprintf(listReturn + strlen(listReturn), "%s,", listStr);
            }
            else
            {
                sprintf(listReturn + strlen(listReturn), "%s", listStr);
            }
            free(listStr);
            lengthTrack++;
        }

        sprintf(listReturn + strlen(listReturn), "]");
    }
    else
    {
        sprintf(listReturn + strlen(listReturn) , "[]");
    }

    printf("ilist returns %s\n", listReturn);
    return listReturn;

}

char* printGEDCOM(const GEDCOMobject* obj)
{

    char * gedcomReturn = malloc(sizeof(char) * 1000);
    if(obj != NULL)
    {

        sprintf(gedcomReturn + strlen(gedcomReturn), "\n\nFamily Tree\n\n");

        if(obj->header != NULL)
        {
            // printf("b00ty\n");
            // Header * tempHeader = (Header*)obj->header;
            sprintf(gedcomReturn + strlen(gedcomReturn), "Header\n    Source: %s\n    GEDCOM Version: %.1f\n\n" ,obj->header->source, obj->header->gedcVersion);
            // printf("Header\nSource: %s\nGEDCOM Version: %f\nEncoding:%s\n\nHeader Other Fields:\n\n" ,obj->header->source, obj->header->gedcVersion, (char*)obj->header->encoding);
            // sprintf(gedcomReturn + strlen(gedcomReturn), "Header\nSource: %f\n", tempHeader->gedcVersion);

            if(getLength(obj->header->otherFields)!= 0)
            {
                sprintf(gedcomReturn + strlen(gedcomReturn), "    Header Other Fields:\n");
                void* headerFieldsElem;
                ListIterator headerFieldsElemIter = createIterator(obj->header->otherFields);
                while((headerFieldsElem = nextElement(&headerFieldsElemIter)) != NULL)
                {
                    Field* tempField = (Field*)headerFieldsElem;
                    sprintf(gedcomReturn + strlen(gedcomReturn), "     -%s : %s\n", tempField->tag, tempField->value);
                }
            }
        }


        if(getLength(obj->families)!= 0)
        {
            // printf("hiya\n");
            sprintf(gedcomReturn + strlen(gedcomReturn), "\n\nFamilies\n\n");
            void* familiesElem;
            ListIterator familiesElemIter = createIterator(obj->families);
            while((familiesElem = nextElement(&familiesElemIter))!= NULL)
            {
                sprintf(gedcomReturn + strlen(gedcomReturn), "Family\n");
                Family * tempFamily = (Family*)familiesElem;
                if(tempFamily->wife != NULL)
                {
                    Individual * tempWife = (Individual*)tempFamily->wife;
                    sprintf(gedcomReturn + strlen(gedcomReturn), "    Wife: %s %s\n", tempWife->givenName, tempWife->surname);

                }
                else
                {
                    sprintf(gedcomReturn + strlen(gedcomReturn), "    Wife: NULL\n");
                }

                if(tempFamily->husband != NULL)
                {
                    Individual * tempHubby = (Individual*)tempFamily->husband;
                    sprintf(gedcomReturn + strlen(gedcomReturn), "    Husband: %s %s\n", tempHubby->givenName, tempHubby->surname);
                }
                else
                {
                    sprintf(gedcomReturn + strlen(gedcomReturn), "    Husband: NULL\n");
                }

                if(getLength(tempFamily->children)!= 0)
                {
                    // printf("chi\n");
                    void* childElem;
                    ListIterator childElemIter = createIterator(tempFamily->children);
                    while((childElem = nextElement(&childElemIter)) != NULL)
                    {
                        // printf("chi\n");
                        Individual * tempChild = (Individual*)childElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "    Child: %s %s\n", tempChild->givenName, tempChild->surname);
                    }
                }
                // printf("totalFamilyEventCount is %d\n", getLength(tempFamily->events));
                if(getLength(tempFamily->events)!= 0)
                {
                    void* eventElem;
                    ListIterator eventElemIter = createIterator(tempFamily->events);
                    while((eventElem = nextElement(&eventElemIter))!= NULL)
                    {
                        Event* tempEvent = (Event*)eventElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "        Event:\n          Type: %s\n          Date: %s\n          Place: %s\n", tempEvent->type, tempEvent->date, tempEvent->place);

                        if(getLength(tempEvent->otherFields)!= 0)
                        {
                            sprintf(gedcomReturn + strlen(gedcomReturn), "            Event Fields:\n\n");
                            void* eventFieldElem;
                            ListIterator eventFieldElemIter = createIterator(tempEvent->otherFields);
                            while((eventFieldElem = nextElement(&eventFieldElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)eventFieldElem;
                                sprintf(gedcomReturn + strlen(gedcomReturn), "              %s:%s\n", tempField->tag, tempField->value);

                            }
                        }
                    }
                }

                if(getLength(tempFamily->otherFields)!= 0)
                {

                    void* familyFieldElem;
                    ListIterator familyFieldElemIter = createIterator(tempFamily->otherFields);
                    while((familyFieldElem = nextElement(&familyFieldElemIter)) != NULL)
                    {
                        // printf("\n");
                        Field * tempField = (Field*)familyFieldElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "%s:%s\n", tempField->tag, tempField->value);
                    }


                }
                // sprintf(gedcomReturn + strlen(gedcomReturn), "")

            }

        }


        if(getLength(obj->individuals)!= 0)
        {
            sprintf(gedcomReturn + strlen(gedcomReturn), "\n\nIndividuals:\n");
            void* individualElem;
            ListIterator individualElemIter = createIterator(obj->individuals);
            while((individualElem = nextElement(&individualElemIter)) != NULL)
            {
                Individual * tempIndividual = (Individual*)individualElem;
                sprintf(gedcomReturn + strlen(gedcomReturn), "\nIndividual\n    Given Name: %s\n    Surname: %s\n", tempIndividual->givenName, tempIndividual->surname);
                if(getLength(tempIndividual->events)!= 0)
                { 
                    sprintf(gedcomReturn + strlen(gedcomReturn), "\n        Events\n");
                    void* individualEventElem;
                    ListIterator individualEventElemIter = createIterator(tempIndividual->events);
                    while((individualEventElem = nextElement(&individualEventElemIter)) != NULL)
                    {

                        Event * tempEvent = (Event*)individualEventElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "           Type: %s\n           Date: %s\n           Place: %s\n", tempEvent->type, tempEvent->date, tempEvent->place);
                        if(getLength(tempEvent->otherFields)!= 0)
                        {
                            sprintf(gedcomReturn + strlen(gedcomReturn), "\n          Event other fields\n\n");
                            void* eventFieldElem;
                            ListIterator eventFieldElemIter = createIterator(tempEvent->otherFields);
                            while((eventFieldElem = nextElement(&eventFieldElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)eventFieldElem;
                                sprintf(gedcomReturn + strlen(gedcomReturn), "              EOF %s: %s\n", tempField->tag, tempField->value);
                            }
                        }

                    }
                }

                if(getLength(tempIndividual->otherFields)!= 0)
                {

                    sprintf(gedcomReturn + strlen(gedcomReturn), "       Other Fields\n");
                    void* fieldElem;
                    ListIterator fieldElemIter = createIterator(tempIndividual->otherFields);
                    while((fieldElem = nextElement(&fieldElemIter)) != NULL)
                    {
                        Field * tempField = (Field*)fieldElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "         %s:%s\n", tempField->tag, tempField->value);
                    }

                }

                if(getLength(tempIndividual->families)!= 0)
                {
                    sprintf(gedcomReturn + strlen(gedcomReturn), "       Individual Families\n");
                    void* familiesElem;
                    ListIterator familiesElemIter = createIterator(tempIndividual->families);
                    while((familiesElem = nextElement(&familiesElemIter))!= NULL)
                    {
                        sprintf(gedcomReturn + strlen(gedcomReturn), "\n         Family\n");
                        Family * tempFamily = (Family*)familiesElem;
                        if(tempFamily->wife != NULL)
                        {
                            Individual * tempWife = (Individual*)tempFamily->wife;
                            sprintf(gedcomReturn + strlen(gedcomReturn), "           Wife: %s %s\n", tempWife->givenName, tempWife->surname);

                        }
                        else
                        {
                            sprintf(gedcomReturn + strlen(gedcomReturn), "           Wife: NULL\n");
                        }

                        if(tempFamily->husband != NULL)
                        {
                            Individual * tempHubby = (Individual*)tempFamily->husband;
                            sprintf(gedcomReturn + strlen(gedcomReturn), "           Husband: %s %s\n", tempHubby->givenName, tempHubby->surname);
                        }
                        else
                        {
                            sprintf(gedcomReturn + strlen(gedcomReturn), "           Husband: NULL\n");
                        }

                        if(getLength(tempFamily->children)!= 0)
                        {
                            void* childElem;
                            ListIterator childElemIter = createIterator(tempFamily->children);
                            while((childElem = nextElement(&childElemIter)) != NULL)
                            {
                                Individual * tempChild = (Individual*)childElem;
                                sprintf(gedcomReturn + strlen(gedcomReturn), "           Child: %s %s\n", tempChild->givenName, tempChild->surname);
                            }
                        }

                        if(getLength(tempFamily->events)!= 0)
                        {
                            void* eventElem;
                            ListIterator eventElemIter = createIterator(tempFamily->events);
                            while((eventElem = nextElement(&eventElemIter))!= NULL)
                            {
                                Event* tempEvent = (Event*)eventElem;
                                sprintf(gedcomReturn + strlen(gedcomReturn), "               Event:\n                 Type: %s\n                 Date: %s\n                 Place: %s\n", tempEvent->type, tempEvent->date, tempEvent->place);

                                if(getLength(tempEvent->otherFields)!= 0)
                                {
                                    sprintf(gedcomReturn + strlen(gedcomReturn), "                 Event Other Fields:\n");
                                    void* eventFieldElem;
                                    ListIterator eventFieldElemIter = createIterator(tempEvent->otherFields);
                                    while((eventFieldElem = nextElement(&eventFieldElemIter)) != NULL)
                                    {
                                        Field * tempField = (Field*)eventFieldElem;
                                        sprintf(gedcomReturn + strlen(gedcomReturn), "                   %s:%s\n", tempField->tag, tempField->value);

                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(obj->submitter != NULL)
            {
                sprintf(gedcomReturn + strlen(gedcomReturn), "\n\nSubmitter\nName: %s\nAddress: %s\n", obj->submitter->submitterName, obj->submitter->address);
                if(getLength(obj->submitter->otherFields) != 0)
                {
                    sprintf(gedcomReturn + strlen(gedcomReturn), "Submitter Other Fields:\n");
                    void* subOtherElem;
                    ListIterator subOtherElemIter = createIterator(obj->submitter->otherFields);
                    while((subOtherElem = nextElement(&subOtherElemIter)) != NULL)
                    {
                        Field* tempField = (Field*)subOtherElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "%s:%s\n", tempField->tag, tempField->value);
                    }
                }
            }

            // }


    }



}
return gedcomReturn;
}

void deleteGEDCOM(GEDCOMobject* obj)
{

    if(obj != NULL)
    {

        if(obj->header != NULL)
        {
            if(getLength(obj->header->otherFields) != 0)
            {
                void* fieldElem;
                ListIterator fieldElemIter = createIterator(obj->header->otherFields);
                while((fieldElem = nextElement(&fieldElemIter)) != NULL)
                {
                    deleteField(fieldElem);
                    // Field* tempField = (Field*)fieldElem;
                    // if(strlen(tempField->tag) != 0)
                    // {
                        // free(tempField->tag);
                    // }

                    // if(strlen(tempField->value) != 0)
                    // {
                        // free(tempField->value);
                    // }
                    // deleteDataFromList(&obj->header->otherFields, fieldElem);
                }
            }
            free(&obj->header);
            // clearList(&obj->header->otherFields);
        }

        if(obj->submitter != NULL)
        {

            Submitter * tempSubm = (Submitter*)obj->submitter;
            if(strlen(tempSubm->address) != 0)
            {
                free(tempSubm->address);
            }

            
            if(getLength(obj->submitter->otherFields) != 0)
            {   
                void* fieldElem;

                ListIterator fieldElemIter = createIterator(obj->submitter->otherFields);
                while((fieldElem = nextElement(&fieldElemIter)) != NULL)
                {
                    deleteField(fieldElem);
        //             Field* tempField = (Field*)fieldElem;
        //             if(strlen(tempField->tag) != 0)
        //             {
        //                 free(tempField->tag);
        //             }

        //             if(strlen(tempField->value) != 0)
        //             {
        //                 free(tempField->value);
        //             }
        //             deleteDataFromList(&obj->submitter->otherFields, fieldElem);
                }
                // clearList(&obj->submitter->otherFields);
            }
        //     // obj->submitter = NULL;
            // free(&obj->submitter);
        }

        if(getLength(obj->individuals) != 0)
        {
            void* indElem;
            ListIterator indElemIter = createIterator(obj->individuals);
            while((indElem = nextElement(&indElemIter)) != NULL)
            {
                deleteIndividual(indElem);
        //         Individual * tempIndividual = (Individual*)indElem;
        //         if(getLength(tempIndividual->otherFields) != 0)
        //         {
        //             void* fieldElem;
        //             ListIterator fieldElemIter = createIterator(tempIndividual->otherFields);
        //             while((fieldElem = nextElement(&fieldElemIter)) != NULL)
        //             {
        //                 deleteField(fieldElem);
        //                 // Field* tempField = (Field*)fieldElem;
        //                 // if(strlen(tempField->tag) != 0)
        //                 // {
        //                 //     free(tempField->tag);
        //                 // }

        //                 // if(strlen(tempField->value) != 0)
        //                 // {
        //                 //     free(tempField->value);
        //                 // }
        //                 deleteDataFromList(&tempIndividual->otherFields, fieldElem);
        //             }
        //             clearList(&tempIndividual->otherFields);
        //         }
        //         clearList(&tempIndividual->families);
        //         if(strlen(tempIndividual->surname) != 0)
        //         {
        //             free(tempIndividual->surname);
        //         }
        //         if(strlen(tempIndividual->givenName) != 0)
        //         {
        //             free(tempIndividual->givenName);
        //         }

        //         void* eventElem;
        //         ListIterator eventElemIter = createIterator(tempIndividual->events);
        //         while((eventElem = nextElement(&eventElemIter)) != NULL)
        //         {
        //             Event * tempEvent = (Event*)eventElem;
        //             if(getLength(tempEvent->otherFields) != 0)
        //             {
        //                 void* fieldElem;
        //                 ListIterator fieldElemIter = createIterator(tempEvent->otherFields);
        //                 while((fieldElem = nextElement(&fieldElemIter)) != NULL)
        //                 {
        //                     Field* tempField = (Field*)fieldElem;
        //                     if(strlen(tempField->tag) != 0)
        //                     {
        //                         free(tempField->tag);
        //                     }

        //                     if(strlen(tempField->value) != 0)
        //                     {
        //                         free(tempField->value);
        //                     }
        //                     deleteDataFromList(&tempEvent->otherFields, fieldElem);
        //                 }
        //                 clearList(&tempEvent->otherFields);
        //             }
        //             // clearList(&tempEvent->otherFields);
        //             if(strlen(tempEvent->date) != 0)
        //             {
        //                 free(tempEvent->date);
        //             }
        //             if(strlen(tempEvent->place) != 0)
        //             {
        //                 free(tempEvent->place);
        //             }
        //         }
        //         clearList(&tempIndividual->events);
                deleteDataFromList(&obj->individuals, indElem);
            }
        }

        if(getLength(obj->families) != 0)
        {
            void* indElem;
            ListIterator indElemIter = createIterator(obj->families);
            while((indElem = nextElement(&indElemIter)) != NULL)
            {
                deleteFamily(indElem);
        //         Family * tempFamily = (Family*)indElem;
        //         if(getLength(tempFamily->otherFields) != 0)
        //         {
        //             void* fieldElem;
        //             ListIterator fieldElemIter = createIterator(tempFamily->otherFields);
        //             while((fieldElem = nextElement(&fieldElemIter)) != NULL)
        //             {
        //                 Field* tempField = (Field*)fieldElem;
        //                 if(strlen(tempField->tag) != 0)
        //                 {
        //                     free(tempField->tag);
        //                 }

        //                 if(strlen(tempField->value) != 0)
        //                 {
        //                     free(tempField->value);
        //                 }
        //                 deleteDataFromList(&tempFamily->otherFields, fieldElem);
        //             }
        //             clearList(&tempFamily->otherFields);
        //         }
        //         clearList(&tempFamily->children);
        //         void* eventElem;
        //         ListIterator eventElemIter = createIterator(tempFamily->events);
        //         while((eventElem = nextElement(&eventElemIter)) != NULL)
        //         {
        //             Event * tempEvent = (Event*)eventElem;
        //             if(getLength(tempEvent->otherFields) != 0)
        //             {
        //                 void* fieldElem;
        //                 ListIterator fieldElemIter = createIterator(tempEvent->otherFields);
        //                 while((fieldElem = nextElement(&fieldElemIter)) != NULL)
        //                 {
        //                     Field* tempField = (Field*)fieldElem;
        //                     if(strlen(tempField->tag) != 0)
        //                     {
        //                         free(tempField->tag);
        //                     }

        //                     if(strlen(tempField->value) != 0)
        //                     {
        //                         free(tempField->value);
        //                     }
        //                     deleteDataFromList(&tempEvent->otherFields, fieldElem);
        //                 }
        //                 clearList(&tempEvent->otherFields);
        //             }
        //             if(strlen(tempEvent->date) != 0)
        //             {
        //                 free(tempEvent->date);
        //             }
        //             if(strlen(tempEvent->place) != 0)
        //             {
        //                 free(tempEvent->place);
        //             }
        //         }
        //         clearList(&tempFamily->events);
                deleteDataFromList(&obj->families, indElem);
            }
        }
        // free(obj);
    }

}

char* printError(GEDCOMerror err)
{

    char * errorCodeReturn = malloc(sizeof(char) * 256);
    if(err.type == INV_FILE)
    {
        strcpy(errorCodeReturn, "INV_FILE: there's a problem with file argument - its null, it;âs a empty string, file doesn't exist or - cannot be opened,file doesn't have the.ics extension\n");
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
    else if (err.type == WRITE_ERROR)
    {
        strcpy(errorCodeReturn, "WRITE_ERROR: Some WRITE error has happened\n");
    }
    else if (err.type == OTHER_ERROR)
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
    if(familyRecord != NULL)
    {
        if(getLength(familyRecord->individuals) > 0 && familyRecord->individuals.head != NULL && person != NULL)
        {
            void *individualElem;
            ListIterator individualElemIter = createIterator(familyRecord->individuals);
            while((individualElem = nextElement(&individualElemIter)) != NULL)
            {

                Individual* testInd = (Individual*)individualElem;
                Individual* refInd = (Individual*)person;

                if (refInd->givenName != NULL && testInd->givenName != NULL && (strcmp(testInd->givenName, refInd->givenName ) == 0))
                {
                    // printf("given names are fucked, test is <%s> ref is <%s>\n", testInd->givenName, refInd->givenName);
                    // printf("sur names are fucked, test is <%s> ref is <%s>\n", testInd->surname, refInd->surname);

                    if (refInd->surname != NULL && testInd->surname != NULL && (strcmp(testInd->surname, refInd->surname ) == 0)){
                        // printf("surnames are fucked\n");
                        return testInd;
                    }
                }
            }
            return NULL;
        }
    }
    return NULL;
}

List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{
    List individualDescendants = initializeList(printIndividual, deleteIndividual, compareIndividuals);
    if(familyRecord != NULL)
    {
        if(person != NULL)
        {
            // Individual * individualFamilyTreePerson = findPerson(familyRecord, customIndividualCompareFunction, (void*)person);
            // printf("person getDescendants is %s %s\n", individualFamilyTreePerson->givenName, individualFamilyTreePerson->surname);
            // printf("line 2\n");
            // printf("person gname %s %s\n", person->givenName, person->surname);
            // if(getLength(individualFamilyTreePerson->families) != 1)
            // {
            individualDescendants = getChild(familyRecord, person, individualDescendants);
            // printf("list size is %d\n", getLength(individualDescendants));


            // void* tempElem;
            // ListIterator tempElemIter = createIterator(individualDescendants);
            // while((tempElem = nextElement(&tempElemIter)) != NULL)
            // {
            //     Individual * tempPerson = (Individual*)tempElem;
            //     // printf("name is %s %s\n", tempPerson->givenName, tempPerson->surname);
            // }

        }
        }
        printf("\n\n");
        return individualDescendants;

    }

    List getChild(const GEDCOMobject* familyRecord, const Individual* person, List list)
    {

        void *individualFamilyFindElem;
        ListIterator individualFamilyFindElemIter = createIterator(person->families);
        while((individualFamilyFindElem = nextElement(&individualFamilyFindElemIter)) != NULL)
        {
            Family * tempFamily = (Family*)individualFamilyFindElem;
            Individual * tempHubby = tempFamily->husband;
            Individual * tempWifey = tempFamily->wife;
            // printf("Wife: %s %s Husdand: %s %s\n", tempWifey->givenName, tempWifey->surname, tempHubby->givenName, tempHubby->surname);

            if (((strcmp(person->givenName, tempHubby->givenName) == 0) && ((strcmp(person->surname, tempHubby->surname) == 0))) || ((strcmp(person->givenName, tempWifey->givenName ) == 0) && (strcmp(person->surname, tempWifey->surname) == 0)))
            {
                if(getLength(tempFamily->children) != 0)
                {
                    void *childElem;
                    ListIterator childElemIter = createIterator(tempFamily->children);
                    while((childElem = nextElement(&childElemIter)) != NULL)
                    {
                        Individual * tempIndividual = (Individual*)childElem;
                        // printf("    %s %s\n", tempIndividual->givenName, tempIndividual->surname);
                        /*If the list is empty just add the individual */
                        if(getLength(list) == 0)
                        {
                            // printf("list empty\n");
                            insertBack(&list, tempIndividual);
                            list = getChild(familyRecord, tempIndividual, list); 
                        }
                        else
                        {
                            void* dupeElem;
                            ListIterator dupeElemIter = createIterator(list);
                            dupeElem = dupeElemIter.current->data;
                            int check = 0;
                            while(dupeElem != NULL)
                            {
                                Individual* testInd = (Individual*)childElem;
                                Individual* refInd = (Individual*)dupeElem;
                                if ((strcmp(testInd->givenName, refInd->givenName) == 0) && (strcmp(testInd->surname, refInd->surname) == 0))
                                {
                                    check = 1;
                                    break;
                                }
                                dupeElem = nextElement(&dupeElemIter);
                            }
                            if (check == 0){
                                insertBack(&list, tempIndividual);
                                list = getChild(familyRecord, tempIndividual, list);
                            }
                        }
                    }
                }
            } 
        }
        return list;
    }






    //************************************************************************************************************

    //****************************************** List helper functions *******************************************
    void deleteEvent(void* toBeDeleted)
    {

        if(toBeDeleted != NULL)
        {
            Event * tempEvent = (Event*)toBeDeleted;
            if(tempEvent->date != NULL)
            {
                free(tempEvent->date);
            }

            if(tempEvent->place != NULL)
            {
                free(tempEvent->place);
            }

            if(getLength(tempEvent->otherFields) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempEvent->otherFields);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteField(elem);
                    deleteDataFromList(&tempEvent->otherFields, elem);
                }
            }
        
        free(toBeDeleted);
        toBeDeleted = NULL;
    }
    }

    int compareEvents(const void* first,const void* second)
    {
        return strcmp((char*)first, (char*)second);
    }

    char* printEvent(void* toBePrinted)
    {
        if(toBePrinted!=NULL){
            return (char *)toBePrinted;
        }
        return NULL;
    }

    void deleteIndividual(void* toBeDeleted)
    {
        if(toBeDeleted != NULL)
        {
            Individual * tempIndividual = (Individual*)toBeDeleted;
            if(tempIndividual->givenName != NULL)
            {
                free(tempIndividual->givenName);
            }
            if(tempIndividual->surname != NULL)
            {
                free(tempIndividual->surname);
            }

            if(getLength(tempIndividual->otherFields) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempIndividual->otherFields);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteField(elem);
                    deleteDataFromList(&tempIndividual->otherFields, elem);
                }
            }

            if(getLength(tempIndividual->events) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempIndividual->otherFields);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteEvent(elem);
                    deleteDataFromList(&tempIndividual->events, elem);
                }
            }

            if(getLength(tempIndividual->families) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempIndividual->otherFields);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteFamily(elem);
                    deleteDataFromList(&tempIndividual->families, elem);
                }
            }
        
        free(toBeDeleted);
        toBeDeleted = NULL;
    }
    }

    int compareIndividuals(const void* first,const void* second)
    {
        return strcmp((char*)first, (char*)second);
    }

    char* printIndividual(void* toBePrinted)
    {
        if(toBePrinted!=NULL){
            return (char *)toBePrinted;
        }
        return NULL;
    }

    void deleteFamily(void* toBeDeleted)
    {

        if(toBeDeleted != NULL)
        {
            Family * tempFamily = (Family*)toBeDeleted;

            if(getLength(tempFamily->otherFields) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempFamily->otherFields);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteField(elem);
                    deleteDataFromList(&tempFamily->otherFields, elem);
                }
            }

            if(getLength(tempFamily->children) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempFamily->children);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteIndividual(elem);
                    deleteDataFromList(&tempFamily->children, elem);
                }
            }

            if(getLength(tempFamily->events) != 0)
            {
                void* elem;
                ListIterator elemIter = createIterator(tempFamily->events);
                while((elem = nextElement(&elemIter)) != NULL)
                {
                    deleteEvent(elem);
                    deleteDataFromList(&tempFamily->events, elem);
                }
            }
            free(toBeDeleted);
            toBeDeleted = NULL;

        }
        // toBeDeleted = NULL;
        // free(toBeDeleted);
        // free((Family*)toBeDeleted);
    }

    int compareFamilies(const void* first,const void* second)
    {
        return strcmp((char*)first, (char*)second);
    }

    char* printFamily(void* toBePrinted)
    {
        if(toBePrinted!=NULL){
            return (char *)toBePrinted;
        }
        return NULL;
    }

    void deleteGeneration(void* toBeDeleted)
    {
        toBeDeleted = NULL;
        // free(toBeDeleted);
        // free((Family*)toBeDeleted);
    }

    int compareGenerations(const void* first,const void* second)
    {
        return strcmp((char*)first, (char*)second);
    }

    char* printGeneration(void* toBePrinted)
    {
        if(toBePrinted!=NULL){
            return (char *)toBePrinted;
        }
        return NULL;
    }

    void deleteField(void* toBeDeleted)
    {

        if(toBeDeleted != NULL)
        {
            Field* fieldDelete = (Field*)toBeDeleted;
            if(fieldDelete->tag != NULL)
            {
                free(fieldDelete->tag);
            }

            if(fieldDelete->value != NULL)
            {
                free(fieldDelete->value);
            }

            free(toBeDeleted);
            toBeDeleted = NULL;
        }

    }

    int compareFields(const void* first,const void* second)
    {
        return strcmp((char*)first, (char*)second);
    }

    char* printField(void* toBePrinted)
    {
        if(toBePrinted!=NULL){


            return (char *)toBePrinted;
        }
        return NULL;
    }

    bool customIndividualCompareFunction(const void* first, const void* second)
    {
        if(strcmp((char*)first, (char*)second) == 0)
        {
            return true;
        }
        return false;
    }

    Individual * initializeIndividual(char* givenName, char* surname)
    {
        Individual* tempIndividual = malloc(sizeof(Individual));

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
        Family* tempFamily = malloc(sizeof(Family));
        tempFamily->children = initializeList(printIndividual, deleteIndividual, compareIndividuals);
        tempFamily->events = initializeList(printEvent, deleteEvent, compareEvents);
        tempFamily->otherFields = initializeList(printField, deleteField, compareFields);

        return tempFamily;

    }

    Header * initializeHeader(char* source, char* gedcVersion, char* encodingType)
    {
        // printf("source before insert is %s\n", source);
        Header* tempHeader = malloc(sizeof(Header) + 1);
        strcpy(tempHeader->source, source);
        tempHeader->gedcVersion = atof(gedcVersion);
        tempHeader->otherFields = initializeList(printField, deleteField, compareFields);
        if(strcmp(encodingType, "ANSEL")==0)
        {
            // printf("b00ty\n" );
            tempHeader->encoding = ANSEL;
            // printf("heading: %s\n", (char*)tempHeader->encoding);
        }
        else if (strcmp(encodingType, "UTF-8")==0)
        {
            tempHeader->encoding = UTF8;
        }
        else if (strcmp(encodingType, "ASCII")==0)
        {
            tempHeader->encoding = ASCII;
        }
        else if (strcmp(encodingType, "UNICODE")==0)
        {
            tempHeader->encoding = UNICODE;
        }

        return tempHeader;

    }

    GEDCOMobject * initializeGEDCOMobject()
    {
        GEDCOMobject* tempObject = malloc(sizeof(GEDCOMobject));

        tempObject->families = initializeList(printFamily, deleteFamily, compareFamilies);
        tempObject->individuals = initializeList(printIndividual, deleteIndividual, compareIndividuals);

        return tempObject;

    }

    Submitter * initializeSubmitter(char* submitterName, char* address)
    {
        Submitter* tempSubmitter;

        if(strlen(address) != 0)
        {
            tempSubmitter = malloc(sizeof(submitterName) + (sizeof(char)*(strlen(address)+1)));
            strcpy(tempSubmitter->submitterName, submitterName);
            strcpy(tempSubmitter->address, address);
            tempSubmitter->otherFields = initializeList(printField, deleteField, compareFields);

        }
        else
        {
            tempSubmitter = malloc(sizeof(submitterName) + (sizeof(char)*5));
            strcpy(tempSubmitter->submitterName, submitterName);
            strcpy(tempSubmitter->address, "");
            tempSubmitter->otherFields = initializeList(printField, deleteField, compareFields);
        }

        return tempSubmitter;
    }

    Field * initializeOtherField(char* tag, char* value)
    {
        Field* tempField = malloc(sizeof(Field));

        tempField->tag = malloc(sizeof(tag));
        tempField->value = malloc(sizeof(value));
        strcpy(tempField->tag, tag);
        strcpy(tempField->value, value);

        return tempField;

    }

    Event * initializeEvent(char* type, char* date, char* place)
    {
        Event* tempEvent = malloc(sizeof(Event));

        strcpy(tempEvent->type, type);
        tempEvent->date = malloc(sizeof(date));
        strcpy(tempEvent->date, date);
        tempEvent->place = malloc(sizeof(place)*10);
        strcpy(tempEvent->place, place);
        tempEvent->otherFields = initializeList(printField, deleteField, compareFields);

        return tempEvent;

    }
