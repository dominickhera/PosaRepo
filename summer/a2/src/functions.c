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

void passwordChecker(char * masterPassword, char * passwordCheck, int maxX, int maxY)
{

	int passCount = 3;

	while(strcmp(masterPassword, passwordCheck) != 0)
    {
        clearTextLine(((maxY/6)*2),((maxX/6)*2) - 5);
        mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter master password: ");
        getstr(passwordCheck);



        if (masterPassword[strlen(masterPassword) - 1] == '\n')
        {
            masterPassword[strlen(masterPassword) - 1] = '\0';
        } 
        else
        {
            masterPassword[strlen(masterPassword)] = '\0';
        }


        if(strcmp(masterPassword, passwordCheck) != 0)
        {
            passCount--;
            if(passCount > 0)
            {
                mvprintw(((maxY/6)*2) + 4 , (((maxX/6) * 2) - 10), "invalid password. %d tries remaining.", passCount);
            }
            else
            {
                mvprintw((((maxY/3)*2) + 15) , 0, "max limit of tries reached. exiting program now...");
                // destroyTable(hashTable);
                endwin();
                exit(1);
            }
        }
        else
        {
            clearTextLine(((maxY/6)*2),((maxX/6)*2) - 5);
            clearTextLine((((maxY/3)*2) + 16),0);
            noecho();
            break;
        }

        memset(passwordCheck, 0, 256);
    }
}

void clearMainMenu(int maxX, int maxY)
{
    for(int i = 4; i <= ((maxY/3)*2); i++)
    {
        for(int k = 3; k <= (maxX - 4 ); k++)
        {
            mvaddch(i - 2, k  , ' ');
        }
    }
}

void makeMainMenuOptions(int maxX, int maxY, int i, char * menuOptions)
{
    mvprintw(((maxY/8) * i), 4, "[");
    move((maxY/8) * i, 4);

    mvprintw(((maxY/8) * i), 6, "]");
    move((maxY/8) * i, 6);

    mvprintw((((maxY/8) * i)), 8, menuOptions);
    move((((maxY/8) * i)), 8);
}


void getPos(int * y, int * x)
{
    * y = getcury(stdscr);
    * x = getcurx(stdscr);

    return;
}
