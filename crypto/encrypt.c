/* Encryption functionality for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson, Jayden Lee
 */

# include <stdio.h> /* fgets, printf, */
# include <stdlib.h> /* system */
# include <string.h> /* strlen */
# include <math.h>
# include "encrypt.h" /* custom library header file for cryptography functionality */

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
	int i;

	/* string data */
	char plaintext[INPUT_STRING_BUFFER];
	char ciphertext[INPUT_STRING_BUFFER];
	int length_plaintext_data;
	/* Define byte arrays */
	int byte_key_stream[MAX_KEY_LEN];
	int byte_state_vector[MAX_KEY_LEN];
	int pseudo_rand_key[MAX_KEY_LEN];
	/* Byte converted key */
	char key_val[MAX_KEY_LEN];
	int keyLength;

	keyLength = getKey(key_val);
	byteStreamInitialiser((int*) key_val, byte_state_vector, &keyLength);
	genPseudoRandKey(byte_state_vector, pseudo_rand_key);				printf("KeyLength:%d\n", keyLength);
	length_plaintext_data = getPlaintext(plaintext); 					printf("Plaintext Length:%d\n", length_plaintext_data);

	XORencrypt(plaintext, ciphertext, byte_key_stream);
	printf("Ciphertext:\n");
	for (i = 0; i < 10; i++){
		printf("%d", ciphertext[i]);
	}
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
int getKey(char* userInputKey) {

	int length;
	char* explanation = "The key value may contain any ASCII valid characters.\
(TODO: escape sequences?? - implement testing later)\
Only the first 256 characters inputed will be used.";
	
	printf("[echo]");
	system("echo off");  /* Do not print the key in plaintext back to the shell! */
	printf("%s\nEnter the key:\n", explanation);
	clearStdin();
	fgets(userInputKey, 5, stdin);

	length = strlen(userInputKey);

	if (userInputKey[length - 1] == '\n') {
    	/* 
    	 * Replace last character, \n, with \0 (replace the EOL with end of
    	 * end-of-string EOS character )
    	 */
        userInputKey[length - 1] = '\0';
    } else {
    	/* 
         * Set the last possible buffer index to EOS character then,
         * clear stdin of any excess characters, avoiding the possible 
         * buffer overflow
         */
        userInputKey[MAX_KEY_LEN] = '\0';
        clearStdin();
    }
   	/*
   	 * re enable echo then convert input ASCII key to 
   	 * "byte" key before returning length of user input key
   	 */
    printf("[echo]");
    system("echo on"); 
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
void byteStreamInitialiser(int* userInputKey,  int* byteStateVector, int* keyLength) {
	int byteTempVecotr[MAX_KEY_LEN];
	int i, j;
	/* KSA */
	/* loops input key, generates a byte stream vector (byte-key) of 256 */
	for (i = 0; i < MAX_KEY_LEN; i++) {
		byteStateVector[i] = i;
		byteTempVecotr[i] = userInputKey[i % MAX_KEY_LEN - *keyLength];
	}

	for (i = 0; i < MAX_KEY_LEN; i++) {
		j = (j + byteStateVector[i] + byteTempVecotr[i] % MAX_KEY_LEN);
		swap(&byteStateVector[i], &byteStateVector[j]);

	}
}

/*******************************************************************************
 * Utilise byte state vector array to generate a pseudo random key-stream.
 * Inputs: 
 *	- mem address for state_vector
 * Outputs:
 *	- mem address return_key byte stream.
*******************************************************************************/
int genPseudoRandKey(int* byteStateVector, int* byteStreamKey) {
	int i, j, t;
	/* PRGA */
	while(i != MAX_KEY_LEN) {
		i = (i+1) % MAX_KEY_LEN;
		j = (j + byteStateVector[i]) % MAX_KEY_LEN;
		swap(&byteStateVector[i], &byteStateVector[j]);
		t = (byteStateVector[i] + byteStateVector[j]) % 256;
		byteStreamKey[i] = byteStateVector[t];
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
int XORencrypt(char* plaintext, char* ciphertext, int* byteStreamKey) {
	int i;

	for (i = 0; i < strlen(plaintext); i++) {
		/* note: ^ is the XOR operator. Do not confuse with power operation */
		ciphertext[i] = byteStreamKey[i]^plaintext[i];
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
	int lengthPlainText;
	char* explanation = "Enter the data to be encrypted! Note: currently only\
1024 characters are supported, all remaining characters\
will be ignored!";

	printf("\n%s\n", explanation);
	clearStdin();

	fgets(plaintext, INPUT_STRING_BUFFER, stdin);

	lengthPlainText = strlen(plaintext);

	if (plaintext[lengthPlainText - 1] == '\n') {
    	/* 
    	 * Replace last character, \n, with \0 (replace the EOL with end of
    	 * end-of-string EOS character )
    	 */
        plaintext[lengthPlainText - 1] = '\0';
    } else {
        /* 
         * Set the last possible buffer index to EOS character then,
         * clear stdin of any excess characters, avoiding the possible 
         * buffer overflow
         */
    	plaintext[INPUT_STRING_BUFFER] = '\0';
        clearStdin();
    }
	return lengthPlainText;
}
