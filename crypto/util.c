/* utility functions used by the libCrypto
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee
 */

# include "encrypt.h" 
/* custom library header file for cryptography functionality */
# include <stdlib.h> 
/* Using fopen, fprintf and fclose from stdlib.h */ 


/* FOR DEBUGGING: Return of 1 is working. Return of 0 is not working. */

/*******************************************************************************
 * Utility function that clears stdin until newline or EOF
*******************************************************************************/
void clear_stdin() {
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
void swap(unsigned char *firstElem, unsigned char *secondElem) {
	int* temp_P = firstElem;
	firstElem = secondElem;
	secondElem = temp_P;
}

/*******************************************************************************
 * Utility function that writes ciphertext back into a file called
 * encrypt.locked. 
*******************************************************************************/

int writecipher(char* ciphertext)
{
	FILE* fp;
	fp = fopen(FILENAME, "wb");
	fprintf(fp, &ciphertext);
	fclose(fp);
	return 1;
}
/*******************************************************************************
 * Utility function that reads ciphertext from a file called encrypt.locked. 
*******************************************************************************/
int readcipher(char* ciphertext)
{
	FILE* fp;
	fp = fopen(FILENAME, "r");
	if (fp == NULL) /* If file doesn't exist*/
    {
        printf("Read error, make sure there is a encrypt.locked \n");
        return 0;
    }
	   	fscanf(fp, "%c", ciphertext);
	    fclose(fp);
	    return 1;
}

