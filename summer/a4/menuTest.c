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
        mvaddch(((maxY/3)*3),i,'=');
        if(i > 1)
        {
            mvaddch(1, i , '=');
            mvaddch((((maxY/3)*3) - 1), i - 1, '=');
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
    for(int i = 4; i <= ((maxY/3)*3); i++)
    {
        for(int k = 3; k <= (maxX - 4 ); k++)
        {
            mvaddch(i - 2, k  , ' ');
        }
    }
}

void makeMainMenuOptions(int maxX, int maxY, int i, char * menuOptions)
{
    mvprintw(((maxY/9) * i), 4, "[");
    move((maxY/9) * i, 4);

    mvprintw(((maxY/9) * i), 6, "]");
    move((maxY/9) * i, 6);

    mvprintw((((maxY/9) * i)), 8, menuOptions);
    move((((maxY/9) * i)), 8);
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
    int tempMenuNumb[8];

    initscr();
    noecho();
    getmaxyx(stdscr,maxY,maxX);
    // box(stdscr, maxY - 5, maxX - 5);

    makeMainMenu(maxX, maxY);

    for(int i = 1; i < 8; i++)
    {
        makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);
    }

    mvprintw((maxY/9),5,character);
    move((maxY/9),5);


    c = getch();

    while (c != 'q')
    {

        if(c == 'w') 
        {
            getPos(&y,&x);
            if(y > 1) 
            {
                if((y - (maxY/9)) > 1)
                {

                    printw(" "); 
                    mvprintw((y - (maxY/9)), x,character);
                    move(y - (maxY/9) , x);
                }
            }

        }
        else if(c == 's')
        {
            getPos(&y,&x);
            if(y < (maxY - (maxY/9)))
            {
                if((y + (maxY/9)) < ((maxY/9) * 8))
                {
                    printw(" ");
                    mvprintw((y +(maxY/9)), x,character);
                    move((y + (maxY/9)), x);
                }
            }

        }
        else if(c == '\n')
        {

            getPos(&y, &x);

            prevY = y;
            prevX = x;
            for(int i = 1; i < 8; i++)
            {
                tempMenuNumb[i] = (maxY/9) * i;
            }

            for(int i = 0; i < maxX; i++)
            {
                mvaddch(((maxY/3)*3) + 3, i, ' ');
            }

            if(y == tempMenuNumb[1])
            {
                echo();
                clearTextLine((((maxY/3)*3) + 2),0);
                memset(tempID, 0, strlen(tempID));
                memset(tempPriority, 0, strlen(tempPriority));
                memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(5 , (maxX/2) - 50, "%s", "enter game title : ");
                getstr(tempID);
                // clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                // mvprintw(8 , (maxX/2) - 50, "%s", "Found this: ");
                // getstr(tempPriority);
                // clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                // mvprintw(((maxY/6)*2) , (((maxX/6) * 2) - 5), "%s", "enter symptom Code: ");
                // getstr(tempSymptomCode);

                // clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));
                // clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));

                 for(int i = 1; i < 9; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
                makeMainMenu(maxX, maxY);
            }
            else if(y == tempMenuNumb[2])
            {
                echo();
                clearMainMenu(maxX, maxY);
                memset(tempID, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw(5 , 15, "%s","enter Product ID of game to add : ");
                getstr(tempID);
                mvprintw(8 , 15, "%s", "Found this: ");
                mvprintw(15, 15, "%s", "How many copies would you like to purchase? (X in stock): ");
                // clearTextLine(((maxY/6)*2) + 5 , (((maxX/6) * 2) - 5));

                for(int i = 1; i < 8; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
                makeMainMenu(maxX, maxY);
            }
            else if (y == tempMenuNumb[3])
            {
                echo();
                clearTextLine((((maxY/3)*3) + 2),0);
                memset(tempID, 0, strlen(tempID));
                memset(tempPriority, 0, strlen(tempPriority));
                memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(5 , 15, "%s", "enter game title to remove: ");
                getstr(tempID);

                 for(int i = 1; i < 8; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }
                makeMainMenu(maxX, maxY);
                // clearTextLine(((maxY/6)*2) , (((maxX/6) * 2) - 5));
                // mvprintw(8 , (maxX/2) - 50, "%s", "Found this: ");
            }
            else if(y == tempMenuNumb[4])
            {
                echo();
                clearTextLine((((maxY/3)*3) + 2),0);
                memset(tempID, 0, strlen(tempID));
                memset(tempPriority, 0, strlen(tempPriority));
                memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(5 , 15, "%s", "enter game title : ");
                getstr(tempID);

                for(int i = 1; i < 8; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }

                makeMainMenu(maxX, maxY);
                // printf("Exiting...\n");

                // endwin();
                // break;
            }
            else if(y == tempMenuNumb[5])
            {
                echo();
                clearTextLine((((maxY/3)*3) + 2),0);
                memset(tempID, 0, strlen(tempID));
                // memset(tempPriority, 0, strlen(tempPriority));
                // memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(5 , 15, "%s", "enter game title : ");
                getstr(tempID);

                for(int i = 1; i < 8; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }

                makeMainMenu(maxX, maxY);
                // printf("Exiting...\n");

                // endwin();
                // break;
            }
            else if(y == tempMenuNumb[6])
            {
                echo();
                clearTextLine((((maxY/3)*3) + 2),0);
                memset(tempID, 0, strlen(tempID));
                // memset(tempPriority, 0, strlen(tempPriority));
                // memset(tempSymptomCode, 0, strlen(tempSymptomCode));
                clearMainMenu(maxX, maxY);
                mvprintw(5 , (maxX/2) - 50, "%s", "enter game title : ");
                getstr(tempID);

                for(int i = 1; i < 8; i++)
                {
                    makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

                }

                makeMainMenu(maxX, maxY);
                // printf("Exiting...\n");

                // endwin();
                // break;
            }
            else if(y == tempMenuNumb[7])
            {

                printf("Exiting...\n");

                endwin();
                break;
            }
            // else if(y == tempMenuNumb[8])
            // {

            //     printf("Exiting...\n");

            //     endwin();
            //     break;
            // }
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
