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
# include "libs/Compression/compression.h"

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

int main(int argc, char *argv[])  {
	int plainTextLen = 0;
	unsigned char encryptedData[INPUT_STRING_BUFFER]; /* macro from encrypt.h */
	char testKey[INPUT_STRING_BUFFER];
	char *decryptedData = malloc(sizeof(char) * plainTextLen); 
/* - Main program control logic follows */
/*****************************************************************************/
    /* Defaults:
     * Colour: green 
     * Print vals: random
     */
    char* color = KGRN;
    unsigned int isRandom = 0;

    /* 
     * - Handle flags
     * test if arguments passed, 
     * else program cannot decrypt un-entered data!! 
     */
    if (argc > 1) {
        int i;
        for (i = 0; i < argc; i++) {
            switch(*argv[i]) {  
                case 'e': /* request console data input to encrypt */
                    plainTextLen = encrypt(encryptedData);
                    break;
                case 'r': /* red */
                    color = KRED;
                    break;
                case 'm': /* magenta */ 
                    color = KMAG;
                    break;
                case 'c': /* cyan */
                    color = KCYN;
                    break;
                case 'y': /* yellow */
                    color = KYEL;
                    break;
                case 'b': /* blue */
                    color = KBLU;
                    break;
                case 'w': /* white */
                    color = KWHT;
                    break;
                case 'z': /* Print rand vals */
                    isRandom = 1;
                    break;
                case 'd':
                plainTextLen = readcipher(encryptedData, plainTextLen);
                decryptedData = (char*) malloc(sizeof(char) * plainTextLen); 
                decrypt(encryptedData, decryptedData, plainTextLen, testKey);
               		break;

            } 
        }
    } else {
    	/* no arguments were passed! */
    	printf("No arguments were passed, check your inputs and try again!\n");
    	return 0;
    }

    if (plainTextLen == 0 && isRandom == 0) { /* no encrypted data exists! */
        printf("Printing random string as encrypted was not selected.\n");
        isRandom = 1;
        char validString[plainTextLen];	/* hold validated string */
        
        int LINES = atoi(getenv("LINES"));
		int COLUMNS = atoi(getenv("COLUMNS"));

		print_raindrops(validString, LINES, COLUMNS, color, isRandom);
		/* success! */
		return 1; 
    } else if (plainTextLen > 0) { /* encrypted data was returned */
/******************************************************************************
 * Matrix will now print entered (encrypted) data as screensaver
******************************************************************************/
        decryptedData = (char *) malloc(sizeof(char) * plainTextLen); 
        unsigned char words[plainTextLen]; /* holds encrypted string */
        char validString[plainTextLen];	/* hold validated string */

		decrypt(encryptedData, decryptedData, plainTextLen, testKey);
		readcipher(words, plainTextLen); /* Reads in encrypted datafile */
		checkValidRange(words, plainTextLen, validString); /* Checks if the 
		string is valid or not.  */
		int binaryNumber;
		compression(validString, plainTextLen, &binaryNumber);

		/* MAKE SURE THESE ARE EXPORTED OTHERWISE WE SEGFAULT 
		 *  TO Export, run: 
	     *  export LINES=$LINES; export COLUMNS=$COLUMNS
		 */
		int LINES = atoi(getenv("LINES"));
		int COLUMNS = atoi(getenv("COLUMNS"));
		print_raindrops(validString, LINES, COLUMNS, color, isRandom);
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

