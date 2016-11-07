/*@author: Julian Sovernigo
 *      A special thanks to all my friends,
 *      who put up with my attitude and 
 *      obbsession, and still helped to 
 *      test this.
 *
 * The following program is a C and NCurses developed version
 * of the classic game battleship.  The program uses simple 
 * scan commands and TCP AF_INET sockets to communicate
 * between two hosts.  It is in no way complete, functional,
 * useful, helpful, informative, well coded, or in any way
 * what you are using it for.  Probably, anyway.
 *
 *@disclaimer
 *      In addition to above, any user who compiles, views,
 *      runs, or in any way changes this code, by any means,
 *      assumes full responsibility for their own actions.
 *      Absolutely no sympathy or fault is felt or assumed
 *      by the author. In other words, if this program is 
 *      used by you in any way, shape or form, and it causes
 *      something bad to happen to your computer, tough shit.
 *
 *@bugs:
 *      Currently, no glaring bugs have been observed.
 *      due to the nature of scanf, the underlying program
 *      which powers scanw, there are going to be input
 *      errors.  Once again, tough shit.
 */

#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include <stdbool.h>

#define OK "+OK"
#define NO "-NO"
#define SHOT "+SHOT"
#define HIT "+HIT"
#define MISS "+MISS"
#define DONE "+DONE"
#define CONTINUE "+CONT"


#define MAX_ROW 10
#define MIN_ROW 0
#define MAX_COL 10
#define MIN_COL 0

struct board
{
    char enemy_field[MAX_ROW][MAX_COL];
    char my_field[MAX_ROW][MAX_COL];
};


typedef struct board BOARD;

int board_over(BOARD *board);
int get_coords(int *row, int *col, int wx, int wy, char* msg);
int host();
int init_board(BOARD *board);
int join(char *ip_addr);
int play(BOARD *board, int client_fd, int mx, int my, bool is_host);
int print(BOARD board, int mx, int my);
int setup(BOARD* board, int mx, int my);


/**
 *Function main:
 *          Entry point for the program.     
 *@param:   Receives nothing.
 *
 *@return:  literal 0 for success.
 */
int main(int argc, char **argv)
{
    char c;

    bool is_host;

    int result;
    int maxX;
    int maxY;
    int row, col;

    int client_fd;
    
    BOARD board;

    init_board(&board);

    if(argc < 2)
    {
        printf("Improper usage; please use as:\n\tbattleship [join] [ip address]\nOr:\n\tbattleship [host]\n");
        return 1;
    }
    else if(argc < 3 && strcmp(argv[1],"join") == 0)
    {
        printf("Improper usage; please include an ip address.\n\tbattleship [join] [ipaddress]\n");
        return 1;
    }

    initscr();
    getmaxyx(stdscr, maxY, maxX);
    
    //print(board, maxX, maxY);
    //setup(&board, maxX, maxY);

    if(strcmp(argv[1],"host") == 0)
    {
        client_fd = host();
        is_host = true;
    }
    else if(strcmp(argv[1], "join") == 0)
    {
        client_fd = join(argv[2]);
        is_host = false;
    }
    else
    {
        endwin();
        printf("Unknown flag.  Please use \'host\' or \'join\'\n");
        return 1;
    }

    result = play(&board, client_fd, mx, my, is_host);

    getch();

    endwin();

    return 0;
}


/**
 *Function get_coords:
 *          Moves the cursor to the correct position, then prompts the user to input.
 *@param row: a pointer to the row integer. 
 *       col: a pointer to the col integer.
 *       wx: the desired x value of the screen
 *       wy: the desired y value of the screen.
 *       msg: a string that can be used to override the default message.
 *
 *@return: literal 0 on success.
 */
int get_coords(int *row, int *col, int wx, int wy, char* msg)
{
    char* DEFAULT_MSG = "Please enter coordinates.  (e.g. A 1)";
    char r;
    char* r_msg;

    r_msg = (strcmp(msg, "") == 0) ? DEFAULT_MSG : msg; // check to see if msg overrides or not.

    move(wy,wx);   
    printw("%s", r_msg);//this will print the message above the prompt.
    move(wy + 1, wx + 1);

    do
    {
        deleteln(); // clear the area.
        scanw(" %c %d", &r, col);

        r = toupper(r);

        *row = ((int)r) - 65;// while this is kind of weird, it converts the row to a number, rather than a letter.

    }while((*row < 0 || *row > 9) || (*col < 0 || *col > 9)); // while the guess has yet to be entered correctly.


    return 0;
}


/**
 *Function host:
 *          Creates a socket to communicate with the other player. 
 *          If the process fails, the program exits.
 *@param:   Receives nothing.
 *
 *@return:  client_fd: an integer denoting the client socket.
 */
int host()
{
    int main_fd, client_fd;
    int port;
    int cli_len;
    struct sockaddr_in serv_addr, cli_addr;

    main_fd = socket(AF_INET, SOCK_STREAM, 0); // create the main socket file descriptor.

    if(main_fd < 0) // if it was not created and placed on the table.
    {

        perror("Error in creating host socket.\n");
        return -1;
    }
    bzero((char*) &serv_addr, sizeof(&serv_addr)); // TODO switch to memset. This zeros memory, so that the address is not misread.

    port = 23128;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if(bind(main_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) //bind the socket, and then check to see if it failed
    {
        perror("Error while binding host socket.\n");
        return -1;
    }

    listen(main_fd,5); // wait for something to talk to us...

    cli_len = sizeof(cli_addr);

    client_fd = accept(main_fd, (struct sockaddr* ) &cli_addr, &cli_len); // this accepts the incoming connection.

    return client_fd;
}


/**
 *Function init_board: 
 *          Initializes the board struct pointer's field values.
 *@param board: a board pointer to the game's board.
 *
 *@return: literal 0 for success.
 */
int init_board(BOARD *board)
{
    int i;
    int j;
    for(i = MIN_ROW; i < MAX_ROW; i++) // loop through the rows.
    {
        for(j = MIN_COL; j < MAX_COL; j++) // loop through the columns
        {
            board->enemy_field[i][j] = '.';
            board->my_field[i][j] = '.';
        } 
    }
    return 0;
}


/**
 *Function join:
 *          Looks for an open server socket that can be used to play.
 *          Creates a client socket after and then returns it.
 *@param: receives nothing.
 *
 *@return: int client_fd
 */
int join(char* ip_addr)
{
    int client_fd;
    int port;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    port = 23128;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(client_fd < 0) // the socket encountered an error which prevented its creation.
    {
        perror("Error in establishing a socket.\n");
        return -1;
    }

    server = gethostbyname(ip_addr); // converts an ip address from string form to struct form

    if(server == NULL) // the server was not created.
    {
        perror("Error, no such host exists.\n");
        return -1;
    }

    bzero((char*) &serv_addr, sizeof(serv_addr)); // zero the characters associated with the server address
    serv_addr.sin_family = AF_INET;

    bcopy((char*)server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length); // copy the server address to the serv_addr's address
    serv_addr.sin_port = htons(port); // uses magical "htons" to make a valid sin port.

    if(connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) // the connection was unable to be established.
    {
        perror("Error in connecting to the host.\n");
        return -1;
    }

    return client_fd; // return client
}


/**
 *Function play:
 *          This is the main function of the program. In it, information is
 *          exchanged between the two sockets, guesses are made, and the
 *          game is played.  The returning integer tells which player won.
 *@param board: A pointer to the board struct constructed earlier in the
 *              in the program.
 *       client_fd: an integer representing the fd location of the socket
 *                  that was created earlier in the program
 *       mx: an integer representing the maximum x value possible on the
 *           screen.
 *       my: an integer representing the maximum y value possible on the
 *           screen.
 *       is_host: a boolean representing who is the host.  This will be used
 *                to determined PROTOCOL ORDER. !!!SUPER IMPORTANT!!!
 *
 *@return: literal 1 for a current player victory.
 *         literal 0 for a current player loss
 */ 
int play(BOARD *board, int client_fd, int mx, int my, bool is_host)
{
    int result;
    
    bool quit;
    
    
    result = 0;

    if(host)
    {
        send(client_fd, "+SHOT%d,%d", sizeof("+SHOT%d,%d"), 0);
    }

    while(!quit)
    {
        //read shot
        //
        //check for win/loss
        //  return win/loss
        //
        //send response to shot
        //send shot.
        //read response
    }
    //TODO establish protocol.

    return result;
}

/**
 *Function print:
 *          Prints the board struct to the field, starting with the opponents field, then the players field.
 *@param board: a BOARD struct, passed by value, which will have its contents printed.
 *
 *@return: literal 0 for success.
 *
 *@additionals: This method contains very few comments.  For individual description of lines, please
 *              email jsovernigo@hotmail.com
 */
int print(BOARD board, int mx, int my)
{
    int i;
    int j;
    int currY;

    int s = (mx - 42) / 2; // another crappy expression. Finds the start of the 42-unit wide field.

    //
    // BEGIN ENEMY FIELD.
    //
    currY = 0;
    move(0,s);
    printw("*");
    for(i = 0; i < 40; i++) // create the upper border.
    {
        printw("=");
    }
    printw("*");

    currY++; // move up the current y value

    move(currY,s);
    printw("|%-10s","Enemy:");

    for(i = 0; i < 10; i++) // print 0 - 9 label
    {
        printw(" %d", i);
    }
    printw("%11c",'|');

    for(i = 0; i < 10; i++) // print the row of lines and letters and dots
    {   
        currY++;
        move(currY,s);
        printw("|%10c",i+65);
        for(j = 0; j < 10; j++)
        {
            printw(" %c", board.enemy_field[i][j]); // print the arrays current value.
        }
        printw("%11c",'|');
    }
    currY++;
    move(currY,s);
    printw("*");
    for(i = 0; i < 40; i++)
    {
        printw("=");
    }
    printw("*");
    //
    //BEGIN FRIENDLY FIELD.
    //
    move(++currY, s);
    printw("|%-10s","Player:");

    for(i = 0; i < 10; i++)
    {
        printw(" %d", i);
    }
    printw("%11c",'|');

    for(i = 0; i < 10; i++)
    {   
        currY++;
        move(currY,s);
        printw("|%10c",i+65);
        for(j = 0; j < 10; j++)
        {
            printw(" %c", board.my_field[i][j]); // array at
        }
        printw("%11c",'|');
    }
    currY++;
    move(currY,s);

    printw("*");
    for(i = 0; i < 40; i++)
    {
        printw("=");
    }
    printw("*");
    move(my-1, 0);

    return 0;
}

/**
 *Function setup:
 *          This fuction sets up the board and their positions
 *@param board: a pointer to the game's board struct.
 *
 *@return: literal 0 on success.
 */
int setup(BOARD *board, int mx, int my)
{

    char dir; // should be 'u' 'd' 'l' or 'r'
    int max_dist;
    int user_row;
    int user_col;
    int i; // loop variable
    int ship; // main loop variable

    bool valid;

    for(ship = 0; ship < 5; ship++)
    {

        max_dist = (ship != 3) ? ship + 2 : 4; // This accounts for the fouth ship, which also has 4 units.
        max_dist = (max_dist == 6) ? 5 : max_dist;

        do // keep looping as long as the points make no sense.
        {
            erase();
            move(my-3, 0);
            printw("Now placing the %d-long ship.", max_dist);
            print(*board, mx, my);
            get_coords(&user_row, &user_col, 0, my-2, "Please enter the starting coordinate: (e.g. A 1)");

        }while((user_row < 0 || user_row > 9) || (user_col < 0 || user_col > 9));

        erase();
        print(*board, mx, my);
        move(my-3, 0);
        printw("Now placing the %d-long ship.", max_dist);
        move(my-2, 0);
        printw("Please enter a direction (u, d, l, or r)");
        move(my-1, 0);

        do // get the direction.
        {
            scanw(" %c", &dir);
            dir = tolower(dir);
        }while(!strchr("udlr",dir)); // while the user hasn't entered u d l or r.

        if(dir == 'l')
        {
            valid = true;
            if(user_col > 9 || user_col - max_dist < 0)
            {
                ship --;
                continue; // terrible code, but lets you skip back an itteration.
            }
            else
            {
                    for(i = user_col; i > user_col - max_dist; i--)
                {
                    if(board->my_field[user_row][i] != '.')
                    {
                        valid = false;
                    }
                }
                if(!valid)
                {
                    ship --;
                    continue; // see above
                }
            
            }
            for(i = user_col; i > user_col - max_dist; i--) // loop horizontally.
            {
                board->my_field[user_row][i] = max_dist + '0'; // convert max_dist to its char form, and set the array to it.
            }
            
        }
        else if( dir == 'r') // assign horizontally
        {
            valid = true;
            if(user_col < 0 || user_col + max_dist > 9)
            {
                ship --;
                continue; // terrible code, but lets you skip back an itteration.
            }
            else
            {
                for(i = user_col; i < user_col + max_dist; i++)
                {
                    if(board->my_field[user_row][i] != '.')
                    {
                        valid = false;
                    }
                }
                if(!valid)
                {
                    ship --;
                    continue; // see above
                }
            }
            for(i = user_col; i < user_col + max_dist; i++) // loop horizontally.
            {
                board->my_field[user_row][i] = max_dist + '0'; // convert max_dist to its char form, and set the array to it.
            }
        }
        else if(dir == 'u')
        {
            valid = true;
            if(user_row - max_dist < 0 || user_row > 9)
            {
                ship --;
                continue; // terrible code, but lets you skip back an itteration.
            }
            else
            {
                for(i = user_row; i > user_row - max_dist; i--)
                {
                    if(board->my_field[i][user_col] != '.')
                    {
                        valid = false;
                    }
                }
                if(!valid)
                {
                    ship --;
                    continue; // see above
                }
            
            }
            for(i = user_row; i > user_row - max_dist; i--) // loop horizontally.
            {
                board->my_field[i][user_col] = max_dist + '0'; // convert max_dist to its char form, and set the array to it.
            }
        }    
        else if(dir == 'd') // assign vertically
        {
            valid = true;
            if(user_row < 0 || user_row + max_dist > 9)
            {
                ship --;
                continue; // terrible code, but lets you skip back an itteration.
            }
            else
            {
                for(i = user_row; i < user_row + max_dist; i++)
                {
                    if(board->my_field[i][user_col] != '.')
                    {
                        valid = false;
                    }
                }
                if(!valid)
                {
                    ship --;
                    continue; // see above
                }
            
            }
            for(i = user_row; i < user_row + max_dist; i++) // loop horizontally.
            {
                board->my_field[i][user_col] = max_dist + '0'; // convert max_dist to its char form, and set the array to it.
            }
        }

    }

    return 0;
}








