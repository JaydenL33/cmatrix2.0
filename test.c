 #include <stdio.h> 
 #include <stdlib.h>
 #include <string.h> 

/*
 *   Authors:    
 *  - Jayden Lee
 *   Date: 
 *   30/05/2019
 */


int checkValidRange (unsigned char *unCheckedArray, int plaintextlen, char* checkedArray);

int main(int argc, char *argv[])
{
    int amount = 10;
    unsigned char testArray = "test";
    printf("test array is %s", testArray);
    char CheckedArray[amount];
    checkValidRange(testArray, amount, CheckedArray);
    printf("Checked Range is %s", CheckedArray);

}

/**************************************************************************
 * We need to get this to work in main.c. 
 * Take in options like colour and set the value of color to ?
 * print list if invalid option. 
 * crappy input, no input. 
****************************************************************************/
  
int checkValidRange (unsigned char *unCheckedArray, int plaintextlen, char* checkedArray) {
    int decASCII;
    int i;
    int j = 0;
    
    for (i = 0; i < plaintextlen; i++)
    {
        decASCII = (int) unCheckedArray[i]; 
        if (decASCII >= 33 && decASCII <= 126)
        {
            checkedArray[j] = (char) (decASCII - 127) ;
            j++;
        }
    }
    checkedArray[j] = '\0';
    return 1;
}

