/* utility functions used by the libCrypto
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee
 */

# include "encrypt.h" /* custom library header file for cryptography functionality */
# include <stdlib.h> /* Using fopen, fprintf and fclose from stdlib.h */ 
# include <stdio.h> /* getchar,  EOF*/

/*******************************************************************************
 * Utility function that clears stdin until newline or EOF
*******************************************************************************/
void clearStdin() {
    int c;
    while (!((c = getchar() == '\n') || c == EOF));
}

/*******************************************************************************
 * Utility function that initialises int arrays to all 1
*******************************************************************************/
void StateVectorConstructor(int* initArray, int len) {
	int i;
	for (i = 0; i < len; ++i)
		initArray[i] = 1;
}

/*******************************************************************************
 * Utility function that swaps input_arr1 with input_arr2
*******************************************************************************/
void swap(unsigned char* firstElem, unsigned char* secondElem) {
	unsigned char* temp_P = firstElem;
	firstElem = secondElem;
	secondElem = temp_P;
}

/*******************************************************************************
 * Utility function that writes cipherText back into a file called
 * encrypt.locked. 
*******************************************************************************/

int writecipher(char* cipherText) {
	FILE* fp;
	fp = fopen(FILENAME, "wb");
	fprintf(fp, "%s", cipherText);
	fclose(fp);
	return 0;
}

/*******************************************************************************
 * Utility function that reads cipherText from a file called encrypt.locked. 
*******************************************************************************/
int readcipher(char* cipherText) {
	FILE* fp;
	fp = fopen(FILENAME, "r");
	if (fp == NULL) /* If file doesn't exist*/
    {
        printf("Read error, make sure there is a encrypt.locked \n");
        return 0;
    }
	   	fscanf(fp, "%s", cipherText);
	    fclose(fp);
	    return 0;
}
