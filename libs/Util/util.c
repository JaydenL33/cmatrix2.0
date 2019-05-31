/* utility functions used by all libs
 * Fund-O-C Assesment 3
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee, Sebastian Southern
 */

# include <stdlib.h>  /* fopen, fprintf and fclose  */ 
# include <stdio.h>   /* getchar, EOF 		    	*/
# include <string.h>  /* strlen 					*/
/* custom library header file for cryptography functionality */
# include "util.h" 	  

/*******************************************************************************
 * Utility function that clears stdin until newline or EOF
*******************************************************************************/
void clearStdin() {
    int c;
    while (!((c = getchar() == '\n') || c == EOF));
}

/*******************************************************************************
 * Utility function that swaps array[i] with array[j]
*******************************************************************************/
void swap(unsigned char* array, int i, int j) {
	unsigned char temp_p = array[i];
	array[i] = array[j];
	array[j] = temp_p;
}

/*******************************************************************************
* Utility function that writes cipher_text_ptr back into a file called encrypt.locked
*******************************************************************************/
int writecipher(unsigned char* cipher_text_ptr, int plain_text_len ) {
	FILE* fp;
	fp = fopen(FILENAME, "w");
	int i;
	for (i = 0; i < plain_text_len; i++) 
	{
		fprintf(fp, "%c", cipher_text_ptr[i]);
	}
	fclose(fp);
	return 0;
}

/*******************************************************************************
 * Utility function that reads cipher_text_ptr from a file called encrypt.locked
*******************************************************************************/
int readcipher(unsigned char* cipher_text_ptr, int plain_text_len) {
	FILE* fp;
	int i;
	fp = fopen(FILENAME, "r");
	if (fp == NULL) { /* If file doesn't exist */
        printf("Read error, make sure there is an encrypt.locked\n");
        return 0;
    }
   		for (i = 0; i < plain_text_len; i++)
	   	fscanf(fp, "%c", &cipher_text_ptr[i]);
	   	fclose(fp);
	    return 1;
}

/*******************************************************************************
 * Utility function that takes an input array, the length of that array and 
   a output array. Any unsigned char that doesn't represent ascii code that is 
   displayable by the terminal or a space or DEL is thrown out. Everything else 
   is appended to the output array. 
*******************************************************************************/
int checkValidRange (unsigned char *un_checked_array_ptr, 
int plain_text_len, char* checked_array_ptr) {
	int dec_ASCII;
	int i;
	int j = 0;
	
	for (i = 0; i < plain_text_len; i++)
	{
		dec_ASCII = (int) un_checked_array_ptr[i]; 
		if (dec_ASCII >= 33 && dec_ASCII <= 126)
		{
			checked_array_ptr[j] = (char) un_checked_array_ptr[i] ;
			j++;
		}
	}
	checked_array_ptr[j] = '\0';
	return 1;
}

