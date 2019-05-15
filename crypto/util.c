/* utility functions used by the libCrypto
 * Fund-O-C Assesment 3
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Albert Ferguson Jayden Lee
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

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
void StateVectorConstructor(int* init_arr, int len) {
	int i;
	for (i = 0; i < len; ++i)
		init_arr[i] = 1;
}

/*******************************************************************************
 * Utility function that swaps input_arr1 with input_arr2
*******************************************************************************/
void swap(int* input_arr1, int* input_arr2) {
	int* tmp_p;
	tmp_p = input_arr1;
	input_arr1 = input_arr2;
	input_arr2 = tmp_p; 
}
