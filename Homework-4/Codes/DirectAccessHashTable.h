#ifndef DIRECTACCESSHASHTABLE_H_INCLUDED
#define DIRECTACCESSHASHTABLE_H_INCLUDED

#include<stdlib.h>
#include<string>
#include<iostream>
#include<math.h>

using namespace std;


/*

A simple class implemnting the
direct access hash table data
structure.


Author:
    Nazmul (mh2752@nau.edu)

*/



class DirectAccessHashTable
{

    public:       
        
        // Overloaded class ctor.
        //
        // Parameter 1: Radix base / Number of unique nucleotides (4 for A,C,G,T)
        //
        // Parameter 2: Max length of a sequence.
        //
        // Size of the hash table will depend on the above two
        // parameter values (size = pow(Parameter 1, Parameter 2)).
        DirectAccessHashTable(unsigned int,unsigned int);


        // Default dtor:
        ~DirectAccessHashTable();

        
        // Function for inserting a sequence into the hash table.
        //
        // Parameter 1: char pointer to the sequence array.
        //
        // Parameter 2: length of the char array.
        //
        // Parameter 3: Which K-th mer is it of the SARS-COV2 genome
        void Insert_Sequence_Into_DirectAccessHashTable(const char*,unsigned int,int);


        
        // Function for searching the given sequence fragment.
        //
        // Parameter 1: char pointer to the search key sequence array.
        //
        // Parameter 2: length of the char array.
        //
        // Parameter 3: true if search key found. false otherwise.
        //
        // Parameter 4: which kth-mer was the key of the SARS-COV2 genome
        void Search_Sequence_In_DirectAccessHashTable(const char*,unsigned int,bool&,int&);


        // Return the length of the hash table:
        unsigned long int Get_Size_Of_The_DirectAccessHashTable();



    private:

        // Base of the radix calculation
        unsigned int radix_base;

        // Max length of a sequence
        unsigned int max_sequence_length;

        // default length for any buffer array
        const unsigned int buffer_size = 256;

        // Size of the direct access hash table:
        unsigned long int hash_table_size = 0;

        // The actual direct access table:
        bool* hash_table = NULL;

        // Table for storing k-th mer info
        // (which k-th mer is it of the actual SARS genome):
        int* hash_table_kth_mer_info = NULL;


       
        // ----- A private member function for
        // calculating the radix of a given
        // sequence:
        //
        // Parameter 1: char array
        //              representing the sequence
        //
        // return type: A unsigned integer which is
        //              the radix of the given sequence
        unsigned long int Get_Radix_Of_The_Sequence(const char*);


         // Function for returning the radix value of a
        // single nucleotide.
        //
        // Parameter 1: the char code for the nucleotide.
        unsigned long int Get_Radix_Digit_Value(char);




        // ------ A priavte member function
        // for clearing a char buffer array
        //
        // Parameter 1: Pointer to the buffer
        //                char array
        void Clear_Buffer_Array(char*&);



        // ------ A priavte member function
        // for clearing a char buffer array
        //
        // Parameter 1: Pointer to the buffer
        //                char array
        // Parameter 2: Length of the given array
        void Clear_Buffer_Array_With_Length(char*&,unsigned int); 


};

#endif