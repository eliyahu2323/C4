#include <stdio.h>
#include "frequency.h"


int main(int argc, char* argv[]) {
    trie* root;
    root = readText();


    if (argc > 1 && *(argv[1]) == 'r')
        printTrieReverse(root);
    else if (argc == 1)
        printTrie(root);
    else {
        printf("Invalid input\n");
        exit(1);
    }
    freeTrie(root);
}