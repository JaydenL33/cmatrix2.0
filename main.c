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

#define MAX_KEY_LEN 256
#define INPUT_STRING_BUFFER 1024

/* app functionality */
void print_menu();
void print_raindrops(char* input);

/* Compression functionality */
void compress();
void decompress();

/* Encryption/Decryption functionality */
int encrypt(void);
int xor_encrypt(char* plaintext, char* ciphertext, int* keystream);
/* Note: decryption is simply reapplying xor_encrypt with the keystream */
int decrypt(char* plaintext, char* ciphertext, char* keystream);
/* Generators for stream cipher algorithm */
int gen_key(int* key_arr, int* key);
int gen_pseudo_rand_key(int* state_vector, int* return_key);
/* state vector initiliser - 256 list based on key */
void initialisation(int* key_arr,  int* state_vector, int key_len);
/* plaintext getter */
int get_plaintext(char* plaintext);


/* file handling */
int save(char* input);
int load(char* output);

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

/* utility functions */
void clear_stdin();
void init_int_arr(int* init_arr, int len);
void swap_elems(int* input_arr1, int* input_arr2);

int main(int argc, char* arv[]) {

    return 1;
}

/*******************************************************************************
 * Implement gen_key to retrieve a user-defined key. Then generate a pseudo rand
 * byte stream from this key with gen_pseudo_rand_key. Finally use xor_encrypt 
 * to output ciphertext byte array.
 * Inputs: 
 *	- none
 * Outputs:
 *	- ciphertext
*******************************************************************************/
int encrypt(void) {
	/* string data */
	char plaintext[INPUT_STRING_BUFFER];
	char ciphertext[INPUT_STRING_BUFFER];
	int length_plaintext_data;
	/* Define byte arrays */
	int byte_key_stream[MAX_KEY_LEN];
	int byte_state_vector[MAX_KEY_LEN];
	int pseudo_rand_key[MAX_KEY_LEN];
	/* Byte converted key */
	int key_val[MAX_KEY_LEN];

	gen_key(byte_key_stream, key_val);
	gen_pseudo_rand_key(byte_state_vector, pseudo_rand_key);
	length_plaintext_data = get_plaintext(plaintext); 					printf("%d\n", length_plaintext_data);

	xor_encrypt(plaintext, ciphertext, byte_key_stream);
	return 1;
}

/*******************************************************************************
 * Get key from user, account for buffer overflow. Avoids printing key in 
 * plaintext.
 * Inputs: 
 *	- mem address for key_arr ("byte" ~ int value of ASCII)
 * Outputs:
 *	- int length of key
 *	- BYTE struct converted key to mem address provided
*******************************************************************************/
int gen_key(int* key_arr, int* key) {

	int length;
	init_int_arr(key_arr, MAX_KEY_LEN);
	char user_input_key[MAX_KEY_LEN+1];
	char* explanation = "The key value may contain any ASCII valid characters.\
						(TODO: escape sequences?? - implement testing later)\
						Only the first 256 characters inputed will be used.";
	
	printf("%s\n", explanation);
	printf("Enter the key:\n");
	/* Do not print the key in plaintext back to the shell! */
	system("@echo off"); 
	
	/* avoid a buffer overflow */
	clear_stdin();
	fgets(user_input_key, MAX_KEY_LEN, stdin);
	length = strlen(user_input_key);

	if (user_input_key[length - 1] == '\n') {
    	/* Replace \n with \0 (replace the EOL with end of string)*/
        user_input_key[length - 1] = '\0';
    } else {
        user_input_key[MAX_KEY_LEN] = '\0';
        /*Clear stdin if overflow */
        clear_stdin();
    }
   	/*re enable echo */
    system("@echo on"); 
    /* convert input ASCII key to "byte" key */
    key = (int*) user_input_key;
	return 0;
}

/*******************************************************************************
 * Utilise key to create a state vector.
 * Inputs: 
 *	- mem address for key_arr
 *	- int length of key
 * Outputs:
 *	- mem address of state vector to store to
*******************************************************************************/
void initialisation(int* key_arr,  int* state_vector, int key_len) {

	int S[MAX_KEY_LEN];
	int T[MAX_KEY_LEN];
	int i, j;

	for (i = 0; i < MAX_KEY_LEN; i++) {
		S[i] = i;
		T[i] = key_arr[i % MAX_KEY_LEN - key_len];

	}

	for (i = 0; i < MAX_KEY_LEN; i++) {
		j = (j + S[i] + T[i] % MAX_KEY_LEN);
		swap_elems(&S[i], &S[j]);

	}
	/* return the mem address of our state vector */
	state_vector = S;
}

/*******************************************************************************
 * Utilise byte state vector array to generate a pseudo random key-stream.
 * Inputs: 
 *	- mem address for state_vector
 * Outputs:
 *	- mem address return_key byte stream.
*******************************************************************************/
int gen_pseudo_rand_key(int* state_vector, int* return_key) {
	int i, j, t;

	while(1) {
		i = (i+1) % MAX_KEY_LEN;
		j = (j + state_vector[i]) % MAX_KEY_LEN;
		swap_elems(&state_vector[i], &state_vector[j]);
		t = (state_vector[i] + state_vector[j]) % 256;
		return_key[i] = state_vector[t];
	}

	return 0;
}

/*******************************************************************************
 * Utilise keystream (bytes) to pseudo-randomly xor each plaintext (byte) value.
 * Inputs: 
 *	- mem address for plaintext
 * 	- mem address for keystream
 * Outputs:
 *	- mem address for ciphertext
*******************************************************************************/
int xor_encrypt(char* plaintext, char* ciphertext, int* keystream) {
	int i;

	for (i = 0; i < MAX_KEY_LEN; i++) {
		ciphertext[i] = keystream[i]^plaintext[i];
	}

	return 0;
}


/*******************************************************************************
 * Plaintext getter. Prompts user for plaintext entry to be encrypted. 
 * WARNING: Max plaintext entered currently allows 1024 char's!! All remaining 
 * ignored!
 *	- mem address for plaintext
 * Outputs:
 *	- int length of plaintext entered.
*******************************************************************************/
int get_plaintext(char* plaintext) {
	int len_plaintext;
	char* explanation = "Enter the data to be encrypted! Note: currently only\
						1024 characters are supported, all remaining characters\
						will be ignored!";

	printf("\n%s\n", explanation);
	clear_stdin();
	fgets(plaintext, INPUT_STRING_BUFFER, stdin);
	len_plaintext = strlen(plaintext);

	if (plaintext[len_plaintext - 1] == '\n') {
    	/* Replace \n with \0 (replace the EOL with end of string)*/
        plaintext[len_plaintext - 1] = '\0';
    } else {
        plaintext[MAX_KEY_LEN] = '\0';
        /*Clear stdin if overflow */
        clear_stdin();
    }
	return len_plaintext;
}

/*******************************************************************************
 * Utility function that clears stdin until newline or EOF
*******************************************************************************/
void clear_stdin() {
    int c;
    while (!((c = getchar() == '\n') || c == EOF));
}

/*******************************************************************************
 * Utility function that initialises int arrays to all 1
*******************************************************************************/
void init_int_arr(int* init_arr, int len) {
	int i;
	for (i = 0; i < len; ++i)
		init_arr[i] = 1;
}

/*******************************************************************************
 * Utility function that swaps input_arr1 with input_arr2
*******************************************************************************/
void swap_elems(int* input_arr1, int* input_arr2) {
	int* tmp_p;
	tmp_p = input_arr1;
	input_arr1 = input_arr2;
	input_arr2 = tmp_p; 
}