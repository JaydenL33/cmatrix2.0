/*
 *   Authors:    
 *  - Sebastian Southern 
 *  - Ben Gillespie
 *  - Lachlan Leslie
 *  - Albert Ferguson
 *  - Jayden Lee
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "crypto/encrypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CLEAR printf("\033[H\033[J") /* Clears the entire terminal */
#define HIDE_CURSOR printf("\e[?25l") /* Hide the cursor in the terminal */

/* Various colours that can be used during printing */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void print_menu();
void print_raindrops(char* encryptedString, int LINES, int COLUMNS);
void rand_str(char *dest, size_t length);
void rand_encrypted_str(char *input, char *str, size_t length);

/* Compression functionality */
void compress();
void decompress();

/* file handling */
int save(char* input);
int load(char* output);

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

int main(int argc, char *argv[])  {
    int plainTextLen;
    char testKey[INPUT_STRING_BUFFER];
    unsigned char encryptedData[INPUT_STRING_BUFFER]; /* macro from encrypt.h */

    plainTextLen = encrypt(encryptedData);
	char* decryptedData = malloc(sizeof(char) * plainTextLen);
	decrypt(encryptedData, decryptedData, plainTextLen, testKey);

    char words[130]; /* Will hold the encrypted string */
    int num = readcipher(words, 130); /* Reads in encrypted string */
    char validString[plainTextLen];
    checkValidRange(words, plainTextLen, validString);

    printf("argc is %d", argc);
    if (argc == 3) {
        int LINES = atoi(argv[1]);
        int COLUMNS = atoi(argv[2]);
        print_raindrops(validString, LINES, COLUMNS);
    }

    return 1;
}

void delay() {
    int c, d;
    /* Can change the time of delay with this, Cheap method but works... */
    for (c = 1; c <= 32767 / 8; c++) {
        for (d = 1; d <= 32767 / 8; d++) {}
    }
}

void print_raindrops(char* encryptedString, int LINES, int COLUMNS) {
    char* matrix[LINES-1][COLUMNS];
    int count = 0;
    HIDE_CURSOR;

    int spaces[COLUMNS]; /* Used when printing spaces */
    int non_spaces[COLUMNS]; /* Used when printing chars */
    int i;
    for (i = 0; i < COLUMNS; i++) {
        spaces[i] = 0;
        non_spaces[i] = 0;
    }

    /* This should print infinitely unless input specified */
    while (1) {
        /* Generate a random string of length COLUMNS */
        char temp_str[COLUMNS];

        rand_str(temp_str, COLUMNS); /* Generates a random string of characters */
        /* Based on encrypted string */
        /* rand_encrypted_str(temp_str, encryptedString, COLUMNS); */

        int i;
        for (i = LINES - 2; i >= 0; i--) {
            if (i == 0) {
                int j;
                for (j = 0; j < COLUMNS; j++) {
                    if (non_spaces[j] == 0) {
                        int rand_num = (int) (rand() % LINES + 1) * 4;
                        spaces[j] = rand_num;
                        non_spaces[j] = rand_num / 4;
                    }
                    if (spaces[j] > 0) {
                        matrix[0][j] = ' ';
                        spaces[j] = spaces[j] - 1;
                    }   else if (non_spaces[j] > 0) {
                        matrix[0][j] = temp_str[j];
                        non_spaces[j] = non_spaces[j] - 1;
                    }
                }
            } else {
                /* Check for valid character, not needed on mac, not sure about linux. */
                /* if (matrix[i-1][0] >= 'a' && matrix[i-1][0] <= 'z'
                    matrix[i-1][0] >= 'A' && matrix[i-1][0] <= 'Z'
                    matrix[i-1][0] >= '0' && matrix[i-1][0] <= '9' 
                    matrix[i-1][0] == ' ') { */
                    int j;
                    for (j = 0; j < COLUMNS; j++) {
                        matrix[i][j] = matrix[i-1][j];
                    }  
                /* } */
            }
        }

        char finalString[(LINES) * (COLUMNS)];
        int tempCount = 0;
        for (i = 0; i < LINES; i++) {
            int j;
            for (j = 0; j < COLUMNS; j++) {
                finalString[tempCount] = matrix[i][j];
                tempCount++;
            }   
            finalString[tempCount] = '\n';
            tempCount++;
        }
        CLEAR;
        /* Prints the entire matrix in a specified colour */
        printf("%s%s", KCYN, finalString);
        delay();  
        count++;
    }
}

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
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *str++ = charset[index];
    }
    *str = '\0';
}

/**************************************************************************
*  Generates a random string from the encrypted string of size COLUMNS
*  'new_str' will be the generated string from this function.
*  'encrypted_str' is the encrypted string to generate the new string from.
*  'length' is the desired width of the string, generally will be width of
*  the terminal.
*
****************************************************************************/
void rand_encrypted_str(char *new_str, char *encrypted_str, size_t length) {
    int i;
    for (i = 0; encrypted_str[i] != '\0'; i++) {}
    
    while (length-- > 0) {
        size_t index = (int) rand() % i;
        *new_str++ = encrypted_str[index];
    }
}