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
 * to output ciphertext byte array.
 * Inputs: 
 *	- none
 * Outputs:
 *	- ciphertext
*******************************************************************************/
int encrypt(void) {
	int i; /* Crypt test print back */

	/* string data */
	char plainText[INPUT_STRING_BUFFER];
	char cipherText[INPUT_STRING_BUFFER];
	int lengthPlainText;
	/* Define byte arrays */
	unsigned char byteStateVector[KEY_LEN];
	int pseudoRandKey[KEY_LEN];
	/* Byte converted key */

	int keyVal[KEY_LEN];
	int keyLength;

	/* Fuction Processing  */
	lengthPlainText = getPlaintext(plainText); 					                printf("%d\n", lengthPlainText);
	keyLength = getKey(keyVal);
	byteStreamInitialiser(keyVal, byteStateVector, keyLength);
	genPseudoRandKey(byteStateVector, pseudoRandKey, cipherText);				printf("%d\n", keyLength);
  
  /* test cipher output */
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
	char userInputKey[KEY_LEN];
	char* explanation = 
	"The key value may contain any ASCII valid characters\
	(TODO: escape sequences?? - implement testing later)\
	Only the first 256 characters inputed will be used.";
	
	printf("[echo]");
	system("echo off");  /* Do not print the key in plaintext back to the shell! */
	printf("%s\nEnter the key:\n", explanation);
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
	int keyLength) {
  
	int byteTempVecotr[KEY_LEN];
	int i, j;
  
	/* KSA */
	/* loops input key, generates a byte stream vector (byte-key) of 256 */
	for (i = 0; i < KEY_LEN; i++) {
		byteStateVector[i] = i;
	}

	for (i = 0; i < KEY_LEN; i++) {
		j = (j + byteStateVector[i] + key_arr[i % keyLength]) % N;
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
    char* plaintext, unsigned char* ciphertext)  {
  
	int i = 0;  /* i ~ byteStateVector 1st index "randomiser" */
  int j = 0;  /* j ~ byteStateVector 2nd index "randomiser" */
  int t;      /* t ~ loop counter creating temp index */
  
  /* 
   * length of the plaintext input, as plaintext already here, 
   * quicker to recalc' one int val.
   */
  int len = strlen(plaintext);

  /* PRGA algorithm */
	for (t=0; t < len, t++) {
		i = (i+1) % KEY_LEN;
		j = (j + byteStateVector[i]) % KEY_LEN;

		swap(&byteStateVector[i], &byteStateVector[j]);
		int rnd = byteStateVector[byteStateVector[i] + byteStateVector[j] % KEY_LEN];

		ciphertext[t] = rnd^plaintext[n];
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