/* Encryption functionality for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson
 * Jayden Lee
 */

# include <stdio.h>   /* fgets, printf 	*/
# include <stdlib.h>  /* system 		*/
# include <string.h>  /* strlen 		*/
# include "encrypt.h" /* custom library header file for cryptography functionality */

/*******************************************************************************
 * Implement library to encrypt data
 * this function expects an external decleration of encrypted data to write to!
 * returns int length of the encrypted data, which equals the length of 
 * the original, unencrypted (plaintext), data.
*******************************************************************************/
int encrypt(unsigned char* encryptedData) {

	printf("\nENCRYPTING....\n");
	
	unsigned char byteStateVector[BYTE_STATE_LEN]; /* intermediate used by RC4 encryption */

	char plainText[INPUT_STRING_BUFFER]; /* user input (either from file or console) */
	char keyVal[BYTE_STATE_LEN];
	/* Fuction Processing  */
	int plainTextLength = getPlainText(plainText);
	int keyLength = keyLength = getKey(keyVal);	
	
	byteStreamInitialiser(keyVal, byteStateVector, keyLength);

	genPseudoRandKey(byteStateVector, plainText, encryptedData, 0, 
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
	int lenEncrytpedData, char* userInputKey) {

	readcipher(encryptedData, lenEncrytpedData);
  
	printf("\nDECRYPTING....\n");
	/* intermediate used by RC4 encryption */
	unsigned char byteStateVector[BYTE_STATE_LEN]; 
	int keyLength = getKey(userInputKey);
	byteStreamInitialiser(userInputKey, byteStateVector, keyLength);

	genPseudoRandKey(byteStateVector, decryptedData, encryptedData, 1, 
					 lenEncrytpedData, keyLength);
	return 0;
}

/*******************************************************************************
 * Get key from user (stdin)
*******************************************************************************/
int getKey(char* userInputKey) {
  
	int length;
	system("echo off"); /* Do not print the key in plainText back to the shell! */
	printf("%s\nEnter the key:\n", GETKEY_EXPLANATION);
  
  	/* note user input-key cannot exceed 256 bytes! */
	fgets(userInputKey, BYTE_STATE_LEN, stdin);
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
        userInputKey[BYTE_STATE_LEN] = '\0';
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
 * returns the length of the plainText
*******************************************************************************/
int getPlainText(char* plainText) {
	int lengthplainText;

	printf("\n%s\n", PLAINTEXT_EXPLANATION);
	fgets(plainText, INPUT_STRING_BUFFER, stdin);

	lengthplainText = strlen(plainText);

	if (plainText[lengthplainText - 1] == '\n') {
    	/* 
    	 * Replace last character, \n, with \0 (replace the EOL with end of
    	 * end-of-string EOS character )
    	 */
        plainText[lengthplainText - 1] = '\0';
    } else {
        /* 
         * Set the last possible buffer index to EOS character then,
         * clear stdin of any excess characters, avoiding the possible 
         * buffer overflow
         */
    	plainText[INPUT_STRING_BUFFER] = '\0';
        clearStdin();
    }
	return lengthplainText;
}

/*******************************************************************************
 * char userInputKey, user inputed key used in the initialisation
 * unsigned char byteStateVector, the byte state vector TOBE randomised by 
 * genPseudoRandKey
 * int userKeyLength, length of the user inputed key
 * 
 * state vector initiliser - initialises a BYTE_STATE_LEN byte key using the 
 * KSA algorithm (step 1 of RC4)
*******************************************************************************/
void byteStreamInitialiser(char* userInputKey, unsigned char* byteStateVector, 
	int userKeyLength) {
	int i, j = 0;
  
	/* KSA */
	/* loops input key, generates a byte stream vector (byte-key) of 256 */
	for (i = 0; i < BYTE_STATE_LEN; i++) {
		byteStateVector[i] = i;
	}

	for (i = 0; i < BYTE_STATE_LEN; i++) {
		j = (j + byteStateVector[i] + userInputKey[i % userKeyLength]) % BYTE_STATE_LEN;
		swap(byteStateVector, i, j);		
	}
	printf("\n");
	return;
}

/*******************************************************************************
 * unsigned char byte state vector
 * char plaintext, data to be encrypted
 * unsigned char ciphertext, data encrypted
 * int reverse, decrypt (0/false) vs encrypt (1/true)
 * int dataLen, length of data encrypted/decrypted
 * int keyLen, length of user inputed key
 *
 * Generates a "pseudo random" BYTE_STATE_LEN byte key using the PRGA algorithm 
 * (step 2 of RC4)
*******************************************************************************/
int genPseudoRandKey(unsigned char* byteStateVector, char* plainText, 
	unsigned char* cipherText, int reverse, int dataLen, int keyLen)  {

    int i = 0;  /* i ~ byteStateVector 1st index "randomiser" 	*/
  	int j = 0;  /* j ~ byteStateVector 2nd index "randomiser" 	*/
  	int t;      /* t ~ loop counter creating temp index 		*/

    /* PRGA algorithm */
	for (t = 0; t < dataLen; t++) {
		i = (i+1) % keyLen;
		j = (j + byteStateVector[i]) % keyLen;
		swap(byteStateVector, i, j);
		int byteStateAddition = byteStateVector[i] + byteStateVector[j] % keyLen;
		unsigned char xorElem = byteStateVector[byteStateAddition];
		
		
		if(reverse) {
			plainText[t]  = xorElem ^ cipherText[t];
		} else {
			cipherText[t] = xorElem ^ plainText[t];
		}
	}

	return 0;
}
