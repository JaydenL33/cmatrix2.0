/* Compression functionality header for libCompression.
 * Note: utility functions moved to seperate util lib!!!
 *
 * See the github: github.com/rlcaust/Fund-O-C
 * 
 * Authors:
 * Benjamin Gillespie
 */

# ifndef _COMPRESSION_H_
# define _COMPRESSION_H_

#define MAX_TREE_HT 100 /*Max heigh of huffman tree*/
#define DB_NAME "database.txt" /*File containing text to compression*/
#define COMPRESS_NAME "compressed.bin" /*Compressed file name*/

/*A Huffman tree node*/
struct MinHeapNode {
    char data; /*A unique character for that node*/
    unsigned freq; /*Frequency of the character*/
    struct MinHeapNode *left, *right; /*Left and right child of this node*/
};

/*A Min Heap: Collection of min-heap (or Huffman tree) nodes*/
struct MinHeap {
    unsigned size; /*Current size of min heap*/
    unsigned capacity; /*Capacity of min heap*/
    struct MinHeapNode** array; /*Array of minheap node pointers*/
};

struct MinHeapNode* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int index);
int isSizeOne(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
void printArr(int arr[], int size);
void writeArr(int arr[], int size);
int isLeaf(struct MinHeapNode* root);
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void printCodes(struct MinHeapNode* tree, int binary[], int top);
void saveCode(struct MinHeapNode* current, int binary[], int top, char c, int * binaryNumber);
void writeCode(struct MinHeapNode* current, struct MinHeapNode* tree, int binary[], int top);
void load(char *str, int n);
void loadCompressed(int binary[], int binaryNumber);
void save(char data[], int freq[], int size, char *str, int * binaryNumber);
void addChar(char *str, char c);
char* getChars(char *str);
int indexOfChar(char *str, char c);
int* getFreq(char *arr, char *str);
void compression(char* str, int n, int * binaryNumber);
void decompression(char* str, int binaryNumber);

# endif