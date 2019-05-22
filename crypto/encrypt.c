/* Encryption functionality for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson
 * Jayden Lee
 */

# include <stdio.h> /* fgets, printf, */
# include <stdlib.h> /* system */
# include <string.h> /* strlen */
# include <math.h>
# include "encrypt.h" /* custom library header file for cryptography functionality */

/*******************************************************************************
 * Implement getKey to retrieve a user-defined key. Then use  byteStreamInitialiser
 * to generate the byteStateVector. Finally pseudo-randomise the key and XOR it
 * by implementing genPseudoRandKey.  
 * Inputs: 
 *	- none
 * Outputs:
 *	- mem address cipherText
 * 	- int length of plaintext/ciphertext
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

	return plainTextLength;
}

int decrypt(unsigned char* encryptedData, char* decryptedData,
	int lenEncrytpedData, char* userInputKey) {

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
 * Get key from user, account for buffer overflow. Avoids printing key in 
 * plainText.
 * Inputs: 
 *	- mem address for key_arr ("byte" ~ int value of ASCII)
 * Outputs:
 *	- int length of key
 *	- BYTE struct converted key to mem address provided
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
 * plainText getter. Prompts user for plainText entry to be encrypted. 
 * WARNING: Max plainText entered currently allows 1024 char's!! All remaining 
 * ignored!
 *	- mem address for plainText
 * Outputs:
 *	- int length of plainText entered.
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
 * Utilise key to create a state vector.
 * Inputs: 
 *	- mem address for key_arr
 *	- int length of key
 * Outputs:
 *	- mem address of state vector to store to
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
 * Utilise byte state vector array to generate a pseudo random key-stream.
 * Inputs: 
 *	- mem address for state_vector
 * Outputs:
 *	- mem address return_key byte stream.
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
