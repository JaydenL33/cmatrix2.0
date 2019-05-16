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
 * Implement gen_key to retrieve a user-defined key. Then generate a pseudo rand
 * byte stream from this key with gen_pseudo_rand_key. Finally use xor_encrypt 
 * to output cipherText byte array.
 * Inputs: 
 *	- none
 * Outputs:
 *	- cipherText
*******************************************************************************/
int encrypt(void) {
	int i; /* Crypt test print back */

	/* string data */
	char plainText[INPUT_STRING_BUFFER];
	unsigned char cipherText[INPUT_STRING_BUFFER];
	int lengthplainText;
	/* Define byte arrays */
	unsigned char byteStateVector[KEY_LEN];
	/* Byte converted key */

	char keyVal[KEY_LEN];
	int keyLength;

	/* Fuction Processing  */
	lengthplainText = getPlainText(plainText); 					            printf("%d\n", lengthplainText);
	keyLength = getKey(keyVal);
	byteStreamInitialiser(keyVal, byteStateVector, keyLength);
	genPseudoRandKey(byteStateVector, plainText, cipherText);				printf("%d\n", keyLength);

  /* test cipher output */
	printf("cipherText:\n");
	for (i = 0; i < 10; i++){
		printf("%c", cipherText[i]);
	}

	return 1;
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
	
	printf("[echo]");
	system("echo off");  /* Do not print the key in plainText back to the shell! */
	printf("%s\nEnter the key:\n", GETKEY_EXPLANATION);
	clearStdin();
  
	fgets(userInputKey, KEY_LEN, stdin);
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
        userInputKey[KEY_LEN] = '\0';
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
void byteStreamInitialiser(char* userInputKey, unsigned char* byteStateVector, 
	int userKeyLength) {
	int i, j;
  
	/* KSA */
	/* loops input key, generates a byte stream vector (byte-key) of 256 */
	for (i = 0; i < KEY_LEN; i++) {
		byteStateVector[i] = i;
	}

	for (i = 0; i < KEY_LEN; i++) {
		j = (j + byteStateVector[i] + userInputKey[i % userKeyLength]) % KEY_LEN;
		swap(&byteStateVector[i], &byteStateVector[j]);

	}
	return;
}

/*******************************************************************************
 * Utilise byte state vector array to generate a pseudo random key-stream.
 * Inputs: 
 *	- mem address for state_vector
 * Outputs:
 *	- mem address return_key byte stream.
*******************************************************************************/
int genPseudoRandKey(unsigned char* byteStateVector,  
    char* plainText, unsigned char* cipherText)  {

    int i = 0;  /* i ~ byteStateVector 1st index "randomiser" */
  	int j = 0;  /* j ~ byteStateVector 2nd index "randomiser" */
  	int t;      /* t ~ loop counter creating temp index */
  
   /* 
    * length of the plainText input, as plainText already here, 
    * quicker to recalc' one int val.
    */
	int len = strlen(plainText);

    /* PRGA algorithm */
	for (t=0; t < len; t++) {
		i = (i+1) % KEY_LEN;
		j = (j + byteStateVector[i]) % KEY_LEN;

		swap(&byteStateVector[i], &byteStateVector[j]);
		int xorElem = byteStateVector[byteStateVector[i] + byteStateVector[j] % KEY_LEN];

		cipherText[t] = xorElem^plainText[t];
	}

	return 0;
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

	printf("\n%s\n", plainText_EXPLANATION);
	clearStdin();

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