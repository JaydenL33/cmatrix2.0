#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100
#define DB_NAME "database.txt"
#define COMPRESS_NAME "compressed.bin"
#define TREE_STORE "tree.dat"
  
// A Huffman tree node
struct MinHeapNode {
    char data; // An input character
    unsigned freq; // Frequency of the character
    struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {
    unsigned size; // Current size of min heap
    unsigned capacity; // Capacity of min heap
    struct MinHeapNode** array; // Array of minheap node pointers
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp  = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0; // current size is 0
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

    return minHeap;
}
  
// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
  
// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    unsigned int left = 2 * idx + 1;
    unsigned int right = 2 * idx + 2;
  
    if(left < minHeap->size && minHeap->array[left]->
freq < minHeap->array[smallest]->freq)
        smallest = left;
  
    if(right < minHeap->size && minHeap->array[right]->
freq < minHeap->array[smallest]->freq)
        smallest = right;
  
    if(smallest != idx){
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
  
// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}
  
// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
  
    return temp;
}
  
// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while(i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq){
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}
  
// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for(i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
  
// A utility function to print an array of size n
void printArr(int arr[], int n) {
    int i;
    for(i = 0; i < n; ++i)
        printf("%d", arr[i]);
}

// A utility function to write to file an array of size n
void writeArr(int arr[], int n) {
    FILE *fp;
	fp = fopen(COMPRESS_NAME, "ab");
    fwrite(arr, sizeof(int), n, fp);
    fclose(fp);
    printArr(arr, n);
}
  
// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root) { 
    return !(root->left) && !(root->right); 
}
  
// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) { 
    struct MinHeap* minHeap = createMinHeap(size); 
    for(int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
    
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  

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
 * - int * binaryNumber = Pointer to int representing amount of bits in compressed file
 * outputs:
 * - None
*******************************************************************************/
void saveCode(struct MinHeapNode* current, int binary[], int top, char c, int * binaryNumber) {
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
         *Prints the huff code for every char that appears in original text file
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
void writeCode(struct MinHeapNode* current, struct MinHeapNode* tree, int binary[], int top) {
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
    FILE *fp;
	fp = fopen(DB_NAME, "r");
	if(fp != NULL){
		while(fgets(str, n, fp) != NULL)
		fclose(fp);
	}
    else {
        printf("Read error\n");
    }
}

void loadCompressed(struct MinHeapNode* root, int  binary[], int binaryNumber) {
    FILE *fp;
	fp = fopen(COMPRESS_NAME, "rb");
	if(fp != NULL){
        fread(binary, sizeof(int), binaryNumber, fp);
		fclose(fp);
        printf("\nLOAD BINARY CODES\n");
        int i;
        for(i = 0; i < binaryNumber; i++){
            printf("%d", binary[i]);
        }
	}
    else {
        printf("Read error\n");
    }
}

void save(char data[], int freq[], int size, char *str, int * binaryNumber) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int len = strlen(str);
    int i;
    printf("Compressed binary code for text file\n");
    /*For every character from database file(original string) save its huffman code value to binary file*/
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
 * - char* arr = String with character appended
*******************************************************************************/
void addChar(char *str, char c) {
    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 );
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
char* getChars(char *str) {
    int i;
    size_t len = strlen(str);
    char *arr = (char*) malloc(26 * sizeof(char));
    memset(arr, '\0', sizeof(arr));
    char *ret;
    char c;
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
int indexOfChar(char *str, char c) {
    int index;
    size_t len = strlen(str);
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
int* getFreq(char *arr, char *str) {
    int i, index;
    size_t len = strlen(str);
    int *freq = malloc(strlen(arr) * sizeof(int));
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

void compression(char* str, int n, int * binaryNumber){
    load(str, n);
    char *arr = getChars(str);
    int *freq = getFreq(arr, str);
    int size = strlen(arr)/sizeof(arr[0]);
    save(arr, freq, size, str, binaryNumber);

    /*DEBUG
     *Prints huffman code for every charcter in file - allows manual compression/decompression
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
    /*Build tree for decompression*/
    char *arr = getChars(str);
    int *freq = getFreq(arr, str);
    int size = strlen(arr)/sizeof(arr[0]);
    struct MinHeapNode* root  = buildHuffmanTree(arr, freq, size);

    int binary[binaryNumber];
    int count, loadTop = 0;
    /*Initialise binary array*/
    for(count = 0; count < binaryNumber; count++){
        binary[count] = -1;
    }
    /*Load bits from compressed file to binary array and prints code*/
    loadCompressed(root, binary, binaryNumber);
    printf("\nORIGINGAL STRING IS: \n%s\n", str);
    printf("\nDECOMPRESSED STRING IS:\n");
    writeCode(root, root, binary, loadTop);
}
  
int main() { 
    /* All to be done in main and called when compress/decompress is desired
     * n - is the number of chars in text file to read from
     */
    int n = 5000;
    int binaryNumber;
    char *str = malloc(n);
    compression(str, n, &binaryNumber);
    decompression(str, binaryNumber);
    return 0; 
} 