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
#include "LinkedListAPI.h"
#include "CalenderParser.h"

Calendar* initializeCalendar(float version, char prodID[]);
Event* initializeEvent(char UID, DateTime creationDateTime);
Property* initializeProperty(char propName, char propDescr[]);
Alarm* initializeAlarm(char action, char* trigger);
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

const char* printError(ErrorCode err)
{

}

Calendar* initializeCalendar(float version, char prodID[])
{
	Calendar * temp = malloc(sizeof(Calendar));
    temp->prodID = malloc(sizeof(prodID)*1000);
    temp->version = version;
    strcpy(temp->prodID, prodID);
    temp->event = NULL;

    return Calendar
}

Event* initializeEvent(char UID, DateTime creationDateTime)
{

	Event * tempEvent = malloc(sizeof(Event));
    tempEvent->UID = malloc(sizeof(char)*1000);
    strcpy(tempEvent->UID, UID);
    tempEvent->properties = NULL;
	tempEvent->alarms = NULL;

	return tempEvent;

}

Property* initializeProperty(char propName, char propDescr[])
{

	Property * tempProp = malloc(sizeof(Property));
	tempProp->propName = malloc(sizeof(char)*200);
	// tempProp->propDescr = malloc(sizeof(propDescr));
	strcpy(tempProp->propName, propName);
	strcpy(tempProp->propDescr, propDescr);

	return tempProp;

}

Alarm* initializeAlarm(char action, char* trigger)
{

	Alarm * tempAlarm = malloc(sizeof(Alarm));
    tempAlarm->action = malloc(sizeof(char)*200);
    tempAlarm->trigger = malloc(sizeof(trigger));
    strcpy(tempAlarm->action, action);
    strcpy(tempAlarm->trigger, trigger);
    tempAlarm->properties = NULL;

    return tempAlarm;

}

DateTime* initializeDateTime(char date[], char timeValue[], bool UTC)
{
	DateTime *tempTime = malloc(sizeof(DateTime));
	strcpy(tempTime->date, date);
	strcpy(tempTime->timeValue, timeValue);
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
