#ifndef TRIE_NODE_H_INCLUDED
#define TRIE_NODE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>

using namespace std;

/*

Header file containing the Trie_Node
struct for using in Suffix_Trie class.

Author:
    Nazmul (mh2752@nau.edu)

*/


struct Trie_Node
{

    // Pointers to the child nodes representing
    // the nucleotides and the terminating 
    // '$' character.
    Trie_Node* A = NULL;
    Trie_Node* C = NULL;
    Trie_Node* G = NULL;
    Trie_Node* T = NULL;
    Trie_Node* DS = NULL;
    

};


#endif