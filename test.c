 #include<stdio.h> 

/* Function Prototype */

int getArguments(int argc,char* argv[]);


int main(void)
{

    return 1; 
}
  
int getArguments(int argc,char* argv[]) 
{ 
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
        printf("\n----Following Are The Command Line Arguments Passed----"); 
        for(counter=0;counter<argc;counter++) 
        printf("\nargv[%d]: %s",counter,argv[counter]); 
    } 
    return 0; 
} 