/*

 * CIS2750 F2017

 * Assignment 1

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

 * This implementation is based on the List API that I implemented in my Assignment 1 for CIS2520, which I took

 * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

 * my current CIS2750 professor, Denis Nikitenko.

 */

#include <string.h>
#include <stdio.h>
#include <ctype.h>
// #include "LinkedListAPI.h"
#include "CalendarParser.h"

Calendar* initializeCalendar();
Event* initializeEvent();
Property* initializeProperty(char propName, char propDescr[]);
Alarm* initializeAlarm();
DateTime* initializeDateTime(char *date, char *timeValue, bool UTC);
void  testDestroy(void *data);
char * testPrint(void *toBePrinted);
int testCompare(const void * one, const void * two);

ErrorCode createCalendar(char* fileName, Calendar** obj)
{
    FILE *fp;
    char line[256];
    char lineStorage[256][500];
    char UIDStorage[256];
    char VersionStorage[256];
    char PROIDStorage[256];
    char DSTAMPStorage[256];
    char triggerStorage[256];
    char actionStorage[128];
    char * tempStorage = malloc(sizeof(char) * 1000);
    char * otherTempStorage = malloc(sizeof(char) * 1000);
    char * fileTypeCheck;
    char * calenderCheck;
    char * eventCheck;
    char * alarmCheck;
    // char * propertyCheck;
    char * UIDCheck;
    char * versionCheck;
    char * proIDCheck;
    char * beginCheck;
    char * endCheck;
    char * timeStampCheck;
    char * otherCheck;
    int count = 0;
    int tempSize = 0;
    int eventFlag = 0;
    int calendarFlag = 0;
    int alarmFlag = 0;
    // int propertyFlag = 0;
    int tempCount = 0;


    //parsing into a string array
    if(fileName != NULL && fileName[0] == '\0')
    {
        if((fileTypeCheck = strstr(fileName, ".ics")))
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
                return INV_FILE;
            }
        }
        else
        {
            return INV_FILE;
        }
    }
    else
    {
        return INV_FILE;
    }

    Calendar * parseCalendar = NULL;
    Event * parseEvent = NULL;
    Alarm * tempAlarm;
    Property * tempProperty;

    //time to actually start going through the file and figuring out what the fuck is in here

    for(int i = 0; i < count; i++)
    {
        if((beginCheck = strcasestr(lineStorage[i], "BEGIN")) && (calenderCheck = strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 0)
        {
            parseCalendar = initializeCalendar();
            calendarFlag++;
        }
        else if((proIDCheck = strcasestr(lineStorage[i], "PROID")))
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(PROIDStorage, tempStorage);
            strcpy(parseCalendar->prodID, PROIDStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000);
        }
        else if((versionCheck = strcasestr(lineStorage[i], "VERSION")))
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(VersionStorage, tempStorage);
            parseCalendar->version = atof(VersionStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000);
        }
        else if((beginCheck = strcasestr(lineStorage[i], "BEGIN")) && (eventCheck = strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 0)
        {
            eventFlag++;
            parseEvent = initializeEvent();
            parseCalendar->event = parseEvent;
        }
        else if((UIDCheck = strcasestr(lineStorage[i], "UID")) && eventFlag != 0)
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(UIDStorage, tempStorage);
            strcpy(parseEvent->UID, UIDStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
        }
        else if((timeStampCheck = strcasestr(lineStorage[i], "DSTAMP")))
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(DSTAMPStorage, tempStorage);
            char tempTime[7];
            char tempDate[9];
            char * boolCheck;
            bool tempUTC;
            if((boolCheck = strstr(DSTAMPStorage, "Z")))
            {
                tempUTC = true;
            }
            else
            {
                tempUTC = false;
            }

            char * strTokTime;
            char * strTokDate;

            strTokTime = strtok(DSTAMPStorage, "T Z");
            strTokDate = strtok(DSTAMPStorage, "T Z");
            strcpy(tempTime, strTokTime);
            strcpy(tempDate, strTokDate);

            parseEvent->creationDateTime = *initializeDateTime(tempTime, tempDate, tempUTC);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
        }
        else if((endCheck = strcasestr(lineStorage[i], "END")) && (eventCheck = strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 1)
        {
            eventFlag--;
        }
        else if((beginCheck = strcasestr(lineStorage[i], "BEGIN")) && (alarmCheck = strcasestr(lineStorage[i], "VALARM")) && eventFlag == 1 && alarmFlag == 0)
        {
            alarmFlag++;
            tempAlarm = (Alarm*)malloc(sizeof(Alarm));
            // parseEvent->alarms = initializeAlarm();
        }
        else if((otherCheck = strcasestr(lineStorage[i], "TRIGGER")) && eventFlag == 1 && alarmFlag == 1)
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ';')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(triggerStorage, tempStorage);
            strcpy(tempAlarm->trigger, triggerStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
        }
        else if((otherCheck = strcasestr(lineStorage[i], "ACTION")) && eventFlag == 1 && alarmFlag == 1)
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }

            strcpy(actionStorage, tempStorage);
            strcpy(tempAlarm->action, actionStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
        }
        else if((endCheck = strcasestr(lineStorage[i], "END")) && (alarmCheck = strcasestr(lineStorage[i], "VALARM")) && alarmFlag == 1 && eventFlag == 1)
        {
            alarmFlag--;
            insertFront(&parseEvent->alarms, (void*)tempAlarm);
        }
        //alarm property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1)
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':' || lineStorage[i][j] != ';')
                {
                    j++;
                    while(lineStorage[i][j] != '\0' || lineStorage[i][j] != ';')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
                else
                {
                    while(lineStorage[i][j] != ':' || lineStorage[i][j] != ';')
                    {
                        otherTempStorage[tempCount] = lineStorage[i][j];
                        tempCount++;
                        j++;
                    }
                    // tempCount++;
                }
            }

            tempProperty = initializeProperty(*tempStorage, otherTempStorage);
            insertFront(&tempAlarm->properties, (void *)tempProperty);
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
        }
        //event property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 0)
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':' || lineStorage[i][j] != ';')
                {
                    j++;
                    while(lineStorage[i][j] != '\0' || lineStorage[i][j] != ';')
                    {
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
                else
                {
                    while(lineStorage[i][j] != ':' || lineStorage[i][j] != ';')
                    {
                        otherTempStorage[tempCount] = lineStorage[i][j];
                        tempCount++;
                        j++;
                    }
                    // tempCount++;
                }
            }

            tempProperty = initializeProperty(*tempStorage, otherTempStorage);
            insertFront(&parseEvent->properties, tempProperty);
            tempSize = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
        }


    }
}

void deleteCalendar(Calendar* obj)
{

}

char* printCalendar(const Calendar* obj)
{

}

char* printError(ErrorCode err)
{

}

Calendar* initializeCalendar()
{
    Calendar * temp = malloc(sizeof(Calendar));
    temp->event = NULL;

    return temp;
}

Event* initializeEvent()
{

    Event * tempEvent = malloc(sizeof(Event));
    tempEvent->properties = initializeList(testPrint, testDestroy, testCompare);
    tempEvent->alarms = initializeList(testPrint, testDestroy, testCompare);

    return tempEvent;

}

Property* initializeProperty(char propName, char *propDescr)
{

    Property * tempProp = malloc(sizeof(Property));
    strcpy(tempProp->propName, &propName);
    strcpy(tempProp->propDescr, propDescr);

    return tempProp;

}

Alarm* initializeAlarm()
{

    Alarm * tempAlarm = malloc(sizeof(Alarm));
    tempAlarm->properties = initializeList(testPrint, testDestroy, testCompare);

    return tempAlarm;

}

DateTime* initializeDateTime(char *date, char *timeValue, bool UTC)
{
    DateTime *tempTime = malloc(sizeof(DateTime));
    strcpy(tempTime->date, date);
    strcpy(tempTime->time, timeValue);
    tempTime->UTC = UTC;

    return tempTime;
}

void  testDestroy(void *data)
{
    free(data);
}

char * testPrint(void *toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
    }
    return NULL;
}

int testCompare(const void * one, const void * two)
{
    return strcmp((char*)one, (char*)two);
}
