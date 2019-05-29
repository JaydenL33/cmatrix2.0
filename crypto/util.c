/* utility functions used by the libCrypto
 * Fund-O-C Assesment 3
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee
 */

# include "encrypt.h" /* custom library header file for cryptography functionality */
# include <stdlib.h>  /* fopen, fprintf and fclose  */ 
# include <stdio.h>   /* getchar,  EOF 		    	*/

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
	unsigned char temp_P = array[i];
	array[i] = array[j];
	array[j] = temp_P;
}

/*******************************************************************************
 * Utility function that writes cipherText back into a file called encrypt.locked
*******************************************************************************/
int writecipher(unsigned char* cipherText, int plaintextlen ) {
	FILE* fp;
	fp = fopen(FILENAME, "w");
	int i;
	for (i = 0; i < plaintextlen; i++) {
		fprintf(fp, "%c", cipherText[i]);
	}
	fclose(fp);
	return 0;
}

/*******************************************************************************
 * Utility function that reads cipherText from a file called encrypt.locked
*******************************************************************************/
int readcipher(unsigned char* cipherText, int plaintextlen) {
	FILE* fp;
	int i;
	fp = fopen(FILENAME, "r");
	if (fp == NULL) { /* If file doesn't exist */
        printf("Read error, make sure there is an encrypt.locked\n");
        return 0;
    }
   		for (i = 0; i < plaintextlen; i++)
	   		fscanf(fp, "%c", &cipherText[i]);
	   	fclose(fp);
	    return 1;
}

/*******************************************************************************
 * Utility function that takes an input array, the length of that array and 
   a output array. Any unsigned char that doesn't represent ascii code that is 
   displayable by the terminal or a space or DEL is thrown out. Everything else 
   is appended to the output array. 
*******************************************************************************/
int checkValidRange (unsigned char *unCheckedArray, int plaintextlen, unsigned char* checkedArray) {
	int decASCII;
	int i;
	int j = 0;
	
	for (i = 0; i < plaintextlen; i++)
	{
		decASCII = (int) unCheckedArray[i]; 
		if (decASCII >= 33 && decASCII <= 126)
		{
			checkedArray[j] = unCheckedArray[i];
			j++;
		}
	}
	checkedArray[j] = '\0';
	/* Why return 0? */
	return 0;
}
