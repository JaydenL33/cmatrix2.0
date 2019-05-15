/* Encryption functionality for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson, Jayden Lee
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "encrypt.h"

# define MAX_KEY_LEN 256
# define INPUT_STRING_BUFFER 1024

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
	int keyLength;

	keyLength = getKey(key_val);
	byteStreamInitialiser(key_val, byte_state_vector, &keyLength);
	genPseudoRandKey(byte_state_vector, pseudo_rand_key);				printf("%d\n", keyLength);
	length_plaintext_data = getPlaintext(plaintext); 					printf("%d\n", length_plaintext_data);

	XORencrypt(plaintext, ciphertext, byte_key_stream);
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
int getkey(int* key_arr) {

	int length;
	char user_input_key[MAX_KEY_LEN+1];
	char* explanation = "The key value may contain any ASCII valid characters.\
						(TODO: escape sequences?? - implement testing later)\
						Only the first 256 characters inputed will be used.";
	
	printf("%s\n", explanation);
	printf("Enter the key:\n");
	/* Do not print the key in plaintext back to the shell! */
	system("@echo off"); 
	
	/* avoid a buffer overflow */
	clearStdin();
	fgets(user_input_key, MAX_KEY_LEN, stdin);
	length = strlen(user_input_key);

	if (user_input_key[length - 1] == '\n') {
    	/* Replace \n with \0 (replace the EOL with end of string)*/
        user_input_key[length - 1] = '\0';
    } else {
        user_input_key[MAX_KEY_LEN] = '\0';
        /*Clear stdin if overflow */
        clearStdin();
    }
   	/*re enable echo */
    system("@echo on"); 
    /* convert input ASCII key to "byte" key */
    key_arr = (int*) user_input_key;
	return length;
}

/*******************************************************************************
 * Utilise key to create a state vector.
 * Inputs: 
 *	- mem address for key_arr
 *	- int length of key
 * Outputs:
 *	- mem address of state vector to store to
*******************************************************************************/
void byteStreamInitialiser(int* key_arr,  int* state_vector, int* keyLength) {

	int S[MAX_KEY_LEN];
	int T[MAX_KEY_LEN];
	int i, j;

	/* loops input key, generates a byte stream vector (byte-key) of 256 */
	for (i = 0; i < MAX_KEY_LEN; i++) {
		S[i] = i;
		T[i] = key_arr[i % MAX_KEY_LEN - *keyLength];
	}

	for (i = 0; i < MAX_KEY_LEN; i++) {
		j = (j + S[i] + T[i] % MAX_KEY_LEN);
		swap(&S[i], &S[j]);

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
int genPseudoRandKey(int* state_vector, int* return_key) {
	int i, j, t;

	while(1) {
		i = (i+1) % MAX_KEY_LEN;
		j = (j + state_vector[i]) % MAX_KEY_LEN;
		swap(&state_vector[i], &state_vector[j]);
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
int XORencrypt(char* plaintext, char* ciphertext, int* keystream) {
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
int getPlaintext(char* plaintext) {
	int len_plaintext;
	char* explanation = "Enter the data to be encrypted! Note: currently only\
						1024 characters are supported, all remaining characters\
						will be ignored!";

	printf("\n%s\n", explanation);
	clearStdin();

	fgets(plaintext, INPUT_STRING_BUFFER, stdin);

	len_plaintext = strlen(plaintext);

	if (plaintext[len_plaintext - 1] == '\n') {
    	/* Replace \n with \0 (replace the EOL with end of string)*/
        plaintext[len_plaintext - 1] = '\0';
    } else {
        plaintext[INPUT_STRING_BUFFER] = '\0';
        /*Clear stdin if overflow */
        clearStdin();
    }
	return len_plaintext;
}
