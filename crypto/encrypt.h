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
int XORencrypt(char* plaintext, char* ciphertext, int* keystream);

/*******************************************************************************
 * Key request from user, byte stream generation and pseudo 
 * randomisation functions.
*******************************************************************************/

int getKey(int* key_arr);

int genPseudoRandKey(int* state_vector, int* return_key);

/* state vector initiliser - 256 list based on key */
void byteStreamInitialiser(int* key_arr,  int* state_vector, int* keyLength);

/* plaintext getter */
int getPlaintext(char* plaintext);

/*******************************************************************************
 * Utility functionality required by library/
*******************************************************************************/
void clearStdin();
void StateVectorConstructor(int* init_arr, int len);
void swap(int* input_arr1, int* input_arr2);

# endif