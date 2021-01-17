#include <stdlib.h>
#define NUM_LETTERS ((int)26)

typedef enum { FALSE = 0, TRUE = 1 } boolean;

#ifndef Node
#define Node

typedef struct node {

	char letter;
	long unsigned int count;
	struct node* children[NUM_LETTERS];
	boolean isEndOfWord;
	boolean hasChild;

} node;
#endif

#ifndef Trie
#define Trie

typedef struct trie {

	node* children[NUM_LETTERS];
	node* topical;
	char* word;
	int MaxWordLen;
	boolean empty;

} trie;
#endif

void memoryAlloctionError();
node* newNode();
node* resetNode(node* n, char ch);
node* createNode(char ch);
void freeNode(node* n);
trie* newTrie();
trie* resetTrie(trie* t);
trie* createTrie();
boolean isEmpty(trie* root);
int readLetter(trie* root, int c);
trie* readText();
void printWordsReverse(trie* root);
void printTrieReverse(trie* root);
void printWords(trie* root);
void printTrie(trie* root);
void freeTrie(trie* t);