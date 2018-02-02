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

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

    FILE *fp;
    char line[256];
    char lineStorage[1000][500];
    char *tempFieldStorage = malloc(sizeof(char) * 256);
    char *tempDataStorage = malloc(sizeof(char) * 256);

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
    // int headFlag = 0;
    // int indiFlag = 0;
    // int submFlag = 0;
    // int famFlag = 0;
    // int endFlag = 0;
    // int printCount = 0;
    // int subPrintCount = 0;
    int count = 0;


    if(fileName != NULL && fileName[0] != '\0')
    {
        if(strcasestr(fileName, ".ged"))
        {
            if((fp = fopen(fileName, "r")))
            {
                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    if(line[strlen(line) - 1] == '\n')
                    {
                        line[strlen(line) - 1] = '\0';
                    }

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


    for(int i = 0; i < 500; i++)
    {
        familyHusbandFindArray[i] = -1;
        familyWifeFindArray[i] = -1;
    }

    GEDCOMobject * tempObject = initializeGEDCOMobject();

    for(int i = 0; i < count; i++)
    {
        // printf("count is %d\n", count);
        // printf("line[%d]: <%s>\n", i, lineStorage[i]);
        //start of thing
        if(lineStorage[i][0] == '0')
        {
            printf("line[%d]: <%s>\n", i, lineStorage[i]);
            if(strcasestr(lineStorage[i], "HEAD"))
            {
                // printf("head found\n");
                // headFlag = 1;
                i++;
                while(lineStorage[i+1][0] != '0')
                {

                    // printf("line[%d]<%s>\n",i, lineStorage[i]);
                    // printf("first item of line is <%c>\n", lineStorage[i][0]);
                    if(strcasestr(lineStorage[i], "SOUR"))
                    {
                        for(int j = 0; j < strlen(lineStorage[i]); j++)
                        {
                            if(lineStorage[i][j] == 'R')
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


                        strcpy(sourceStore, tempFieldStorage);
                        // printf("sourceStore: <%s>\n", tempFieldStorage);
                        memset(tempFieldStorage, '\0', 256);
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
                        // printf("gedc: <%s>\n", tempFieldStorage);
                        strcpy(gedcVersionStore, tempFieldStorage);
                        memset(tempFieldStorage, '\0', 256);
                        tempSize = 0;

                    }
                    else if(strcasestr(lineStorage[i], "CHAR"))
                    {
                        for(int j = 7; j < strlen(lineStorage[i]); j++)
                        {
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;   
                        }
                        // printf("char: <%s>\n", tempFieldStorage);
                        strcpy(encodingTypeStore, tempFieldStorage);
                        memset(tempFieldStorage, '\0', 256);
                        tempSize = 0;
                    }
                    else
                    {
                        for(int j = 0; j < strlen(lineStorage[i]); j++)
                        {
                            // printf("char1[%d]: %c\n", j, lineStorage[i][j]);
                            if(isalpha((unsigned char)lineStorage[i][j+1]) != 0)
                            {
                                // printf("b00ty j is %d\n",j);
                                while(isalpha((unsigned char)lineStorage[i][j]) != 0)
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
                                        while(j < strlen(lineStorage[i]) )
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

                    // printf("header tag: <%s>, value: <%s>\n", tempFieldStorage, tempDataStorage);
                    strcpy(headerOtherFieldTagStorage[headerOtherFieldCount], tempFieldStorage);
                    strcpy(headerOtherFieldValueStorage[headerOtherFieldCount], tempDataStorage);
                    headerOtherFieldCount++;
                    memset(tempFieldStorage, '\0', 256);
                    memset(tempDataStorage, '\0', 256);
                    tempSize = 0;
                    tempSizeTwo = 0;

                }

                i++;
            }
        }
        else if(strcasestr(lineStorage[i], "INDI"))
        {
            // printf("indi found\n");
            // indiFlag = 1;
            i++;
            // printf("indi found on line %d\n", i);
            while(lineStorage[i+1][0] != '0')
            {
                // i++;

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
                    if((strcasestr(lineStorage[i+1], "DATE")))
                    {
                        // printf("(bawe111r)\n" );
                        for(int j = 0; j < strlen(lineStorage[i]); j++)
                        {
                            if(isalpha(lineStorage[i][j]) != 0)
                            {
                                while(lineStorage[i][j+1] != '\0')
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
                                while(lineStorage[i][j+1] != lineStorage[i][strlen(lineStorage[i])])
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
                            for(int j = 7; j < strlen(lineStorage[i]); j++)
                            {
                                tempFieldStorage[tempSize] = lineStorage[i][j];
                                tempSize++;
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
                                        while(j != strlen(lineStorage[i])-1)
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

            i++;
        }
        totalIndividualEventArray[totalIndividualCount] = totalIndividualEventCount;
        totalIndividualCount++;
    }
    else if(strcasestr(lineStorage[i], "FAM"))
    {
        // printf("fam found\n");
        // famFlag = 1;
        // i++;
        while(lineStorage[i+1][0] != '0')
        {
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
                printf("1\n");
                printf("line is <%s>\n", lineStorage[i]);
                 for(int j = 7; j < strlen(lineStorage[i]); j++)
                {
                    while(lineStorage[i][j] != '@' && j < strlen(lineStorage[i]) )
                    {
                        if((isalpha(lineStorage[i][j])) == 0)
                        {
                            printf("lineStorage char is currently <%c>\n", lineStorage[i][j]);
                            tempFieldStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                        }
                        j++;
                    }
                }
                printf("child num is <%d>\n", atoi(tempFieldStorage));
                // familyChildCount++;
                familyChildFindArray[familyChildCount] = atoi(tempFieldStorage) - 1;
printf("2\n");
                memset(tempFieldStorage, '\0', 256);
                printf("3\n");
                tempSize = 0;
                printf("4\n");
                familyChildCount++;
                printf("5\n");

            }
            else
            {

                if((strcasestr(lineStorage[i+1], "DATE")))
                {
                    // printf("lolcats\n");
                    for(int j = 2; j < strlen(lineStorage[i]) - 1; j++)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                    }
                    // printf("date storage thing: <%s>\n", tempFieldStorage);
                    strcpy(familyEventTypeStorage[totalFamilyEventCount], tempFieldStorage);
                    memset(tempFieldStorage, '\0', 256);
                    tempSize = 0;
                    i++;
                    for(int j = 7; j < strlen(lineStorage[i]) - 1; j++)
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
                    for(int j = 2; j < strlen(lineStorage[i]) - 1; j++)
                    {
                        tempFieldStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                    }
                    printf("date storage thing: <%s>\n", tempFieldStorage);
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
            
            }

        // i++;
    }
    totalFamilyEventArray[totalFamilyCount] = totalFamilyEventCount;
    familyChildFindCountArray[totalFamilyCount] = familyChildCount;
    totalFamilyCount++;
}
else if(strcasestr(lineStorage[i], "SUBM"))
{
    printf("subm found on line %d\n", i);
    // submFlag = 1;
    // if(strcasestr(lineStorage[i+1], "NAME"))
    // { 
    // printf("next line has name\n");
    // i++;

    while(lineStorage[i+1][0] != '0')
    {
        printf("line[%d]: <%s>\n", i, lineStorage[i]);
        // printf("this line\n");
        // i++;
        if(strcasestr(lineStorage[i+1], "NAME"))
        {
            i++;
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
            // strcpy(individualSurNameStorage[totalIndividualCount], tempDataStorage);
            memset(tempFieldStorage, '\0', 256);
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

            // i++;
            // }
    }

}
}
}
// else if(strcasestr(lineStorage[i], "TRLR"))
// {
// printf("end found\n");
// endFlag = 1;
// printf("enddddd\n");
printf("there are %d families and a total of %d kids overall\n", totalFamilyCount, familyChildCount);

// GEDCOMobject * tempObject;   
Individual * tempIndividual;
Family * tempFamily;
Header * tempHeader;
Field * tempOtherField;
Event * tempEvent;
Submitter * tempSubm;

// initializeHeader(char* source, char* gedcVersion, char* encodingType, char* submitterName, char* address)
// {
// tempObject->submitter = initializeHeader(char* source, char* gedcVersionStore, char* encodingTypeStore, char* submitterNameStore, char* submitterAddress);
// tempObject = initializeGEDCOMobject();
// printf("submittername: %s, submitterAddress: %s\n", submitterNameStore, submitterAddress);
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
        // printf("other val: <%s>\n", headerOtherFieldValueStorage[j]);
        tempOtherField = initializeOtherField(headerOtherFieldTagStorage[j], headerOtherFieldValueStorage[j]);
        insertBack(&tempHeader->otherFields, (void*)tempOtherField);
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
                                insertBack(&tempEvent->otherFields, (void*)tempOtherField);
                            }
                        }
                        else
                        {
                            for(int m = totalIndividualEventOtherFieldArray[k - 1]; m < totalIndividualEventOtherFieldArray[k]; m++)
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
                                insertBack(&tempEvent->otherFields, (void*)tempOtherField);
                            }
                        }
                        else
                        {
                            for(int m = totalIndividualEventOtherFieldArray[k - 1]; m < totalIndividualEventOtherFieldArray[k]; m++)
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
                for(int k = totalIndividualOtherFieldArray[j - 1]; k < totalIndividualOtherFieldArray[j]; k++)
                {

                    // Event * initializeEvent(char* type, char* date, char* place)
                    tempOtherField = initializeOtherField(individualOtherFieldTagStorage[k], individualOtherFieldValueStorage[k]);
                    insertBack(&tempIndividual->otherFields, (void*)tempOtherField);
                }
            }
        }

        insertBack(&tempObject->individuals, tempIndividual);
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
                                insertBack(&tempEvent->otherFields, (void*)tempOtherField);
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
                                insertBack(&tempEvent->otherFields, (void*)tempOtherField);
                            }
                        } 
                    }
                    insertBack(&tempFamily->events, tempEvent);
                }
            }
            else
            {
                for(int k = totalFamilyEventArray[j - 1]; k < totalFamilyEventArray[j] + 1; k++)
                {
                    tempEvent = initializeEvent(familyEventTypeStorage[k], familyEventDateStorage[k], familyEventPlaceStorage[k]);
                    if(k == 0)
                    {
                        if(totalFamilyEventOtherFieldArray[k] != 0)
                        {
                            for(int m = 0; m < totalFamilyOtherFieldArray[k]; m++)
                            {
                                tempOtherField = initializeOtherField(familyEventOtherFieldTagStorage[m], familyEventOtherFieldValueStorage[m]);
                                insertBack(&tempEvent->otherFields, (void*)tempOtherField);
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
                                insertBack(&tempEvent->otherFields, (void*)tempOtherField);
                            }
                        } 
                    }
                    insertBack(&tempFamily->events, tempEvent); 
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
                    insertBack(&tempFamily->otherFields, (void*)tempOtherField);

                }

            }
            else
            {
                for(int k = totalFamilyOtherFieldArray[j-1]; k < totalFamilyOtherFieldArray[j]; k++)
                {
                    tempOtherField = initializeOtherField(familyOtherFieldTagStorage[k], familyEventOtherFieldValueStorage[k]);
                    insertBack(&tempFamily->otherFields, (void*)tempOtherField);
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
            // if(j == 0)
            // {
            //     printf("here at fam %d\n", familyChildFindCountArray[j]);
            //     for(int k = 0; k < familyChildFindCountArray[j] - 1; k++)
            //     {
            //         void *individualElem;
            //         ListIterator individualElemIter = createIterator(tempObject->individuals);
            //         while((individualElem = nextElement(&individualElemIter)) != NULL)
            //         {
            //             Individual * tempIndividualFind = (Individual*)individualElem;
            //             if(strcmp(tempIndividualFind->surname, individualSurNameStorage[familyChildFindArray[k]]) == 0 && strcmp(tempIndividualFind->givenName, individualGivenNameStorage[familyChildFindArray[k]]) == 0)
            //             {
            //                 insertBack(&tempFamily->children, tempIndividualFind);
            //                 insertBack(&tempIndividualFind->families, tempFamily);
            //                 printf("surnam is <%s>\n",individualGivenNameStorage[familyChildFindArray[k]]);
            //                 // tempFamily->wife = tempIndividualFind;
            //             }
            //         }
            //     }
            // }
            // else
            // {
                for(int k = familyChildFindCountArray[j - 1]; k < familyChildFindCountArray[j]; k++)
                {
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
                            insertBack(&tempFamily->children, tempIndividualFind);
                            insertBack(&tempIndividualFind->families, tempFamily);
                            break;
                            // tempFamily->wife = tempIndividualFind;
                        }
                    }
                }
            // }
        }

        insertBack(&tempObject->families, tempFamily);
        // }
        // *obj = tempObject;
        // }
        // *obj = tempObject;

        // }

        // }
        }
*obj = tempObject;

// char * str = printGEDCOM(tempObject);
// printf("temp idea\n%s\n", str);

}
// char * str = printGEDCOM(tempObject);
// printf("temp idea\n%s\n", str);
// *obj = tempObject;
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

        sprintf(gedcomReturn + strlen(gedcomReturn), "\n\nFamily Tree\n\n");
        printf("fucker\n");
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
            printf("hiya\n");
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
                printf("totalFamilyEventCount is %d\n", getLength(tempFamily->events));
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
                    sprintf(gedcomReturn + strlen(gedcomReturn), "events\n");
                    void* individualEventElem;
                    ListIterator individualEventElemIter = createIterator(tempIndividual->events);
                    while((individualEventElem = nextElement(&individualEventElemIter)) != NULL)
                    {

                        Event * tempEvent = (Event*)individualEventElem;
                        sprintf(gedcomReturn + strlen(gedcomReturn), "Type: %s\nDate: %s\nPlace%s\n", tempEvent->type, tempEvent->date, tempEvent->place);
                        if(getLength(tempEvent->otherFields)!= 0)
                        {
                            sprintf(gedcomReturn + strlen(gedcomReturn), "event other fields\n\n");
                            void* eventFieldElem;
                            ListIterator eventFieldElemIter = createIterator(tempEvent->otherFields);
                            while((eventFieldElem = nextElement(&eventFieldElemIter)) != NULL)
                            {
                                Field * tempField = (Field*)eventFieldElem;
                                sprintf(gedcomReturn + strlen(gedcomReturn), "EOF %s: %s\n", tempField->tag, tempField->value);
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
                        sprintf(gedcomReturn + strlen(gedcomReturn), "         Family\n");
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
                void* headerFieldsElem;
                ListIterator headerFieldsElemIter = createIterator(obj->header->otherFields);
                while((headerFieldsElem = nextElement(&headerFieldsElemIter)) != NULL)
                {
                    Field* headerFieldDelete = (Field*)headerFieldsElem;
                    free(headerFieldDelete->tag);
                    free(headerFieldDelete->value);
                }
                clearList(&obj->header->otherFields);
            }

        }

        if(getLength(obj->families) != 0)
        {
            void* familyDeleteElem;
            ListIterator familyDeleteElemIter = createIterator(obj->families);
            while((familyDeleteElem = nextElement(&familyDeleteElemIter)) != NULL)
            {
                Family* familyDelete = (Family*)familyDeleteElem;
                if(getLength(familyDelete->events) != 0)
                {
                    void* familyEventsElem;
                    ListIterator familyEventsElemIter = createIterator(familyDelete->events);
                    while((familyEventsElem = nextElement(&familyEventsElemIter)) != NULL)
                    {
                        Event* familyEventDelete = (Event*)familyEventsElem;
                        free(familyEventDelete->date);
                        free(familyEventDelete->place);
                        if(getLength(familyEventDelete->otherFields) != 0)
                        {
                            void* familyEventOtherElem;
                            ListIterator familyEventOtherElemIter = createIterator(familyEventDelete->otherFields);
                            while((familyEventOtherElem = nextElement(&familyEventOtherElemIter)) != NULL)
                            {
                                Field* familyEventOtherDelete = (Field*)familyEventOtherElem;
                                free(familyEventOtherDelete->tag);
                                free(familyEventOtherDelete->value);
                            }

                            clearList(&familyEventDelete->otherFields);
                        }
                    }
                    clearList(&familyDelete->events);
                }

                if(getLength(familyDelete->children) != 0)
                {
                    void* familyChildrenElem;
                    ListIterator familyChildrenElemIter = createIterator(familyDelete->children);
                    while((familyChildrenElem = nextElement(&familyChildrenElemIter)) != NULL)
                    {
                        Individual* individualDelete = (Individual*)familyChildrenElem;
                        // free(individualDelete->givenName);
                        // free(individualDelete->surname);
                        if(getLength(individualDelete->events) != 0)
                        {
                            void* individualEventsElem;
                            ListIterator individualEventsElemIter = createIterator(individualDelete->events);
                            while((individualEventsElem = nextElement(&individualEventsElemIter)) != NULL)
                            {
                                Event* eventDelete = (Event*)individualEventsElem;
                                free(eventDelete->date);
                                free(eventDelete->place);
                                if(getLength(eventDelete->otherFields) != 0)
                                {
                                    void* eventOtherElem;
                                    ListIterator eventOtherElemIter = createIterator(eventDelete->otherFields);
                                    while((eventOtherElem = nextElement(&eventOtherElemIter)) != NULL)
                                    {
                                        Field* eventOther = (Field*)eventOtherElem;
                                        free(eventOther->tag);
                                        free(eventOther->value);
                                    }
                                    clearList(&eventDelete->otherFields);
                                }
                            }
                            clearList(&individualDelete->events);
                        }
                        if(getLength(individualDelete->families) != 0)
                        {
                            clearList(&individualDelete->families);
                        }
                        if(getLength(individualDelete->otherFields) != 0)
                        {

                            void* individualOtherElem;
                            ListIterator individualOtherElemIter = createIterator(individualDelete->otherFields);
                            while((individualOtherElem = nextElement(&individualOtherElemIter)) != NULL)
                            {
                                Field* individualOther = (Field*)individualOtherElem;
                                free(individualOther->tag);
                                free(individualOther->value);
                            }

                            clearList(&individualDelete->otherFields);

                        }
                    }
                }

                if(getLength(familyDelete->otherFields) != 0)
                {
                    void* familyOtherElem;
                    ListIterator familyOtherElemIter = createIterator(familyDelete->otherFields);
                    while((familyOtherElem = nextElement(&familyOtherElemIter)) != NULL)
                    {
                        Field* familyOtherDelete = (Field*)familyOtherElem;
                        free(familyOtherDelete->tag);
                        free(familyOtherDelete->value);
                    }
                    clearList(&familyDelete->otherFields);
                }

            }
        }

        if(getLength(obj->individuals) != 0)
        {
            void* individualElem;
            ListIterator individualElemIter = createIterator(obj->individuals);
            while((individualElem = nextElement(&individualElemIter)) != NULL)
            {
                Individual* individualDelete = (Individual*)individualElem;
                free(individualDelete->givenName);
                free(individualDelete->surname);
                if(getLength(individualDelete->events) != 0)
                {
                    void* individualEventsElem;
                    ListIterator individualEventsElemIter = createIterator(individualDelete->events);
                    while((individualEventsElem = nextElement(&individualEventsElemIter)) != NULL)
                    {
                        Event* eventDelete = (Event*)individualEventsElem;
                        free(eventDelete->date);
                        free(eventDelete->place);
                        if(getLength(eventDelete->otherFields) != 0)
                        {
                            void* eventOtherElem;
                            ListIterator eventOtherElemIter = createIterator(eventDelete->otherFields);
                            while((eventOtherElem = nextElement(&eventOtherElemIter)) != NULL)
                            {
                                Field* eventOther = (Field*)eventOtherElem;
                                free(eventOther->tag);
                                free(eventOther->value);
                            }
                            clearList(&eventDelete->otherFields);
                        }
                    }
                    clearList(&individualDelete->events);
                }
                if(getLength(individualDelete->families) != 0)
                {
                    clearList(&individualDelete->families);
                }
                if(getLength(individualDelete->otherFields) != 0)
                {

                    void* individualOtherElem;
                    ListIterator individualOtherElemIter = createIterator(individualDelete->otherFields);
                    while((individualOtherElem = nextElement(&individualOtherElemIter)) != NULL)
                    {
                        Field* individualOther = (Field*)individualOtherElem;
                        free(individualOther->tag);
                        free(individualOther->value);
                    }

                    clearList(&individualDelete->otherFields);

                }
            }
        }

        if(obj->submitter != NULL)
        {
            if(strlen(obj->submitter->address) != 0)
            {
                free(obj->submitter->address);
            }
            if(getLength(obj->submitter->otherFields) != 0)
            {
                void* submitterOtherElem;
                ListIterator submitterOtherElemIter = createIterator(obj->submitter->otherFields);
                while((submitterOtherElem = nextElement(&submitterOtherElemIter)) != NULL)
                {
                    Field* submitterOther = (Field*)submitterOtherElem;
                    free(submitterOther->tag);
                    free(submitterOther->value);

                }
                clearList(&obj->submitter->otherFields);
            }

        }
        free(obj);

    }
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
    void *individualElem;
    ListIterator individualElemIter = createIterator(familyRecord->individuals);
    while((individualElem = nextElement(&individualElemIter)) != NULL)
    {
        Individual * tempIndividualFind = (Individual*)individualElem;
        if(compareIndividuals(tempIndividualFind, (Individual*)person) == 0)
        {
            return tempIndividualFind;
        }
    }
    return NULL;
}

List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{

    // Individual * individualFamilyTreePerson = findPerson(familyRecord, customIndividualCompareFunction, (void*)person);
    List individualDescendants = initializeList(printIndividual, deleteIndividual, compareIndividuals);

    // if(getLength(individualFamilyTreePerson->families) != 0)
    // {
    //     void *individualFamilyFindElem;
    //     ListIterator individualFamilyFindElemIter = createIterator(individualFamilyTreePerson->families);
    //     while((individualFamilyFindElem = nextElement(&individualFamilyFindElemIter)) != NULL)
    //     {
    //         //this will go through all the families this person has, add all the children of each person, spouse etc
    //         if((customIndividualCompareFunction(individualFamilyTreePerson, individualFamilyFindElem->husband)) ||(customIndividualCompareFunction(individualFamilyTreePerson, individualFamilyFindElem->wife)))
    //         {
    //             if(getLength(individualFamilyFindElem->children) != 0)
    //             {

    //             }
    //         } 
    //     }
    // }
    return individualDescendants;
}
/*
   Family * getChild()
   {
   if(getLength(childFamily->children) != 0)
   {
   void *childElem;
   ListIterator childElemIter = createIterator(childFamily->children);
   while((childElem = nextElement(&childElemIter)) != NULL)
   {
   Individual *child = (Individual*)childElem;
   insertBack(&individualDescendants, child);
   getChild(child, 

   } 

   }

   }
 */





//************************************************************************************************************

//****************************************** List helper functions *******************************************
void deleteEvent(void* toBeDeleted)
{

}

int compareEvents(const void* first,const void* second)
{
    return strcmp((char*)first, (char*)second);
}

char* printEvent(void* toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
    }
    return NULL;
}

void deleteIndividual(void* toBeDeleted)
{

}

int compareIndividuals(const void* first,const void* second)
{
    return strcmp((char*)first, (char*)second);
}

char* printIndividual(void* toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
    }
    return NULL;
}

void deleteFamily(void* toBeDeleted)
{

}

int compareFamilies(const void* first,const void* second)
{
    return strcmp((char*)first, (char*)second);
}

char* printFamily(void* toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
    }
    return NULL;
}

void deleteField(void* toBeDeleted)
{

}

int compareFields(const void* first,const void* second)
{
    return strcmp((char*)first, (char*)second);
}

char* printField(void* toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
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
    Header* tempHeader = malloc(sizeof(Header));

    strcpy(tempHeader->source, source);
    tempHeader->gedcVersion = 5.1;
    tempHeader->otherFields = initializeList(printField, deleteField, compareFields);
    if(strcmp(encodingType, "ANSEL")==0)
    {
        // printf("b00ty\n" );
        tempHeader->encoding = ANSEL;
        // printf("heading: %s\n", (char*)tempHeader->encoding);
    }
    else if (strcmp(encodingType, "UTF8")==0)
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
    // case "ANSEL":
    //     tempHeader->encoding = ANSEL;
    //     break;
    // case "UTF8":
    //     tempHeader->encoding = UTF8;
    //     break;
    // case "ASCII":
    //     tempHeader->encoding = ASCII;
    //     break;
    // case "UNICODE":
    //     tempHeader->encoding = UNICODE;
    //     break;
    // default:
    //     break;
    // }
    // tempHeader->submitter = initializeSubmitter(submitterName, address);

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
    tempField->value = malloc(sizeof(value) * 3);
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
    tempEvent->place = malloc(sizeof(place));
    strcpy(tempEvent->place, place);
    tempEvent->otherFields = initializeList(printField, deleteField, compareFields);

    return tempEvent;

}
