#ifndef FASTAREADSET_CHAIN_H_INCLUDED
#define FASTAREADSET_CHAIN_H_INCLUDED
#include "LinkedList.h"
#include "math.h"

/*

This class implements the 'size limited'
hash table data structure with chaining 
method for resolving collisions.

*/


class FASTAreadset_Chain{


    public:

        // Default class Ctor()
        //
        // Default size of the hash table
        // will be set to 10000
        FASTAreadset_Chain();

        // Overloaded class Ctor()
        //
        // Parameter 1: Size of the hash table
        FASTAreadset_Chain(unsigned long int);

        // Default class Dtor()
        ~FASTAreadset_Chain();



        // ----- Function for reading in 
        // the 'read data set'.
        //
        // Parameter 1: Null terminated char array
        //              containing the file path.
        void Read_In_Read_Data_Set(const char*);

        
        
        // ------ Function for reading the 
        // 'Bacillus genome sequence'
        //
        // Parameter 1: Null terminated char array
        //                containing  the file path.
        void Read_In_Bacillus_Genome(const char*);


        // ------ Function for creating 16-mers 
        // from the 'Bacillus genome sequence'
        void Generate_Bacillus_16mers();

        
        
        // ------ Function for searching the given 16mer
        // in the direct access hash table.
        //
        // Parameter 1: Null terminated char array
        //              representing the 16mer to search
        //              for in the hash table
        //
        // return type: Returns boolean 'true' if the 16mer
        //              is found in the hash table. Returns
        //              'false' otherwise.
        bool Search_Hash_Table_For_Given_16mer(const char*);



        // ------ Function returning the size of
        // the hash table:
        unsigned long int Get_Hash_Table_Size();



        // ------ Function returning the total number
        // of collisions:
        unsigned long int Get_Total_Number_Of_Hash_Collisions();



        // ------ Function for returning the
        // number of unique key elements in
        // the hash table (Number of 'Chains'
        // stored in the hash table):
        unsigned long int Get_Num_Of_Unique_Hash_Keys();



        // ------- Function for getting the total
        // number of 16mers generated:
        unsigned long int Get_Total_Number_Of_16mers();


        // ------ Function for searching all
        // the 16mers in the hash table.
        //
        // Parameter 1: #of First 16mers to search
        //              for in the hash table. If set
        //              to zero, it will search for all
        //              the 16mers generated.
        unsigned long int Search_Hash_Table_For_16mers(unsigned long int);



    private:

        // Base of the radix:
        const unsigned int radix_base = 4;

        // Max length of a sequence:
        const unsigned int max_sequence_length = 16;

        // Length of a 16mer:
        const unsigned int length_of_a_16mer = 16;


        // Size of a buffer char array:
        const unsigned int buffer_size = 256;



        // A private unsigned int variable to
        // to store the size of the hash table:
        unsigned long int hash_table_size;


        // A private unsigned int variable to
        // keep a record of the total number
        // of collisions in the hash table:
        unsigned long int total_collisions;



        // An array of LinkedList type
        // pointers which is essentially
        // the hash table in question
        LinkedList **hash_table;


        // A private char pointer pointing to a char
        // array of size[1-by-(length_of_the_bacillus_genome)]
        // holding the full sequence of the Bacillus
        // genome:
        char *full_bacillus_genome;


        // A private unsigned int variable for
        // holding the length info (#of characters)
        // of the full Bacillus genome sequence:
        unsigned long int length_of_full_bacillus_genome;



        // A private linked list data structure
        // for holding all the 16mers generated
        // from the Bacillus genome sequence:
        LinkedList *all_bacillus_16mers;





        // ----- A private member function for
        // calculating the radix of a given
        // sequence:
        //
        // Parameter 1: char array
        //                representing the sequence
        //
        // return type: A unsigned integer which is
        //              the radix of the given sequence
        unsigned long int Get_Radix_Of_The_Sequence(const char*); 




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




        // Additional Helper Private Member Functions:
        unsigned long int Get_Radix_Digit_Value(char);









};


#endif