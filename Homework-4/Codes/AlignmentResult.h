#ifndef ALIGNMENTRESULT_H_INCLUDED
#define ALIGNMENTRESULT_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <limits.h>

using namespace std;


/*

A simple class for holding the resulting
alignment info given by the Smith-Waterman
algorithm.

Author:
Nazmul (mh2752@nau.edu)

*/

class AlignmentResult
{
    public:

        // Default Class Ctor()
        AlignmentResult();


        // Overloaded Class Ctor()
        //
        // Parameter 1: an unsigned int variable represnting 
        //              the length values of the
        //              resulting char arrays
        AlignmentResult(unsigned int);


        // Default Class Dtor()
        ~AlignmentResult();


        // Function for setting the length
        // of the aligned portions.
        //
        // Parameter 1: Length of the aligned portion
        void Set_Aligned_Portion_Length(unsigned int);



        // Function fort setting the aligned
        // portion of the subject (e.g: SARS genome) 
        // sequence fragment.
        //
        // Parameter 1: a char array holding the fragment
        //              sequence portion to copy char values
        //              from.
        //
        // Parameter 2: an int variable representing the length
        //              of the given char array.
        void Set_Aligned_Subject_Sequence_Portion(const char*,const unsigned int);


        // Function fort setting the aligned
        // portion of the target sequence
        // fragment.
        //
        // Parameter 1: a char array holding the fragment
        //              sequence portion to copy char values
        //              from.
        //
        // Parameter 2: an int variable representing the length
        //              of the given char array.
        void Set_Aligned_Target_Sequence_Portion(const char*,const unsigned int);



        // Function fort setting the alignment
        // codes from the alignment process.
        //
        // Parameter 1: a char array holding the fragment
        //              sequence portion to copy char values
        //              from.
        //
        // Parameter 2: an int variable representing the length
        //              of the given char array.
        void Set_Alignment_Codes(const char*,const unsigned int);




        // Function for getting the aligned subject
        // sequence portion.
        //
        // Parameter 1: The array to copy the info to.
        //
        // Parameter 2: Length of the given array
        void Get_Aligned_Subject_Sequence_Portion(char*&,const unsigned int);


        // Function for getting the aligned target
        // sequence portion.
        //
        // Parameter 1: The array to copy the info to.
        //
        // Parameter 2: Length of the given array
        void Get_Aligned_Target_Sequence_Portion(char*&,const unsigned int);



        // Function for getting the alignment codes 
        //
        // Parameter 1: The array to copy the info to.
        //
        // Parameter 2: Length of the given array
        void Get_Alignment_Codes(char*&,const unsigned int);


        // Rerturns the aligned portion length:
        unsigned int Get_Aligned_portion_Length();


        // Print the contents:
        void Print_Results();

        

    private:


        // Pointer to the array holding the
        // aligned subject portion info.
        char* aligned_subject_portion;

        // Pointer to the array holding the
        // aligned target portion info.
        char* aligned_target_portion;


        // Pointer to the array holding the
        // alignment codes info.
        char* alignment_codes;


        // Length value for all
        // the arrays above.
        unsigned int aligned_portion_length;

};

#endif