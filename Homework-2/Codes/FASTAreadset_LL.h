#ifndef FASTAREADSET_H_INCLUDED
#define FASTAREADSET_H_INCLUDED

#include "LinkedList.h"


class FASTAreadset_LL
{

    public:

        // Deafult Ctor()
        FASTAreadset_LL();

        // Overloaded constructor. 
        // 1st char* = pointer to the file path string (null terminated)
        // 2nd char* = pointer to the source file containing the anthrax genome data
        // 1st int = #of lines to read from the first source file      
        FASTAreadset_LL(char*&,char*&,int);

        // Copy Ctor()
        FASTAreadset_LL(const FASTAreadset_LL &external_frst);

        // Default Dtor()
        ~FASTAreadset_LL();

        // Read the lines from the source data file.
        void Read_From_Source_File();

        // Search for a given sequence fragment inside linked list held by this FASTAreadset_LL object
        void Search_For_Given_Seq(char*&,ListNode*&);

        // Return lengths of char arrays holding the source_file and anthrax_genome_file paths
        void Get_File_Path_Lengths(int&,int&)const; 

        // Generate all possible 50mers from the full anthrax genome data
        void Generate_Anthrax_Genome_50mers(); 

        // Search the specified number of 50mers in the FASTA seq readset
        void Search_FASTA_Seq_Frags_For_50mers(int); 

    private:


        // How many lines to read from the FASTA file 
        int num_of_lines_to_read;

        // Length of the full Bacillus Anthracis genome.
        // Includes terminating null character
        int banthrax_genome_full_length = 0; 


        // Maximum length of the buffer array:
        int max_buffer_length = 1024;

        // length of all FASTA sequence fragments
        int all_seq_frag_length = 50;


        // total number of 50mers generated:
        int total_50mers_generated = 0;


        // null terminated char arrays
        // holding file path information
        char* path_to_source_file;
        char* path_to_anthrax_genome_file;


        // The linked list objects:
        LinkedList* all_seq_fragments;
        LinkedList* banthrax_genome_50mers;

        // The array for holding the full length
        // Bacillus Anthracis genome code:
        char* banthrax_genome_full;

};

#endif
