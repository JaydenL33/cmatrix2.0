/*
    Authors:    
   - Sebastian Southern 
   - Ben Gillespie
   - Lachlan Leslie
   - Albert Ferguson
   - Jayden Lee
   - Hong Kung (steve)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h> /* THIS WILL NEED TO BE DELETED, just for testing */
#define clear printf("\033[H\033[J")

void print_menu();
void print_raindrops();
void compress();
/* int encrypt();
int decrypt(); */
int save();
int load();
void pepe();
void squash_pepe();

/*
while (*envp) {
     printf("%s\n", *envp++);
}
*/

int main(void) {
    /* clear; */
    printf("hi, lines is %d and cols is %d\n", LINES, COLUMNS);
    /* printf("LINES: %s\n", getenv("LINES"));
    printf("COLUMNS: %s\n", getenv("COLUMNS")); */
    /* Lines and Columns need to be passed in at compile time with -D flag */
    print_raindrops();

    return 1;
}


void delay() {
    int c, d;
   /* Can change the time of delay with this, Cheap method but works... */
   for (c = 1; c <= 32767 / 2; c++) {
       for (d = 1; d <= 32767 / 2; d++) {}
   }
}
void print_raindrops() {
    char* matrix[LINES-1][COLUMNS]; /* Might need to clear :) */


    // printf("made it to this function");
    int count = 0;
    char asciiChar = 'A';
    while (count < 20) {
        /* Generate a random string of size COLUMNS */
         /* Just for testing basic concept of printing a and b */
        char tempString[COLUMNS];
        /* Create string, can defs be done better */
        int i;
        for (i = 0; i < COLUMNS; i++) {
            tempString[i] = asciiChar;
        }
        
        for (i = LINES-1; i >= 0; i--) {
            if (i == 0) {
                int j;
                for (j = 0; j < COLUMNS; j++) {
                    matrix[i][j] = tempString[i];
                    // printf("%c", tempString[i]);
                }
                // printf("\n");
            } else {
                /* Check for valid character, not needed on mac, not sure about linux. */
                if (matrix[i-1][0] == 'A' || matrix[i-1][0] == 'B') {
                    int j;
                    for (j = 0; j < COLUMNS; j++) {
                        // matrix[i][j] = tempString[j];
                        matrix[i][j] = matrix[i-1][j];
                        // printf("%c", matrix[i][j]);
                    }  
                    // printf("\n");
                }
                 
            }
        }

        char finalString[LINES * COLUMNS];
        int tempCount = 0;
        for (i = 0; i < LINES; i++) {
            int j;
            for (j = 0; j < COLUMNS; j++) {
                finalString[tempCount] = matrix[i][j];
                // printf("%c", matrix[i][j]);
                tempCount++;
            }   
            finalString[tempCount] = '\n';
            tempCount++;
        }

        /* after we update matrix, need to loop through matrix and add all strings to one big string with \n :) */
        clear;
        printf("%s", finalString);
        delay();  
        count++;
        if (asciiChar == 'A') {
            asciiChar = 'B';
        } else {
            asciiChar = 'A';
        }
    }   
}

/* int main(int argc, char *argv[], char *envp[]) {} */

/*
for (int i = 0; i < LINES; i++) {
            char s[156];
            for (int j = 0; j < COLUMNS; j++) {
                if (j == 156) {
                    s[j] = 'A';
                } else {
                    s[j] ='x';
                }
            }
            printf("%s\n", s);
            sleep(1);
        }
*/