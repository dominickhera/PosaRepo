#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "HashTableAPI.h"

#define character "X"
#define wall '=';

int main()
{

    int c;
    int maxX;
    int maxY;
    int y;
    int x;
    int i;
 
    
    y = 0;
    x = 0;
    
    
    // printf("Ncurses demo of moving the cursor.\n\nUse i,j,k,m to move the cursor\nPress any key to begin.");
    // getchar();
    initscr();
    noecho();
    getmaxyx(stdscr,maxY,maxX);
    
    for(i = 0; i <= ((maxX/3)*2); i++)
    {
        mvaddch(0,i,'=');
        mvaddch(((maxY/3)*2),i,'=');
    }
    
    for(i = 0; i <= ((maxY/3)*2); i++)
    {
        mvaddch(i,0,'|');
        mvaddch(i,(maxX/3)*2,'|');
    }

    mvprintw(1, ((maxX/3)) - 5, "~ iVault ~");
    move(1, ((maxX/3)) - 3);

    for(i = 1; i < 7; i++)
    {
        mvprintw(((maxY/10) * i), 3, "[");
        move((maxY/10) * i, 3);

        mvprintw(((maxY/10) * i), 5, "]");
        move((maxY/10) * i, 5);

    }

    mvprintw((maxY/10),4,character);
    move((maxY/10),4);
    
    
    c = getch();

    
    while (c != 'q')
    {
    /*printw("%d",c);*/
        if(c == 'w') /*Wanting to move upwards*/
        {
          getPos(&y,&x);
            if(y > 1) /* than we can move up because were not at the top of the screen */
            {
                printw(" "); /*remove what the cursor is curently ontop of should be '@'*/
                mvprintw((y - 3), (x),character); /*Print the character in the new position */
                move(y -3 , x); /*re place the cursor into the correct position */
                
            }
          
          // printw("Y : %d , X : %d, Max Y : %d, Max X : %d \n",y,x,maxY,maxX);
        }
        // else if (c == 'a') /*Wanting to move left*/
        // {
        //     getPos(&y,&x);
        //     if(x > 1)
        //     {
        //             printw(" ");
        //             mvprintw(y,(x - 1),character);
        //             move(y,(x - 1));
        //     }
            
        // }
        else if(c == 's') /*Wanting to move down*/
        {
            getPos(&y,&x);
            if(y < (maxY - 3))
            {
                printw(" ");
                mvprintw((y+3), x,character);
                move((y + 3), x);
            }
        }
        else if(c == '\n')
        {
            for(int i = 0; i < maxX; i++)
            {
                mvaddch(maxY, i, ' ');
            }
            // mvprintw(((maxX/3) * 2) + 3, 1, "butts");
            mvprintw(25, 25, "butts");

            // printf("suck it");

        }
        // else if (c == 'd') /*Wanting to move right*/
        // {
        //     getPos(&y,&x);
        //     if(x < (maxX - 2))
        //     {
        //         printw(" ");
        //         mvprintw(y,(x+1),character);
        //         move(y,(x+1));
                
        //     }
        // }
    refresh();
    c = getch();
    }
    endwin();
    // int userInput = 0;
    // int passwordVaultSize = 0;
    // char fileName[256];
    // char line[256];
    // char tempPass[256];
    // char tempKey[256];
    // char tempStr[256];
    // char * parse;
    // FILE *fp;
    // FILE *fo;

    // HTable * hashTable = createTable(500, &hashData, &free, &printData);

    // while(userInput != 7)
    // {
    //     printf("1: Open Password File\n2: Add New Password\n3: Remove Password\n4: Retrieve a Password\n5: Update a Password\n6: Print List of Passwords\n7: Exit\n\n> ");
    //     scanf("%d", &userInput);
    //     switch(userInput)
    //     {
    //         case 1:
    //             printf("enter file name: ");
    //             scanf("%s", fileName);
    //             fp = fopen(fileName, "r");
    //             if(fp == NULL)
    //             {
    //                 printf("could not find file\n\n");
    //                 break;
    //             }

    //             while(fgets(line, sizeof(line), fp) != NULL)
    //             {
    //                 // printf("%s\n", line);
    //                 if(line[strlen(line) - 1] == '\n')
    //                 {
    //                     line[strlen(line) - 1] = '\0';
    //                 }

    //                 parse = strtok(line, ",");
    //                 // tempStore = parse;
    //                 strcpy(tempKey, parse);
    //                 // printf("website: %s ", parse);
    //                 while((parse = strtok(NULL, ",")) != NULL)
    //                 {
    //                     // tempStore = parse;
    //                     strcpy(tempPass, parse);
    //                     // printf("key: %s, data: %s\n", tempStore, parse);
    //                     // printf("password: %s\n", tempStore);
    
    //                 }
    //                 insertData(hashTable, tempKey, tempPass);
    //                 passwordVaultSize++;

    //                 // printf("key: %s, data: %s\n", parse, tempStore);

    //             }

    //             fclose(fp);
    //             break;
    //         case 2:
    //             memset(tempPass, 0, 256);
    //             memset(tempKey, 0, 256);
    //             printf("what program/site is this for? : ");
    //             scanf("%s", tempKey);
    //             if(lookupData(hashTable, tempKey) == NULL)
    //             {
    //                 printf("enter new password into vault: ");
    //                 scanf("%s", tempPass);
    //                 insertData(hashTable, tempKey, tempPass);
    //                 passwordVaultSize++;
    //             }
    //             else
    //             {
    //                 printf("\n\nYou already have a password entered for %s, try removing it or updating it instead\n\n", tempKey);
    //             }
    //             break;
    //         case 3:
    //             memset(tempPass, 0, 256);
    //             memset(tempKey, 0, 256);
    //             printf("what is the site/program you want to delete your info for? : ");
    //             scanf("%s", tempKey);
    //             removeData(hashTable, tempKey);
    //             break;
    //         case 4:
    //             memset(tempStr, 0, 256);
    //             printf("what program/website is this password for? : ");
    //             scanf("%s", tempStr);

    //             if(lookupData(hashTable, tempStr) != NULL)
    //             {
    //                 printf("\nFound it!\nYour %s Password is %s\n\n", tempStr,(char*)lookupData(hashTable, tempStr));
    //             }
    //             else
    //             {
    //                 printf("\nSorry, but I couldn't find any password for your %s account...\n\n", tempStr);
    //             }
    //             break;
    //         case 5:
    //             memset(tempPass, 0, 256);
    //             memset(tempKey, 0, 256);
    //             printf("what program/site account info do you wanto to update? : ");
    //             scanf("%s", tempKey);

    //             if(lookupData(hashTable, tempKey) != NULL)
    //             {

    //                 printf("enter updated password into vault: ");
    //                 scanf("%s", tempPass);
    //                 insertData(hashTable, tempKey, tempPass);

    //             }
    //             else
    //             {
    //                 printf("\n\nYou haven't entered a password for %s yet, try adding one instead\n\n", tempKey);
    //             }
    //             break;
    //         case 6:
    //             printList(hashTable);
    //             // printf("print list\n");
    //             // for(int i = 0; i < hashTable->size;i++)
    //             // {
    //             //     printf("key[%d], data[%s]\n", i, (char*)lookupData(hashTable, "facebook"));
    //             // }
    //             break;
    //         case 7:
    //             destroyTable(hashTable);
    //             return 0;
    //         default:
    //             printf("please enter a number between 1-7\n");
    //     }
    // }

    return 0;
}

