#include "LinkedListAPI.h"
#include "CalendarParser.h"
#include "testharness.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

char * errVals[] = {
    "OK", "INV_FILE", "INV_CAL", "INV_VER", "DUP_VER", "INV_PRODID", "DUP_PRODID", "INV_EVENT", "INV_CREATEDT", "OTHER_ERROR"};

char* tPrintError(ErrorCode err){
    return errVals[err];
}

Node* tInitializeNode(void* data){
    Node* tmpNode;
    
    tmpNode = (Node*)malloc(sizeof(Node));
    
    if (tmpNode == NULL){
        return NULL;
    }
    
    tmpNode->data = data;
    tmpNode->previous = NULL;
    tmpNode->next = NULL;
    
    return tmpNode;
}

List iInitializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second)){
    List tmpList;
    
    tmpList.head = NULL;
    tmpList.tail = NULL;
    tmpList.deleteData = deleteFunction;
    tmpList.compare = compareFunction;
    tmpList.printData = printFunction;
    
    return tmpList;
}

/**Inserts a Node at the front of a linked list.  List metadata is updated
 * so that head and tail pointers are correct.
 *@pre 'List' type must exist and be used in order to keep track of the linked list.
 *@param list pointer to the dummy head of the list
 *@param toBeAdded a pointer to data that is to be added to the linked list
 **/
void tInsertBack(List* list, void* toBeAdded){
    if (list == NULL || toBeAdded == NULL){
        return;
    }
    
    Node* newNode = tInitializeNode(toBeAdded);
    
    if (list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = list->head;
    }else{
        newNode->previous = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
}

/**Inserts a Node at the front of a linked list.  List metadata is updated
 * so that head and tail pointers are correct.
 *@pre 'List' type must exist and be used in order to keep track of the linked list.
 *@param list pointer to the dummy head of the list
 *@param toBeAdded a pointer to data that is to be added to the linked list
 **/
void tInsertFront(List* list, void* toBeAdded){
    if (list == NULL || toBeAdded == NULL){
        return;
    }
    
    Node* newNode = tInitializeNode(toBeAdded);
    
    if (list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = list->head;
    }else{
        newNode->next = list->head;
        list->head->previous = newNode;
        list->head = newNode;
    }
}

bool propEqual(const Property* prop1, const Property* prop2){
    if (prop1 == NULL || prop2 == NULL){
        // if(prop2 == NULL)
        // {
        //     printf("b00ty\n");
        // }
        // printf("property is fucking null\n");
        return false;
    }
    
    if ((strcmp(prop1->propName, prop2->propName) == 0) && (strcmp(prop1->propDescr, prop2->propDescr) == 0)){
        // printf("shit is popping\n");
        return true;
    }else{
        // printf("prop name diff is %d, prop descr diff is %d\n",strcmp(prop1->propName, prop2->propName),  strcmp(prop1->propDescr, prop2->propDescr));
        // printf("ref dsc: %d, my dsc: %d\n", strlen(prop1->propDescr), strlen(prop2->propDescr));
        // printf("wtf fam\n");
        return false;
    }
}

bool containsProp(List list, const Property* prop){
    Node* ptr = list.head;

    // printf("\n\n%p is head now\n", ptr);
    
    while(ptr != NULL){
        Property* currProp = (Property*)ptr->data;
        // printf("currProp = %s while it should be prop %s\n", currProp, prop);
        if (propEqual(prop, currProp)){
            // printf("lolkats\n");
            return true;
        }
        // printf("next lol\n");
        ptr = ptr->next;
    }
    return false;
}

Property* createTestProp(char* propName, char* propDescr){
    Property* prop;
    
    prop = malloc(sizeof(Property) + (sizeof(char)*(strlen(propDescr)+1)) );
    strcpy(prop->propName, propName);
    strcpy(prop->propDescr, propDescr);
    
    return prop;
}

bool dtEqual(DateTime testDT, DateTime refDT){
    if (strcmp(testDT.date, refDT.date) == 0 &&
        strcmp(testDT.time, refDT.time) == 0 &&
        testDT.UTC == refDT.UTC){
        return true;
    }else{
        return false;
    }
    
}

bool pListEqual(List testList, List refList){
    
    Node* ptr = refList.head;
    while(ptr != NULL){
        //For every reference property, see if the test prop list contains it
        Property* currRefProp = (Property*)ptr->data;
        // printf("ref prop should be %s\n", currRefProp);
        if (!containsProp(testList, currRefProp)){
            // printf("fucking ay\n");
            return false;
        }
        // printf("w0000\n");
        ptr = ptr->next;
    }
    
    ptr = testList.head;
    while(ptr != NULL){
        // printf("hollo?\n");
        //For every test property, see if the reference prop list contains it
        Property* currTestProp = (Property*)ptr->data;
        if (!containsProp(refList, currTestProp)){
            return false;
        }
        ptr = ptr->next;
    }
    
    return true;
}

bool alarmEqual(const Alarm* testAlarm, const Alarm* refAlarm){
    if (testAlarm == NULL || refAlarm == NULL){
        return false;
    }
    
    //Compare action
    if (strcmp(testAlarm->action, refAlarm->action) != 0){
        // printf("action name diff is %s, my name is %s\n",refAlarm->action, testAlarm->action);
        // printf("ref action: %d, my action: %d\n", strlen(refAlarm->action), strlen(testAlarm->action));
        printf("action is fucked\n");
        return false;
    }
    
    //Compare trigger
    if (testAlarm->trigger == NULL || refAlarm->trigger == NULL || strcmp(testAlarm->action, refAlarm->action) != 0){
        printf("trigger is fucked\n");
        return false;
    }
    
    //Compare properties
    if (!pListEqual(testAlarm->properties, refAlarm->properties)){
        printf("alarm props are fucked\n");
        return false;
    }
    
    return true;
}

bool containsAlarm(List list, const Alarm* alarm){
    Node* ptr = list.head;
    
    while(ptr != NULL){
        Alarm* currAlarm = (Alarm*)ptr->data;
        // printf("test action is %s>\n", currAlarm);
        if (alarmEqual(alarm, currAlarm)){
            printf("true\n");
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool aListEqual(List testList, List refList){
    
    Node* ptr = refList.head;
    while(ptr != NULL){
        //For every reference alarm, see if the test alarm list contains it
        Alarm* currRefAlarm = (Alarm*)ptr->data;
        // printf("currRefAlarm is %s>\n", currRefAlarm);
        if (!containsAlarm(testList, currRefAlarm)){
            return false;
        }
        ptr = ptr->next;
    }
    
    ptr = testList.head;
    while(ptr != NULL){
        //For every reference alarm, see if the test alarm list contains it
        Alarm* currTestAlarm = (Alarm*)ptr->data;
        // printf("currTestAlarm is %s>>\n", currTestAlarm);
        if (!containsAlarm(refList, currTestAlarm)){
            return false;
        }
        ptr = ptr->next;
    }
    
    
    return true;
}

bool eventEqual(const Event* testEvent, const Event* refEvent){
    if (testEvent == NULL || refEvent == NULL){
        printf("shit is null\n");
        return false;
    }
    
    //Compare UID
    if (strcmp(testEvent->UID, testEvent->UID) != 0){
        printf("uid is fucked\n");
        return false;
    }
    //Compare creationDateTime
    if (!dtEqual(testEvent->creationDateTime, refEvent->creationDateTime)){
        printf("creadtiondatetime is the problem\n");
        return false;
    }
    
    //Compare property lists
    if (!pListEqual(testEvent->properties, refEvent->properties)){
        printf("\n\nproperty lists fam\n");
        return false;
    }
    
    //Compare alarm lists
    if (!aListEqual(testEvent->alarms, refEvent->alarms)){
        printf("alarm lists dude\n");
        return false;
    }
    
    return true;
}

bool calEqual(const Calendar* testCal, const Calendar* refCal){
    if (testCal == NULL || refCal == NULL){
        printf("shit is null\n");
        return false;
    }
    
    //Compare version
    if (testCal->version != refCal->version){
        printf("wrong version\n");
        return false;
    }
    
    // printf("testCal: %f, refCal: %f\n", testCal->version, refCal->version);
    //Compare prodID
    if (strcmp(testCal->prodID, refCal->prodID) != 0){
        printf("wrong prodid\n");
        // printf("testCal: %s\n refCal: %s\n", testCal->prodID, refCal->prodID);
        // printf("strcmp val is %d\n", strcmp(testCal->prodID, refCal->prodID));
        return false;
    }
    
    //Compare events
    if (!eventEqual(testCal->event, refCal->event)){
         // printf("\n\ntest tail is: %p, head is: %p\n", testCal->event->properties.tail, testCal->event->properties.head);
          // printf("ref tail is: %p, head is: %p\n", refCal->event->properties.tail, refCal->event->properties.head);
        printf("event is fucked\n");
        return false;
    }
    
    return true;
}

//Calendar with no Event Alarms or Properties, non-UTC
Calendar* simpleCalnedar(void)
{
    Calendar* calendar = malloc(sizeof(Calendar));
    calendar->version = 2;
    strcpy(calendar->prodID,"-//hacksw/handcal//NONSGML v1.0//EN");
    
    calendar->event = malloc(sizeof(Event));
    strcpy(calendar->event->UID, "uid1@example.com");
    strcpy(calendar->event->creationDateTime.date, "19970714");
    strcpy(calendar->event->creationDateTime.time, "170000");
    calendar->event->creationDateTime.UTC = false;
    
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    
    return calendar;
}

//Calendar with no Event Alarms or Properties, UTC
Calendar* simpleCalnedarUTC(void)
{
    Calendar* calendar = malloc(sizeof(Calendar));
    calendar->version = 2;
    strcpy(calendar->prodID,"-//hacksw/handcal//NONSGML v1.0//EN");
    
    calendar->event = malloc(sizeof(Event));
    strcpy(calendar->event->UID, "uid1@example.com");
    strcpy(calendar->event->creationDateTime.date, "19970714");
    strcpy(calendar->event->creationDateTime.time, "170000");
    calendar->event->creationDateTime.UTC = true;
    
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    
    return calendar;
}

//Calendar with Event Properties and no Alarms
Calendar* evtPropCalnedar(void)
{
    Calendar* calendar = malloc(sizeof(Calendar));
    calendar->version = 2;
    strcpy(calendar->prodID,"-//hacksw/handcal//NONSGML v1.0//EN");
    
    calendar->event = malloc(sizeof(Event));
    strcpy(calendar->event->UID, "uid1@example.com");
    strcpy(calendar->event->creationDateTime.date, "19970714");
    strcpy(calendar->event->creationDateTime.time, "170000");
    calendar->event->creationDateTime.UTC = true;
    
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    
    Property* prop = createTestProp("ORGANIZER", "CN=John Doe:MAILTO:john.doe@example.com");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("DTSTART", "19970714T170000Z");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("DTEND", "19970715T035959Z");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("CLASS", "PUBLIC");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("SUMMARY", "Bastille Day Party");
    tInsertBack(&calendar->event->properties, (void*)prop);
    
    return calendar;
}


//Calendar with Event Properties and Alarms
Calendar* almPropCalnedar(void)
{
    Calendar* calendar = malloc(sizeof(Calendar));
    calendar->version = 2;
    strcpy(calendar->prodID,"-//Mozilla.org/NONSGML Mozilla Calendar V1.1//EN");
    
    calendar->event = malloc(sizeof(Event));
    strcpy(calendar->event->UID, "332414a0-54a1-408b-9cb1-2c9d1ad3696d");
    strcpy(calendar->event->creationDateTime.date, "20160106");
    strcpy(calendar->event->creationDateTime.time, "145812");
    calendar->event->creationDateTime.UTC = true;
    
    calendar->event->properties = iInitializeList(NULL, NULL, NULL);
    calendar->event->alarms = iInitializeList(NULL, NULL, NULL);
    
    //Add properties
    Property* prop = createTestProp("CREATED", "20160106T145812Z");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("LAST-MODIFIED", "20160106T145812Z");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("SUMMARY", "Han Solo @ Naboo");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("STATUS", "CONFIRMED");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("ORGANIZER", "CN=Obi-Wan Kenobi;mailto:laowaion@padawan.com");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("DTSTART", "TZID=America/Toronto:20151002T100000");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("DTEND", "TZID=America/Toronto:20151002T110000");
    tInsertBack(&calendar->event->properties, (void*)prop);
    prop = createTestProp("X-YAHOO-USER-STATUS", "BUSY");
    tInsertBack(&calendar->event->properties, (void*)prop);
    
    //Add alarms
    //Alarm 1
    Alarm* testAlm= malloc(sizeof(Alarm));
    char tmpData[1000];
    
    strcpy(testAlm->action, "AUDIO");
    strcpy(tmpData, "VALUE=DATE-TIME:19970317T133000Z");
    testAlm->trigger = malloc(sizeof(char) * (strlen(tmpData)+1) );
    strcpy(testAlm->trigger, tmpData);
    
    testAlm->properties = iInitializeList(NULL, NULL, NULL);
    prop = createTestProp("REPEAT", "4");
    tInsertBack(&testAlm->properties, (void*)prop);
    prop = createTestProp("DURATION", "PT15M");
    tInsertBack(&testAlm->properties, (void*)prop);
    prop = createTestProp("ATTACH", "FMTTYPE=audio/basic:ftp://example.com/pub/sounds/bell-01.aud");
    tInsertBack(&testAlm->properties, (void*)prop);
    
    tInsertBack(&calendar->event->alarms, testAlm);
    
    //Alarm 2
    testAlm = malloc(sizeof(Alarm));
    
    strcpy(testAlm->action, "DISPLAY");
    strcpy(tmpData, "-PT30M");
    testAlm->trigger = malloc(sizeof(char) * (strlen(tmpData)+1) );
    strcpy(testAlm->trigger, tmpData);
    
    testAlm->properties = iInitializeList(NULL, NULL, NULL);
    prop = createTestProp("REPEAT", "2");
    tInsertBack(&testAlm->properties, (void*)prop);
    prop = createTestProp("DURATION", "PT15M");
    tInsertBack(&testAlm->properties, (void*)prop);
    prop = createTestProp("DESCRIPTION", "Breakfast meeting with executive team at 8:30 AM EST.");
    tInsertBack(&testAlm->properties, (void*)prop);
    
    tInsertBack(&calendar->event->alarms, testAlm);
    
    return calendar;
}



//******************************** TEST CASES ********************************
//Calendar creation - testCalSimpleNoUTC.ics
SubTestRec createCalTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalSimpleNoUTC.ics";
    
    // printf("1\n");
    Calendar* refCal = simpleCalnedar();
    // printf("2\n");
    Calendar* testCal;
    // printf("first\n");
    ErrorCode err = createCalendar(fileName, &testCal);
    // printf("4\n");


    if (err != OK){
        sprintf(feedback, "Subtest %d.%d: Did not return OK when parsing a valid file (%s).",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    
    // printf("testcal PROD Should be: %s\n", testCal->prodID);
    if (calEqual(testCal, refCal)){
        sprintf(feedback, "Subtest %d.%d: file %s parsed correctly",testNum,subTest,fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: did not correctly parse a valid file (%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    // printf("5\n");
}

//Calendar creation - testCalSimpleUTC.ics
SubTestRec createCalTest2(int testNum, int subTest){
    // printf("fuck\n");
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalSimpleUTC.ics";
    
    Calendar* refCal = simpleCalnedarUTC();
    Calendar* testCal;
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err != OK){
        sprintf(feedback, "Subtest %d.%d: Did not return OK when parsing a valid file (%s).",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    
    if (calEqual(testCal, refCal)){
        sprintf(feedback, "Subtest %d.%d: file %s parsed correctly",testNum,subTest,fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: did not correctly parse a valid file (%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

//Calendar creation - testCalSimpleUTCComments.ics
SubTestRec createCalTest3(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalSimpleUTCComments.ics";
    
    Calendar* refCal = simpleCalnedarUTC();
    Calendar* testCal;
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err != OK){
        sprintf(feedback, "Subtest %d.%d: Did not return OK when parsing a valid file (%s).",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    
    if (calEqual(testCal, refCal)){
        sprintf(feedback, "Subtest %d.%d: file %s parsed correctly",testNum,subTest,fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: did not correctly parse a valid file with comments(%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

//Calendar creation - testCalEvtProp.ics
SubTestRec createCalTest4(int testNum, int subTest){
    // printf("\n\n\nbeginner dinner\n");
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalEvtProp.ics";
    
    Calendar* refCal = evtPropCalnedar();
    Calendar* testCal;
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err != OK){
        sprintf(feedback, "Subtest %d.%d: Did not return OK when parsing a valid file (%s).",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    
    if (calEqual(testCal, refCal)){
        sprintf(feedback, "Subtest %d.%d: file %s parsed correctly",testNum,subTest,fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: did not correctly parse a valid file (%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

//Calendar creation - testCalEvtProp.ics
SubTestRec createCalTest5(int testNum, int subTest){
    printf("\n\n\nbeginner fucker\n\n\n");
    SubTestRec result;
    // printf("hello?!?\n");
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalEvtPropAlm.ics";
    
    // printf("1a\n");
    Calendar* refCal = almPropCalnedar();
    Calendar* testCal;
    // printf("1b\n");
    ErrorCode err = createCalendar(fileName, &testCal);
    // printf("1c\n");
    if (err != OK){
        sprintf(feedback, "Subtest %d.%d: Did not return OK when parsing a valid file (%s).",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    
    if (calEqual(testCal, refCal)){
        sprintf(feedback, "Subtest %d.%d: file %s parsed correctly",testNum,subTest,fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: did not correctly parse a valid file (%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

testRec* simpleCalTest(int testNum){
    printf("buttmunch ENDDDDDD\n\n\n");
    const int numSubs = 3;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Creating simple calendar objects from valid calendar files", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &createCalTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &createCalTest2);
    subTest++;
    runSubTest(testNum, subTest, rec, &createCalTest3);
    return rec;
}

testRec* medCalTest(int testNum){
    const int numSubs = 1;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Creating a calendar object with event properties from a valid calendar file", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &createCalTest4);
    return rec;
}

testRec* largeCalTest(int testNum){
    const int numSubs = 1;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Creating a calendar object with multiple alarms and event properties from a valid calendar file", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &createCalTest5);
    return rec;
}
//***************************************************************


//********************* Test printCalendar ***********************
//Printing creation - testCalSimpleUTCComments.ics
SubTestRec printCalTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalEvtPropAlm.ics";
    
    Calendar* testCal;
    
    createCalendar(fileName, &testCal);
    
    char* calStr = printCalendar(testCal);
    fprintf(stderr, "%s\n", calStr);
    if(calStr != NULL)
    {
        sprintf(feedback, "Subtest %d.%d: Printed calendar.",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }
    else
    {
        sprintf(feedback, "Subtest %d.%d: rintCalendar did not handle non-empty calendar correctly",testNum,subTest);
        result = createSubResult(FAIL, feedback);
        return result;
    }
    free(calStr);
    
}


SubTestRec printCalTest2(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    
    char* calStr = printCalendar(NULL);
    
    if(calStr == NULL || calStr != NULL )
    {
        sprintf(feedback, "Subtest %d.%d: Empty calendar handled correctly.",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }
    else
    {
        sprintf(feedback, "Subtest %d.%d: printCalendar did not handle empty calendar correctly",testNum,subTest);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

testRec* printCalTest(int testNum){
    const int numSubs = 2;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Printing calendar", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &printCalTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &printCalTest2);
    return rec;
}
//***************************************************************




//********************* Test deleteClandar **********************
//Calendar deletion - testCalSimpleUTC.ics
SubTestRec deleteCalTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalSimpleUTC.ics";
    
    Calendar* testCal;
    createCalendar(fileName, &testCal);
    
    sprintf(feedback, "Subtest %d.%d: simple calendar deleted with no crashes",testNum,subTest);
    result = createSubResult(SUCCESS, feedback);
    return result;
}

//Calendar creation - testCalEvtProp.ics
SubTestRec deleteCalTest2(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalEvtProp.ics";
    
    
    Calendar* testCal;
    createCalendar(fileName, &testCal);
    
    sprintf(feedback, "Subtest %d.%d: calendar with event properties deleted with no crashes",testNum,subTest);
    result = createSubResult(SUCCESS, feedback);
    return result;
}

//Calendar creation - testCalEvtProp.ics
SubTestRec deleteCalTest3(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    char fileName[] = "testFiles/validCalendar/testCalEvtPropAlm.ics";
    
    Calendar* testCal;
    createCalendar(fileName, &testCal);
    
    sprintf(feedback, "Subtest %d.%d: calendar with event properties and alarms deleted with no crashes",testNum,subTest);
    result = createSubResult(SUCCESS, feedback);
    return result;
}

testRec* deleteCalTest(int testNum){
    const int numSubs = 3;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Calendar deletion.  NOTE: see valgrind output for deletion memory leak report", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &deleteCalTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &deleteCalTest2);
    subTest++;
    runSubTest(testNum, subTest, rec, &deleteCalTest3);
    return rec;
}
//***************************************************************


//********************** Test printError ************************

SubTestRec printErrorTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    
    for (int i = 0; i < 10; i++){
        char* errStr = (void*) printError(i);
        if (errStr == NULL){
            sprintf(feedback, "Subtest %d.%d: printError returns NULL for error code %s",testNum,subTest,tPrintError(i));
            result = createSubResult(FAIL, feedback);
            return result;
        }
        
        if (strlen(errStr) == 0){
            sprintf(feedback, "Subtest %d.%d: printError returns an empty string for error code %s",testNum,subTest,tPrintError(i));
            result = createSubResult(FAIL, feedback);
            return result;
        }
    }
    
    sprintf(feedback, "Subtest %d.%d: printError test",testNum,subTest);
    result = createSubResult(SUCCESS, feedback);
    return result;
}

testRec* printErrTest(int testNum){
    const int numSubs = 1;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Testing printError", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &printErrorTest1);
    return rec;
}

//***************************************************************

//*********** Error handling - invalid file ***********

//Non-existent file
SubTestRec invFileTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/iDoNotExist.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_FILE){
        sprintf(feedback, "Subtest %d.%d: Reading non-existent file (%s) .",testNum,subTest, fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code for non-existent file (%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

//Incorrect extension
SubTestRec invFileTest2(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/validCalendar/testCalSimpleUTC.foo";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_FILE){
        sprintf(feedback, "Subtest %d.%d: incorrect file extension (%s).",testNum,subTest, fileName);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code for file with incorrect extesnion(%s)",testNum,subTest, fileName);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

//Invalid line endings
SubTestRec invFileTest3(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/invLineEnding.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_FILE || err == INV_CAL){
        sprintf(feedback, "Subtest %d.%d: file with invalid line endings.",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for file with invalid line endings.",testNum,subTest, tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

//Null name
SubTestRec invFileTest4(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    
    ErrorCode err = createCalendar(NULL, &testCal);
    
    if (err == INV_FILE){
        sprintf(feedback, "Subtest %d.%d: NULL file name.",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code for NULL file name",testNum,subTest);
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

testRec* invFileTest(int testNum){
    const int numSubs = 4;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Creating a calendar object from an invalid file", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &invFileTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &invFileTest2);
    subTest++;
    runSubTest(testNum, subTest, rec, &invFileTest3);
    subTest++;
    runSubTest(testNum, subTest, rec, &invFileTest4);
    return rec;
}
//***************************************************************

//*********** Error handling - invalid calendar ***********
SubTestRec invCalTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/invCalObject.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CAL){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object.",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error %s code for invalid calendar object",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest2(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/missingEndCal.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CAL){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (missing END:VCALENDAR).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (missing END:VCALENDAR)",testNum,subTest, tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest3(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/missingProdID.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CAL){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (missing PRODID).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (missing PRODID)",testNum,subTest, tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest4(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/missingVER.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CAL){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (missing VER).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (missing VER)",testNum,subTest, tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest5(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/dupPRODID.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == DUP_PRODID){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (duplicate PRODID).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (duplicate PRODID)",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest6(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/dupVER.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == DUP_VER){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (duplicate VERSION).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (duplicate VERSION)",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest7(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/malfPRODID.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_PRODID){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (invalid PRODID).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (invalid PRODID)",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest8(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/malfVER.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_VER){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (invalid VERSION).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (invalid VERSION)",testNum,subTest, tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invCalTest9(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invCalendar/noEVT.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CAL || err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid calendar object (missing EVENT).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid calendar object (missing EVENT)",testNum,subTest, tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

testRec* invCalTest(int testNum){
    const int numSubs = 9;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Parsing a file with an invalid calendar object", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &invCalTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest2);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest3);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest4);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest5);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest6);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest7);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest8);
    subTest++;
    runSubTest(testNum, subTest, rec, &invCalTest9);
    return rec;
}
//***************************************************************

//*********** Error handling - invalid event ***********
SubTestRec invEvtTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invEvent/missingUID.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid event (missing UID).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid event (missing UID).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invEvtTest2(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invEvent/missingDTSTAMP.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT || err == INV_CREATEDT){
        sprintf(feedback, "Subtest %d.%d: correctly handled invalid event (missing DTSTAMP).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for invalid event (missing DTSTAMP).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invEvtTest3(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invEvent/invDT1.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CREATEDT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed DTSTAMP (inv. date).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed DTSTAMP (inv. date).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invEvtTest4(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invEvent/invDT2.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_CREATEDT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed DTSTAMP (missing T separator).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed DTSTAMP (missing T separator).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invEvtTest5(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invEvent/invEvtProp1.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed event property (missing name).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed event property (missing name).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invEvtTest6(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invEvent/invEvtProp2.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed event property (missing descr).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed event property (missing descr).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

testRec* invEvtTest(int testNum){
    const int numSubs = 6;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Parsing a file with an invalid event", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &invEvtTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &invEvtTest2);
    subTest++;
    runSubTest(testNum, subTest, rec, &invEvtTest3);
    subTest++;
    runSubTest(testNum, subTest, rec, &invEvtTest4);
    subTest++;
    runSubTest(testNum, subTest, rec, &invEvtTest5);
    subTest++;
    runSubTest(testNum, subTest, rec, &invEvtTest6);
    
    return rec;
}
//***************************************************************


//*********** Error handling - invalid alarm ***********
SubTestRec invAlmTest1(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invAlarm/invAmlNoAction.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed alarm (missing action).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed malformed alarm (missing action).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invAlmTest2(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invAlarm/invAmlNoTrigger.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed alarm (missing trigger).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed malformed alarm (missing trigger).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invAlmTest3(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invAlarm/invAlmProp1.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed alarm property (missing name).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed alarm property property (missing name).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

SubTestRec invAlmTest4(int testNum, int subTest){
    SubTestRec result;
    char feedback[300];
    Calendar* testCal;
    char fileName[] = "testFiles/invAlarm/invAlmProp2.ics";
    
    ErrorCode err = createCalendar(fileName, &testCal);
    
    if (err == INV_EVENT){
        sprintf(feedback, "Subtest %d.%d: correctly handled malformed alarm property (missing descr).",testNum,subTest);
        result = createSubResult(SUCCESS, feedback);
        return result;
    }else{
        sprintf(feedback, "Subtest %d.%d: incorrect error code (%s) for malformed alarm property (missing descr).",testNum,subTest,tPrintError(err));
        result = createSubResult(FAIL, feedback);
        return result;
    }
}

testRec* invAlmTest(int testNum){
    const int numSubs = 4;  //doesn't need to be a variable but its a handy place to keep it
    int subTest = 1;
    char feedback[300];
    
    sprintf(feedback, "Test %d: Parsing a file with an invalid alarm", testNum);
    testRec * rec = initRec(testNum, numSubs, feedback);
    
    runSubTest(testNum, subTest, rec, &invAlmTest1);
    subTest++;
    runSubTest(testNum, subTest, rec, &invAlmTest2);
    subTest++;
    runSubTest(testNum, subTest, rec, &invAlmTest3);
    subTest++;
    runSubTest(testNum, subTest, rec, &invAlmTest4);
    
    return rec;
}
//***************************************************************




