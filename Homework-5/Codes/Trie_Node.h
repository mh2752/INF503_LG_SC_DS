#ifndef TRIE_NODE_H_INCLUDED
#define TRIE_NODE_H_INCLUDED

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <fstream>

using namespace std;


/*

Struct representing a node for
the Prefix_Trie class.


Author:

    Nazmul (mh2752@nau.edu)

*/




struct  Trie_Node
{
    Trie_Node* A = NULL;
    Trie_Node* C = NULL;
    Trie_Node* G = NULL;
    Trie_Node* T = NULL;

    bool is_leaf = false;

};

#endif