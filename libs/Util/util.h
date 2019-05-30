/* utility header file, used by all libs
 * Fund-O-C Assesment 3
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee, Sebastian Southern
 */

# ifndef _UTIL_H_
# define _UTIL_H_

# define FILENAME "encrypt.locked" /* temp file output for writing encrypt data tp */

/*******************************************************************************
 * Utility functions required by all libraries
*******************************************************************************/
void clearStdin();

void swap(unsigned char* array, int i, int j);

int writecipher(unsigned char* cipherText, int plaintextlen);

int readcipher(unsigned char* cipherText, int plaintextlen);

int checkValidRange (unsigned char *unCheckedArray, int plaintextlen, char* checkedArray);

# endif
