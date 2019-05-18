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
#define clear printf("\033[H\033[J")
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void print_menu();
void print_raindrops();
void rand_str(char *dest, size_t length);
void compress();
/* int encrypt();
int decrypt(); */
int save();
int load();
void pepe();
void squash_pepe();

int main(void) {
    /* printf("LINES: %s\n", getenv("LINES"));
    printf("COLUMNS: %s\n", getenv("COLUMNS")); */
    /* Lines and Columns need to be passed in at compile time with -D flag */
    print_raindrops();

    return 1;
}


void delay() {
    int c, d;
   /* Can change the time of delay with this, Cheap method but works... */
   for (c = 1; c <= 32767 / 6; c++) {
       for (d = 1; d <= 32767 / 6; d++) {}
   }
}

void print_raindrops() {
    char* matrix[LINES-1][COLUMNS];
    int count = 0;
    char asciiChar = 'A';
    printf("\e[?25l"); /* Hides the cursor */
    while (count < 100) {     
        char temp[COLUMNS];
        rand_str(temp, COLUMNS);
        /* Create string, can defs be done better */
        int i;
        for (i = LINES-1; i >= 0; i--) {
            if (i == 0) {
                int j;
                for (j = 0; j < COLUMNS; j++) {
                    matrix[i][j] = temp[j];
                }
            } else {
                /* Check for valid character, not needed on mac, not sure about linux. */
                if (matrix[i-1][0] >= 'a' && matrix[i-1][0] <= 'z' || 
                    matrix[i-1][0] >= 'A' && matrix[i-1][0] <= 'Z' ||
                    matrix[i-1][0] >= '0' && matrix[i-1][0] <= '9' || 
                    matrix[i-1][0] == ' ') {
                    int j;
                    for (j = 0; j < COLUMNS; j++) {
                        matrix[i][j] = matrix[i-1][j];
                    }  
                }
                
            }
        }

        char finalString[(LINES) * (COLUMNS)];
        int tempCount = 0;
        /* LINES - 1 is needed otherwise it prints on the same line.... */
        for (i = 0; i < LINES-1; i++) {
            int j;
            for (j = 0; j < COLUMNS; j++) {
                finalString[tempCount] = matrix[i][j];
                tempCount++;
            }   
            finalString[tempCount] = '\n';
            tempCount++;
        }
        clear;
        printf("%s%s", KGRN, finalString);
        
        delay();  
        count++;       
    }   
}

/* int main(int argc, char *argv[], char *envp[]) {} */
/********************************************** 
*  *str = variable to put random string into
*  length = size of length in bytes
*
*  Generates random string 
*  rand_str(str, sizeof str - 1)
*
***********************************************/
void rand_str(char *str, size_t length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "                          "
                     "                          "
                     "                          "
                     "                          "
                     "                          "
                     "                          "
                     "                          "
                     "                          ";

   

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *str++ = charset[index];
    }
    *str = '\0';
}
