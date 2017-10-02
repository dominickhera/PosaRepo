#include "LinkedListAPI.h"
#include "CalendarParser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Calendar* initializeCalendarMain();

int main()
{
	// printf("uh; %s\n", argv[]);

	// char * choice = argv[1];
	Calendar * pleaseWorkCalendar = initializeCalendarMain();
	enum ers errorCodeThing;

	// if(strcmp(choice, "1") == 0)
	// {
		//easy
		printf("easy\n");
		errorCodeThing = createCalendar("./assets/testCalShort.ics", &pleaseWorkCalendar);

	// }
	// else if(strcmp(choice, "2") == 0)
	// {
	// 	//hard
	// 	printf("hard\n" );
	// 	errorCodeThing = createCalendar("./assets/testCalLong.ics", &pleaseWorkCalendar);
	// }
	
	return 0;
}

Calendar* initializeCalendarMain()
{
    Calendar * temp = malloc(sizeof(Calendar));
    temp->event = NULL;

    return temp;
}

