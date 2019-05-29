/* Encryption header file for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson, Jayden Lee
 */

# ifndef _MYLIB_H_
# define _MYLIB_H_

# define BYTE_STATE_LEN 256
# define INPUT_STRING_BUFFER 1025

# define PLAINTEXT_EXPLANATION "Enter the data to be encrypted!\nNote: currently only\
 1024 characters are supported, all remaining characters\
 will be ignored!"
# define GETKEY_EXPLANATION "The key value may contain any ASCII valid characters\
 \nOnly the first 256 characters inputed will be used."

/*******************************************************************************
 * Implement library to encrypt data
 * this function expects an external decleration of encrypted data to write to!
 * returns int length of the encrypted data, which equals the length of 
 * the original, unencrypted (plaintext), data.
*******************************************************************************/
int encrypt(unsigned char* encryptedData);

/*******************************************************************************
 * Implement the library to decrypt data
 * this function expects an external decleration of encrypted and decrypted data
 * to write to! 
 * This also requires the length of encrypted data as well as the key to decrypt
 * it (obviously).
*******************************************************************************/
int decrypt(unsigned char* encryptedData, char* decryptedData, int lenEncrytpedData,
	char* userInputKey);

/*******************************************************************************
 * Get key from user (stdin)
*******************************************************************************/
int getKey(char* userInputKey);

/*******************************************************************************
 * gets the plaintext entered by the user into the program's stdin source
 * returns the length of the plainText
*******************************************************************************/
int getPlainText(char* plainText);

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
	 int userKeyLength);

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
	unsigned char* cipherText, int reverse, int dataLen, int keyLen);

# endif
