/** @addtogroup mines
 * @{
 */
/**
 * @file
 */

static volatile const char copyright[] =
    "\t\t@(#) Copyright (c) 2004\n"
    "\t\tZmaj from ZmajSoft.  Use this as you wish.\n";

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <str.h>
#include <stdint.h>
#include <io/style.h>
#include <io/console.h>
#include <types/common.h>

#include "main.h"
#include <time.h>

#define FLUSH fflush(stdin)

void difficulty( void );
void beginner( void );
void intermediate( void );
void expert( void );
void custom( void );
void minefield_generator( void );
void print_minefield( void );
void guess( void );
void boom( void );
void print_final_minefield( void );
void win( void );
void play_again( void );
void game_over( void );
extern void scr_end(void);
int x, y;
int M, N;
float diff;
int total_mines = 0;
int mines = 0;
int minefield[30][30];                                      //This 2-D array contains all of the mines, numbers and blank spaces
int blank_minefield[30][30];                                //This contains the minefield full of '|-|' characters
int final_minefield[30][30];

console_ctrl_t *console;
//static int curscore;
static int curscore;

int Rows;
int Cols;
char key_msg[116];



int main()
{ 
    console = console_init(stdin, stdout);
    scr_init();
   
    printf("\t\tWelcome to Minesweeper\n\n\n\n");

    fprintf(stderr, "%s", copyright);

     printf("\n\n\t\tFOR NEXT PRESS ANY KEY.");
   if (getchar()){
    beginner();
    return 0;
}
}



void beginner( void )                                       //Gives the minefield the 'beginner' grid and mines
{
    M = 6;
    N = 6;
    total_mines = 8;
    minefield_generator();
    guess();
}


void minefield_generator( void )                            //Function that generates the minefield
{
    int i = 0, j = 0;

    srand( time( NULL ) );                                  //Starts the random no. generator

    while( j < N )                                          //Nested loop for making the blank minefield and final minefield
    {
        while( i < M)
        {
            minefield[i][j] = '-';
            blank_minefield[i][j] = minefield[i][j];        
            final_minefield[i][j] = minefield[i][j];        
            i++;
        }
        i = 0;
        j++;
    }
    mines = 0;
    while( mines < total_mines )                            //Randomly generates the mines into the minefield
    {
        i = rand()%(M);
        j = rand()%(N);
        if( minefield[i][j] != '*')                         //If statement that checks if there is a mine already there and doesn't place a mine if there is
        {
            minefield[i][j] = '*';
            final_minefield[i][j] = minefield[i][j];
            mines++;
        }
    }
    i = 0;
    j = 0;

    while( j < N )                                          //While loop that generates the numbers for any adjacent mines
    {
        while( i < M)
        {
            if( minefield[i][j] != '*')
            {
                minefield[i][j] = 0;
            }   
            if((minefield[i-1][j-1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i-1][j] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i][j-1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i-1][j+1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i+1][j-1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i+1][j] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i][j+1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            if((minefield[i+1][j+1] == '*') && (minefield[i][j] != '*'))
            {
                minefield[i][j]++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    i = 0;
    j = 0;
}

void print_minefield(void)                                  // This function prints the minefield
{
    printf("\n");
    int i = 0, j = 0, z = 0;
     printf("   ");
    while( z < M )                                          // This while loop prints out the line of co-ordinates along the x axis of the minefield
    {
        if( z == 0 )
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while( j < N )                                          // Loop that prints out each character in the minefield                         
    {   
        printf("|%d|\t", j);
        while( i < M)
        {
            if( blank_minefield[i][j] == '-')
            {
                printf("|%c|\t", blank_minefield[i][j]);

            }
            else if( minefield[i][j] == 0 )                 // This changes any spaces with values of zero to the character 'B'
            {
                blank_minefield[i][j] = 'B';                
                printf("|%c|\t", blank_minefield[i][j]);
            }
            else
            {
                printf("|%d|\t", blank_minefield[i][j]);

            }
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}

static void resume_normal(void)
{
	console_flush(console);
	console_set_style(console, STYLE_NORMAL);
}

void moveto(sysarg_t r, sysarg_t c)
{
	console_flush(console);
	console_set_pos(console, c, r);
}

void scr_init(void)
{
	console_cursor_visibility(console, 0);
	resume_normal();
	scr_clear();
}


/*
 * Clear the screen, forgetting the current contents in the process.
 */
void scr_clear(void)
{
	resume_normal();
	console_clear(console);
	curscore = -1;
	
}



void guess( void )
{
    console_clear(console);
    //moveto(0, 0);
    //scr_clear();
    int i=0, j=0, match=0;
    print_minefield();
    while( j < N )                                          // While loop for testing whether or not the user has cleared the minefield
    {
        while( i < M )
        {
            if(minefield[i][j] == blank_minefield[i][j])
            {
                match++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    if( match == (( M * N ) - total_mines))                 // If the user has cleared the minefield, the win() function is run
    {
        win();
    }
    printf("\nEnter the x value, then a space, then the y value:");
    scanf("%d %d", &x, &y);                                 // Reading in the co-ordinates for the guess
      if (getchar()){                 
    FLUSH;
    if( (x >= M) || (x < 0) || (y < 0) || (y >= N) )
    {
        printf("\nYou Enter X value: %d",x);      
        printf("\nYou enter Y value: %d\n",y);  
        printf("\nPlease enter a value inside the grid\n");
        if (getchar()){
        guess();
        }
    }
    if( minefield[x][y] == '*' )                            // Runs the boom() function if the user selects a mine
    {
        boom();
    }
    if( blank_minefield[x][y] != '-' )
    {
        printf("\nYou Enter X value: %d",x);      
        printf("\nYou enter Y value: %d\n",y);  
        printf("\nPlease enter a value that has not already been entered\n\nPlease for your next move, first press any key!");
        if (getchar()){
        guess();
        }
    }
    

    else                                                // Checks if the adjacent spaces are blank, then changes the values in the blank_minefield array. Because they are changed, they will now print out in the print_minefield function
    {
        blank_minefield[x][y] = minefield[x][y];
        if( minefield[x][y] == 0 )
        {
            if( minefield[x-1][y-1] == 0 )
            {
                blank_minefield[x-1][y] = minefield[x-1][y];
            }
            if( minefield[x-1][y] == 0 )
            {
                blank_minefield[x-1][y] = minefield[x-1][y];
            }
            if( minefield[x][y-1] == 0 )
            {
                blank_minefield[x][y-1] = minefield[x][y-1];
            }
            if( minefield[x-1][y+1] == 0 )
            {
                blank_minefield[x-1][y+1] = minefield[x-1][y+1];
            }
            if( minefield[x+1][y-1] == 0 )
            {
                blank_minefield[x+1][y-1] = minefield[x+1][y-1];
            }
            if( minefield[x+1][y] == 0 )
            {
                blank_minefield[x+1][y] = minefield[x+1][y];
            }
            if( minefield[x][y+1] == 0 )
            {
                blank_minefield[x][y+1] = minefield[x][y+1];
            }
            if( minefield[x+1][y+1] == 0 )
            {
                blank_minefield[x+1][y+1] = minefield[x+1][y+1];
            }
          else { guess();}
        }   else { guess();} }
       
    }
      
}

void boom( void )                                       // Runs the print_final_minefield function, then the play_again function                    
{
    print_final_minefield();
    printf("\n\n\t\tYou hit a mine at %d,%d\n\t\tYOU LOSE!!!!", x, y);
    printf("\n\n\t\tFOR NEXT PRESS ANY KEY.");
    if (getchar()){
    play_again();
}
}

void print_final_minefield( void )                      // Prints the minefield, showing where all of the mines are placed
{
    int i = 0, j = 0, z = 0;
    while( z < M )
    {
        if( z == 0 )
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while( j < N )
    {   
        printf("|%d|\t", j);
        while( i < M)
        {
            printf("|%c|\t", final_minefield[i][j]);
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}

void win( void )                                        // Runs the play_again function
{
    printf("\n\n\n\t\t\tYOU WIN!!!!!\n\n\n");
    printf("\n\n\t\tFOR NEXT PRESS ANY KEY.");
     if (getchar()){
    play_again();
     }
}

void play_again( void )                                 // Gives the user the option to play again
{
    char option[2];
    printf("\n\t\tWould you like to play again(Y/N)?:");
    scanf("%c", &option[0]);
    FLUSH;
    if((option[0] == 'Y') || (option[0] == 'y'))        // Restarts the program from after the welcome message
    {
        beginner();
    }
    else if( (option[0] == 'N') || (option[0] == 'n'))
    {
        game_over();
    }
    else
    {
        printf("\nPlease enter either Y or N");
     if (getchar()){
        play_again();
     }
    }

}

/*
 * End screen mode.
 */
void scr_end(void)
{
	console_cursor_visibility(console, 1);
}


void game_over( void )                                  // Ends the program
{
    printf("\n\n\t\tGame Over");
     printf("\n\n\t\tFOR NEXT PRESS ANY KEY.");
     if (getchar()){
    scr_end();
    exit(1);
     }
}


/** @}
 */
