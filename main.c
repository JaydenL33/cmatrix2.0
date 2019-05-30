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
	char testKey[INPUT_STRING_BUFFER];
	unsigned char encryptedData[INPUT_STRING_BUFFER]; /* macro from encrypt.h */

	char* decryptedData = malloc(sizeof(char) * plainTextLen);



/**************************************************************************
 * Reading Arguments to the Program
****************************************************************************/
	
	int i; 
    printf("Program Name Is: %s",argv[0]); 
    if(arguCounter==1) 
    {
        printf("Test \n");
        /* Execute Some Function */
    }

    if(arguCounter>=2) 
    {
        printf("\nNumber Of Arguments Passed: %d",arguCounter); 
        printf("\n Case/if Statement Testing. "); 
        for (i=0; i<arguCounter; i++) 
        {
            if ((int) *argv[i] == '-')
            {
                if (strcmp(argv[i], "-c") == 0)
                {
                    printf("\n The Code is %s, and the number in front of it is %s. \n", argv[i], argv[i+1]);
                    if (strcmp(argv[i + 1], "1") == 0)
                    {
                        printf("HOLY FUCK ITS WORK \n");
                        
                    }
                }
                if (strcmp(argv[i], "-E") == 0)
                {
                    plainTextLen = encrypt(encryptedData);
                }  
            }
        }
        return 0; 
    } 

/**************************************************************************
 * End of Reading Arguments to the Program. 
****************************************************************************/




	decrypt(encryptedData, decryptedData, plainTextLen, testKey);

	char words[130]; /* Will hold the encrypted string */
	int num = readcipher(words, 130); /* Reads in encrypted string */
	char validString[plainTextLen];
	checkValidRange(words, plainTextLen, validString);

	int is_random = 0;

	/* MAKE SURE THESE ARE EXPORTED OTHERWISE WE SEGFAULT */
	int LINES = atoi(getenv("LINES"));
	int COLUMNS = atoi(getenv("COLUMNS"));
	/* print_raindrops(validString, LINES, COLUMNS, color, is_random); */
	return 1;

/**************************************************************************
 * Reading Arguments to the Program
****************************************************************************/
	
	int i; 
    printf("Program Name Is: %s",argv[0]); 
    if(arguCounter==1) 
    {
        printf("Test \n");
        /* Execute Some Function */
    }

    if(arguCounter>=2) 
    {
        printf("\nNumber Of Arguments Passed: %d",arguCounter); 
        printf("\n Case/if Statement Testing. "); 
        for (i=0; i<arguCounter; i++) 
        {
            if ((int) *argv[i] == '-')
            {
                if (strcmp(argv[i], "-c") == 0)
                {
                    printf("\n The Code is %s, and the number in front of it is %s. \n", argv[i], argv[i+1]);
                    if (strcmp(argv[i + 1], "1") == 0)
                    {
                        printf("HOLY FUCK ITS WORK \n");
                        
                    }
                }
                if (strcmp(argv[i], "-E") == 0)
                {
                    plainTextLen = encrypt(encryptedData);
                }  
            }
        }
    } 
/**************************************************************************
 * End of Reading Arguments to the Program. 
****************************************************************************/
    return 0; 
} 


