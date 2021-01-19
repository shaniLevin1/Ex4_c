#define NUM ((int)26)
#ifndef Node
#define Node
typedef enum {no=0, y=1} boolean;
typedef struct node{
char letter;
long unsigned int count;
struct node* child[NUM];
boolean EndOfWord;
boolean hasChild;
} node;
#endif

#ifndef Trie
#define Trie
typedef struct trie{
node* child[NUM];
node* currNode;
char* word;
int MaxLen;
boolean empty;
} trie;
#endif


void FreeTrieMemory(trie* t);
trie* appendText();
void mallocErr(void);
void maloccErrorWord(trie* root);
node* newNode(char ch);
void ClearNode(node* n);
trie* NewTrie();
int charToIndex(char x);
void closeWord(trie* root);
boolean isEmpty(trie* root);
int appendChar(trie* root, int c);
void printWords(trie* root);
void printWordsReverse(trie* root);
void printTrieReverse(trie* root);
void printTrie(trie* root);
