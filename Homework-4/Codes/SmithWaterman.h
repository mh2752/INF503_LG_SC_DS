#ifndef SMITHWATERMAN_H_INCLUDED
#define SMITHWATERMAN_H_INCLUDED

#include "AlignmentResult.h"
#include <stdlib.h>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;




/*
    A simple class implementing the
    Smith-Waterman sequence alignment
    algorithm.


    We do NOT assume the strings/ char
    arrays passed as parameters are
    null terminated EXCEPT filepaths.

    Author:
        Nazmul (mh2752@nau.edu)

*/


class SmithWaterman{


    public:

        // Default Class Ctor()
        SmithWaterman();
        
        
        // Overloaded Class Ctor()
        //
        // Parameter 1: a 5x5 similarity scoring matrix
        //              for A, C, G, T, and a gap.
        SmithWaterman(int**&);

       
        // Default Class Dtor()
        ~SmithWaterman();


        // Function for reading the SARS-COV2 full
        // genome data from file into memory.
        //
        // Parameter 1: char array holding the path to
        //              the file containing the genome data.
        //
        // Parameter 2: Length of the file path array.
        void Read_SARS_Genome_Data(const char*,const unsigned int);




        // Function for setting target sequence to the  
        // given sequence. Once Result is obtained,
        // should free this memory.
        //
        // Parameter 1: The char array representing
        //              the target sequence.
        //
        // Parameter 2: Length of the given sequence.
        void Set_Target_Sequence(const char*,const unsigned int);



         // Function for aligning set target sequence
        // against the full genome to find
        // local match using Smith-Waterman
        // algorithm.       
        void Execute_Smith_Waterman_Alignment();


        // Function for obtaining the results
        // of the alignment. Frees the target
        // sequence memory at the end.
        //
        // Parameter 1: A 'pass-by-reference' int
        //              variable to hold the 
        //              alginment score.
        //
        // Parameter 2: A pointer to a passed-by-reference 
        //              'AlignmentResult' object
        void Obtain_Alignment_Results(int&,AlignmentResult*&);



        // Function For Testing against AppnedixB fragments:
        //
        // Parameter 1: Filepath to the text file containing
        //              the AppnedixB fragments.
        //
        // Parameter 2: Length of the filepath array
        void Test_Against_AppendixB_Fragments(const char*,unsigned int);

        // Function For Generating & Testing Against 1K Random Fragments:
        void Test_Against_Random_1K_Fragments();

        // Function For Generating & Testing Against 10K Random Fragments:
        void Test_Against_Random_10K_Fragments();

        // Function For Generating & Testing Against 100K Random Fragments:
        void Test_Against_Random_100K_Fragments();

        // Function For Generating & Testing Against 1 Million Random Fragments:
        void Test_Against_Random_1Million_Fragments();    


    private:

        // Size of the square similarity
        // score matrix:
        unsigned int similarity_score_matrix_size = 5;

        // Number of characters in the header of the
        // SARS COV2 genome header file:
        unsigned int sars_genome_header_size = 38;

        // char pointer to the
        // 1D array holding the
        // SARS genome sequence
        // in full.
        char* subject_sequence;


        // char pointer to the array
        // holding the given sequence
        // to be aligned against the
        // SARS genome sequence
        char* target_sequence;


        // Length of the SARS
        // sequence array.
        unsigned int subject_length;


        // Length of the target
        // sequence array.
        unsigned int target_length;



        // A 2D int array (5x5) holding the
        // similarity matrix info.
        //
        // Order of nucleotides in the
        // similarity matrix:
        //
        // Gap (index 4, represented by whitspace char) 
        // A (index 0)
        // C (index 1)
        // G (index 2)
        // T (index 3)    
        int** similarity_score_matrix;

        // Variables holding gap score 
        // from the similarity score matrix:
        int gap_score;


        // a 2D [target_length+1 by subject_length+1]
        // int array representing the path score
        // matrix.
        int** path_score;


        // An int variable to store the 
        // best path score.
        int best_path_score;


        // A 2D array [target_length+1 by subject_length+1] 
        // to save the path moves made to backtrack:
        char** path_moves;


        // int variables for holding
        // the row and col indices
        // of the best path score
        // in the path_score matrix.
        int best_score_row;
        int best_score_col;

        // Deafult size of a buffer
        // char array:
        unsigned int buffer_length = 256;

        // 3 string objects for stroing the
        // alignment codes:
        string tgt_aligned,sub_aligned,align_codes;



        // Private functions for clearing buffer arrays
        void Clear_Buffer_Array(char*&);
        void Clear_Buffer_Array_With_Length(char*&,unsigned int);

        
        // Private function for determining the max of
        // {
        //      D(i,j-1)+gap_score
        //      D(i-1,j)+gap_score
        //      D(i-1,j-1)+match_mismatch_score
        //      0
        // }
        //
        // Parameter 1: D(i,j-1)+gap_score value
        //
        // Parameter 2: D(i-1,j)+gap_score value
        //
        // Parameter 3: D(i-1,j-1)+match_mismatch_score
        //
        // Parameter 4: Cell which gave the max value
        //              1 = upper left cell
        //              2 = left cell
        //              3 = direct upper cell
        //              0 = No cell chosen. All were -ve.
        int Get_Max_Score(int,int,int,int&);



        // Private function for obtaining
        // the match/ mismatch score:
        //
        // Parameter 1: index of the character 
        //              in the target sequence
        //
        // Parameter 2: index of the character 
        //              in the subject sequence
        int Get_Match_Mismatch_Score(char,char);


        // Private function for getting the
        // index of characters from the 
        // similarity score matrix:
        int Get_Char_Index(char);




        // Private function for generating a
        // random 50-nucleotide sequence.
        //
        // Parameter 1: string object to receive
        //              the generated sequence
        void Generate_A_Random_Sequence(string&);


};

#endif
