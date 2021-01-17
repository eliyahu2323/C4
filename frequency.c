#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "frequency.h"
#define NUM_LETTERS ((int)26)


void memoryAlloctionError() {

    printf("Memory allocation ERROR!\n");
    exit(1);
}


//A function that allocates space in memory for the node
node* newNode() {

    node* n;

    if (!(n = (node*)malloc(sizeof(node))))
        memoryAlloctionError();

    return n;
}


//A function that initializes the node
node* resetNode(node* n, char ch) {

    n->letter = ch;
    n->count = 0;
    n->hasChild = FALSE;
    n->isEndOfWord = FALSE;
    for (int i = 0; i < NUM_LETTERS; i++) {
        (n->children)[i] = NULL;
    }
    return n;
}

//A function that creates a new node
node* createNode(char ch) {

    node* createdNode;
    createdNode = newNode();
    return  resetNode(createdNode, ch);
}

//free the memory of the node
void freeNode(node* n) {

    if (n == NULL) {
        return;
    }
    if ((n->hasChild) != 0) {
        for (int i = 0; i < NUM_LETTERS; i++) {
            freeNode((n->children)[i]);
        }

    }
    free(n);
    return;
}


//A function that allocates space in memory for the trie
trie* newTrie() {

    trie* t;
    if (!(t = (trie*)malloc(sizeof(trie))))
        memoryAlloctionError();
    return t;
}


//A function that initializes the trie
trie* resetTrie(trie* t) {

    for (int i = 0; i < NUM_LETTERS; i++) {
        t->children[i] = NULL;
    }
    t->topical = NULL;
    t->empty = TRUE;
    t->MaxWordLen = 0;

    return t;

}


//A function that creates a new trie
trie* createTrie() {
    trie* createdTrie;
    createdTrie = newTrie();
    return resetTrie(createdTrie);
}




//A function that prints the trie
void printTrie(trie* root) {

    if (root == NULL) return;
    if (isEmpty(root)) return;
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (root->children[i] == NULL)
            continue;
        root->topical = root->children[i];
        printWords(root);
    }
}

///free the memory of the trie
void freeTrie(trie* t) {

    if (t == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++) {
        freeNode(t->children[i]);
    }
    free(t->word);
    free(t);
}


//boolean function that checks whether the tree is empty or not
boolean isEmpty(trie* root) {
    return root->empty;
}



//A function that gets trie and character, checks if the character is
// alphabetic and build the trie, returns the word length.
int readLetter(trie* root, int c) {
    int index;
    int wordLen = 0;
    if (!(isalpha(c))) {
        if (c != ' ' && c != '\t' && c != '\n') return wordLen;
        if (root->topical == NULL) return wordLen;
        root->topical->count++;
        root->topical->isEndOfWord = TRUE;
        root->topical = NULL;
        return wordLen;
    }
    wordLen++;
    c = tolower(c);
    index = c - 'a';

    if (root->topical == NULL) {
        if (root->children[index] == NULL)
            root->children[index] = createNode(c);
        root->topical = root->children[index];
        root->empty = FALSE;
    }
    else {
        root->topical->hasChild = TRUE;
        if (root->topical->children[index] == NULL)
            root->topical->children[index] = createNode(c);
        root->topical = root->topical->children[index];
    }
    return wordLen;
}


//The function reads the list of words read in the input
trie* readText() {

    int c;
    int wordLen;
    trie* root;
    root = createTrie();
    while ((c = getchar()) != EOF) {

        wordLen = readLetter(root, c);
        if (wordLen > root->MaxWordLen)
            root->MaxWordLen = wordLen;
    }
    free(root->word);
    if (!(root->word = (char*)malloc(1 + sizeof(char) * (root->MaxWordLen))))
        memoryAlloctionError();
    return root;
}


//Print the list of words read in the input along with the number of occurrences per word sorted in descending lexicographic order
void printWordsReverse(trie* root) {

    static int tmp = 0;
    node* topical;
    root->word[tmp++] = root->topical->letter;


    if (root->topical->hasChild) {
        for (int i = NUM_LETTERS - 1; i >= 0; i--) {
            if (root->topical->children[i] == NULL)
                continue;
            topical = root->topical; //remember
            root->topical = root->topical->children[i];
            printWordsReverse(root);
            root->topical = topical; //recall
        }
    }
    else {
        if (root->topical->isEndOfWord) {
            root->word[tmp] = '\0';
            printf("%s\t%ld\n", root->word, root->topical->count);
        }
        --tmp;
        return;
    }
    if (root->topical->isEndOfWord) {
        root->word[tmp] = '\0';
        printf("%s\t%ld\n", root->word, root->topical->count);
    }
    --tmp;

}


//Print the list of words read in the input along with the number of occurrences
// per word sorted in descending lexicographic order
void printTrieReverse(trie* root) {


    if (root == NULL) return;
    if (isEmpty(root)) return;
    for (int i = NUM_LETTERS - 1; i >= 0; i--) {
        if (root->children[i] == NULL)
            continue;
        root->topical = root->children[i];
        printWordsReverse(root);
    }
}


//Print the list of words read in the input
void printWords(trie* root) {

    static int tmp = 0;
    node* topical;
    root->word[tmp++] = root->topical->letter;
    if (root->topical->isEndOfWord) {
        root->word[tmp] = '\0';
        printf("%s\t%ld\n", root->word, root->topical->count);
    }
    if (root->topical->hasChild) {
        for (int i = 0; i < NUM_LETTERS; i++) {
            if (root->topical->children[i] == NULL)
                continue;
            topical = root->topical;
            root->topical = root->topical->children[i];
            printWords(root);
            root->topical = topical;
        }
    }
    else {
        --tmp;
        return;
    }

    --tmp;
}