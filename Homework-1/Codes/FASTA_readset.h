#ifndef FASTA_READSET_H_INCLUDED
#define FASTA_READSET_H_INCLUDED

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
using namespace std;


class FASTA_readset
{

    public:       
        
        // Ctor with input filepath to read the entire file
        FASTA_readset(const char*,int); // pointer to file path name, length of the file path name

        // Overloaded ctor with input filepath to read the specified number of lines from the file
        FASTA_readset(const char*,int,int); // pointer to file path name, length of the file path name, #of lines to read
       
        // Default dtor
        ~FASTA_readset();

        // Function for reading data from input file
        void Read_Data_From_File();
        
        // Function for computing and printing all stats
        void Compute_All_Stats();

        // Function for solving sub-problem A
        void Compute_A();

        // Function for solving sub-problem B
        void Compute_B();

        // Function for solving sub-problem C
        void Compute_C(); 

        // Function for sorting the read seq data
        void Sort_Seq_Data();     
    
   
   
    private:
       
        // Total number of sequences to read from the source
        // file into the memory.
        int total_read_size;

        // Length of each sequence
        int single_sequence_length;

        // Number of data sets
        int num_of_data_sets;
        
        
        // A 2D [size: 36M-by-50] char array for storing all the seuquences read
        char **all_genomic_sequence;

        
        // An integer array [size: 1-by-14] for storing the total read counts
        int *data_sets_total_reads;

        // An integer array for [size: 1-by-14] for storing the unique read counts
        int *data_sets_unique_read_counts;

        // An integer array [size: 1-by-14] for holding the current read-count values only
        int *data_sets_current_read_count;

        // An integer array [size: 14-by-4] for stroing letter frequency for each data set
        int **data_set_letter_frequency; // Serial: frequency of A,T,G,C


        // Path to the source data file
        char *file_path;


        // Assuming max length of the read header is 1024 Bytes (1KB)
        int max_read_header_length = 1024;
        
        
        // -------------------- Helper Member Functions -----------------------------------------------------
        
        // Will count the frequerncy of the letters A,T,G,C in the given sequence.
        void Count_Letter_Frequency(const char*,int&,int&,int&,int&); 
        
        // For determining alphabetical order of seniority between two sequences.
        bool Is_SeqA_Greater_Than_SeqB(const char*,const char*);         

};

#endif