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
# include "crypto\encrypt.h"

/* app functionality */
void print_menu();
void print_raindrops(char* input);

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

int main(int argc, char* arv[]) {
    int i, plainTextLen;
    char testKey[INPUT_STRING_BUFFER];
    unsigned char encryptedData[INPUT_STRING_BUFFER]; /* macro from encrypt.h */
    char decryptedData[INPUT_STRING_BUFFER];
    plainTextLen = encrypt(encryptedData);

    /* test cipher output */
	printf("\nCipherText HEX:\n");
	
	for (i = 0; i < plainTextLen; i++){
		printf("%x", encryptedData[i]);
	}

	printf("\nCipherText CHAR:\n");
	
	for (i = 0; i < plainTextLen; i++){
		printf("%c", encryptedData[i]);
	}

	decrypt(encryptedData, decryptedData, plainTextLen, testKey);
	printf("\nPlaintext HEX:\n");
	for (i = 0; i < plainTextLen; i++){
		printf("%x", decryptedData[i]);
	}

	printf("\nPlaintext CHAR:\n");
	for (i = 0; i < plainTextLen; i++){
		printf("%c", decryptedData[i]);
	}
    return 0;
}