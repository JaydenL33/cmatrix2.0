/* Printing functionality header for libPrintRaindrops.
 * Note: utility functions moved to seperate util lib!!!
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Sebastian Southern
 */

# ifndef _MYLIB_H_
# define _MYLIB_H_

/* Various colours that can be used during printing */
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define CLEAR printf("\033[H\033[J") /* Clears the entire terminal */
# define HIDE_CURSOR printf("\e[?25l") /* Hide the cursor in the terminal */

void print_raindrops(char* encryptedString, int LINES, int COLUMNS, char* color, unsigned int isRandom);
void rand_str(char *dest, size_t length);
void rand_encrypted_str(char *input, char *str, size_t length);
void getOptions(int argc, char* argv[], char* color, int* is_random);

# endif
