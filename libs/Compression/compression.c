/* Compression functionality source code for libCompression.
 * Note: utility functions moved to seperate util lib!!!
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Benjamin Gillespie
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compression.h"

/*******************************************************************************
 * This is a utility function to allocate a new Min Heap/Tree node with a given
 * character and frequency of the character
 * - unsinged capacity - Size of Min Heap/Tree node to create
 * Outputs:
 * - struct MinHeapNode* newNode = Min Heap/Tree node that was created 
*******************************************************************************/
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* newNode  = 
(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->left = newNode->right = NULL;
    newNode->data = data;
    newNode->freq = freq;

    return newNode;
}

/*******************************************************************************
 * This is a utility function to create a Min Heap/Tree of given capacity
 * - unsinged capacity - Size of Min Heap/Tree to create
 * Outputs:
 * - None
*******************************************************************************/
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0; 
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * 
sizeof(struct MinHeapNode*));

    return minHeap;
}

/*******************************************************************************
 * This is a utility function to swap two Min Heap/Tree nodes
 * - struct MinHeapNode** a = Pointer to node a
 * - struct MinHeapNode** b = Pointer to node b
 * Outputs:
 * - None
*******************************************************************************/
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

/*******************************************************************************
 * This is a utility function to Min Heapify a Min Heap/Tree
 * - struct MinHeap* minHeap = Min Heap/Tree
 * - int index = Starting index
 * Outputs:
 * - None
*******************************************************************************/
void minHeapify(struct MinHeap* minHeap, int index) {
    int smallest = index;
    unsigned int left = 2 * index + 1;
    unsigned int right = 2 * index + 2;
  
    if(left < minHeap->size && minHeap->array[left]->
freq < minHeap->array[smallest]->freq)
        smallest = left;
  
    if(right < minHeap->size && minHeap->array[right]->
freq < minHeap->array[smallest]->freq)
        smallest = right;
  
    if(smallest != index){
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }
}

/*******************************************************************************
 * This is a utility function to check if size of heap is 1
 * - struct MinHeap* minHeap = Min Heap/Tree
 * Outputs:
 * - int = Size of Min Heap
*******************************************************************************/
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

/*******************************************************************************
 * This is a utility function to extract the minimum value node from Heap/Tree
 * - struct MinHeap* minHeap = Min Heap/Tree
 * Outputs:
 * - None
*******************************************************************************/
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
  
    return temp;
}

/*******************************************************************************
 * This is a utility function to insert a new node to Min Heap
 * - struct MinHeap* minHeap = Min Heap/Tree
 * - struct MinHeapNode* minHeapNode = Node to insert into Heap/Tree
 * Outputs:
 * - None
*******************************************************************************/
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while(i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq){
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

/*******************************************************************************
 * This is a utility function to build Min Heap
 * - struct MinHeap* minHeap = Min Heap/Tree
 * Outputs:
 * - None
*******************************************************************************/
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for(i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

/*******************************************************************************
 * This is a utility function to print an array of size
 * - int arr[] = Array of integers
 * - int size = Size of the array
 * Outputs:
 * - None
*******************************************************************************/
void printArr(int arr[], int size) {
    int i;
    for(i = 0; i < size; ++i)
        printf("%d", arr[i]);
}

/*******************************************************************************
 * This function writes the huffman binary to the compressed file
 * Inputs:
 * - int arr[] = Array of bits representing the Huffman binary of a character
 * - int size = Number of bits in array
 * Outputs:
 * - int = 1 if root is a leaf
*******************************************************************************/
void writeArr(int arr[], int size) {
    FILE* fp;
	fp = fopen(COMPRESS_NAME, "ab");
    fwrite(arr, sizeof(int), size, fp);
    fclose(fp);
    /*DEBUG
     *Prints all the binary code that is being written to the binary file
    if(DEBUG){
        printArr(arr, size);
    }*/
}

/*******************************************************************************
 * This function builds a MinHeap of capacity equal to size and inserts all 
 * characters of data[] in the heap.
 * Inputs:
 * - struct MinHeapNode* root = Huffman tree node
 * Outputs:
 * - int = 1 if root is a leaf
*******************************************************************************/
int isLeaf(struct MinHeapNode* root) { 
    return !(root->left) && !(root->right); 
}

/*******************************************************************************
 * This function builds a MinHeap of capacity equal to size and inserts all 
 * characters of data[] in the heap.
 * Inputs:
 * - char data[] = String containing each character that appeared
 * - int freq[] = Frequency of every character that appeared
 * - int size = Number of characters in data
 * Outputs:
 * - struct MinHeapNode* = MinHeap node that was built
*******************************************************************************/
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) { 
    struct MinHeap* minHeap = createMinHeap(size); 
    int i;
    for (i = 0; i < size; ++i) 
    {
        minHeap->array[i] = newNode(data[i], freq[i]); 
    }
    
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 

/*******************************************************************************
 * This function builds the Huffman tree
 * Inputs:
 * - char data[] = String containing each character that appeared
 * - int freq[] = Frequency of every character that appeared
 * - int size = Number of characters in data
 * Outputs:
 * - struct MinHeapNode* = Huffman tree root node was built
*******************************************************************************/
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) { 
    struct MinHeapNode *left, *right, *top; 
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
    while(!isSizeOne(minHeap)){ 
        left = extractMin(minHeap); 
        right = extractMin(minHeap);  
        top = newNode('$', left->freq + right->freq); 
        top->left = left; 
        top->right = right; 
        insertMinHeap(minHeap, top); 
    }  
    return extractMin(minHeap); 
} 

/*******************************************************************************
 * This function transverses the huffman tree and prints codes for every 
 * character in the tree
 * inputs:
 * - struct MinHeapNode* tree = Current node on tree as it's traversed
 * - int binary[] = Binary code produced for character by the traversal
 * - int top = Keeps track of current position of binary
 * outputs:
 * - None
*******************************************************************************/
void printCodes(struct MinHeapNode* tree, int binary[], int top) {  
    if(tree->left){ 
        binary[top] = 0; 
        printCodes(tree->left, binary, top + 1); 
    } 
    if(tree->right){ 
        binary[top] = 1; 
        printCodes(tree->right, binary, top + 1); 
    } 
    if(isLeaf(tree)){ 
        printf("%c: ", tree->data); 
        printArr(binary, top); 
        printf(" ");
    } 
}

/*******************************************************************************
 * This function transverses the huffman tree for every character in text file
 * and writes it to binary to file
 * inputs:
 * - struct MinHeapNode* current = Current node on tree as it's traversed
 * - int binary[] = Binary code produced for character by the traversal
 * - int top = Keeps track of current position of binary
 * - char c = The character whos binary is being found
 * - int * binaryNumber = Pointer to int representing amount of bits in 
 * compressed file
 * outputs:
 * - None
*******************************************************************************/
void saveCode(struct MinHeapNode* current, int binary[], int top, char c,
int * binaryNumber) {
    if(current->left){ 
        binary[top] = 0;
        saveCode(current->left, binary, top + 1, c, binaryNumber); 
    } 
    if(current->right){ 
        binary[top] = 1;
        saveCode(current->right, binary, top + 1, c, binaryNumber); 
    } 
    if(isLeaf(current) && current->data == c){ 
        /*DEBUG
         *Prints the huff code for every char that appears in text file
        if(DEBUG){
            printf("Huff code for %c is:", c);
        }*/
        *binaryNumber = *binaryNumber + top;
        writeArr(binary, top);
    } 
}

/*******************************************************************************
 * This function transverses the huffman tree from the binary file and  prints
 * every character as it is found
 * Inputs:
 * - struct MinHeapNode* current = Current node on tree as it's traversed
 * - struct MinHeapNode* tree = Huffman tree
 * - int binary[] = binary of compressed binary file
 * - int top = Keeps track of current position of binary
 * Outputs:
 * - None
*******************************************************************************/
void writeCode(struct MinHeapNode* current, struct MinHeapNode* tree, 
int binary[], int top) {
    if(current->left && binary[top] == 0){ 
        writeCode(current->left, tree, binary, top + 1); 
    } 
    if(current->right && binary[top] == 1){ 
        writeCode(current->right, tree, binary, top + 1); 
    } 
    if(isLeaf(current)){
        /*DEBUG
         *Print character found and its binary code from binary file
        if(DEBUG){
            printf("%c: ", current->data);
            printArr(arr, top);
        }*/
        char c = current->data;
        printf("%c", c);
        writeCode(tree, tree, binary, top);
    } 
}

/*******************************************************************************
 * This function loads text file to a string
 * Inputs:
 * - char *str = String to load file to
 * - int n = Number of characters to read into str
 * Outputs:
 * - None
*******************************************************************************/
void load(char *str, int n) {
    FILE* fp;
	fp = fopen(DB_NAME, "r");
	if(fp != NULL){
		while(fgets(str, n, fp) != NULL)
		fclose(fp);
	}
    else {
        printf("Read error\n");
    }
}

/*******************************************************************************
 * This function loads binary from compressed file into an array
 * Inputs:
 * - int  binary[] = Array to load binary from file into 
 * - int binaryNumber = How many bits are in the binary file
 * Outputs:
 * - None
*******************************************************************************/
void loadCompressed(int binary[], int binaryNumber) {
    FILE* fp;
	fp = fopen(COMPRESS_NAME, "rb");
	if(fp != NULL){
        fread(binary, sizeof(int), binaryNumber, fp);
		fclose(fp);
        /*DEBUG
         *Prints the binary code that has been read from compressed file
        if(DEBUG){
            printf("\nLOAD BINARY CODES\n");
            int i;
            for(i = 0; i < binaryNumber; i++){
                printf("%d", binary[i]);
            }
        }*/
	}
    else {
        printf("Read error\n");
    }
}

/*******************************************************************************
 * This function saves the compressed string
 * Inputs:
 * - char data[] = String containing each character that appeared
 * - int freq[] = Frequency of every character that appeared
 * - int size = Number of characters in data
 * - char *str = Loaded string of text in saved file
 * - int * binaryNumber = Pointer to int representing amount of bits in 
 * compressed file
 * Outputs:
 * - None
*******************************************************************************/
void save(char data[], int freq[], int size, char *str, int * binaryNumber) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int len = strlen(str);
    int i;
    /*DEBUG
     *Indicator that binary code will be printed
    if(DEBUG){
        printf("Compressed binary code for text file\n");
    }*/

    /*For every character from database file(original string) save its huffman 
    code value to binary file*/
    int binary[MAX_TREE_HT], top = 0;
    for(i = 0; i < len; i++){
        saveCode(root, binary, top, str[i], binaryNumber);
    }
}

/*******************************************************************************
 * This function adds a char to the back of input string
 * Inputs:
 * - char *str = String to add to
 * - char c = Character to add to string
 * Outputs:
 * - None
*******************************************************************************/
void addChar(char *str, char c) {
    size_t len = strlen(str);
    char* str2 = malloc(len + 1 + 1 );
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    /*DEBUG 
     *Print string everytime a char is added
    if(DEBUG){
        printf("%s\n", str2);
    }*/
    strcpy(str, str2);
    free(str2);
}

/*******************************************************************************
 * This function returns a string with every character that appears in the input
 * string
 * Inputs:
 * - char *str = String of text file
 * Outputs:
 * - char* arr = String containing every character that appeared
*******************************************************************************/
char* getChars(char* str) {
    int i, size = 26;
    int len = strlen(str);
    char* arr = (char*) malloc(size * sizeof(char));
    memset(arr, '\0', size);
    char* ret;
    for(i = 0; i < len; i++){
        char c = str[i];
        ret = strchr(arr, c);
        if(!ret){
            /*DEBUG
             *Print every char that appears and will be added to str
            if(DEBUG){
                printf("add char %c\n", c);
            }
            */
            addChar(arr, c);
        }
    }
    return arr;
}

/*******************************************************************************
 * This function returns the index of a character within a string
 * Inputs:
 * - char *str = String to search through
 * - char c =  Character to find in string
 * Outputs:
 * - int index = Index of character in the string
*******************************************************************************/
int indexOfChar(char* str, char c) {
    int index;
    int len = strlen(str);
    for(index = 0; index < len; index++){
        if(str[index] == c)
            return index;
    }
    return -1;
}

/*******************************************************************************
 * This function returns the frequency of every character in string str
 * Inputs:
 * - char *str = String from file
 * - char *arr = String of every character that appears in file
 * Outputs:
 * - int *freq = Int array of frequency of each character
*******************************************************************************/
int* getFreq(char* arr, char* str) {
    int i, index;
    int len = strlen(str);
    int* freq = malloc(strlen(arr) * sizeof(int));
    /*Initialises freq array to 0*/
    for(i = 0; i < strlen(arr); i++){
        freq[i] = 0;
    }
    for(i = 0; i < len; i++){
        index = indexOfChar(arr, str[i]);
        if (index != -1){
            freq[index]++;
        }
    }
    /*DEBUG
     *Prints each character in file and ammount it occurrs
    if(DEBUG){
        for(i = 0; i < strlen(arr); i++){
            printf("char %c occurs %d\n", arr[i], freq[i]);
        }
    }
    */
    return freq;
}

void compression(char* str, int n, int* binaryNumber){
    FILE* fp;
    fp = fopen(COMPRESS_NAME, "wb");
    fclose(fp);
    load(str, n);
    printf("\nSTRING BEING COMPRESSED IS:\n %s\n", str);
    printf("\nCOMPRESSING....\n");
    char* arr = getChars(str);
    int* freq = getFreq(arr, str);
    int size = strlen(arr)/sizeof(arr[0]);
    save(arr, freq, size, str, binaryNumber);

    /*DEBUG
     *Prints huffman code for every charcter in file - allows manual 
     compression/decompression
     *to calculate expected results
    if(DEBUG){
        struct MinHeapNode* root = buildHuffmanTree(arr, freq, size);
        int arr1[MAX_TREE_HT], top = 0;
        printf("\n\nHUFFMAN CODES ARE: \n");
        printCodes(root, arr1, top);
    }
    */
}

void decompression(char* str, int binaryNumber){
    printf("\nDECOMPRESSING....\n");
    /*Build tree for decompression*/
    char* arr = getChars(str);
    int* freq = getFreq(arr, str);
    int size = strlen(arr)/sizeof(arr[0]);
    struct MinHeapNode* root  = buildHuffmanTree(arr, freq, size);

    int binary[binaryNumber];
    int count, loadTop = 0;
    /*Initialise binary array*/
    for(count = 0; count < binaryNumber; count++){
        binary[count] = -1;
    }
    /*Load bits from compressed file to binary array and prints code*/
    loadCompressed(binary, binaryNumber);
    printf("\nDECOMPRESSED STRING IS:\n");
    writeCode(root, root, binary, loadTop);
}
  
int main() { 
    /* All to be done in main and called when compress/decompress is desired
     * n - is the number of chars in text file to read from
     */
    int n = 5000;
    int binaryNumber;
    char* str = malloc(n);
    compression(str, n, &binaryNumber);
    decompression(str, binaryNumber);
    return 0; 
} 