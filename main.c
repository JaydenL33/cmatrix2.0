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
#define clear printf("\033[2J")

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



void print_raindrops() {
    
    printf("hi\n");
    printf("made it to this function\n");
    char* matrix[LINES-1]; /* Might need to clear :) */

    // printf("made it to this function");
    int count = 0;
    while (count < 1) {
    //     /* Generate a random string of size COLUMNS */
        char asciiChar = 'A'; /* Just for testing basic concept of printing a and b */
        char *tempString = ""; /* Random String */
    //     /* Create string, can defs be done better */
    
        int i;
        for (i = 0; i < COLUMNS; i++) {
            tempString += asciiChar;
        }
        
        // printf("Made it here");
        
        for (i = LINES-1; i >= 0; i--) {
            if (i == 0) {
                matrix[0] = tempString;
            } else {
                matrix[i] = matrix[i-1];
            }
            asciiChar = asciiChar == 'A' ? 'B' : 'A';
        }

        char *finalString = "";
        for (i = 0; i < LINES; i++) {
            finalString = matrix[i];
            printf("final string is %s", finalString);
            finalString += '\n';
        }
        /* after we update matrix, need to loop through matrix and add all strings to one big string with \n :) */
        
        // clear;
        printf("%s", finalString);
        // sleep(1);
        count++;
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