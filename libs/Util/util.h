/* utility header file, used by all libs
 * Fund-O-C Assesment 3
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee, Sebastian Southern
 */

# ifndef _UTIL_H_
# define _UTIL_H_
/* temp file output for writing encrypt data tp */
# define FILENAME "encrypt.locked" 
/* call this an easter egg....idek */
# define UNKNOWN "An unknown error has occured,\
 please try again or contact your system administator\n"

/*******************************************************************************
 * Utility functions required by all libraries
*******************************************************************************/
void clearStdin();

void swap(unsigned char* array_ptr, int i, int j);

int writecipher(unsigned char* cipher_text_ptr, int plain_text_len);

int readcipher(unsigned char* cipher_text_ptr, int plain_text_len);

int checkValidRange (unsigned char *un_checked_array_ptr,
int plain_text_len, char* checked_array_ptr);

# endif
