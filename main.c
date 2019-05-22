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

    printf("[ENCRYPTED INTS]:");
    for (i = 0; i < plainTextLen; i++) {
    	printf("%d ", encryptedData[i]);
    }
	decrypt(encryptedData, decryptedData, plainTextLen, testKey);
	
	printf("\n[DECRYPTED INTS]:");
	for (i = 0; i < plainTextLen; i++){
		printf("%d ", decryptedData[i]);
	}
	printf("\n%s\n", decryptedData);
	
    return 0;
}