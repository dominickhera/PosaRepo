#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define character "X"
#define wall '=';


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
        mvaddch(((maxY/3)*3 - 1),i,'=');
        if(i > 1)
        {
            mvaddch(1, i , '=');
            mvaddch((((maxY/3)*3) - 2), i - 1, '=');
        }
    }

    for(int i = 0; i <= ((maxY/3)*3); i++)
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

    mvprintw(1, (maxX / 2) - 11, " <~ Stop for Games ~> ");
    move(1, ((maxX/3)) - 3);
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


int main()
{

    char line[256];
    char tempID[256];
    char tempPriority[50];
    char tempSymptomCode[50];
    int parseCount = 0;
    int c;
    int v;
    int cycle = 0;
    int maxX;
    int maxY;
    int y = 0;
    int x = 0;
    int prevX;
    int prevY;


    char * menuOptions[] = {"Search by Product Name", "Add Item by Product ID", "Remove Product from Inventory", "Print Inventory Report", "Print Customer Invoice", "Edit Customer Invoice", "Exit"}; 
    int tempMenuNumb[9];

    initscr();
    noecho();
    getmaxyx(stdscr,maxY,maxX);
    // box(stdscr, maxY - 5, maxX - 5);

    makeMainMenu(maxX, maxY);

    for(int i = 1; i < 8; i++)
    {
        makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);
    }

    mvprintw((maxY/8),5,character);
    move((maxY/8),5);


    c = getch();

    while (c != 'q')
    {

        if(c == 'w') 
        {
            getPos(&y,&x);
            if(y > 1) 
            {
                if((y - (maxY/8)) > 1)
                {

                    printw(" "); 
                    mvprintw((y - (maxY/8)), x,character);
                    move(y - (maxY/8) , x);
                }
            }

        }
        else if(c == 's')
        {
            getPos(&y,&x);
            if(y < (maxY - (maxY/8)))
            {
                if((y + (maxY/8)) < ((maxY/8) * 8))
                {
                    printw(" ");
                    mvprintw((y+(maxY/8)), x,character);
                    move((y + (maxY/8)), x);
                }
            }

        }
        else if(c == 'd')
        {
            getPos(&y,&x);
            if(y < (maxY - (maxY/8)))
            {
                if((y + (maxY/8)) < ((maxY/8) * 8))
                {
                    printw(" ");
                    mvprintw((y+(maxY/8)), x,character);
                    move((y + (maxY/8)), x);
                }
            }
        }
        else if(c == 'a')
        {
            getPos(&y,&x);
            if(y < (maxY - (maxY/8)))
            {
                if((y + (maxY/8)) < ((maxY/8) * 8))
                {
                    printw(" ");
                    mvprintw((y+(maxY/8)), x,character);
                    move((y + (maxY/8)), x);
                }
            }
        }
        else if(c == '\n')
        {

            getPos(&y, &x);

            prevY = y;
            prevX = x;
            for(int i = 1; i < 6; i++)
            {
                tempMenuNumb[i] = (maxY/8) * i;
            }

            for(int i = 0; i < maxX; i++)
            {
                mvaddch(((maxY/3)*2) + 3, i, ' ');
            }

            if(y == tempMenuNumb[1])
            {
                echo();
                clearTextLine((((maxY/3)*2) + 2),0);
                memset(tempID, 0, strlen(tempID));
                memset(tempPriority, 0, strlen(tempPriority));
                memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter clientID : ");
                getstr(tempID);
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter new client priority : ");
                getstr(tempPriority);
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter symptom Code: ");
                getstr(tempSymptomCode);
                clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));

                for(int i = 1; i < 5; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
            }
            else if(y == tempMenuNumb[2])
            {
                echo();
                clearMainMenu(maxX, maxY);
                memset(tempID, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s","enter clientID you'd like to delete from the list. : ");
                getstr(tempID);
                clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));

                for(int i = 1; i < 5; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
                makeMainMenu(maxX, maxY);
            }
            else if (y == tempMenuNumb[3])
            {
                echo();
                clearMainMenu(maxX, maxY);
                
                clearTextLine(((maxY/6)*2) , (((maxX/6) * 2)) - 25);
                clearTextLine(5, (maxX / 2) - 7);
                clearTextLine(3, (maxX / 2) - 18);

                for(int i = 1; i < 5; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }

                makeMainMenu(maxX, maxY);
            }
            else if(y == tempMenuNumb[4])
            {

                printf("Exiting...\n");

                // endwin();
                break;
            }
            else if(y == tempMenuNumb[5])
            {

                printf("Exiting...\n");

                // endwin();
                break;
            }
            else if(y == tempMenuNumb[6])
            {

                printf("Exiting...\n");

                // endwin();
                break;
            }
            else if(y == tempMenuNumb[7])
            {

                printf("Exiting...\n");

                // endwin();
                break;
            }
            else if(y == tempMenuNumb[8])
            {

                printf("Exiting...\n");

                endwin();
                break;
            }
            else
            {
                printf("error");
            }

            noecho();
            mvprintw(prevY, prevX,character);
            move(prevY, prevX);

        }

        refresh();
        c = getch();
    }
    endwin();

    return 0;
}
