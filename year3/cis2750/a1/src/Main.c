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
	Calendar * pleaseWorkCalendar;
	

	// if(strcmp(choice, "1") == 0)
	// {
		//easy
		printf("easy\n");
		enum ers errorCodeThing = createCalendar("./assets/otherTestCalShort.ics", &pleaseWorkCalendar);

		char * str = printError(errorCodeThing);

		printf("%s\n", str);

		char * clr = printCalendar(pleaseWorkCalendar);

		printf("%s\n", clr);

	// }
	// else if(strcmp(choice, "2") == 0)
	// {
	// 	//hard
	// 	printf("hard\n" );
	// 	errorCodeThing = createCalendar("./assets/testCalLong.ics", &pleaseWorkCalendar);
	// }
	
	return 0;
}

Calendar* initializeCalendarMain(pleaseWorkCalendar)
{
    Calendar * temp = malloc(sizeof(Calendar));
    temp->event = NULL;

    return temp;
}

