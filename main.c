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

# include "libs/Crypto/encrypt.h"
# include "libs/Util/util.h"
# include "libs/PrintRaindrops/printraindrops.h"

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

int main(int argc, char *argv_ptr[])  {
	int plain_text_len = 0;
	unsigned char encrypted_data[INPUT_STRING_BUFFER]; /* macro from encrypt.h */
	char test_key[INPUT_STRING_BUFFER];

/* - Main program control logic follows */
/*****************************************************************************/
    /* Defaults:
     * Colour: green 
     * Print vals: random
     */
    char* color_ptr = KGRN;
    unsigned int is_random = 0;

    /* 
     * - Handle flags
     * test if arguments passed, 
     * else program cannot decrypt un-entered data!! 
     */
    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            switch(*argv_ptr[i]) {  
                case 'e': /* request console data input to encrypt */
                    plain_text_len = encrypt(encrypted_data);
                   	printf("%d \n", plain_text_len);
                    break;
                case 'g': /* green */
                    color_ptr = KGRN;
                    break;
                case 'r': /* red */
                    color_ptr = KRED;
                    break;
                case 'm': /* magenta */ 
                    color_ptr = KMAG;
                    break;
                case 'c': /* cyan */
                    color_ptr = KCYN;
                    break;
                case 'y': /* yellow */
                    color_ptr = KYEL;
                    break;
                case 'b': /* blue */
                    color_ptr = KBLU;
                    break;
                case 'w': /* white */
                    color_ptr = KWHT;
                    break;
                default:
                    printf("------------------------------------------------"
                    "\nPlease pass in a valid option:"
                    "\ne: Encrypt"
                    "\ng: Green"
                    "\nr: Red"
                    "\nm: Magenta"
                    "\nc: Cyan"
                    "\ny: Yellow"
                    "\nb: Blue"
                    "\nw: White"
                    "\n------------------------------------------------\n");
                    return 0;
            } 
        }
    } else {
    	/* no arguments were passed! */
    	printf("No arguments were passed, check your inputs and try again!\n");
        
    	return 0;
    }

    if (plain_text_len == 0 && is_random == 0) { /* no encrypted data exists! */
        printf("Printing random string as encrypted was not selected.\n");
        is_random = 1;
        char valid_string[plain_text_len];	/* hold validated string */
        
        int LINES = atoi(getenv("LINES"));
		int COLUMNS = atoi(getenv("COLUMNS"));

		print_raindrops(valid_string, LINES, COLUMNS, color_ptr, is_random);
		return 1; 
    } else if (plain_text_len > 0) { /* encrypted data was returned */
/******************************************************************************
 * Matrix will now print entered (encrypted) data as screensaver
******************************************************************************/
        char* decryptedData = malloc(sizeof(char) * plain_text_len); 
        unsigned char words[plain_text_len]; /* holds encrypted string */
        char valid_string[plain_text_len];	/* hold validated string */

		decrypt(encrypted_data, decryptedData, plain_text_len, test_key);
		readcipher(words, plain_text_len); /* Reads in encrypted datafile */
		checkValidRange(words, plain_text_len, valid_string);

		/* MAKE SURE THESE ARE EXPORTED OTHERWISE WE SEGFAULT 
		 *  TO Export, run: 
	     *  export LINES=$LINES; export COLUMNS=$COLUMNS
		 */
		int LINES = atoi(getenv("LINES"));
		int COLUMNS = atoi(getenv("COLUMNS"));
		print_raindrops(valid_string, LINES, COLUMNS, color_ptr, is_random);
		/* success! */
		return 1; 
    } else {
    	printf(UNKNOWN);
    }
/******************************************************************************
 * End of Reading Arguments to the Program. 
******************************************************************************/
    /* if you have reached this point, something is quite wrong */
	return 0; 
}

