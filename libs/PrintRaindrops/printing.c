/* Printing functionality source code for libPrintRaindrops.
 * Note: utility functions moved to seperate util lib!!!
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Sebastian Southern
 */

# include <stdio.h>   			/* fgets, printf 	*/
# include <stdlib.h>  			/* system 			*/
# include <string.h>  			/* strlen 			*/

# include "printraindrops.h" /* printing functionality 		*/
# include "../Util/util.h"	/* utility functions 			*/

/**************************************************************************
 * Generates a 2D matrix that fills up the terminal via LINES and COLUMNS.
 * This then fills the 0th index with a random string or random string that
 * is generated from an encrypted string. It will then loop infinitely
 * continuously shifting elements down and clearing the screen to produce a
 * 'falling raindrop' effect. The length of the raindrops are randomly 
 * generated.
****************************************************************************/
void print_raindrops(char* encryptedString, int LINES, int COLUMNS, char* color, unsigned int isRandom) {
	char matrix[LINES][COLUMNS];
	int count = 0;
	HIDE_CURSOR;

	int spaces[COLUMNS]; /* Used when printing spaces */
	int non_spaces[COLUMNS]; /* Used when printing chars */
	int i;
	for (i = 0; i < COLUMNS; i++) {
		spaces[i] = 0;
		non_spaces[i] = 0;
	}
	printf("Is random is %c\n", isRandom);

	/* This should print infinitely unless input specified */
	while (1) {
		/* Generate a random string of length COLUMNS */
		char temp_str[COLUMNS];
		
		if (isRandom) {
			/* Generates a random string of characters */
			rand_str(temp_str, COLUMNS);
		} else {
			/* Based on encrypted string */
			rand_encrypted_str(temp_str, encryptedString, COLUMNS);
		}

		int i;
		/* Loop from bottom of matrix and shift elements down */
		for (i = LINES - 2; i >= 0; i--) {
			if (i == 0) {
				int j;
				/* Loop through width of terminal */
				for (j = 0; j < COLUMNS; j++) {
					/* Used to control the length of the 'raindrop' */
					if (non_spaces[j] == 0) {
						int rand_num = (int) (rand() % LINES + 1) * 4;
						spaces[j] = rand_num;
						non_spaces[j] = rand_num / 4;
						// non_spaces[j] = (int) (rand() % rand_num + 1) / 2;
					}
					/* If spaces[j] isn't empty, print a space and -1 */
					if (spaces[j] > 0) {
						matrix[0][j] =  ' ';
						spaces[j] = spaces[j] - 1;
					}   else if (non_spaces[j] > 0) {
						matrix[0][j] = temp_str[j];
						non_spaces[j] = non_spaces[j] - 1;
					}
				}
			} else {
				int j;
				for (j = 0; j < COLUMNS; j++) {
					matrix[i][j] = matrix[i-1][j];
				}  
			}
		}

		/* Creates a string of the entire matrix that can be printed to the terminal */
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
		
		/* Clear the terminal */
		CLEAR;
		/* Prints the entire matrix in a specified colour */
		printf("%s%s", color, finalString);
		delay();  
		count++;
	}
}

/********************************************** 
 * *str = variable to put random string into
 * length = size of length in bytes
 *
 * Generates random string 
 * rand_str(str, sizeof str - 1)
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
 * Generates a random string from the encrypted string of size COLUMNS
 * 'new_str' will be the generated string from this function.
 * 'encrypted_str' is the encrypted string to generate the new string from.
 * 'length' is the desired width of the string, generally will be width of
 * the terminal.
****************************************************************************/
void rand_encrypted_str(char *new_str, char *encrypted_str, size_t length) {
	int i;
	for (i = 0; encrypted_str[i] != '\0'; i++) {}
	
	while (length-- > 0) {
		size_t index = (int) rand() % i;
		*new_str++ = encrypted_str[index];
	}
}

void getOptions(int argc, char* argv[], char* color, int* is_random) {
	/* put ':' at the start of the 
	 * string so that program can  
	 * distinguish between '?' and ':'  
	 */

	int opt; 
	while((opt = getopt(argc, argv, "rmcybwztf:")) != -1) {  
		switch(opt) {  
			case 'r':    
				/* strcpy(color, KRED); */
				color = KRED;
				break;
			case 'm':    
				color = KMAG;
				break;
			case 'c':
				color = KCYN;
				break;
			case 'y': 
				color = KYEL;
				break;
			case 'b':
				color = KBLU;
				break;
			case 'w':
				color = KWHT;
				break;
			case 'z': /* Random */
				*is_random = 1;
				break;
			case ':':  
				printf("option needs a value\n");  
				break;  
			case '?':  
				printf("???");
				break;
		}  
	}
}