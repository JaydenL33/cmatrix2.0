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
		/* if LINES and COLUMNS are passed in from the CLI we can access them this way */
		// int LINES = atoi(argv[1]);
		// int COLUMNS = atoi(argv[2]);

		// print_raindrops(validString, LINES, COLUMNS);
	}
	
	char* color = KGRN;
	int is_random = 0;
	getOptions(argc, argv, color, &is_random);
	  

	/* MAKE SURE THESE ARE EXPORTED OTHERWISE WE SEGFAULT */
	int LINES = atoi(getenv("LINES"));
	int COLUMNS = atoi(getenv("COLUMNS"));
	print_raindrops(validString, LINES, COLUMNS, color, is_random);
	return 1;
}
