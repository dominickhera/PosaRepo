#include "functions.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int hashData(size_t hashSize, char * dataKey)
{

	int tempKey = 0;

	while(*dataKey != '\0')
	{
		tempKey = tempKey + *dataKey;
		dataKey++;
	}

	return tempKey % hashSize;
}

void clearTextLine(int x, int y)
{
    move(x,y);
    clrtoeol();
}

void makeMainMenu(int maxX, int maxY)
{
	 for(int i = 0; i <= ((maxX - 1)); i++)
    {
        mvaddch(0,i,'=');
        mvaddch(((maxY/3)*2),i,'=');
        if(i > 1)
        {
            mvaddch(1, i , '=');
            mvaddch((((maxY/3)*2) - 1), i - 1, '=');
        }
    }

    for(int i = 0; i <= ((maxY/3)*2); i++)
    {
        mvaddch(i,0,'|');
        mvaddch(i,(maxX - 1),'|');
        if(i > 1)
        {
            mvaddch(i - 1, 1, '#');
            mvaddch(i - 1, (maxX - 2), '#');
            mvaddch(i - 1, 2,'|');
            mvaddch(i - 1, (maxX - 3),'|');
        }

    }

       mvprintw(1, (maxX / 2) - 7, " <~ iVault ~> ");
    move(1, ((maxX/3)) - 3);
}

void makeMainMenuOptions(int maxX, int maxY, int i, char * menuOptions)
{
		mvprintw(((maxY/10) * i), 4, "[");
        move((maxY/10) * i, 4);

        mvprintw(((maxY/10) * i), 6, "]");
        move((maxY/10) * i, 6);

        mvprintw((((maxY/10) * i)), 8, menuOptions);
        move((((maxY/10) * i)), 8);
}


void getPos(int * y, int * x)
{
    * y = getcury(stdscr);
    * x = getcurx(stdscr);
    return;
}
