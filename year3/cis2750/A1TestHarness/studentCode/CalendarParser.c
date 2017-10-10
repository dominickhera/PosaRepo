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
Property* initializeProperty(char propName, char propDescr[]);
Alarm* initializeAlarm();
// DateTime* initializeDateTime(char *date, char *timeValue, bool UTC);
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
    char *tempStorage = malloc(sizeof(char) * 1000);
    char *otherTempStorage = malloc(sizeof(char) * 9);
    // char *tempThirdStorage = malloc(sizeof(char) * 7);
    char tempDateStorage[9];
    char tempTimeStorage[7];
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
    int versionFlag = 0;
    int proidFlag = 0;
    int tempCount = 0;


    // printf("fucker\n");
    //parsing into a string array
    if(fileName != NULL && fileName[0] != '\0')
    {
        // printf("hi\n");
        if((fileTypeCheck = strstr(fileName, ".ics")))
        {
            // printf("fuck\n");
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

    Calendar *parseCalendar = *obj;
    Event * parseEvent = NULL;
    Alarm * tempAlarm;
    Property * tempProperty;
    printf("1\n");
    // printf("hi\n")m;
    //time to actually start going through the file and figuring out what the fuck is in here

    for(int i = 0; i < count; i++)
    {
        if((beginCheck = strcasestr(lineStorage[i], "BEGIN")) && (calenderCheck = strcasestr(lineStorage[i], "VCALENDAR")) && calendarFlag == 0)
        {
            printf("2\n");
            parseCalendar = malloc(sizeof(Calendar));
            // parseCalendar = initializeCalendar();
            calendarFlag++;
            // printf("count = %d\n", i);
        }
        else if((proIDCheck = strcasestr(lineStorage[i], "PRODID")) && calendarFlag == 1)
        {
            printf("3\n");
            proidFlag++;
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                // printf("4\n");
                if(lineStorage[i][j] == ':')
                {
                    printf("5\n");
                    j++;
                    while(lineStorage[i][j] != '\0')
                    {
                        // printf("6\n");
                        tempStorage[tempSize] = lineStorage[i][j];
                        tempSize++;
                        j++;
                    }
                }
            }
            printf("7\n");
            strcpy(PROIDStorage, tempStorage);
            printf("7.1\n");
            strcpy(parseCalendar->prodID, PROIDStorage);
            printf("7.2\n");
            // strcpy(obj->prodID, PROIDStorage);
            tempSize = 0;
            memset(tempStorage, '\0', 1000);
        }
        else if((versionCheck = strcasestr(lineStorage[i], "VERSION")) && calendarFlag == 1)
        {
            printf("8\n");
            if((otherCheck = strcasestr(lineStorage[i], "2")))
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

                printf("8.1\n");
                strcpy(VersionStorage, tempStorage);
                printf("8.3\n");

                for(int j = 0; j < strlen(VersionStorage); j++)
                {
                    printf("char is %c\n", VersionStorage[j]);
                }
                // if(VersionStorage[strlen(VersionStorage) - 1] == '\n')
                // {
                //         VersionStorage[strlen(VersionStorage) - 1] = '\0';
                // }
                tempVersion = atof(VersionStorage);
                printf("8.3.5\n");
                printf("atofuck is %.1f, tempSize is %d\n", atof(VersionStorage), tempSize);
                // parseCalendar->version = 2;
                // printf("versionStorage = %f\n", parseCalendar->version);
                // strcpy(parseCalendar->version,(versionStorage));
                parseCalendar->version = tempVersion;
                printf("8.4\n");
                tempSize = 0;
                printf("8.5\n");
                memset(tempStorage, '\0', 1000);
            }
            else
            {
                return INV_VER;
            }
        }
        else if((beginCheck = strcasestr(lineStorage[i], "BEGIN")) && (eventCheck = strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 0 && calendarFlag == 1)
        {
            printf("9\n");
            eventFlag++;
            parseEvent = initializeEvent();
            parseCalendar->event = parseEvent;
        }
        else if((UIDCheck = strcasestr(lineStorage[i], "UID")) && eventFlag != 0)
        {
            printf("10\n");
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
        else if((timeStampCheck = strcasestr(lineStorage[i], "DTSTAMP")))
        {
            printf("11\n");
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
            // char tempTime[7];
            // char tempDate[9];
            char * boolCheck;
            bool tempUTC;
             // tempSize = 0;
            // tempCount = 0;
            // memset(otherTempStorage, '\0', 1000);
            // memset(tempStorage, '\0', 1000); 
            int tempThirdVal = 0;
            if((boolCheck = strstr(DSTAMPStorage, "Z")))
            {
                tempUTC = true;
                parseCalendar->event->creationDateTime.UTC = true;
            }
            else
            {
                tempUTC = false;
                parseCalendar->event->creationDateTime.UTC = false;
            }

            // char * strTokTime;
            // char * strTokDate;

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
                                // printf("%c is the char \n", DSTAMPStorage[j]);
                                tempTimeStorage[tempThirdVal] = DSTAMPStorage[j];
                                j++;
                                tempThirdVal++;
                            }
                            else
                            {
                                j++;
                                // break;
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


            strcpy(parseCalendar->event->creationDateTime.date, tempDateStorage);
            // printf("fuck2\n");
            strcpy(parseCalendar->event->creationDateTime.time, tempTimeStorage);
            tempSize = 0;
            tempCount = 0;
            tempThirdVal = 0;
            memset(otherTempStorage, '\0', 1000);
            memset(tempStorage, '\0', 1000); 
        }
        else if((endCheck = strcasestr(lineStorage[i], "END")) && (eventCheck = strcasestr(lineStorage[i], "VEVENT")) && eventFlag == 1)
        {
            printf("12\n");
            // printf("fuck\n");
            eventFlag--;
        }
        else if((beginCheck = strcasestr(lineStorage[i], "BEGIN")) && (alarmCheck = strcasestr(lineStorage[i], "VALARM")) && eventFlag == 1 && alarmFlag == 0)
        {
            printf("13\n");
            // printf("fuck\n");
            alarmFlag++;
            tempAlarm = (Alarm*)malloc(sizeof(Alarm));
            // parseEvent->alarms = initializeAlarm();
        }
        else if((otherCheck = strcasestr(lineStorage[i], "TRIGGER")) && calendarFlag == 1&&  eventFlag == 1 && alarmFlag == 1)
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
        else if((otherCheck = strcasestr(lineStorage[i], "ACTION")) && calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1)
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
        else if((endCheck = strcasestr(lineStorage[i], "END")) && (alarmCheck = strcasestr(lineStorage[i], "VALARM")) && calendarFlag == 1 && alarmFlag == 1 && eventFlag == 1)
        {
            printf("6\n");
            alarmFlag--;
            insertFront(&parseCalendar->event->alarms, (void*)tempAlarm);
        }
        //alarm property
        else if(calendarFlag == 1 && eventFlag == 1 && alarmFlag == 1)
        {
            printf("fuck\n");
            for(int j = 0; j < strlen(lineStorage[i]); j++)
            {
                if(lineStorage[i][j] == ':' || lineStorage[i][j] != ';')
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
            insertFront(&tempAlarm->properties, tempProperty);
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
                    while(lineStorage[i][j] != '\0')
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

            tempProperty = initializeProperty(*otherTempStorage, tempStorage);
            insertFront(&parseCalendar->event->properties, tempProperty);
            tempSize = 0;
            tempCount = 0;
            memset(tempStorage, '\0', 1000);
            memset(otherTempStorage, '\0', 1000);
        }
        else if((versionCheck = strcasestr(lineStorage[i], "VERSION")) && versionFlag == 1)
        {
            return DUP_VER;
        }
        else if((proIDCheck = strcasestr(lineStorage[i], "PROID")) && proidFlag == 1)
        {
            return DUP_PRODID;
        }
        // printf("uh\n");
    }
    printf("hi\n");

    if(calendarFlag != 0 && proidFlag != 1 && versionFlag != 1)
    {
        printf("fuck\n");
        return INV_CAL;
    }
    else
    {
        printf("what\n");
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
    tempAlarm->properties = initializeList(NULL, NULL, NULL);

    return tempAlarm;

}

// DateTime* initializeDateTime(char *date, char *timeValue, bool UTC)
// {
//     printf("a1\n");
//     DateTime tempTime;
//     printf("2\n");
//     strcpy(tempTime.date, date);
//     printf("3\n");
//     strcpy(tempTime.time, timeValue);
//     printf("4\n");
//     tempTime.UTC = UTC;
//     printf("5\n");

//     return &tempTime;
// }

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


