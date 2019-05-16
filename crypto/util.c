/* utility functions used by the libCrypto
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee
 */

# include "encrypt.h" /* custom library header file for cryptography functionality */

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
void swap(int* firstElem, int* secondElem) {
	int* temp_P = firstElem;
	firstElem = secondElem;
	secondElem = temp_P; 
}
