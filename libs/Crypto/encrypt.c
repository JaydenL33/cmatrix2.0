/* Encryption functionality for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson
 * Jayden Lee
 */

# include <stdio.h>   	/* fgets, printf 	*/
# include <stdlib.h>  	/* system 			*/
# include <string.h>  	/* strlen 			*/

# include "encrypt.h" 		/* cryptography functionality 	*/
# include "../Util/util.h"	/* utility functions 			*/

/*******************************************************************************
 * Implement library to encrypt data
 * this function expects an external decleration of encrypted data to write to!
 * returns int length of the encrypted data, which equals the length of 
 * the original, unencrypted (plaintext), data.
*******************************************************************************/
int encrypt(unsigned char* encryptedData) {

	printf("\nENCRYPTING....\n");
	/* intermediate used by RC4 encryption */
	unsigned char byte_state_vector_ptr[BYTE_STATE_LEN]; 
    /* user input (either from file or console) */
	char plain_text[INPUT_STRING_BUFFER]; 
	char keyVal[BYTE_STATE_LEN];
	/* Fuction Processing  */
	int plainTextLength = getPlainText(plain_text);
	int keyLength = keyLength = getKey(keyVal);	
	
	byteStreamInitialiser(keyVal, byte_state_vector_ptr, keyLength);

	genPseudoRandKey(byte_state_vector_ptr, plain_text, encryptedData, 0, 
					 plainTextLength, keyLength);

	writecipher(encryptedData, plainTextLength);

	return plainTextLength;
}

/*******************************************************************************
 * Implement the library to decrypt data
 * this function expects an external decleration of encrypted and decrypted data
 * to write to! 
 * This also requires the length of encrypted data as well as the key to decrypt
 * it (obviously).
*******************************************************************************/
int decrypt(unsigned char* encryptedData, char* decryptedData,
	int lenEncrytpedData, char* user_input_key) {

	readcipher(encryptedData, lenEncrytpedData);
  
	printf("\nDECRYPTING....\n");
	/* intermediate used by RC4 encryption */
	unsigned char byte_state_vector_ptr[BYTE_STATE_LEN]; 
	int keyLength = getKey(user_input_key);
	byteStreamInitialiser(user_input_key, byte_state_vector_ptr, keyLength);

	genPseudoRandKey(byte_state_vector_ptr, decryptedData, encryptedData, 1, 
					 lenEncrytpedData, keyLength);
	return 0;
}

/*******************************************************************************
 * Get key from user (stdin)
*******************************************************************************/
int getKey(char* user_input_key) {
  
	int length;
    /* Do not print the key in plain_text back to the shell!*/
	system("echo off"); 
	printf("%s\nEnter the key:\n", GETKEY_EXPLANATION);
  
  	/* note user input-key cannot exceed 256 bytes! */
	fgets(user_input_key, BYTE_STATE_LEN, stdin);
	length = strlen(user_input_key);

	if (user_input_key[length - 1] == '\n') {
    	/* 
    	 * Replace last character, \n, with \0 (replace the EOL with end of
    	 * end-of-string EOS character )
    	 */
        user_input_key[length - 1] = '\0';
    } else {
    	/* 
         * Set the last possible buffer index to EOS character then,
         * clear stdin of any excess characters, avoiding the possible 
         * buffer overflow
         */
        user_input_key[BYTE_STATE_LEN] = '\0';
        clearStdin();
    }
   	/*
   	 * re enable echo then convert input ASCII key to 
   	 * "byte" key before returning length of user input key
   	 */
    system("echo on");
	return length;
}

/*******************************************************************************
 * gets the plaintext entered by the user into the program's stdin source
 * returns the length of the plain_text
*******************************************************************************/
int getPlainText(char* plain_text) {
	int lengthplainText;

	printf("\n%s\n", PLAINTEXT_EXPLANATION);
	fgets(plain_text, INPUT_STRING_BUFFER, stdin);

	lengthplainText = strlen(plain_text);

	if (plain_text[lengthplainText - 1] == '\n') {
    	/* 
    	 * Replace last character, \n, with \0 (replace the EOL with end of
    	 * end-of-string EOS character )
    	 */
        plain_text[lengthplainText - 1] = '\0';
    } else {
        /* 
         * Set the last possible buffer index to EOS character then,
         * clear stdin of any excess characters, avoiding the possible 
         * buffer overflow
         */
    	plain_text[INPUT_STRING_BUFFER] = '\0';
        clearStdin();
    }
	return lengthplainText;
}

/*******************************************************************************
 * char user_input_key, user inputed key used in the initialisation
 * unsigned char byte_state_vector_ptr, the byte state vector TOBE randomised by 
 * genPseudoRandKey
 * int user_key_length, length of the user inputed key
 * 
 * state vector initiliser - initialises a BYTE_STATE_LEN byte key using the 
 * KSA algorithm (step 1 of RC4)
*******************************************************************************/
void byteStreamInitialiser(char* user_input_key, 
unsigned char* byte_state_vector_ptr, int user_key_length) {
	int i, j = 0;
  
	/* KSA */
	/* loops input key, generates a byte stream vector (byte-key) of 256 */
	for (i = 0; i < BYTE_STATE_LEN; i++) {
		byte_state_vector_ptr[i] = i;
	}

	for (i = 0; i < BYTE_STATE_LEN; i++) {
		j = (j + byte_state_vector_ptr[i] + user_input_key[i % user_key_length]) 
        % BYTE_STATE_LEN;
		swap(byte_state_vector_ptr, i, j);		
	}
	printf("\n");
	return;
}

/*******************************************************************************
 * unsigned char byte state vector
 * char plaintext, data to be encrypted
 * unsigned char ciphertext, data encrypted
 * int reverse, decrypt (0/false) vs encrypt (1/true)
 * int data_len, length of data encrypted/decrypted
 * int key_len, length of user inputed key
 *
 * Generates a "pseudo random" BYTE_STATE_LEN byte key using the PRGA algorithm 
 * (step 2 of RC4)
*******************************************************************************/
int genPseudoRandKey(unsigned char* byte_state_vector_ptr, char* plain_text, 
	unsigned char* cipher_text, int reverse, int data_len, int key_len)  {

    int i = 0;  /* i ~ byte_state_vector_ptr 1st index "randomiser" 	*/
  	int j = 0;  /* j ~ byte_state_vector_ptr 2nd index "randomiser" 	*/
  	int t;      /* t ~ loop counter creating temp index 		*/

    /* PRGA algorithm */
	for (t = 0; t < data_len; t++) {
		i = (i+1) % key_len;
		j = (j + byte_state_vector_ptr[i]) % key_len;
		swap(byte_state_vector_ptr, i, j);
		int byte_state_addition = byte_state_vector_ptr[i] +
         byte_state_vector_ptr[j] % key_len;
		unsigned char xor_elem = byte_state_vector_ptr[byte_state_addition];
		
		
		if(reverse) {
			plain_text[t]  = xor_elem ^ cipher_text[t];
		} else {
			cipher_text[t] = xor_elem ^ plain_text[t];
		}
	}

	return 0;
}
