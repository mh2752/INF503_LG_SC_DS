#include "SmithWaterman_Blast.h"

/*

Class definition for the class "SmithWaterman_Blast

Author:
    Nazmul (mh2752@nau.edu)

*/


// -------------------------------------------- Begin: Class Ctor & Dtor -------------------------------------------------------------------------
// Default Ctor()
SmithWaterman_Blast::SmithWaterman_Blast()
{
    // Initialize everything to
    // NULL or zero (as appropriate).
    subject_sequence = NULL;
    target_sequence = NULL;
    similarity_score_matrix = NULL;
    path_score = NULL;
    path_moves = NULL;

    sars_cov2_full_genome = NULL;
    sars_cov2_full_genome_length = 0;

    hash_table = NULL;

    subject_length = 0;
    target_length = 0;
    best_path_score = 0;

    // -ve indices to indicate that
    // algorithm hasn't been executed.
    best_score_row = -1;
    best_score_col = -1;

}


// Overloaded Ctor
SmithWaterman_Blast::SmithWaterman_Blast(int** &sim_matrix)
{
    // Initialize to NULL
    subject_sequence = NULL;
    target_sequence = NULL;
    path_score = NULL;
    path_moves = NULL;

    sars_cov2_full_genome = NULL;
    sars_cov2_full_genome_length = 0;

    // Initializing to zeros
    subject_length = 0;
    target_length = 0;
    best_path_score = 0;

    // -ve indices to indicate that
    // algorithm hasn't been executed.
    best_score_row = -1;
    best_score_col = -1;

    // Create and initialize the hash table:
    hash_table = new DirectAccessHashTable(radix_base,kmer_length);

    // Now, allocate memories for the similarity
    // score matrix and copy in the info:
    try
    {
        // Allocate memories:
        similarity_score_matrix = new int*[similarity_score_matrix_size];
        for(unsigned int i=0;i<similarity_score_matrix_size;i++)
        {
            similarity_score_matrix[i] = new int[similarity_score_matrix_size];
        }

        // Copy in the contents:
        for(unsigned int r=0;r<similarity_score_matrix_size;r++)
        {
            for(unsigned int c=0;c<similarity_score_matrix_size;c++)
            {
                similarity_score_matrix[r][c] = sim_matrix[r][c];
            }
        }


        // Update the gap_score member variable:
        gap_score = similarity_score_matrix[0][4];
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught In SmithWaterman Overloaded Constructor. Exiting Program Now."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    

}


// Default Dtor
SmithWaterman_Blast::~SmithWaterman_Blast()
{
    // De-allocate all dynamically allocated memories:   
    
    // Free subject sequence array
    if(subject_sequence != NULL)
    {
        delete[] subject_sequence;
    }    

    // Free target sequence array
    if(target_sequence != NULL)
    {
        delete[] target_sequence;
    }

    // Free the similarity score matrix:
    if(similarity_score_matrix!=NULL)
    {
        for(unsigned int i=0;i<similarity_score_matrix_size;i++)
        {
            delete[] similarity_score_matrix[i];
        }
        delete[] similarity_score_matrix;
    }

    // Free SARS genome array:
    if(sars_cov2_full_genome != NULL)
    {
        delete[] sars_cov2_full_genome;
    }

   
}


// -------------------------------------------- End: Class Ctor & Dtor ---------------------------------------------------------------------------







// -------------------------------------------- Begin: Class Public Member Functions --------------------------------------------------------------



void SmithWaterman_Blast::Read_SARS_Genome_Data(const char* file_path,const unsigned int file_path_length)
{
    // Check the file path validity
    if(file_path == NULL || file_path_length == 0)
    {
        cout<<"\n\t\tInvalid File Path Details Given. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        // Open ifstream to file
        ifstream stream_to_file;
        stream_to_file.open(file_path);

        if((!stream_to_file) || (!stream_to_file.is_open()))
        {
            cout<<"\n\t\tCouldnot Open Stream to Data File. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }

        
        // -------------------------------------------------------------------------------------------

        // Find out the size/ total length of the SARS
        // genome sequence:
        
        unsigned long int sequence_length_with_header = 0;
        unsigned long int sequence_length_with_out_header = 0;

        // A 256-length char buffer array:
        char* buffer_1;
        buffer_1 = new char[buffer_length];

        // A temporary string object:
        string temp_str;

        while(!stream_to_file.eof())
        {   
            // Clear the buffer first:
            Clear_Buffer_Array(buffer_1);
            stream_to_file>>buffer_1;

            // Clear the string:
            temp_str.clear();

            // Assign the buffer content
            // to the temp string:
            temp_str.assign(buffer_1);

            // Update length variable:
            sequence_length_with_header += (unsigned long int) temp_str.length();

        }
        // Close the stream:
        stream_to_file.close();

        // Update length of the 'without header' variable:
        sequence_length_with_out_header = sequence_length_with_header - (unsigned long int)sars_genome_header_size;

        
        //cout<<"Debug"<<endl;
        //cout<<"Sequence length with header = "<<sequence_length_with_header<<endl;
        //cout<<"Sequence length without header = "<<sequence_length_with_out_header<<endl;

        
        
        // ---------------------------------------------------------------------------------------------------------

        // Allocate required array memories:
        // Memory for initial array (includes header):
        char initial_array[sequence_length_with_header];
        sars_cov2_full_genome = new char[sequence_length_with_out_header];
        
        // Update the subject length member variable
        sars_cov2_full_genome_length = sequence_length_with_out_header;

        // -----------------------------------------------------------------------------------------------------------

         // Open another stream to the file:
        ifstream stream_to_file_2;
        stream_to_file_2.open(file_path);

        if((!stream_to_file_2) || (!stream_to_file_2.is_open()))
        {
            cout<<"\n\t\tCouldnot Again Open Stream to Data File. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }


        // Now, read in the contents into the
        // array this time
        unsigned int temp_str_length = 0;
        unsigned int array_start_index = 0;

        // Index indicating where in the
        // initial array the next character
        // should go:
        unsigned int initial_array_index = 0;

        while((!stream_to_file_2.eof()) && (initial_array_index < sequence_length_with_header))
        {
            Clear_Buffer_Array(buffer_1);
            stream_to_file_2>>buffer_1;

            // Clear temp string and assign
            // buffer content to it:
            temp_str.clear();
            temp_str.assign(buffer_1);

            temp_str_length = temp_str.length();

            // Copy the characters into the array
            // from the string:
            for(unsigned int index = 0; index < temp_str_length; index++,initial_array_index++)
            {
                initial_array[initial_array_index] = temp_str.at(index);
            }

        }
        // Close the stream:
        stream_to_file_2.close();

        //cout<<"Value of initial array index outside while loop"<<initial_array_index<<endl;

        // Copy from initial array into
        // final array (excluding header)
        for(unsigned int index = 0; index < sars_cov2_full_genome_length; index++)
        {
            sars_cov2_full_genome[index] = initial_array[index+sars_genome_header_size];
        }
       
        // Free buffer and initial arrays
        delete[] buffer_1;        

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Trying to Read From the File. Exiting Program."<<endl;
        cout<<"Exception Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    
}


void SmithWaterman_Blast::Generate_And_Load_SARS_Seeds()
{
    if(sars_cov2_full_genome == NULL ||  sars_cov2_full_genome_length == 0)
    {
        cout<<"\n\t\tEmpty SARS-COV2 Genome Array Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        char* genome_seed;
        genome_seed = new char[kmer_length];

       
        for(unsigned int i = 0; i+(kmer_length-1) < sars_cov2_full_genome_length; i++)
        {
            for(unsigned int j = 0; j < kmer_length; j++)
            {
                genome_seed[j] = sars_cov2_full_genome[i+j];
            }

            // Now insert this seed info into the direct access
            // hash table:
            hash_table->Insert_Sequence_Into_DirectAccessHashTable(genome_seed,kmer_length,(int)i);
           
        }
       

        // Free dynamic memory:
        delete[] genome_seed;
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Generating and Loading SARS Seeds. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    } 

}




void SmithWaterman_Blast::Set_Subject_Sequence(const char* given_sequence,unsigned int seq_length)
{
    if(subject_sequence != NULL || subject_length != 0)
    {
        delete[] subject_sequence;
        subject_sequence = NULL;
        subject_length = 0;
    }

    if(given_sequence == NULL || seq_length == 0)
    {
        cout<<"\n\t\tEmpty Sequence Given as the Subject. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    try
    {

        // Detect any invalid char:
        char temp;
        for(unsigned int i=0;i<seq_length;i++)
        {
            temp = given_sequence[i];
            if((temp!='A') && (temp!='C') && (temp!='G') && (temp!='T'))
            {
                cout<<"Invalid char in Sub Seq Detected"<<endl;
                exit(EXIT_FAILURE);
            }
        }



        // set length
        subject_length = seq_length;

        // Allocate memory:
        subject_sequence = new char[subject_length];

        // Set content
        for(unsigned int i=0; i < subject_length; i++)
        {
            subject_sequence[i] = given_sequence[i];
        }
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Trying to Set Subject Sequence. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    
    
}


void SmithWaterman_Blast::Set_Target_Sequence(const char* given_sequence,unsigned int seq_length)
{
    if(target_sequence != NULL || target_length != 0)
    {
        delete[] subject_sequence;
        subject_sequence = NULL;
        subject_length = 0;
    }

    if(given_sequence == NULL || seq_length == 0)
    {
        cout<<"\n\t\tEmpty Sequence Given as the Target. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    try
    {

        // Detect any invalid char:
        char temp;
        for(unsigned int i=0;i<seq_length;i++)
        {
            temp = given_sequence[i];
            if((temp!='A') && (temp!='C') && (temp!='G') && (temp!='T'))
            {
                cout<<"Invalid char in Tgt Seq Detected"<<endl;
                exit(EXIT_FAILURE);
            }
        }


        // set length
        target_length = seq_length;

        // Allocate memory:
        target_sequence = new char[target_length];

        // Set content
        for(unsigned int i=0; i < target_length; i++)
        {
            target_sequence[i] = given_sequence[i];
        }
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Trying to Set Target Sequence. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

}


void SmithWaterman_Blast::Execute_Smith_Waterman()
{
    if(subject_sequence == NULL || subject_length == 0)
    {
        cout<<"\n\t\tEmpty Subject Sequence Detected While Executing Smith Waterman. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    if(target_sequence == NULL || target_length == 0)
    {
        cout<<"\n\t\tEmpty Target Sequence Detected While Executing Smith Waterman. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        
         // Allocate and initialize path_score 
        // and path_moves memories:

        
        // path score
        path_score = new int*[target_length+1]; // +1 for gap
        
        for(unsigned int i =0; i< target_length+1; i++)
        {
            path_score[i] = new int[subject_length+1]; // +1 for gap

            // Initialize to zero:
            for(unsigned int j=0; j< subject_length+1; j++)
            {
                path_score[i][j] = 0;
            }
        }


        // path moves
        path_moves = new char*[target_length+1]; // +1 for gap
        
        for(unsigned int i=0; i< target_length+1; i++)
        {
            path_moves[i] = new char[subject_length+1];

            // Initialize to null:
            for(unsigned int j=0; j< subject_length+1; j++)
            {
                path_moves[i][j] = '\0';
            }

        }

                    // Must free these above 2D arrays at the end of this function.

        // ---------------------------------------------------------------------------------------


        // Now fill-up the path score matrix following
        // the rule for Smith-Waterman:
        
        
        // For holding match/ mismatch score
        int match_mismatch_score;

        // Cell-value at D(i,j-1)
        int left_cell_value;

        // Cell value at D(i-1,j)
        int upper_cell_value;

        // Characters from the target
        // and subject sequence:
        char target_char,subject_char;


        // Initializing best path score with
        // minimum int value:
        best_path_score = INT_MIN;


        // Cell which gave the max value
        // and path move was made accordingly:
        int cell_moved_from;
        int max_value;


        // Nested loops executing the algorithm:
         for(unsigned int row = 1; row < target_length+1; row++)
        {
            for(unsigned int col = 1; col < subject_length+1; col++)
            {
                target_char = target_sequence[row-1];
                subject_char = subject_sequence[col-1];

                // Obtaining the values according to
                // Smith-Waterman rules:
                match_mismatch_score = Get_Match_Mismatch_Score(target_char,subject_char)+path_score[row-1][col-1];
                left_cell_value = path_score[row][col-1]+gap_score;
                upper_cell_value = path_score[row-1][col]+gap_score;


                // Update the cell value at the current cell
                // according to the rule:
                max_value = Get_Max_Score(match_mismatch_score,left_cell_value,upper_cell_value,cell_moved_from);
                path_score[row][col] = max_value;
                
                // Record the cell move:
                if(cell_moved_from!=0)
                {
                    if(cell_moved_from==1)
                    {
                        // upper left was chosen
                        path_moves[row][col] = '1';

                    }
                    else if(cell_moved_from==2)
                    {
                        // left was chosen
                        path_moves[row][col] = '2';
                    }
                    else if(cell_moved_from==3)
                    {
                        // upper was chosen
                        path_moves[row][col] = '3';
                    }
                    else
                    {
                        cout<<"\n\t\tInvalid Cell Moved From Value. Exiting Porgram."<<endl;
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    // Do nothing. Path move is already initialized to null character.
                }

                if(path_score[row][col]>best_path_score)
                {
                    best_path_score = path_score[row][col];

                    // Save the row and col locations:
                    best_score_row = row;
                    best_score_col = col;
                }
            }
        }



        // ----------------------------------- Tracing back to get alignment info --------------------------------------
        
        // Utility variables:
        char move_made;
        char tgt_char;
        char sub_char;

        // Resetting strings:
        tgt_aligned.clear();
        sub_aligned.clear();
        align_codes.clear();
        

        for(int row = best_score_row, col = best_score_col; (row>=1) && (col>=1) && (path_moves[row][col]!='\0'); )
        {
            move_made = path_moves[row][col];

            if(move_made == '1') // Diagonal move was made
            {                

                // Get the characters from target and subject sequences:
                tgt_char = target_sequence[row-1];
                sub_char = subject_sequence[col-1];

                // Push the chars to the string objects:
                tgt_aligned.push_back(tgt_char);
                sub_aligned.push_back(sub_char);

                if(tgt_char == sub_char)
                {
                    align_codes.push_back('|');
                }
                else
                {
                    align_codes.push_back('X');
                }

                // update row and col values to move to the
                // upper left cell:
                row--;
                col--;
            }

            else if(move_made == '2') // Left move that introduces a gap
            {
                tgt_char = '_'; // Rerpresenting gap with underscore
                sub_char = subject_sequence[col-1];

                // Push the chars to the string objects:
                tgt_aligned.push_back(tgt_char);
                sub_aligned.push_back(sub_char);

                // Push whitespace to align_codes:
                align_codes.push_back(' ');

                // Update col value to move to the left cell:
                col--;
            }

            else if(move_made == '3') // Upper move that introduces a gap
            {
                tgt_char = '_'; // Rerpresenting gap with underscore
                sub_char = subject_sequence[col-1];

                // Push the chars to the string objects:
                tgt_aligned.push_back(tgt_char);
                sub_aligned.push_back(sub_char);

                // Push whitespace to align_codes:
                align_codes.push_back(' ');

                // Update row value to move to upper cell:
                row--;
            }

            else // move_made == 0. Break out of the loop. (I wonder if control can ever reach this block????)
            {
                break;
            }

        }


        // --------------- Releasing path_scores & path_moves array memories -------------------------------

        for(unsigned int i=0; i < target_length+1; i++)
        {
            delete[] path_score[i];
        }
        delete[] path_score;
        path_score = NULL;

        for(unsigned int i=0; i < target_length+1; i++)
        {
            delete[] path_moves[i];
        }
        delete[] path_moves;
        path_moves = NULL;

        // Freeing target sequence:
        delete[] target_sequence;
        target_sequence = NULL;
        target_length = 0;

        // Freeing subject sequence:
        delete[] subject_sequence;
        subject_sequence = NULL;
        subject_length = 0;
        
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Trying to Execute Smith-Waterman. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    
}



void SmithWaterman_Blast::Obtain_Alignment_Results(int& score,AlignmentResult* &result)
{
    // Send the info inside the appropriate 
    // passed-by-reference variables.
    
    // update the score variable:
    score = best_path_score;    


    // Obtain char arrays for the strings:
    const unsigned int length_for_arrays = (const unsigned int) tgt_aligned.length(); // tgt_aligned, sub_aligned, align_codes are same length
    unsigned int length_for_result = (unsigned int)tgt_aligned.length();


    // Reverse the strings' content:
    string tgt_aligned2,sub_aligned2,align_codes2;

    // Utility variables:
    char a1,a2,a3;

    for(int i= ((int)length_for_arrays-1); i >= 0; i--)
    {
        
        tgt_aligned2.push_back(tgt_aligned.at(i));
        sub_aligned2.push_back(sub_aligned.at(i));
        align_codes2.push_back(align_codes.at(i));
    }

  

    char* tgt_aligned_array;
    char* sub_aligned_array;
    char* aligned_codes_array;

    tgt_aligned_array = new char[length_for_arrays+1]; // +1 for terminating null character
    sub_aligned_array = new char[length_for_arrays+1]; // +1 for terminating null character
    aligned_codes_array = new char[length_for_arrays+1]; // +1 for terminating null character

    

    strcpy(tgt_aligned_array,tgt_aligned2.c_str());
    strcpy(sub_aligned_array,sub_aligned2.c_str());
    strcpy(aligned_codes_array,align_codes2.c_str());


    result->Set_Aligned_Portion_Length(length_for_result);
    result->Set_Aligned_Target_Sequence_Portion(tgt_aligned_array,length_for_arrays);
    result->Set_Aligned_Subject_Sequence_Portion(sub_aligned_array,length_for_arrays);
    result->Set_Alignment_Codes(aligned_codes_array,length_for_arrays);

    

    // Free dynamic arrays:
    delete[] tgt_aligned_array;
    delete[] sub_aligned_array;
    delete[] aligned_codes_array;
    
}


bool SmithWaterman_Blast::Generate_And_Search_Sequence_Kmers_AppendixB(const char* given_sequence,unsigned int given_sequence_length)
{
    // Array for holding the sequence kmers:
    unsigned int number_of_kmers = (given_sequence_length - kmer_length + 1);
    char** sequence_kmers;
    
    sequence_kmers = new char*[number_of_kmers];

    for(unsigned int i=0; i < number_of_kmers; i++)
    {
        sequence_kmers[i] = new char[kmer_length];
    }


    // Generate the kmers:
    for(unsigned int i=0; i+(kmer_length-1) < given_sequence_length; i++)
    {
        for(unsigned int j=0; j < kmer_length; j++)
        {
            sequence_kmers[i][j] = given_sequence[j];
        }
    }



    // --------------------- Search phase ----------------------------

    // Utility variables
    char* temp_kmer;
    temp_kmer = NULL;

    char* genome_kmer_expanded;
    genome_kmer_expanded = NULL;

    unsigned int expanded_kmer_length = 0;

    bool hash_search_result; // true if found in hash table, false otherwise
    int sars_kmer_serial; // Indicates which k-th mer from sars genome it is.
    bool final_result = false; // By default, we assume the sequence is not present.

    for(unsigned int i=0; i< number_of_kmers; i++)
    {
        // Allocate memory
        temp_kmer = new char[kmer_length];

        // copy kmer content:
        for(unsigned int j=0; j < kmer_length; j++)
        {
            temp_kmer[j] = sequence_kmers[i][j];
        }

        // Query the hash table about this k-mer:
        hash_table->Search_Sequence_In_DirectAccessHashTable(temp_kmer,kmer_length,hash_search_result,sars_kmer_serial);


        if(hash_search_result == true)
        {


                // ------------------------------ Expanding Genome Kmer ---------------------------------------

                if(sars_kmer_serial == (sars_cov2_full_genome_length-kmer_length)) // the rightmost kmer
                {
                    // take 90 from left, take this, take 10 from right
                    expanded_kmer_length = 101; // 89+1+10

                    genome_kmer_expanded = new char[expanded_kmer_length];

                    // taking 89 from left:
                    for(unsigned int i = 90; i>0; i--)
                    {
                        genome_kmer_expanded[90-i] = sars_cov2_full_genome[sars_kmer_serial-i];
                    }

                    // taking this one:
                    genome_kmer_expanded[90] = sars_cov2_full_genome[sars_kmer_serial];

                    // take 10 from right:
                    for(unsigned int i=1; i<11; i++)
                    {
                        genome_kmer_expanded[90+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                    }

                    
                    
                }

                else if(sars_kmer_serial == 0) // leftmost kmer
                {
                    // take this and 100 from right

                    expanded_kmer_length = 101; // 1+100

                    genome_kmer_expanded = new char[expanded_kmer_length];

                    for(unsigned int i=0;i<101;i++)
                    {
                        genome_kmer_expanded[i] = sars_cov2_full_genome[i];
                    }

                }

                else
                {
                    expanded_kmer_length = 101;
                    genome_kmer_expanded = new char[expanded_kmer_length];                    
                    
                    unsigned int available_on_left = sars_kmer_serial;
                    unsigned int available_on_right = (sars_cov2_full_genome_length - available_on_left -1);                   

                   if(available_on_left>=50 && available_on_right>=50)
                   {
                       // take 50 from left, take this, take 50 from right
                        for(unsigned int i=50; i>0; i--)
                        {
                            genome_kmer_expanded[50-i] = sars_cov2_full_genome[sars_kmer_serial-i];
                        }

                        // take this one
                        genome_kmer_expanded[50] = sars_cov2_full_genome[sars_kmer_serial];

                        // take 49 from right
                        for(unsigned int i=1;i<51;i++)
                        {
                            genome_kmer_expanded[50+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                        }

                   }
                   
                   else if(available_on_right<50) // we surely have more than 101 on left
                   {
                       int take_from_right = Get_Min_Among_Two(available_on_right,50);
                       int take_from_left = (101-take_from_right-1);

                       // taking from left:
                       for(unsigned int i=0; i<take_from_left; i++)
                       {
                           genome_kmer_expanded[i] = sars_cov2_full_genome[sars_kmer_serial - take_from_left];
                       }

                       // taking this one:
                       genome_kmer_expanded[take_from_left] = sars_cov2_full_genome[sars_kmer_serial];

                       // take from right:
                       for(unsigned int i=1;i<take_from_right+1;i++)
                       {
                           genome_kmer_expanded[take_from_left+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                       }
                   }
                   else if (available_on_left<50) // we surely have more than 101 on right
                   {
                       int take_from_left = Get_Min_Among_Two(available_on_left,50);
                       int take_from_right = (101-take_from_left-1);


                       // taking from left:
                       for(unsigned int i=0; i<take_from_left; i++)
                       {
                           genome_kmer_expanded[i] = sars_cov2_full_genome[sars_kmer_serial - take_from_left];
                       }

                       // taking this one:
                       genome_kmer_expanded[take_from_left] = sars_cov2_full_genome[sars_kmer_serial];

                       // take from right:
                       for(unsigned int i=1;i<take_from_right+1;i++)
                       {
                           genome_kmer_expanded[take_from_left+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                       }

                   }                 
                }


            // -----------------------------------------------------------------------------------------------------------------------            


            // perform smith-waterman
               
               // - Set subject & target sequences
               Set_Subject_Sequence(genome_kmer_expanded,expanded_kmer_length);
               Set_Target_Sequence(given_sequence,given_sequence_length);
               
               // - Execute Smith-Waterman
               Execute_Smith_Waterman();
               
               // - Obtain result
               int score;
               AlignmentResult* alignment_result;
               alignment_result = new AlignmentResult;
               Obtain_Alignment_Results(score,alignment_result);

               // Printing Alignment:
               char* seq_for_printing;
               seq_for_printing = new char[given_sequence_length+1];
               
               for(unsigned int i=0;i<given_sequence_length;i++)
               {
                   seq_for_printing[i] = given_sequence[i];
               }
               seq_for_printing[given_sequence_length] = '\0';

               cout<<"\n\t\tGiven Target Sequence: "<<seq_for_printing<<endl;
               alignment_result->Print_Results();

            // if aligned (score == 2*sequence length), final_result = true, else final_result = false
            if(score == 2*(given_sequence_length))
            {
                final_result = true;
            }
            else
            {
                final_result = false;
            }

            
            // Free dynamic memories
            delete[] temp_kmer;
            temp_kmer = NULL;

            delete[] genome_kmer_expanded;
            genome_kmer_expanded = NULL;

            delete[] seq_for_printing;
            seq_for_printing = NULL;

            alignment_result->~AlignmentResult();


            // break from the loop. Only expanding  one seed.
            break;
        }

        // free dynamic memory:
       if(temp_kmer!=NULL)
       {
            delete[] temp_kmer;
            temp_kmer = NULL;
       }

    }

    // Free all dynamic memories

    // free sequence k-mers:
    for(unsigned int i=0; i < number_of_kmers; i++)
    {
        delete[] sequence_kmers[i];
    }
    delete[] sequence_kmers;
    sequence_kmers = NULL;

    // return result from alignment
    return final_result;
}






bool SmithWaterman_Blast::Generate_And_Search_Sequence_Kmers_General(const char* given_sequence,unsigned int given_sequence_length)
{
    // Array for holding the sequence kmers:
    unsigned int number_of_kmers = (given_sequence_length - kmer_length + 1);
    char** sequence_kmers;
    
    sequence_kmers = new char*[number_of_kmers];

    for(unsigned int i=0; i < number_of_kmers; i++)
    {
        sequence_kmers[i] = new char[kmer_length];
    }


    // Generate the kmers:
    for(unsigned int i=0; i+(kmer_length-1) < given_sequence_length; i++)
    {
        for(unsigned int j=0; j < kmer_length; j++)
        {
            sequence_kmers[i][j] = given_sequence[j];
        }
    }



    // --------------------- Search phase ----------------------------

    // Utility variables
    char* temp_kmer;
    temp_kmer = NULL;

    char* genome_kmer_expanded;
    genome_kmer_expanded = NULL;

    unsigned int expanded_kmer_length = 0;

    bool hash_search_result; // true if found in hash table, false otherwise
    int sars_kmer_serial; // Indicates which k-th mer from sars genome it is.
    bool final_result = false; // By default, we assume the sequence is not present.

    //how many were not found:
    int not_found = 0;

    for(unsigned int i=0; i< number_of_kmers; i++)
    {
        // Allocate memory
        temp_kmer = new char[kmer_length];

        // copy kmer content:
        for(unsigned int j=0; j < kmer_length; j++)
        {
            temp_kmer[j] = sequence_kmers[i][j];
        }

        // Query the hash table about this k-mer:
        hash_table->Search_Sequence_In_DirectAccessHashTable(temp_kmer,kmer_length,hash_search_result,sars_kmer_serial);


        if(hash_search_result == true)
        {


                // ------------------------------ Expanding Genome Kmer ---------------------------------------

                if(sars_kmer_serial == (sars_cov2_full_genome_length-kmer_length)) // the rightmost kmer (1)
                {
                    // take 90 from left, take this, take 10 from right
                    expanded_kmer_length = 101; // 90+1+10

                    genome_kmer_expanded = new char[expanded_kmer_length];

                    // taking 90 from left:
                    for(unsigned int i = 90; i>0; i--)
                    {
                        genome_kmer_expanded[90-i] = sars_cov2_full_genome[sars_kmer_serial-i];
                    }

                    // taking this one:
                    genome_kmer_expanded[90] = sars_cov2_full_genome[sars_kmer_serial];

                    // take 10 from right:
                    for(unsigned int i=1; i<11; i++)
                    {
                        genome_kmer_expanded[90+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                    }
                    
                }

                else if(sars_kmer_serial == 0) // leftmost kmer (2)
                {
                    // take this and 100 from right

                    expanded_kmer_length = 101; // 1+99

                    genome_kmer_expanded = new char[expanded_kmer_length];

                    for(unsigned int i=0;i<101;i++)
                    {
                        genome_kmer_expanded[i] = sars_cov2_full_genome[i];
                    }                   

                }

                else
                {
                    expanded_kmer_length = 101;
                    genome_kmer_expanded = new char[expanded_kmer_length];                    
                    
                    unsigned int available_on_left = sars_kmer_serial;
                    unsigned int available_on_right = (sars_cov2_full_genome_length - available_on_left -1);                   

                   if(available_on_left>=50 && available_on_right>=50) // (3)
                   {
                       // take 50 from left, take this, take 50 from right
                        for(unsigned int i=50; i>0; i--)
                        {
                            genome_kmer_expanded[50-i] = sars_cov2_full_genome[sars_kmer_serial-i];
                        }

                        // take this one
                        genome_kmer_expanded[50] = sars_cov2_full_genome[sars_kmer_serial];

                        // take 50 from right
                        for(unsigned int i=1;i<51;i++)
                        {
                            genome_kmer_expanded[50+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                        }                       

                   }
                   
                   else if(available_on_right<50) // we surely have more than 101 on left (4)
                   {
                       int take_from_right = Get_Min_Among_Two(available_on_right,50);
                       int take_from_left = (101-take_from_right-1);

                       // taking from left:
                       for(unsigned int i=0; i<take_from_left; i++)
                       {
                           genome_kmer_expanded[i] = sars_cov2_full_genome[sars_kmer_serial - take_from_left];
                       }

                       // taking this one:
                       genome_kmer_expanded[take_from_left] = sars_cov2_full_genome[sars_kmer_serial];

                       // take from right:
                       for(unsigned int i=1;i<take_from_right+1;i++)
                       {
                           genome_kmer_expanded[take_from_left+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                       }
                      
                   }
                   else if (available_on_left<50) // we surely have more than 101 on right (5)
                   {
                       int take_from_left = Get_Min_Among_Two(available_on_left,50);
                       int take_from_right = (101-take_from_left);


                       // taking from left:
                       for(unsigned int i=0; i<take_from_left; i++)
                       {
                           genome_kmer_expanded[i] = sars_cov2_full_genome[sars_kmer_serial - take_from_left];
                       }

                       // taking this one:
                       genome_kmer_expanded[take_from_left] = sars_cov2_full_genome[sars_kmer_serial];

                       // take from right:
                       for(unsigned int i=1;i<take_from_right+1;i++)
                       {
                           genome_kmer_expanded[take_from_left+i] = sars_cov2_full_genome[sars_kmer_serial+i];
                       }                      

                   }                 
                }


            // -----------------------------------------------------------------------------------------------------------------------            


            // perform smith-waterman
               
               // - Set subject & target sequences
               Set_Subject_Sequence(genome_kmer_expanded,expanded_kmer_length);
               Set_Target_Sequence(given_sequence,given_sequence_length);
               
               // - Execute Smith-Waterman
               Execute_Smith_Waterman();
               
               // - Obtain result
               int score;
               AlignmentResult* alignment_result;
               alignment_result = new AlignmentResult;
               Obtain_Alignment_Results(score,alignment_result);

              

            // if aligned (score == 2*sequence length), final_result = true, else final_result = false
            if(score == 2*(given_sequence_length))
            {
                final_result = true;
            }
            else
            {
                final_result = false;        

            }

            
            // Free dynamic memories
            delete[] temp_kmer;
            temp_kmer = NULL;

            delete[] genome_kmer_expanded;
            genome_kmer_expanded = NULL;            

            alignment_result->~AlignmentResult();


            // break from the loop. Only expanding  one seed.
            break;
        }

        // free dynamic memory:
       if(temp_kmer!=NULL)
       {
            delete[] temp_kmer;
            temp_kmer = NULL;
       }

    }



    // Free all dynamic memories

    // free sequence k-mers:
    for(unsigned int i=0; i < number_of_kmers; i++)
    {
        delete[] sequence_kmers[i];
    }
    delete[] sequence_kmers;
    sequence_kmers = NULL;

    // return result from alignment
    return final_result;
}




void SmithWaterman_Blast::Test_Against_AppendixB_Fragments(const char* filepath,unsigned int path_length)
{
    if(filepath==NULL || path_length == 0)
    {
        cout<<"\n\t\tNull Filepath Received in Testing Against AppendixB. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    // Open the file stream:
    ifstream stream_to_file;
    stream_to_file.open(filepath);

    if(!stream_to_file.is_open() || (!stream_to_file))
    {
        cout<<"\n\t\tFailure to Open Stream to File While Testing Against AppendixB. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    
    // Create and clear buffer arrays:
    char* buffer_array_header;
    buffer_array_header =  new char[buffer_length];

    char* buffer_array_sequence;
    buffer_array_sequence = new char[buffer_length];

    Clear_Buffer_Array(buffer_array_header);
    Clear_Buffer_Array(buffer_array_sequence);


    // Pointer for the sequence char array:
    char* seq_array;
    // Length of the seq array:
    unsigned int seq_length;

    // A temporary string object:
    string str_temp;


    // Tested & Found Counters:
    int test_seqs = 0;
    int found_seqs = 0;
    


    while(!stream_to_file.eof())
    {        
        Clear_Buffer_Array(buffer_array_header);
        Clear_Buffer_Array(buffer_array_sequence);

        stream_to_file>>buffer_array_header;
        stream_to_file>>buffer_array_sequence;

        str_temp.clear();
        str_temp.assign(buffer_array_sequence);

        seq_length = str_temp.length();
        seq_array = new char[seq_length+1];
        strcpy(seq_array,str_temp.c_str());        
        test_seqs++;

        
        bool search_result = Generate_And_Search_Sequence_Kmers_AppendixB(seq_array,seq_length);        

        if(search_result == true)
        {
            found_seqs++;
        }

        // Free dynamic memory:
        delete[] seq_array;
        
    } // while ends


    // Free buffers:
    delete[] buffer_array_header;
    delete[] buffer_array_sequence;


    cout<<"\nNumber of Sequences Searched For = "<<test_seqs<<endl;
    cout<<"\nNumber of Sequences Found = "<<found_seqs<<endl;

}






void SmithWaterman_Blast::Test_Against_Random_1K_Fragments()
{   

    // string object to hold randomly
    // generated sequence:
    string random_sequence;

    // count variable to record number of found
    // sequences:
    int found_sequences = 0;

    // Array pointer to the array
    // representing the sequence:
    char* sequence_array;

    for(int i=0; i< 1000; i++)
    {
        // Clear the string:
        random_sequence.clear();

        // Obtain a randomly generated
        // sequence:
        Generate_A_Random_Sequence(random_sequence);

        // Allocate array memory:
        sequence_array = new char[random_sequence.length()+1];

        // Copy string content:
        strcpy(sequence_array,random_sequence.c_str());

        
        bool search_result = Generate_And_Search_Sequence_Kmers_General(sequence_array,(const unsigned int)random_sequence.length());
        
       
        if(search_result == true)
        {
            found_sequences++;

        }

        // free dynamic array:
        delete[] sequence_array;       
        
    }


    cout<<"\n\t\tOut of 1,000 Random Sequences, "<<found_sequences<<" Were Found in the SARS-COV2 Genome Using Smith-Waterman."<<endl;

}



void SmithWaterman_Blast::Test_Against_Random_10K_Fragments()
{   

    // string object to hold randomly
    // generated sequence:
    string random_sequence;

    
    // count variable to record number of found
    // sequences:
    int found_sequences = 0;

    // Array pointer to the array
    // representing the sequence:
    char* sequence_array;

    for(int i=0; i< 10000; i++)
    {
        // Clear the string:
        random_sequence.clear();

        // Obtain a randomly generated
        // sequence:
        Generate_A_Random_Sequence(random_sequence);

        // Allocate array memory:
        sequence_array = new char[random_sequence.length()+1];

        // Copy string content:
        strcpy(sequence_array,random_sequence.c_str());

        
        bool search_result = Generate_And_Search_Sequence_Kmers_General(sequence_array,(const unsigned int)random_sequence.length());
        
       
        if(search_result == true)
        {
            found_sequences++;

        }

        // free dynamic array:
        delete[] sequence_array;
        
        
    }


    cout<<"\n\t\tOut of 10,000 Random Sequences, "<<found_sequences<<" Were Found in the SARS-COV2 Genome Using Smith-Waterman."<<endl;

}



void SmithWaterman_Blast::Test_Against_Random_100K_Fragments()
{   

    // string object to hold randomly
    // generated sequence:
    string random_sequence;

    

    // count variable to record number of found
    // sequences:
    int found_sequences = 0;

    // Array pointer to the array
    // representing the sequence:
    char* sequence_array;

    for(int i=0; i< 100000; i++)
    {
        // Clear the string:
        random_sequence.clear();

        // Obtain a randomly generated
        // sequence:
        Generate_A_Random_Sequence(random_sequence);

        // Allocate array memory:
        sequence_array = new char[random_sequence.length()+1];

        // Copy string content:
        strcpy(sequence_array,random_sequence.c_str());

        
        bool search_result = Generate_And_Search_Sequence_Kmers_General(sequence_array,(const unsigned int)random_sequence.length());
        
       
        if(search_result == true)
        {
            found_sequences++;

        }

        // free dynamic array:
        delete[] sequence_array;
       
        
    }


    cout<<"\n\t\tOut of 100,000 Random Sequences, "<<found_sequences<<" Were Found in the SARS-COV2 Genome Using Smith-Waterman."<<endl;

}

void SmithWaterman_Blast::Test_Against_Random_1Million_Fragments()
{   

    // string object to hold randomly
    // generated sequence:
    string random_sequence;

     

    // count variable to record number of found
    // sequences:
    int found_sequences = 0;

    // Array pointer to the array
    // representing the sequence:
    char* sequence_array;

    for(int i=0; i< 1000000; i++)
    {
        // Clear the string:
        random_sequence.clear();

        // Obtain a randomly generated
        // sequence:
        Generate_A_Random_Sequence(random_sequence);

        // Allocate array memory:
        sequence_array = new char[random_sequence.length()+1];

        // Copy string content:
        strcpy(sequence_array,random_sequence.c_str());

        
        bool search_result = Generate_And_Search_Sequence_Kmers_General(sequence_array,(const unsigned int)random_sequence.length());
        
       
        if(search_result == true)
        {
            found_sequences++;

        }

        // free dynamic array:
        delete[] sequence_array;
        
        
    }


    cout<<"\n\t\tOut of 1,000,000 Random Sequences, "<<found_sequences<<" Were Found in the SARS-COV2 Genome Using Smith-Waterman."<<endl;

}




void SmithWaterman_Blast::Test_Against_100K_Random_SARS_Fragments()
{ 


    if(sars_cov2_full_genome_length <= 0)
    {
        cout<<"\n\t\tInvalid Length of SARS Genome Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    int num_of_steps = 100000;
    int random_index;
    int mod_value = (int)sars_cov2_full_genome_length;

    bool search_result = false;
    char* temp_seq;
    unsigned int seq_length = 50;

    unsigned int num_of_found_seqs = 0;


    while(num_of_steps>0)
    {
        random_index = rand() % mod_value;

        if(random_index > sars_cov2_full_genome_length-50) // not a valid index
        {
            // do nothing
        }
        else
        {
            // buffer for a single char:
            char char_buffer;

            // Allocate memories:
            temp_seq = new char[seq_length];

            // Chose 50 chars to right of this index (including this one)
            for(unsigned int i=random_index; i < random_index+50; i++)
            {
                // Get the char
                char_buffer = sars_cov2_full_genome[i];

                // copy it in the temp_seq array
                temp_seq[i - random_index] = char_buffer;
            }

            // We got the sequence. Now search for it
            search_result = Generate_And_Search_Sequence_Kmers_General(temp_seq,seq_length);

            if(search_result == true)
            {
                num_of_found_seqs++;
            }


            // Release dynamic memories:
            delete[] temp_seq;
            temp_seq = NULL;

            // Decrease sentinel value:
            num_of_steps--;
        }
    }


    // Printing stats:
    cout<<"\n\t\tOut of 100,000 Randomly Selected Fragments (No Mutation) from SARS-COV2 Full Genome, We Found = "<<num_of_found_seqs<<" Sequences"<<endl;

}



void SmithWaterman_Blast::Test_Against_100K_Random_Mutated_SARS_Fragments()
{ 


    if(sars_cov2_full_genome_length <= 0)
    {
        cout<<"\n\t\tInvalid Length of SARS Genome Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    int num_of_steps = 100000;
    int random_index;
    int mod_value = (int)sars_cov2_full_genome_length;

    bool search_result = false;
    char* temp_seq;
    unsigned int seq_length = 50;

    unsigned int num_of_found_seqs = 0;

    int mutation_probability;
    int mutated_char_choice;


    while(num_of_steps>0)
    {
        random_index = rand() % mod_value;

        if(random_index > sars_cov2_full_genome_length-50) // not a valid index
        {
            // do nothing
        }
        else
        {
            // buffer for a single char:
            char char_buffer;

            // Allocate memories:
            temp_seq = new char[seq_length];

            // Chose 50 chars to right of this index (including this one)
            for(unsigned int i=random_index; i < random_index+50; i++)
            {
                // Get the char
                char_buffer = sars_cov2_full_genome[i];

                // Check if we want to mutate this character:
                mutation_probability = rand() % 100;

                if(mutation_probability>=0 && mutation_probability <= 4) // we mutate this char
                {                    

                    if(char_buffer == 'A') // mutate to C/ G/ T
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'C';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'G';
                        }
                        else
                        {
                            char_buffer = 'T';
                        }
                    }

                    else if(char_buffer == 'C')
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'A';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'G';
                        }
                        else
                        {
                            char_buffer = 'T';
                        }
                    }

                    else if(char_buffer == 'G')
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'A';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'C';
                        }
                        else
                        {
                            char_buffer = 'T';
                        }
                    }

                    else if(char_buffer == 'T')
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'A';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'C';
                        }
                        else
                        {
                            char_buffer = 'G';
                        }
                    }

                }

                // copy it in the temp_seq array
                temp_seq[i - random_index] = char_buffer;
            }

            // We got the sequence. Now search for it
            search_result = Generate_And_Search_Sequence_Kmers_General(temp_seq,seq_length);

            if(search_result == true)
            {
                num_of_found_seqs++;
            }


            // Release dynamic memories:
            delete[] temp_seq;
            temp_seq = NULL;

            // Decrease sentinel value:
            num_of_steps--;
        }
    }


    // Printing stats:
    cout<<"\n\t\tOut of 100,000 Randomly Selected Fragments (With 5% Mutation) from SARS-COV2 Full Genome, We Found = "<<num_of_found_seqs<<" Sequences"<<endl;

}




// -------------------------------------------- End: Class Public Member Functions ----------------------------------------------------------------







// -------------------------------------------- Begin: Class Private Member Functions --------------------------------------------------------------


unsigned int SmithWaterman_Blast::Get_Min_Among_Two(unsigned int a, unsigned int b)
{
    if(a<=b)
    {
        return a;
    }
    else
    {
        return b;
    }
}



void SmithWaterman_Blast::Clear_Buffer_Array(char* &given_buffer)
{
    for(unsigned int i=0;i<buffer_length;i++)
    {
        given_buffer[i] = '\0';
    }
}


void SmithWaterman_Blast::Clear_Buffer_Array_With_Length(char* &given_buffer,unsigned int length)
{
    for(unsigned int i=0;i<length;i++)
    {
        given_buffer[i] = '\0';
    }
}


int SmithWaterman_Blast::Get_Max_Score(int a,int b, int c,int& chosen_cell)
{

    // a = upper left cell => 1
    // b = left cell => 2
    // c = upper cell => 3

    int max = 0;

    if(a>=b)
    {
        max = a;
        chosen_cell = 1;
    }
    else
    {
        max = b;
        chosen_cell = 2;
    }

    if(max<c)
    {
        max = c;
        chosen_cell = 3;
    }

    if(max<0)
    {
        max = 0;
        chosen_cell = 0; // no cell chosen. No Move???
    }

    return max;
}




int SmithWaterman_Blast::Get_Match_Mismatch_Score(char target_char,char subject_char)
{
    
    int row = Get_Char_Index(target_char);
    int col = Get_Char_Index(subject_char);

    if(row<0)
    {
        cout<<"\n\t\tInvalid Char Index Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    if(col<0)
    {
        cout<<"\n\t\tInvalid Char Index Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }


    // Return the value from the similarity
    // score matrix:
    return similarity_score_matrix[row][col];   

}

int SmithWaterman_Blast::Get_Char_Index(char param)
{

    // A = 0, C = 1, G = 2, T = 3 

    if(param == 'A')
    {
        return 0;
    }
    else if(param == 'C')
    {
        return 1;
    }
    else if(param == 'G')
    {
        return 2;
    }
    else if(param == 'T')
    {
        return 3;
    }
    else if(param==' ')
    {
        return 4;
    }
    else
    {
        return -1;
    }
}

void SmithWaterman_Blast::Generate_A_Random_Sequence(string &sequence)
{
    if(sequence.length()!=0)
    {
        sequence.clear();
    }

    int random_int; 

    while(sequence.length()!=50)
    {
        random_int = rand()%4; // Gives 0 or 1 or 2 or 3

        if(random_int == 0)
        {
            sequence.push_back('A');
        }
        else if(random_int == 1)
        {
            sequence.push_back('C');
        }
        else if(random_int == 2)
        {
            sequence.push_back('G');
        }
        else
        {
            sequence.push_back('T');
        }
    }


}


// -------------------------------------------- End: Class Private Member Functions ----------------------------------------------------------------


