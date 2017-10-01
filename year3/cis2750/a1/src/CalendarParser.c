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

Calendar* initializeCalendar(float version, char prodID[]);
Event* initializeEvent(char *UID, char *creationDateTime);
Property* initializeProperty(char propName, char propDescr[]);
Alarm* initializeAlarm(char action, char* trigger);
DateTime* initializeDateTime(char *date, char *timeValue, bool UTC);
void  testDestroy(void *data);
char * testPrint(void *toBePrinted);
int testCompare(const void * one, const void * two);

ErrorCode createCalendar(char* fileName, Calendar** obj)
{
    FILE *fp;
    char line[256];
    char lineStorage[256][500];
    char * fileTypeCheck;
    int count = 0;


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

Calendar* initializeCalendar(float version, char *prodID)
{
	Calendar * temp = malloc(sizeof(Calendar));
    // temp->prodID = malloc(sizeof(prodID)*1000);
    temp->version = version;
    strcpy(temp->prodID, prodID);
    temp->event = NULL;

    return temp;
}

Event* initializeEvent(char *UID, char *creationDateTime)
{

    char tempTime[256];
    char tempDate[256];
    char * boolCheck;
    bool tempUTC;

	Event * tempEvent = malloc(sizeof(Event));
    // tempEvent->UID = malloc(sizeof(char)*1000);
    strcpy(tempEvent->UID, UID);
    // tempEvent->creationDateTime = creationDateTime;

    if(creationDateTime != NULL)
    {

    if((boolCheck = strstr(creationDateTime, "Z")))
    {
        tempUTC = true;
    }
    else
    {
        tempUTC = false;
    }

    char * strTokTime;
    char * strTokDate;

    strTokTime = strtok(creationDateTime, "TZ");
    strTokDate = strtok(creationDateTime, "TZ");
    strcpy(tempTime, strTokTime);
    strcpy(tempDate, strTokDate);

    tempEvent->creationDateTime = *initializeDateTime(tempTime, tempDate, tempUTC);
    }
    else
    {
        tempEvent->creationDateTime = *initializeDateTime(NULL, NULL, NULL);
    }
    tempEvent->properties = initializeList(testPrint, testDestroy, testCompare);
	tempEvent->alarms = initializeList(testPrint, testDestroy, testCompare);

	return tempEvent;

}

Property* initializeProperty(char propName, char *propDescr)
{

	Property * tempProp = malloc(sizeof(Property));
	// tempProp->propName = malloc(sizeof(char)*200);
	// tempProp->propDescr = malloc(sizeof(propDescr));
	strcpy(tempProp->propName, &propName);
	strcpy(tempProp->propDescr, propDescr);

	return tempProp;

}

Alarm* initializeAlarm(char action, char* trigger)
{

	Alarm * tempAlarm = malloc(sizeof(Alarm));
    // tempAlarm->action = malloc(sizeof(char)*200);
    tempAlarm->trigger = malloc(sizeof(trigger));
    strcpy(tempAlarm->action, &action);
    strcpy(tempAlarm->trigger, trigger);
    tempAlarm->properties = initializeList(testPrint, testDestroy, testCompare);

    return tempAlarm;

}

DateTime* initializeDateTime(char *date, char *timeValue, bool UTC)
{
	DateTime *tempTime = malloc(sizeof(DateTime));
	strcpy(tempTime->date, date);
	strcpy(tempTime->time, timeValue);
	tempTime->UTC = UTC;
	// tempTime->date = malloc(sizeof(char) * 9);
	// tempTime->time = malloc

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
