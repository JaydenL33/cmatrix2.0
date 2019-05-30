 #include <stdio.h> 
 #include <stdlib.h>
 #include <string.h> 

/* Function Prototype */

int getArguments(int arguCounter, char* argv[]);


int main(int argc, char *argv[])
{
    getArguments(argc, argv);
    return 1; 
}
  
int getArguments(int arguCounter, char* argv[]) 
{ 
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
        printf("\n Case and Switch Testing "); 
        for (i=0; i<arguCounter; i++) 
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
                
            }  
        }
    } 
    return 0; 
} 