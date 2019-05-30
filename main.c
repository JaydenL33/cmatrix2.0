/*
 *   Authors:    
 *  - Sebastian Southern 
 *  - Ben Gillespie
 *  - Lachlan Leslie
 *  - Albert Ferguson
 *  - Jayden Lee
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "libs/Crypto/encrypt.h"
# include "libs/Util/util.h"
# include "libs/PrintRaindrops/printraindrops.h"

void print_menu();

/* memes be like... */
void pepe();
void squash_pepe();
void matrix_quotes();

int main(int argc, char *argv[])  {
	int plainTextLen;
	unsigned char encryptedData[INPUT_STRING_BUFFER]; /* macro from encrypt.h */


/***************************************************************************/
 	int i; 
    printf("Program Name Is: %s",argv[0]); 

    if(argc==1) 
    {
        printf("Test \n");
        /* Execute Some Function */
    }

    if(argc>=2) 
    {
        printf("\nNumber Of Arguments Passed: %d",argc); 
        printf("\n Case/if Statement Testing. "); 
        for (i=0; i<argc; i++) 
        {
            if ((int) *argv[i] == '-')
            {
                if (strcmp(argv[i], "-c") == 0)
                {
                    
                    if (strcmp(argv[i + 1], "r") == 0)
                    {
                    	printf("Hello \n");
                    }
                }
                if (strcmp(argv[i], "-E") == 0)
                {
                   	plainTextLen = encrypt(encryptedData);
                   	printf("%d \n", plainTextLen);
                }  
            }
        }
    } 

/**************************************************************************
 * End of Reading Arguments to the Program. 
****************************************************************************/
	return 0; 
}

