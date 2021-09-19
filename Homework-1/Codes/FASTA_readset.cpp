#include "FASTA_readset.h"



// ******************************************************** Constructors & Destructor Definitions *******************************************************************



// --------------------------------------------------------------------- Ctor
FASTA_readset::FASTA_readset(const char *path,int name_length)
{
   
    total_read_size = 10; // Default value
    single_sequence_length = 50; // each sequence is 50 chars long
    num_of_data_sets = 14; // 14 data sets available
    
    // Initializing to NULL before allocating memory:
    all_genomic_sequence = NULL;   
    data_sets_total_reads = NULL;
    data_sets_unique_read_counts = NULL;
    file_path = NULL;

    // ---------- Memory Allocation --------------

    try
    {

        // -------- Allocating memory for holding file path name

        file_path = new char[name_length+1]; // 1 extra space for terminating null character ('\0')
        // Now, copying the file path name
        for(int i=0;i<=name_length;i++)
        {
            if(i!=name_length)
            {
                file_path[i] = path[i];
            }
            else
            {
                file_path[i] = '\0';
            }

           
        }      


        // --------- Allocating memory for storing seq data
        
        all_genomic_sequence = new char*[total_read_size];

        for(int i=0;i<total_read_size;i++)
        {
            all_genomic_sequence[i] = new char[single_sequence_length];
        }


        // ------------ Allocating memory for data set letter freq info
        data_set_letter_frequency = new int*[num_of_data_sets];

        for(int i=0;i<num_of_data_sets;i++)
        {
            data_set_letter_frequency[i] = new int[4]; // 4 Letters: A, T, G, C
        }
        //Initializing with zero counts
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_set_letter_frequency[i][0] = 0;
            data_set_letter_frequency[i][1] = 0;
            data_set_letter_frequency[i][2] = 0;
            data_set_letter_frequency[i][3] = 0;
        }

        
        
        // ------- Allocating memory for storing a total, current, and unique read counts 
        //         of all 14 of the data sets
        
        data_sets_total_reads = new int[num_of_data_sets];
        //Initializing with zeros
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_sets_total_reads[i] = 0;
        }


        data_sets_current_read_count = new int[num_of_data_sets];
        //Initializing with zeros:
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_sets_current_read_count[i] = 0;
        }

        data_sets_unique_read_counts = new int[num_of_data_sets];
        //Initializing to zero
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_sets_unique_read_counts[i] = 0;
        }




    }
    catch(bad_alloc& exception)
    {
        cout<<"Dynamic Memory Allocation Failed Inside Overloaded Constructor."<<endl;
        cout<<"\tDetials: "<<exception.what()<<endl;
        exit(EXIT_FAILURE);
    }

}






// ------------------------------------------------------------------------------------ Overloaded ctor
FASTA_readset::FASTA_readset(const char *path,int name_length,int lines_to_read)
{
   
    total_read_size = lines_to_read; // Given value
    single_sequence_length = 50; // each sequence is 50 chars long
    num_of_data_sets = 14; // 14 data sets available
    
    // Initializing to NULL before allocating memory:
    all_genomic_sequence = NULL;   
    data_sets_total_reads = NULL;
    file_path = NULL;

    // ---------- Memory Allocation --------------

    try
    {

        // -------- Allocating memory for holding file path name
       
        file_path = new char[name_length+1]; // 1 extra space for terminating null character ('\0')
        // Now, copying the file path name
        for(int i=0;i<=name_length;i++)
        {
            if(i!=name_length)
            {
                file_path[i] = path[i];
            }
            else
            {
                file_path[i] = '\0';
            }           
        }     



        // --------- Allocating memory for storing seq data
        
        all_genomic_sequence = new char*[total_read_size];

        for(int i=0;i<total_read_size;i++)
        {
            all_genomic_sequence[i] = new char[single_sequence_length];
        }

        
        // ------------ Allocating memory for data set letter freq info
        data_set_letter_frequency = new int*[num_of_data_sets];

        for(int i=0;i<num_of_data_sets;i++)
        {
            data_set_letter_frequency[i] = new int[4]; // 4 Letters: A, T, G, C
        }
         //Initializing with zero counts
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_set_letter_frequency[i][0] = 0;
            data_set_letter_frequency[i][1] = 0;
            data_set_letter_frequency[i][2] = 0;
            data_set_letter_frequency[i][3] = 0;
        }


        
        
        // ------- Allocating memory for storing a total read counts 
        //         of all 14 of the data sets
        
        data_sets_total_reads = new int[num_of_data_sets];
        //Initializing with zeros
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_sets_total_reads[i] = 0;
        }

        data_sets_current_read_count = new int[num_of_data_sets];
        //Initializing with zeros:
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_sets_current_read_count[i] = 0;
        }


        data_sets_unique_read_counts = new int[num_of_data_sets];
        //Initializing to zero
        for(int i=0;i<num_of_data_sets;i++)
        {
            data_sets_unique_read_counts[i] = 0;
        }



    }
    catch(bad_alloc& exception)
    {
        cout<<"Dynamic Memory Allocation Failed Inside Overloaded Constructor."<<endl;
        cout<<"\tDetials: "<<exception.what()<<endl;
        exit(EXIT_FAILURE);
    }

}




// ----------------------------------------------------------------------------- Class dtor
FASTA_readset::~FASTA_readset()
{

    //  ------------- RELEASE the KRAKEN(!!!) - the array holding the read seq data -----------------------------


    time_t start = time(nullptr);
        
    for(int i=0;i<total_read_size;i++)
    {
        // De-allocating the sub-arrays
        delete[] all_genomic_sequence[i];
    }

    // Now, de-allocate the main array
    delete[] all_genomic_sequence;

    // ------------------------------ Releasing other Memories -----------------------------------------------------
    
    // Releasing data set count memory
    delete[] data_sets_total_reads;

    // Releasing the file path array memory
    delete[] file_path;

    // Releasing letter frequency data:
    for(int i=0;i<num_of_data_sets;i++)
    {
        delete[] data_set_letter_frequency[i];
    }
    delete[] data_set_letter_frequency;


    // Releasing current read count memory
    delete[]  data_sets_current_read_count;

    // Releasing unique read counts memory
    delete[] data_sets_unique_read_counts;


    // Getting ending timestamp
    time_t end = time(nullptr);

    time_t duration = end-start;

    cout<<"\n\t\tTime (in seconds) Required to Release All Memory = "<<duration<<endl;

    cout<<"\n\t\t All Dynamically Allocated Memories Have Been Released. Exiting Program Now."<<endl;



}




// ********************************************************** Remaining Member Function Definitions ****************************************************************

void FASTA_readset::Read_Data_From_File()
{

    // ---------- Read the data from the input file --------


    // If file_path is still NULL, exit the program.
    if(file_path==NULL)
    {
        cout<<"NULL File Path Encountered. Exiting Program"<<endl;
        exit(EXIT_FAILURE);
    }


    // Open and Read from the file
    try
    {   

        // Getting the starting timestamp
         time_t start = time(nullptr);

        


        ifstream input_file_stream;
        input_file_stream.open(file_path);

        int lines_read = 0;

        int seq_index = 0; // Index indicating location to store the current sequence

        int header_or_seq_flag = 0; // 1 = sequence line

        char temp_header[max_read_header_length];

        char *token = NULL; // For tokenizing the header line
        int token_number; // Indicates serial number of the token. There should be 15 (0 to 14) tokens (including the read id).

        int data_set_read_count = 0; // Storing the read count of the seq for the data set obtained from atoi(token)
        int temp_read_count; // A temporary read count 

        int freq_A,freq_T,freq_G,freq_C; // For holding the frequency of the letters in the read sequence


        while ((!input_file_stream.eof()) && lines_read<(2*total_read_size) && seq_index<total_read_size)
        {
            if(lines_read==0)
            {
                header_or_seq_flag = 0; // We are reading the first read header
            }

            // We are avoiding costly modulo operation (%)
            // by keeping track of the flag value.

            // It's a header line
            if(header_or_seq_flag==0)
            {
                // Process the information in the header
                
                input_file_stream>>temp_header;

                // Tokenize the header using '_' as the delimiter
                if(token!=NULL)
                {
                    token = NULL;
                }

                token = strtok(temp_header,"_");
                
                token_number = 0;

                while(token!=NULL)
                {
                    if(token_number!=0) // Ignoring the read number in the read header
                    {
                       data_set_read_count = atoi(token);

                       data_sets_total_reads[(token_number-1)] += data_set_read_count;
                       data_sets_current_read_count[(token_number-1)] = data_set_read_count;
                       
                       if(data_set_read_count>0)
                       {
                           data_sets_unique_read_counts[(token_number-1)] += 1;
                       }
                       
                        
                    }
                                       
                    token = strtok(NULL,"_");
                    token_number++;
                }
               

                // Modify the flag
                header_or_seq_flag = 1;
            }


            // It's a sequence line
            else 
            {
                // Process the sequence line information
                input_file_stream>>all_genomic_sequence[seq_index];


                // Find out the frequency of the letters A,T,G,C in the read sequence:
                
                freq_A = 0;
                freq_T = 0;
                freq_G = 0;
                freq_C = 0;

                this->Count_Letter_Frequency(all_genomic_sequence[seq_index],freq_A,freq_T,freq_G,freq_C);

                // Now update the letter frequency counts for each of the 14 data sets
                // using the current read count info:

                for(int i=0;i<num_of_data_sets;i++)
                {
                    temp_read_count = data_sets_current_read_count[i];

                    data_set_letter_frequency[i][0] += temp_read_count * freq_A; // Updating the freq count of letter A for the i-th data set 
                    data_set_letter_frequency[i][1] += temp_read_count * freq_T; // Updating the freq count of letter T for the i-th data set
                    data_set_letter_frequency[i][2] += temp_read_count * freq_G; // Updating the freq count of letter G for the i-th data set
                    data_set_letter_frequency[i][3] += temp_read_count * freq_C; // Updating the freq count of letter C for the i-th data set
                }  

                
                // Increment index
                seq_index++;
                // Modify the flag
                header_or_seq_flag = 0;
            }

            lines_read++;         

        } // While(...) ends here


        // File reading done.
        // Close the file stream.
        if(input_file_stream.is_open())
        {
            input_file_stream.close();
        }  


    }
    catch(const std::exception& e)
    {   
        cout<<"Error Encountered While Trying Open & Read From the Input File. Exiting Program.";
        cout<<"\tDetails: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

}

void FASTA_readset::Compute_All_Stats()
{
    

        cout<<"---------------- Total Number of Unique Sequence Fragments in Each Data Set --------------------"<<endl;
        for(int i=0;i<num_of_data_sets;i++)
        {
           cout<<"Data Set-"<<(i+1)<<" Unique Count = "<<data_sets_unique_read_counts[i]<<endl;
        }
        cout<<endl<<endl;
        
        
        
        
        
        cout<<"--------------- Total Read Counts for Each Data Sets ------------------------------------------------"<<endl;
        for(int i=0;i<num_of_data_sets;i++)
        {
            cout<<"Data Set-"<<(i+1)<<" Totla Read Count = "<<data_sets_total_reads[i]<<endl;
        }
        cout<<endl<<endl;




        cout<<"-------------------------- Letter Frequency for Each Data Sets ----------------------------------------------"<<endl;
        for(int i=0;i<num_of_data_sets;i++)
        {
            cout<<"Data Set-"<<(i+1)<<" : ";
            for(int j=0;j<4;j++)
            {
                switch (j)
                {

                    case 0:
                        cout<<" A = "<<data_set_letter_frequency[i][j];
                        break;
                    
                    case 1:
                        cout<<" T = "<<data_set_letter_frequency[i][j];
                        break;
                    
                    case 2:
                        cout<<" G = "<<data_set_letter_frequency[i][j];
                        break;

                    case 3:
                        cout<<" C = "<<data_set_letter_frequency[i][j];
                        break;

                    default:
                        // do nothing
                        ;
                }  
            }

             cout<<endl;
        }


}





//******************************************************** Helper Member Functions ****************************************************************

void FASTA_readset::Count_Letter_Frequency(const char* seq,int& a,int& t,int& g,int& c)
{
    for(int i=0;i<single_sequence_length;i++)
    {
        if(seq[i]=='A')
        {
            a++;
        }
        else if(seq[i]=='T')
        {
            t++;
        }
        else if(seq[i]=='G')
        {
            g++;
        }
        else if(seq[i]=='C')
        {
            c++;
        }
    }
}

bool FASTA_readset::Is_SeqA_Greater_Than_SeqB(const char* A,const char* B)
{
    string a(A);
    string b(B);

    int compare_result = a.compare(b);
  
    if(compare_result<0)
    {   
        return true;
    }
    else
    {
        return false;
    }
}



void FASTA_readset::Sort_Seq_Data()
{

    // Perforing Insertion Sort on the sequence array 

   
    char key[single_sequence_length];

    char temp_a[single_sequence_length];
    char temp_b[single_sequence_length];

    int compare_result;
    int i,j;

    for(i=1;i<total_read_size;i++)
    {
        for(int index=0;index<single_sequence_length;index++)
        {
            key[index] = all_genomic_sequence[i][index];
        }
       

        j = i-1;

        while(j>=0 && !Is_SeqA_Greater_Than_SeqB(all_genomic_sequence[j],key))
        {          
                
            for(int index=0;index<single_sequence_length;index++)
            {
                all_genomic_sequence[j+1][index] = all_genomic_sequence[j][index];
            }          
        

            j--;
        }

        for(int index=0;index<single_sequence_length;index++)
        {
            all_genomic_sequence[j+1][index] = key[index];
        }

    }


    cout<<"-------------------- Printing First 20 elements from the Sorted Sequence Array -------------------------------"<<endl;

    for(int i=0;i<20;i++)
    {
        cout<<"Seq at Index "<<i<<" = ";
        for(int j=0;j<single_sequence_length;j++)
        {
            cout<<all_genomic_sequence[i][j];
        }
        cout<<endl; 
    }
    

  
}

