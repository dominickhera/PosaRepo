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
#include "LinkedListAPI.h"
#include "CalenderParser.h"

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

	/*

	//allocating and assigning values to ical object

    Calendar * temp = malloc(sizeof(Calendar));
    temp->prodID = malloc(sizeof(prodID));
    temp->version = version;
    strcpy(temp->prodID, prodID);
    */

    /*

    //allocating and assigning values to event object

    Event * tempEvent = malloc(sizeof(Event));
    tempEvent->UID = malloc(sizeof(tempEvent->UID));
    strcpy(tempEvent->UID, UID);
    */

    /*

    //allocating and assigning values to alarm object, might move into seperate function since it can be called multiple times(?) ithink 

    Alarm * tempAlarm = malloc(sizeof(Alarm));
    tempAlarm->action = malloc(sizeof(char)*200);
    tempAlarm->trigger = malloc(sizeof(trigger));
    strcpy(tempAlarm->action, action);
    strcpy(tempAlarm->trigger, trigger);
	*/

	/*

	//allocating information regarding property within an ical event(?) i think
	//moving to seperate function since it can be called N amount of times provided types dont repeat

	Property * tempProp = malloc(sizeof(Property));
	tempProp->propName = malloc(sizeof(char)*200);
	tempProp->propDescr = malloc(sizeof(propDescr));
	strcpy(tempProp->propName, propName);
	strcpy(tempProp->propDescr, propDescr);

	*/


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
