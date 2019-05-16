# ifndef _MYLIB_H_
# define _MYLIB_H_

/* Encryption header file for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson, Jayden Lee
 */

# define KEY_LEN 256
# define INPUT_STRING_BUFFER 1024
# define OUTPUT_CMD_BUFFER 128
# define FILENAME "encrypt.locked" /* temp file output for writing encrypt data tp */

# define plainText_EXPLANATION "Enter the data to be encrypted! Note: currently only\
1024 characters are supported, all remaining characters\
will be ignored!"
# define GETKEY_EXPLANATION "The key value may contain any ASCII valid characters\
(TODO: escape sequences?? - implement testing later)\
Only the first 256 characters inputed will be used."
/*******************************************************************************
 * Implement library to encrypt data
 * Inputs: 
 *	- none
 * Outputs:
 *	- cipherText
*******************************************************************************/
int encrypt(void);

/*******************************************************************************
 * Implement library to decrypt data
 * Inputs: 
 *	- cipherText
 *	- byte key stream
 * Outputs:
 *	- plainText
*******************************************************************************/
int decrypt(char* plainText, char* cipherText, char* keystream);

/*******************************************************************************
 * Key request from user, byte stream generation and pseudo 
 * randomisation functions.
*******************************************************************************/
int getKey(char* userInputKey);

/* TAKES SEED */
int genPseudoRandKey(unsigned char* byteStateVector,  
    char* plainText, unsigned char* cipherText);

/* state vector initiliser - 256 list based on key */
void byteStreamInitialiser(char* userInputKey, unsigned char* byteStateVector, 
						   int userKeyLength);

/* plainText getter */
int getPlainText(char* plainText);

/*******************************************************************************
 * Utility functionality required by library/
*******************************************************************************/
void clearStdin();
void StateVectorConstructor(int* initArray, int len);
void swap(unsigned char* firstElem, unsigned char* secondElem);

int writecipher(char* cipherText);
int readcipher(char* cipherText);

/*******************************************************************************
 * Debug units required by library/
*******************************************************************************/

/* Check overal encryption/decryption and XOR operation */
void CheckEncryptDecrypt(void);
void CheckXORencrypt(char* plainText, char* cipherText, int* byteStreamKey);

/* check user inputs, assert no overflows or segmentation faults */
void CheckUserKeyInput(void);
void CheckUserplainText(char* plainText);

/* check key stream generation process */
void CheckPseudoKeyStream(int* byteStateVector, int* byteStreamKey);
void CheckByteStreamInit(int* userInputKey,  int* byteStateVector, 
				     	 int* keyLength);

# endif