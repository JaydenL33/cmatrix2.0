/*
 *   Authors:    
 *  - Sebastian Southern 
 *  - Ben Gillespie
 *  - Lachlan Leslie
 *  - Albert Ferguson
 *  - Jayden Lee
 *  - Hong Kung (Steven)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* app functionality */
void print_menu();
void print_raindrops(char* input);

/* Compression functionality */
void compress();
void decompress();

/* Encryption/Decryption functionality */
int xor_encrypt(char* plaintext, char* ciphertext, char* keystream);
/* Note: decryption is simply reapplying xor_encrypt with the keystream */
int decrypt(char* plaintext, char* ciphertext, char* keystream);
/* Generators for stream cipher algorithm */
int gen_key(void);
int gen_pseudo_rand_key(int* key);
/* state vector initiliser - 256 list based on key */
int initialisation(int* key);

/* file handling */
int save(char* input);
int load(char* output);

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

int main(void) {

    return 1;
}