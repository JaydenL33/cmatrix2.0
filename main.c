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

void print_menu();

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

int main(int argc, char *argv[])  {
	int plainTextLen;
	unsigned char encryptedData[INPUT_STRING_BUFFER]; /* macro from encrypt.h */
	char testKey[INPUT_STRING_BUFFER];

/***************************************************************************/
 	int i; 
    printf("Program Name Is: %s", argv[0]); 

    if(argc==1) {
        printf("Test \n");
        /* Execute Some Function */
    }

    char* color = KGRN;
    unsigned int is_random = 0;
    if (argc > 1) {
        int i;
        for (i = 0; i < argc; i++) {
            /*
           if (*argv[i] == 'z') {
               printf("random\n\n\n");
           } else if ()
            */
            switch(*argv[i]) {  
                case 'E':
                    plainTextLen = encrypt(encryptedData);
                   	printf("%d \n", plainTextLen);
                    break;
                case 'r':    
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
                    is_random = 1;
                    break;
            } 
        }
    } 
    // printf("\n\ncolor: %s", color);
    printf("\n\nisrandom: %d", is_random);

    char* decryptedData = malloc(sizeof(char) * plainTextLen);
	decrypt(encryptedData, decryptedData, plainTextLen, testKey);

	unsigned char words[plainTextLen]; /* Will hold the encrypted string */
	readcipher(words, plainTextLen); /* Reads in encrypted string */
	char validString[plainTextLen];

	checkValidRange(words, plainTextLen, validString);

	/* MAKE SURE THESE ARE EXPORTED OTHERWISE WE SEGFAULT 
	   TO Export, run: 
       export LINES=$LINES; export COLUMNS=$COLUMNS
	*/
	int LINES = atoi(getenv("LINES"));
	int COLUMNS = atoi(getenv("COLUMNS"));
	print_raindrops(validString, LINES, COLUMNS, color, is_random);
	return 1; 

/**************************************************************************
 * End of Reading Arguments to the Program. 
****************************************************************************/
	return 0; 
}

