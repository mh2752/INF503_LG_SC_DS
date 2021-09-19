#ifndef PREFIX_TRIE_H_INCLUDED
#define PREFIX_TRIE_H_INCLUDED

#include "Stack.h"
#include "Queue.h"
#include "Trie_Node.h"


/*

Class declarition for the Prefix_Trie
class.

Author:
    Nazmul(mh2752@nau.edu)

*/


class Prefix_Trie
{

    public:

        // Default class ctor()      
        Prefix_Trie();

        
        // Overloaded class ctor()
        //
        // Parameter 1: The 2D char array holding all the
        //              queries to insert into the trie.
        //
        // Parameter 2: Number of rows in the 2D array.
        //
        // Parameter 3: Length of each row in the 2D array.
        //              It should be equal to the length of
        //              k-mers being stored.
        Prefix_Trie(const char**,int,int);


        // Copy ctor()
        //
        // Parameter 1: the old prefix trie object
        //              to build the new trie from.
        Prefix_Trie(const Prefix_Trie&);



        // Class dtor()
        ~Prefix_Trie();


        // Function for inserting a
        // sequence into the trie.
        //
        // Parameter 1: the char array holding the
        //              sequence to be inserted.
        //
        // Parameter 2: length of the sequence.
        void Insert_Item_In_Trie(const char*,unsigned int);



        // Function for searching given
        // sequence in the trie (fuzzy
        // matching).
        //
        // Parameter 1: the sequence to search for
        //
        // Parameter 2: length of the sequence
        //
        // Parameter 3: max mismatch tolerance
        //
        // Parameter 4: return variable holding the
        //              result of the search.
        //              true = sequence was found
        //              false = sequence was not found
        void Search_Item_In_Trie(const char*,int,int,bool&);



        // Function for reading the SARS-COV2
        // genome data from the input file
        // specified by the given filepath.
        //
        // Parameter 1: the char array representing
        //              the filepath string.
        //
        // Parameter 2: length of the file path array
        void Read_SARS_Genome_From_File(const char*,int);



        // Function for traversing the trie
        // using the full genome.
        //
        // Parameter 1: the char array representing the genome
        //
        // Parameter 2: length of the genome
        //
        // Parameter 3: #of kmers generated & searched for
        //
        // Parameter 4: #of kmers found
        void Traverse_Trie_Using_Genome(const char*,int,int&,int&);


        // Function for searching all 36mers
        // of the SARS-COV2 genome in the
        // trie.
        //
        // Parameter 1: #of 36mers searched for
        //
        // Parameter 2: #of 36mers found
        void Search_For_All_36mers(int&,int&);


        // Function to check whether the
        // trie is empty or not.
        bool Is_Trie_Empty();



        // Function for generating and populating the
        // trie with the non-mutated 36mers
        //
        // Parameter 1: How many random 36mers to generate
        void Generate_And_Store_36mers(unsigned int);



        // Function for generating and populating the trie
        // with the mutated 36mers:
        //
        // Parameter 1: #of 36mers to generate
        void Generate_And_Store_Mutated_36mers(unsigned int);


        // Function for counting and returning the
        // total number of nodes in the trie.
        unsigned long int Get_Trie_Size();


    private:

        // Root node of the Prefix_Trie
        Trie_Node* root;

        // 1D char array for holding the
        // full SARS-COV2 genome:
        char* sars_full_genome;
        
        // Length of the sars full genome:
        unsigned long int sars_full_genome_length;

        // Number of characters in the header of the
        // SARS COV2 genome header file:
        unsigned int sars_genome_header_size = 38;


        // length of a buffer char array:
        unsigned int buffer_length = 256;



        // Function for clearing a buffer array:
        void Clear_Buffer_Array(char*&);



        // Length of a k-mer (36 for a 36mer)
        unsigned int length_of_a_kmer = 36;   







        // A private function for searching
        // sibling sub-tries for remaining
        // portion of the sequence.
        //
        // Parameter 1: char array of representing the remaining
        //              subsequence portion
        //
        // Parameter 2: length of the remaining portion
        //
        // Parameter 3: Trie_Node pointer indicating the node
        //              in the sub-trie from where the search
        //              process should start.
        bool Search_Sibling_Sub_Trie(const char*,int,Trie_Node*);




        // Private helper function for determining
        // the size of the trie:
        //
        // Parameter 1: the node from where to start
        //              the count.
        unsigned long int Count_Nodes(const Trie_Node*);


};

#endif