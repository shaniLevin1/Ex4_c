#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trie.h"

//Print an error if tere is an malloc error.
void mallocError(void){
printf("Memory error\n");
exit(1);
}

//Crating and init a new node
node* newNode(char letter){
node* n;
if (!(n=(node*)malloc(sizeof(node))))
mallocError();

int i;
n->letter = letter;
n->count = 0;
n->EndOfWord = no;
n->hasChild = no;
for (i=0; i<NUM; i++) {
(n->child)[i] = NULL; //init the children of the node
}
return n;
}
//Clear the memory of a node and his kids, if he got any.
void ClearNode(node* n){
int i;
if (n==NULL) 
return;

if ((n->hasChild)==no){ //if the node has no kids
    free(n);
}
if ((n->hasChild)==y){ //if the node has kids
for (i=0; i<NUM; i++) {
ClearNode((n->child)[i]); 
}
}
return;
}

//Creates a new Trie abd reset the Trie's parameters.
trie* NewTrie(){
trie* ti;
if(!(ti = (trie*)malloc(sizeof(trie))))  //memory error 
       mallocError();

for(int i=0 ; i<NUM; i++){ //init the children of the curr node
	ti->child[i] = NULL;
   }
   ti->currNode = NULL;  
   ti->empty = y; //init the status of the trie to empty
   ti->MaxLen = 0; 

   return ti;
}

//Clears the memory of the Trie.
void FreeTrieMemory(trie* t){

   if(t == NULL) return;

   for(int i=0 ; i<NUM; i++){
      ClearNode(t->child[i]);
   }
   free(t);
}

//Return true if the root is empty, false if not
boolean isEmpty(trie* root){
    return root->empty;
}

//Convert char type to an index number.
int charToIndex(char x){
return x-'a';
}

//If the letter is an end of a word the fubction close the word.
void closeWord(trie* root){
if (root->currNode == NULL)
return;
root->currNode->count++;
root->currNode->EndOfWord = y; //change the status of the EndOfWord of the node to y
root->currNode=NULL; //init the curr node
}

//append one char to the Trie and return the length of the word
int appendChar(trie* root, int c){
int index;
int word_length=0;
if(!isalpha(c)) { //if c is a char in range of a-z
	closeWord(root);
	return word_length;
}
word_length++;

c=tolower(c); //make this letter to small letter
index= charToIndex(c); 
if (root->currNode==NULL) { 
if (root->child[index] == NULL) 
	root->child[index] = newNode(c); 
root->currNode = root->child[index];
root->empty=no;
} 
else {
root->currNode->hasChild = y;
if (root->currNode->child[index] == NULL)
root->currNode->child[index] = newNode(c);
root->currNode=root->currNode->child[index];
}
return word_length;
}

//Print an error if tere is an malloc error.
void maloccErrorWord(trie* root){
free(root->word);
if (!(root->word=(char*)malloc(1+sizeof(char)*(root->MaxLen))) )
mallocError();
}

//append text to the Trie.
trie* appendText(){
trie* root;
int c;
int word_length;
root = NewTrie(); //create new trie
while((c=getchar()) != EOF){
word_length=appendChar(root,c); 
if (word_length>root->MaxLen)
root->MaxLen=word_length;
}
maloccErrorWord(root);
return root;
}

//This function prints the words of a node.
void printWords(trie* root){
static int x=0;
int i;
node* currNode;
root->word[x++]=root->currNode->letter; //append root to word array
if (root->currNode->EndOfWord) {
root->word[x]='\0';
printf("%s %ld\n",root->word,root->currNode->count);
}
if (root->currNode->hasChild) {
for(i=0; i<NUM; ++i) { //
if (root->currNode->child[i] == NULL)
continue;
currNode = root->currNode; 
root->currNode = root->currNode->child[i];
printWords(root);
root->currNode = currNode; 
}
} else {
--x;
return;
}
--x;
}

//Print the word in reverse order.
void printWordsReverse(trie* root){
static int x=0;
int i;
node* currNode;
root->word[x++]=root->currNode->letter;
if (root->currNode->hasChild) {
for (i=NUM-1; i>=0; --i){
if (root->currNode->child[i] == NULL)
continue;
currNode = root->currNode; 
root->currNode = root->currNode->child[i];
printWordsReverse(root);
root->currNode = currNode; 
}
} else {
if (root->currNode->EndOfWord){
root->word[x]='\0';
printf("%s %ld\n",root->word,root->currNode->count);
}
--x;
return;
}
if (root->currNode->EndOfWord){
root->word[x]='\0';
printf("%s %ld\n",root->word,root->currNode->count);
}
--x;
}

//This function print the Trie.
void printTrie(trie* root){
int i;
if (root == NULL) //check if the root is null
return;
if (isEmpty(root)) //check if there are nodes in the trie beside the root
return;
for (i=0; i<NUM; ++i){
if (root->child[i] == NULL) //if there is no children
continue;
root->currNode = root->child[i]; //define the curr node to the children index i
printWords(root);
}
}

//Prints the whole Trie, in reverse order.
void printTrieReverse(trie* root){
int i;
if (root == NULL) //check if the root is null
return;
if (isEmpty(root))//check if there are nodes in the trie beside the root
return;
for (i=NUM-1; i>=0; --i){
if (root->child[i] == NULL) //check if the children of the root in index i is null
continue;
root->currNode = root->child[i]; //efine the curr node to the children index i
printWordsReverse(root);
}
}
