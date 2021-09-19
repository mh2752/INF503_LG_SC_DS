#ifndef SUFFIX_TRIE_H_INCLUDED
#define SUFFIX_TRIE_H_INCLUDED

#include "Trie_Node.h"
#include "Queue.h"


/*
Header file for the class
implementing the Suffix_Trie
data structure.

Author:
    Nazmul (mh2752@nau.edu)

*/


class Suffix_Trie
{

    public:

        // Default Ctor()
        Suffix_Trie();
        
        
        // Overloadded Ctor()
        //
        // Parameter 1: The subject sequence for building
        //              the trie.
        //
        // Parameter 2: Length of the subject sequence.
        Suffix_Trie(const char*,unsigned int);



        // default Dtor()
        ~Suffix_Trie();


        // Function for reading the subject sequence into
        // memory from input file and populating the
        // trie with the suffixes.
        //
        // Parameter 1: Path string to the input file.
        //
        // Parameter 2: Length of the path string.
        void Read_Subject_Sequence_From_File(const char*,int);



        // Function for reading Appendix B sequences
        // and search for them in the trie.
        //
        // Parameter 1: Path string to the file
        //
        // Parameter 2: Length of the path string
        void Read_And_Search_With_AppendixB(const char*,int);



        // Function for intserting a suffix sequence
        // into the Suffix_Trie.
        // 
        // Parameter 1: Char array representing the suffix
        //              sequence to be inserted into the
        //              trie.
        //
        // Parameter 2: Length of the sequence char array.
        void Insert_Into_Trie(const char*,unsigned int);




        // Function for searching a given sequence
        // in the suffix trie object.
        //
        // Parameter 1: Char array representing the given
        //              sequence.
        //
        // Parameter 2: Length of the given sequence.
        //
        // return: true if found, false otherwise.
        bool Search_In_Trie(const char*,unsigned int);

       


        // Function for generating and searching with
        // 5k randomly created 36mers from the SARS-COV2
        // genome sequence.
        unsigned int Generate_And_Search_For_5k_36mers();


        // Function for generating and searching with
        // 50k randomly created 36mers from the SARS-COV2
        // genome sequence.
        unsigned int Generate_And_Search_For_50k_36mers();


        // Function for generating and searching with
        // 100k randomly created 36mers from the SARS-COV2
        // genome sequence.
        unsigned int Generate_And_Search_For_100k_36mers();


        



        // Function to check whether the trie is empty
        // or not.
        //
        // return: true if empty, false otherwise.
        bool Is_Trie_Empty();


        // Function to obtain the size (#of nodes)
        // of the trie.
        unsigned long int Get_Trie_Size();



        // Function for testing with first 10 36mers
        void Test_With_First10_36mers();


    private:

        // Root of the trie:
        Trie_Node* root;

        // Dynamically allocated char array (1D)
        // for holding the SARS-COV2 genome sequence
        // read from the file:
        char* sars_full_genome;


        // Length of the full SARS-COV2
        // genome (without the header):
        unsigned long int sars_full_genome_length;


        // Number of characters in the header of the
        // SARS COV2 genome header file:
        unsigned int sars_genome_header_size = 38;


        // length of a buffer char array:
        unsigned int buffer_length = 256;

        // Length of a 36mer:
        unsigned int length_of_a_kmer = 36;


        // Function for clearing a buffer array:
        void Clear_Buffer_Array(char*&);        



        // Helper function for counting
        // trie nodes.
        unsigned long int Count_Nodes(const Trie_Node*);


        // Function for generating and inserting
        // all the suffixes from a sequence into
        // the trie.
        //
        // Parameter 1: The char array representing the sequence
        //
        // Parameter 2: Length of the sequence 
        void Generate_And_Insert_Sequence_Suffixes(const char*,unsigned int);

        

};

#endif