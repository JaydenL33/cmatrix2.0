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

# define MAX_KEY_LEN 256
# define INPUT_STRING_BUFFER 1024
# define OUTPUT_CMD_BUFFER 128
/*******************************************************************************
 * Implement library to encrypt data
 * Inputs: 
 *	- none
 * Outputs:
 *	- ciphertext
*******************************************************************************/
int encrypt(void);

/*******************************************************************************
 * Implement library to decrypt data
 * Inputs: 
 *	- ciphertext
 *	- byte key stream
 * Outputs:
 *	- plaintext
*******************************************************************************/
int decrypt(char* plaintext, char* ciphertext, char* keystream);

/*******************************************************************************
 * XOR BYTE plaintext to BYTE Ciphertext
 * Inputs: 
 *	- mem address for plaintext
 * 	- mem address for keystream
 * Outputs:
 *	- mem address for ciphertext
*******************************************************************************/
int XORencrypt(char* plaintext, char* ciphertext, int* byteStreamKey);

/*******************************************************************************
 * Key request from user, byte stream generation and pseudo 
 * randomisation functions.
*******************************************************************************/

int getKey(char* userInputKey);

/* TAKES SEED */
int genPseudoRandKey(int* byteStateVector, int* byteStreamKey);

/* state vector initiliser - 256 list based on key */
void byteStreamInitialiser(int* userInputKey,  int* byteStateVector, int* keyLength);

/* plaintext getter */
int getPlaintext(char* plaintext);

/*******************************************************************************
 * Utility functionality required by library/
*******************************************************************************/
void clearStdin();
void StateVectorConstructor(int* initArray, int len);
void swap(int* firstElem, int* secondElem);

/*******************************************************************************
 * Utility functionality required by library/
*******************************************************************************/

/* Check overal encryption/decryption and XOR operation */
void CheckEncryptDecrypt(void);
void CheckXORencrypt(char* plaintext, char* ciphertext, int* byteStreamKey);

/* check user inputs, assert no overflows or segmentation faults */
void CheckUserKeyInput(void);
void CheckUserPlaintext(char* plaintext);

/* check key stream generation process */
void CheckPseudoKeyStream(int* byteStateVector, int* byteStreamKey);
void CheckByteStreamInit(int* userInputKey,  int* byteStateVector, int* keyLength);

# endif