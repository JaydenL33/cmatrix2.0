/* Encryption header file for libCrypto
 * also includes utility functions used by the library.
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson, Jayden Lee
 */

# ifndef _ENCRYPT_H_
# define _ENCRYPT_H_

# define BYTE_STATE_LEN 256
# define INPUT_STRING_BUFFER 1025

# define PLAINTEXT_EXPLANATION "Enter the data to be encrypted!\n\
 Note: currently only\
 1024 characters are supported, all remaining characters\
 will be ignored!"
# define GETKEY_EXPLANATION "The key value may contain\
 any ASCII valid characters\
 \nOnly the first 256 characters inputed will be used."

/*******************************************************************************
 * Implement library to encrypt data
 * this function expects an external decleration of encrypted data to write to!
 * returns int length of the encrypted data, which equals the length of 
 * the original, unencrypted (plaintext), data.
*******************************************************************************/
int encrypt(unsigned char* encrypted_data);

/*******************************************************************************
 * Implement the library to decrypt data
 * this function expects an external decleration of encrypted and decrypted data
 * to write to! 
 * This also requires the length of encrypted data as well as the key to decrypt
 * it (obviously).
*******************************************************************************/
int decrypt(unsigned char* encrypted_data, 
char* decrypted_data, int len_encrytped_data,
	char* user_input_key);

/*******************************************************************************
 * Get key from user (stdin)
*******************************************************************************/
int getKey(char* user_input_key);

/*******************************************************************************
 * gets the plaintext entered by the user into the program's stdin source
 * returns the length of the plain_text
*******************************************************************************/
int getPlainText(char* plain_text);

/*******************************************************************************
 * char user_input_key, user inputed key used in the initialisation
 * unsigned char byte_state_vector, the byte state vector TOBE randomised by 
 * genPseudoRandKey
 * int user_key_length, length of the user inputed key
 * 
 * state vector initiliser - initialises a BYTE_STATE_LEN byte key using the 
 * KSA algorithm (step 1 of RC4)
*******************************************************************************/
void byteStreamInitialiser(char* user_input_key, unsigned char* byte_state_vector, 
	 int user_key_length);

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
int genPseudoRandKey(unsigned char* byte_state_vector, char* plain_text, 
	unsigned char* cipher_text, int reverse, int data_len, int key_len);

# endif
