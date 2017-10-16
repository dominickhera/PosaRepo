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
#include "CalendarParser.h"

Event* initializeEvent();
Property* initializeProperty(char* propName, char* propDescr);
Alarm* initializeAlarm();
void  tDestroy(void *data);
char * tPrint(void *toBePrinted);
int tCompare(const void * one, const void * two);

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
    float tempVersion = 0;
    char newTempStorage[256];
    char newTempDscStorage[200];
    char *tempStorage = malloc(sizeof(char) * 1000);
    char *otherTempStorage = malloc(sizeof(char) * 9);
    char tempDateStorage[9];
    char tempTimeStorage[7];
    int count = 0;
    int tempSize = 0;
    int eventFlag = 0;
    int calendarFlag = 0;
    int alarmFlag = 0;
    int versionFlag = 0;
    int proidFlag = 0;
    int uidFlag = 0;
    int dstampFlag = 0;
    int tempCount = 0;

    //parsing into a string array
    if(fileName != NULL && fileName[0] != '\0')
    {
        // printf("filename is: %s", fileName);
        if((strstr(fileName, ".ics")))
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

    Calendar* parseCalendar;
    // Calendar *parseCalendar = *obj;
    // Event * parseEvent = NULL;
    Alarm * tempAlarm;
    Property* tempProperty;

    for(int i = 0; i < count; i++)
    {
        if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 0)
        {
            // printf("2\n");
            parseCalendar = malloc(sizeof(Calendar));
            // (*obj) = malloc(sizeof(Calendar));
            // parseCalendar = initializeCalendar();
            calendarFlag++;
            // printf("count = %d\n", i);
        }
        else if((strcasestr(lineStorage[i], "PRODID")) && calendarFlag == 1)
        {
            // printf("3\n");

            if(proidFlag == 0)
            {
                proidFlag++;
                for(int j = 0; j < strlen(lineStorage[i]); j++)
                {
                    // printf("4\n");
                    if(lineStorage[i][j] == ':')
                    {
                        // printf("5\n");
                        j++;
                        while(lineStorage[i][j+1] != '\0')
                        {
                            // printf("6\n");
                            tempStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                        }
                    }
                }

                if(tempSize != 0)
                {



                    strcpy(PROIDStorage, tempStorage);
                    strcpy(parseCalendar->prodID, PROIDStorage);
                }
                else
                {
                    return INV_PRODID;
                }


                tempSize = 0;
                memset(tempStorage, '\0', 1000);
            }
            else
            {
                return DUP_PRODID;
            }
        }
        else if((strcasestr(lineStorage[i], "VERSION")) && calendarFlag == 1 && versionFlag == 0)
        {
            // printf("8\n");
            if((strcasestr(lineStorage[i], "2")))
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
                tempVersion = atof(VersionStorage);
                // parseCalendar->version = tempVersion;
                parseCalendar->version = tempVersion;
                tempSize = 0;
                memset(tempStorage, '\0', 1000);
                versionFlag++;
            }
            else
            {
                return INV_VER;
            }
        }
        else if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 0 && calendarFlag == 1)
        {
            // printf("9\n");
            eventFlag++;
            // parseEvent = initializeEvent();
            parseCalendar->event = initializeEvent();
            // (*obj)->event->properties = initializeList(NULL, NULL, NULL);
            // (*obj)->event->alarms = initializeList(NULL, NULL, NULL);
            // parseCalendar->event = parseEvent;
        }
        else if((strcasestr(lineStorage[i], "UID")) && eventFlag == 1)
        {
            // printf("10\n");
            uidFlag++;
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
            strcpy(parseCalendar->event->UID, UIDStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
        }
        else if((strcasestr(lineStorage[i], "DTSTAMP")) && dstampFlag == 0)
        {
            // printf("11\n");
            dstampFlag++;
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
            // char * boolCheck;
            bool tempUTC;
            int tempThirdVal = 0;
            if((strcasestr(DSTAMPStorage, "Z")))
            {
                tempUTC = true;
                parseCalendar->event->creationDateTime.UTC = true;
            }
            else
            {
                tempUTC = false;
                parseCalendar->event->creationDateTime.UTC = false;
            }

            for(int j = 0; j < strlen(DSTAMPStorage); j++)
            {

                while(DSTAMPStorage[j] != 'T')
                {
                    if(DSTAMPStorage[j] != 'T')
                    {
                        tempDateStorage[tempCount] = DSTAMPStorage[j];
                        j++;
                        tempCount++;
                    }
                    else
                    {
                        j++;
                    }
                }

                j++;
                if(tempUTC == true)
                {
                    while(DSTAMPStorage[j+1] != '\0')
                    {

                        if(DSTAMPStorage[j] != 'Z')
                        {
                            tempTimeStorage[tempThirdVal] = DSTAMPStorage[j];
                            j++;
                            tempThirdVal++;
                        }
                        else
                        {
                            j++;
                        }
                    }
                }
                else
                {
                    while(DSTAMPStorage[j+1] != '\0')
                    {
                        tempTimeStorage[tempThirdVal] = DSTAMPStorage[j];
                        j++;
                        tempThirdVal++;
                    }
                }

            }

            if((!strcasestr(DSTAMPStorage, "T")) || tempThirdVal > 7 || tempCount > 9 || tempThirdVal < 5 || tempCount < 7)
            {
                return INV_CREATEDT;
            }
            else
            {
                strcpy(parseCalendar->event->creationDateTime.date, tempDateStorage);
                strcpy(parseCalendar->event->creationDateTime.time, tempTimeStorage);
            }

            tempSize = 0;
            tempCount = 0;
            tempThirdVal = 0;
            memset(otherTempStorage, '\0', 1000);
            memset(tempStorage, '\0', 1000); 
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 1)
        {
            eventFlag++;
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 1)
        {
            calendarFlag++;
        }
        else if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VALARM")) && eventFlag == 1 && alarmFlag == 0)
        {
            // printf("13\n");
            // printf("fuck\n");
            alarmFlag++;
            tempAlarm = (Alarm*)malloc(sizeof(Alarm));
            // parseEvent->alarms = initializeAlarm();
        }
        else if((strcasestr(lineStorage[i], "TRIGGER")) && calendarFlag == 1 &&  eventFlag == 1 && alarmFlag == 1)
        {
            printf("14\n");
            // printf("fuck\n");
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
        else if((strcasestr(lineStorage[i], "ACTION")) && calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1)
        {
            printf("fuck\n");
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
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VALARM")) && calendarFlag == 1 && alarmFlag == 1 && eventFlag == 1)
        {
            printf("6\n");
            alarmFlag--;
            insertFront(&parseCalendar->event->alarms, (void*)tempAlarm);
        }
        //alarm property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1 && lineStorage[i][0] != ';')
        {
            // printf("fucker\n");
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
                else
                {
                    while(lineStorage[i][j] != ':')
                    {
                        otherTempStorage[tempCount] = lineStorage[i][j];
                        tempCount++;
                        j++;
                    }
                    // tempCount++;
                }
            }


            tempProperty = initializeProperty(tempStorage, otherTempStorage);
            insertFront(&tempAlarm->properties, tempProperty);
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
        }
        //event property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 0 && lineStorage[i][0] != ';')
        {

            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] != ':')
                {
                    // j++;
                    while(lineStorage[i][j] != ':')
                    {
                        if(lineStorage[i][j] != ';')
                        {
                            newTempStorage[tempSize] = lineStorage[i][j];
                            tempSize++;
                            j++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                j++;
                while(lineStorage[i][j] != '\0')
                {
                    newTempDscStorage[tempCount] = lineStorage[i][j];
                    tempCount++;
                    j++;
                }
            }

            if(strcmp(newTempStorage, "") != 0 && strcmp(newTempDscStorage, " ") != 0)
            {
            printf("suck a dick\n");
                printf("tempStorage = %s, otherTempStorage = %s\n", newTempStorage, newTempDscStorage);
                tempProperty = initializeProperty(newTempStorage, newTempDscStorage);
                // printf("temp proerpty is %s\n", newTempProperty->propDescr);

                // insertBack(&parseCalendar->event->properties, (void *)tempProperty);
                insertBack(&parseCalendar->event->properties, (void*)tempProperty);
                printf("head val should be %p\n", (void*)parseCalendar->event->properties.head->data);
            }  
            else
            {
                return INV_EVENT;
            } 
            // printf("init: %s, desc: %s\n", getFromBack(&(*obj)->event->properties)->propName, getFromBack(&(*obj)->event->properties)->propDescr);
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
            memset(newTempStorage, '\0', 256);
            memset(newTempDscStorage, '\0', 200);
            // memset(finalTempStorage, '\0', 256);
        }
        else if((strcasestr(lineStorage[i], "VERSION")) && versionFlag == 1)
        {
            return DUP_VER;
        }
        else if((strcasestr(lineStorage[i], "PROID")) && proidFlag == 1)
        {
            return DUP_PRODID;
        }
        // printf("uh\n");
    }
    // printf("hi\n");

    if(calendarFlag != 2 || proidFlag != 1 || versionFlag != 1 || eventFlag != 2)
    {
        // printf("fuck\n");
        return INV_CAL;
    }
    else  if(uidFlag != 1 || dstampFlag != 1)
    {
        return INV_EVENT;
    }
    else
    {
        // printf("what\n");
        *obj = parseCalendar;
        (*obj)->event = parseCalendar->event;
        // strcpy((*obj)->prodID, parseCalendar->prodID);
        // *obj = parseCalendar;
        // printf("but how does this work\n");
        return OK;
    }

}

void deleteCalendar(Calendar* obj)
{
    if(obj != NULL)
    {

        void *eventAlarmsDeleteElem;
        ListIterator eventAlarmsDeleteIter = createIterator(obj->event->alarms);
        while((eventAlarmsDeleteElem = nextElement(&eventAlarmsDeleteIter)) != NULL)
        {
            Alarm* tempEventAlarmDelete = (Alarm*)eventAlarmsDeleteElem;
            // clearList(tempEventAlarmDelete);
            void *alarmPropDeleteElem;
            ListIterator alarmPropDeleteIter = createIterator(tempEventAlarmDelete->properties);
            while((alarmPropDeleteElem = nextElement(&alarmPropDeleteIter)) != NULL)
            {
                List* tempAlarmPropDelete = (List*)alarmPropDeleteElem; 
                clearList(tempAlarmPropDelete);
            }
        }

        void *eventPropertiesDeleteElem;
        ListIterator eventPropertiesDeleteIter = createIterator(obj->event->properties);
        while((eventPropertiesDeleteElem = nextElement(&eventPropertiesDeleteIter)) != NULL)
        {
            List* tempEventPropertiesDelete = (List*)eventPropertiesDeleteElem;
            clearList(tempEventPropertiesDelete);
        }

        free(obj->event);
        free(obj);
    }
}

char* printCalendar(const Calendar* obj)
{

    char * calendarReturn = malloc(sizeof(char) * 1000);

    if(obj != NULL)
    {
        sprintf(calendarReturn, "Calendar\nVersion = %f, ProdID = %s\n", obj->version, obj->prodID);

        if(obj->event != NULL)
        {

            sprintf(calendarReturn + strlen(calendarReturn), "Event\nUID = %s\n", obj->event->UID);
            // if(obj->event->creationDateTime.date != NULL)
            // {
            sprintf(calendarReturn + strlen(calendarReturn), "creationDateTime = %s:%s UTC = %d\n", obj->event->creationDateTime.date, obj->event->creationDateTime.time, obj->event->creationDateTime.UTC);
            // }

            if(obj->event->alarms.head != NULL)
            {
                strcat(calendarReturn, "Alarms:\n");
                void* elem;
                ListIterator eventAlarmsIter = createIterator(obj->event->alarms);
                while((elem = nextElement(&eventAlarmsIter)) != NULL)
                {
                    Alarm* tempAlarmPrint = (Alarm*)elem;

                    sprintf(calendarReturn + strlen(calendarReturn), "Action: %s\nTrigger: %s\nProperties: \n",tempAlarmPrint->action, tempAlarmPrint->trigger);
                    ListIterator eventAlarmsPropIter = createIterator(tempAlarmPrint->properties);
                    void *propElem;
                    while((propElem = nextElement(&eventAlarmsPropIter)) != NULL)
                    {
                        Property* tempPropPrint = (Property*)propElem;
                        sprintf(calendarReturn + strlen(calendarReturn), "%s:%s\n", tempPropPrint->propName, tempPropPrint->propDescr);
                    }

                }
            }

            strcat(calendarReturn + strlen(calendarReturn), "Other Properties:\n");

            void *eventPropElem;
            ListIterator eventPropertiesIter = createIterator(obj->event->properties);
            while((eventPropElem = nextElement(&eventPropertiesIter)) != NULL)
            {
                Property* tempEventPropPrint = (Property*)eventPropElem;
                sprintf(calendarReturn + strlen(calendarReturn), "%s:%s\n", tempEventPropPrint->propName, tempEventPropPrint->propDescr);
            }

        }

        return calendarReturn;
    }

    return NULL;

}

char* printError(ErrorCode err)
{

    // printf("%U is entered\n", err);
    char * errorCodeReturn = malloc(sizeof(char) * 256);
    if(err == INV_FILE)
    {
        strcpy(errorCodeReturn, "INV_FILE: there’s a problem with file argument - its null, it;’s a empty string, file doesn't exist or - cannot be opened,file doesn't have the.ics extension\n");
    }
    else if(err == INV_VER)
    {

        strcpy(errorCodeReturn, "INV_VER: the calendar version property is present but malformed\n");
    }
    else if(err == DUP_VER)
    {

        strcpy(errorCodeReturn,"DUP_VER: the calendar version property appears more than once\n");
    }
    else if(err == INV_PRODID)
    {

        strcpy(errorCodeReturn, "INV_PRODID: the product ID property is present but malformed\n");
    }
    else if(err == DUP_PRODID)
    {

        strcpy(errorCodeReturn, "DUP_PRODID: the product ID property appears more than once\n");
    }
    else if(err == INV_CAL)
    {

        strcpy(errorCodeReturn, "INV_CAL: the calendar itself is invalid (missing required properties or components, invalid opening - closingtags,etc.)\n");
    }
    else if(err == INV_CREATEDT)
    {

        strcpy(errorCodeReturn, "INV_CREADEDT: the event creation date-time property is malformed in some way\n");
    }
    else if(err == INV_EVENT)
    {

        strcpy(errorCodeReturn, "INV_EVENT: the event component is malformed in some way\n");
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

Event* initializeEvent()
{

    Event * tempEvent = malloc(sizeof(Event));
    tempEvent->properties = initializeList(NULL, NULL, NULL);
    tempEvent->alarms = initializeList(NULL, NULL, NULL);

    return tempEvent;

}

Property* initializeProperty(char* propName, char* propDescr)
{

    Property* tempProp;

    tempProp = malloc(sizeof(Property) + (sizeof(char)*(strlen(propDescr)+1)));
    strcpy(tempProp->propName, propName);
    strcpy(tempProp->propDescr, propDescr);
    // printf("name: %s, dsc: %s\n", tempProp->propName, tempProp->propDescr);

    return tempProp;

}

Alarm* initializeAlarm()
{

    Alarm * tempAlarm = malloc(sizeof(Alarm));
    tempAlarm->properties = initializeList(NULL, NULL, NULL);

    return tempAlarm;

}

void  tDestroy(void *data)
{
    free(data);
}

char * tPrint(void *toBePrinted)
{
    if(toBePrinted!=NULL){
        return strdup((char *)toBePrinted);
    }
    return NULL;
}

int tCompare(const void * one, const void * two)
{
    return strcmp((char*)one, (char*)two);
}


