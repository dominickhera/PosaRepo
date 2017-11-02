/*

 * CIS2750 F2017

 * Assignment 3

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

 * This implementation is based on the List API that I implemented in my Assignment 2 for CIS2520, which I took

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
Alarm* initializeAlarm(char* action, char* trigger);
void  tDestroy(void *data);
char * tPrint(void *toBePrinted);
int tCompare(const void * one, const void * two);

ICalErrorCode createCalendar(char* fileName, Calendar** obj)
{
    FILE *fp;
    char line[256];
    char lineStorage[256][500];
    char eventPropNameStorage[256][200];
    char eventPropDscrStorage[256][500];
    char alarmPropNameStorage[256][200];
    char alarmPropDscrStorage[256][500];
    char UIDStorage[256];
    char VersionStorage[256];
    char PROIDStorage[256];
    char DSTAMPStorage[256];
    char triggerStorage[256];
    char actionStorage[200];
    char newOtherTempStorage[256];
    float tempVersion = 0;
    char newTempStorage[200];
    char newTempDscStorage[256];
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
    int eventPropCount = 0;
    int alarmPropCount = 0;

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
                    // printf("line[%d] %s\n", count, line);
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
    Event * parseEvent;
    // Calendar *parseCalendar = *obj;
    // Event * parseEvent = NULL;
    // Alarm * tempAlarm;
    // Property* tempProperty;

    for(int i = 0; i < count; i++)
    {

        if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 0)
        {
            // printf("2\n");
            parseCalendar = malloc(sizeof(Calendar));
            parseCalendar->events = initializeList(NULL, NULL, NULL);
            parseCalendar->properties = initializeList(NULL, NULL, NULL);
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
            parseEvent = initializeEvent();
            // printf("9a\n");
            // parseCalendar->event = malloc(sizeof(Event));
            // parseCalendar->event->properties = initializeList(NULL, NULL, NULL);
            // parseCalendar->event->alarms = initializeList(NULL, NULL, NULL);

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
            strcpy(parseEvent->UID, UIDStorage);
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
                parseEvent->creationDateTime.UTC = true;
            }
            else
            {
                tempUTC = false;
                parseEvent->creationDateTime.UTC = false;
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
                strcpy(parseEvent->creationDateTime.date, tempDateStorage);
                strcpy(parseEvent->creationDateTime.time, tempTimeStorage);
            }

            tempSize = 0;
            tempCount = 0;
            tempThirdVal = 0;
            memset(otherTempStorage, '\0', 1000);
            memset(tempStorage, '\0', 1000); 
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 1)
        {
            Property * testEventInsertVal;
            for(int k = 0; k < eventPropCount; k++)
            {
                if(strlen(eventPropDscrStorage[k]) == 0)
                {
                    return INV_EVENT;
                }
                testEventInsertVal = initializeProperty(eventPropNameStorage[k], eventPropDscrStorage[k]);
                insertBack(&parseEvent->properties, (void*)testEventInsertVal);

            }
            insertBack(&parseCalendar->events, (void*)parseEvent);
            eventPropCount = 0;
            eventFlag++;
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 1)
        {
            calendarFlag++;
        }
        else if((strcasestr(lineStorage[i], "BEGIN")) && (strcasestr(lineStorage[i], "VALARM")) && eventFlag == 1 && alarmFlag == 0)
        {
            alarmFlag++;
        }
        else if((strcasestr(lineStorage[i], "TRIGGER")) && calendarFlag == 1 &&  eventFlag == 1 && alarmFlag == 1)
        {
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ';')
                {
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        newOtherTempStorage[tempSize] = lineStorage[i][j];
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempSize++;
                        j++;
                    }
                }
                else if(lineStorage[i][j] == ':')
                {
                     j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        newOtherTempStorage[tempSize] = lineStorage[i][j];
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempSize++;
                        j++;
                    }
                }
            }

            // printf("tempstorage trigger is %s size is %d\n", newOtherTempStorage, tempSize);
            if(newOtherTempStorage[0] == '\0')
            {
                return INV_EVENT;

                // printf("tempsize isnt 0\n");
            }
            // else
            // {
                // printf("temp is 0\n");
            // }
                strcpy(triggerStorage, newOtherTempStorage);
            // }
            // else
            // {§§
            //     return INV_EVENT;
            // }
            // printf("trigger storage is now %s\n", triggerStorage);
            // tempAlarm->trigger = malloc(sizeof(tempStorage));
            // strcpy(tempAlarm->trigger, triggerStorage);
            tempSize = 0;
            memset(newOtherTempStorage, '\0', 256);
            // memset(triggerStorage, '\0', 200); 
        }
        else if((strcasestr(lineStorage[i], "ACTION")) && calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1)
        {
            // printf("fuck\n");
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':')
                {
                    j++;
                    while(lineStorage[i][j+1] != '\0')
                    {
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempStorage[tempSize] = lineStorage[i][j];
                        // printf("char is %c\n", lineStorage[i][j]);
                        tempSize++;
                        j++;
                    }
                }
            }


            if(tempStorage[0] == '\0')
            {
                return INV_EVENT;
            }
            // tempStorage[tempSize - 1] = '\0';
            strcpy(actionStorage, tempStorage);
            // if(actionStorage == NULL)
            // {
            //     return INV_EVENT;
            // }
            // printf("action storage is %s, tempsize is %d\n", actionStorage, tempSize);
            // strcpy(tempAlarm->action, actionStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000); 
            // memset(actionStorage,'\0', 200);
        }
        else if((strcasestr(lineStorage[i], "END")) && (strcasestr(lineStorage[i], "VALARM")) && calendarFlag == 1 && alarmFlag == 1 && eventFlag == 1)
        {
            Property * tempAlarmProp;
            Alarm * tempAlarm;

            if(strlen(actionStorage) == 0 || strlen(triggerStorage) == 0)
            {
                return INV_EVENT;
            }
            // printf("a: %s, t: %s\n", actionStorage, triggerStorage);
            tempAlarm = initializeAlarm(actionStorage, triggerStorage);
            // printf("ta: %s, tt: %s\n", tempAlarm->action, tempAlarm->trigger);
            for(int k = 0; k < alarmPropCount; k++)
            {
                if(strlen(alarmPropDscrStorage[k]) == 0)
                {
                    return INV_EVENT;
                }
                tempAlarmProp = initializeProperty(alarmPropNameStorage[k], alarmPropDscrStorage[k]);
                insertBack(&tempAlarm->properties, (void*)tempAlarmProp);
            }
            
            memset(triggerStorage, '\0', 200);
            memset(actionStorage,'\0', 200);
            // printf("6b\n");
            alarmFlag--;
            // alarmPropCount = 0;
            // printf("6c\n");
            // printf("alarm->action is %s\n", tempAlarm->action);
            insertBack(&parseEvent->alarms, tempAlarm);
            // printf("6d\n");
        }
        //alarm property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1 && lineStorage[i][0] != ';')
        {
            // printf("test prop fucker\n");
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

            if(tempSize != 0 && tempCount != 0)
            {
                // if(newTempStorage[tempSize - 1] == '\n')
                // {
                //         newTempStorage[tempSize - 1] = '\0';
                // }

                // if(newTempDscStorage[tempCount - 1] == '\n')
                // {
                newTempDscStorage[tempCount - 1] = '\0';
                // }

                strcpy(alarmPropNameStorage[alarmPropCount], newTempStorage);
                strcpy(alarmPropDscrStorage[alarmPropCount], newTempDscStorage);
                alarmPropCount++;


            }  
            else
            {
                return INV_EVENT;
            } 

            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
            memset(newTempStorage, '\0', 200);
            memset(newTempDscStorage, '\0', 256);
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
                while(lineStorage[i][j+1] != '\0')
                {
                    newTempDscStorage[tempCount] = lineStorage[i][j];
                    tempCount++;
                    j++;
                }
            }

            if(tempSize != 0 && tempCount != 0)
            {
                // if(newTempStorage[tempSize - 1] == '\n')
                // {
                //         newTempStorage[tempSize - 1] = '\0';
                // }

                // if(newTempDscStorage[tempCount - 1] == '\n')
                // {
                // newTempDscStorage[tempCount - 1] = '\0';
                // }

                strcpy(eventPropNameStorage[eventPropCount], newTempStorage);
                strcpy(eventPropDscrStorage[eventPropCount], newTempDscStorage);
                eventPropCount++;


            }  
            else
            {
                return INV_EVENT;
            } 
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
            memset(newTempStorage, '\0', 200);
            memset(newTempDscStorage, '\0', 256);
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
        // (*obj)->events = parseCalendar->event;
        // (*obj)->events->properties = parseCalendar->event->properties;
        // (*obj)->events->alarms = parseCalendar->event->alarms;
        // strcpy((*obj)->prodID, parseCalendar->prodID);
        // *obj = parseCalendar;
        // printf("but how does this work\n");
        return OK;
    }

}

ICalErrorCode writeCalendar(char* fileName, const Calendar* obj)
{

    FILE *fo;

     if(fileName != NULL && fileName[0] != '\0')
    {
        // printf("filename is: %s", fileName);
        if((strstr(fileName, ".ics")))
        {
            if((fo = fopen(fileName, "w")))
            {

                char * calendarWrite = malloc(sizeof(char) * 1000);
                sprintf(calendarWrite, "BEGIN:VCALENDAR\nVERSION:%.2f\nPRODID:%s\n", (*obj).version, (*obj).prodID);
                // while(fgets(line, sizeof(line), fp) != NULL)
                // {
                //     if(line[strlen(line) - 1] == '\n')
                //     {
                //         line[strlen(line) - 1] = '\0';
                //     }
                //     strcpy(lineStorage[count], line);
                //     // printf("line[%d] %s\n", count, line);
                //     count++;
                // }

                fclose(fo);
            }
            else
            {
                return WRITE_ERROR;
            }
        }
        else
        {
            return WRITE_ERROR;
        }
    }
    else
    {
        return WRITE_ERROR;
    }


}

ICalErrorCode validateCalendar(const Calendar* obj)
{

}

void deleteCalendar(Calendar* obj)
{
    if(obj != NULL)
    {
        void *calPropDeleteElem;
        void *eventDeleteElem;
        ListIterator calPropDeleteIter = createIterator(obj->properties);
        while((calPropDeleteElem = nextElement(&calPropDeleteIter)) != NULL)
        {
            List* tempCalPropDelete = (List*)calPropDeleteElem;
            clearList(tempCalPropDelete);
        }

        ListIterator eventDeleteIter = createIterator(obj->events);
        while((eventDeleteElem = nextElement(&eventDeleteIter)) != NULL)
        {
            Event* tempEventDelete = (Event*)eventDeleteElem;

            void *eventAlarmsDeleteElem;
            ListIterator eventAlarmsDeleteIter = createIterator(tempEventDelete->alarms);
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
            ListIterator eventPropertiesDeleteIter = createIterator(tempEventDelete->properties);
            while((eventPropertiesDeleteElem = nextElement(&eventPropertiesDeleteIter)) != NULL)
            {
                List* tempEventPropertiesDelete = (List*)eventPropertiesDeleteElem;
                clearList(tempEventPropertiesDelete);
            }
        }

        // free(obj->events);
        free(obj);
    }
}

char* printCalendar(const Calendar* obj)
{

    char * calendarReturn = malloc(sizeof(char) * 1000);

    if(obj != NULL)
    {
        sprintf(calendarReturn, "\n\nCalendar\n     Version = %f, ProdID = %s\n", obj->version, obj->prodID);

        if(obj->events.head != NULL)
        {
            void* eventElem;
            ListIterator eventIter = createIterator(obj->events);
            while((eventElem = nextElement(&eventIter)) != NULL)
            {

                Event* tempEventPrint = (Event*)eventElem;

                sprintf(calendarReturn + strlen(calendarReturn), "\nEvent\nUID = %s\n", tempEventPrint->UID);
                // if(obj->event->creationDateTime.date != NULL)
                // {
                sprintf(calendarReturn + strlen(calendarReturn), "  creationDateTime = %s:%s UTC = %d\n", tempEventPrint->creationDateTime.date, tempEventPrint->creationDateTime.time, tempEventPrint->creationDateTime.UTC);
                // }

                if(tempEventPrint->alarms.head != NULL)
                {
                    strcat(calendarReturn, "\nAlarms:\n");
                    void* elem;
                    ListIterator eventAlarmsIter = createIterator(tempEventPrint->alarms);
                    while((elem = nextElement(&eventAlarmsIter)) != NULL)
                    {
                        Alarm* tempAlarmPrint = (Alarm*)elem;

                        sprintf(calendarReturn + strlen(calendarReturn), "  Action: %s\n    Trigger: %s\n   Properties:\n",tempAlarmPrint->action, tempAlarmPrint->trigger);
                        ListIterator eventAlarmsPropIter = createIterator(tempAlarmPrint->properties);
                        void *propElem;
                        while((propElem = nextElement(&eventAlarmsPropIter)) != NULL)
                        {
                            Property* tempPropPrint = (Property*)propElem;
                            sprintf(calendarReturn + strlen(calendarReturn), "      %s:%s\n", tempPropPrint->propName, tempPropPrint->propDescr);
                        }

                    }
                }

                strcat(calendarReturn + strlen(calendarReturn), "\nOther Properties:\n");

                void *eventPropElem;
                ListIterator eventPropertiesIter = createIterator(tempEventPrint->properties);
                while((eventPropElem = nextElement(&eventPropertiesIter)) != NULL)
                {
                    Property* tempEventPropPrint = (Property*)eventPropElem;
                    sprintf(calendarReturn + strlen(calendarReturn), "  %s:%s\n", tempEventPropPrint->propName, tempEventPropPrint->propDescr);
                }
            }
        }

        return calendarReturn;
    }

    return NULL;

}

char* printError(ICalErrorCode err)
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
    else if(err == INV_ALARM)
    {
         strcpy(errorCodeReturn, "INV_ALARM: the alarm component is malformed in some way\n");
    }
    else if(err == WRITE_ERROR)
    {
         strcpy(errorCodeReturn, "WRITE_ERROR: Error writing to calendar\n");
    }
    else if (err == OTHER_ERROR)
    {
         strcpy(errorCodeReturn, "OTHER_ERROR: Some other error has happened\n");
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

Alarm* initializeAlarm(char* action, char* trigger)
{

    Alarm * tempAlarm = malloc(sizeof(Alarm));
    tempAlarm->trigger = malloc(sizeof(char) * (strlen(trigger)+1));
    tempAlarm->properties = initializeList(NULL, NULL, NULL);

    strcpy(tempAlarm->trigger, trigger);
    strcpy(tempAlarm->action, action);

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


