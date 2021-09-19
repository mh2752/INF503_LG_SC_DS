#include "FASTAreadset_LL.h"


// Default Ctor()
FASTAreadset_LL::FASTAreadset_LL()
{   
        
    path_to_source_file = NULL;
    path_to_anthrax_genome_file = NULL;
    banthrax_genome_full = NULL;    
    num_of_lines_to_read = 0; 

    all_seq_fragments = new LinkedList;
    banthrax_genome_50mers = new LinkedList;

}


// Overloaded Ctor()
FASTAreadset_LL::FASTAreadset_LL(char* &source_file,char* &banthrax_genome_file,int num_of_lines)
{
   
    // Creating the linked list objects first:
    all_seq_fragments = new LinkedList;
    banthrax_genome_50mers = new LinkedList;


    // Copying the file path info:
    
    int length = 0;
    while(source_file[length] != '\0')
    {
        length++;
    }

    path_to_source_file = new char[length+1]; // +1 for terminating null character

    // Copy the file path:
    for(int index = 0; index < length+1; index++)
    {
        if(index!=length)
        {
            path_to_source_file[index] = source_file[index];
        }
        else
        {
            path_to_source_file[index] = '\0';
        }
    }

   

    // -------------------------------------------------------------------------------------
    
    length = 0;
    while(banthrax_genome_file[length] != '\0')
    {
        length++;
    }

    path_to_anthrax_genome_file = new char[length+1]; // +1 for terminating null character

    // Copying the file path:
    for(int index = 0; index < length+1; index++)
    {
        if(index!=length)
        {
            path_to_anthrax_genome_file[index] = banthrax_genome_file[index];
        }
        else
        {
            path_to_anthrax_genome_file[index] = '\0';
        }
    }

   
    num_of_lines_to_read = num_of_lines;
 

}





// Copy Ctor()
FASTAreadset_LL::FASTAreadset_LL(const FASTAreadset_LL &external_frst)
{   



    path_to_source_file = NULL;
    path_to_anthrax_genome_file = NULL;
    banthrax_genome_full = NULL;

    all_seq_fragments = new LinkedList;
    banthrax_genome_50mers = new LinkedList;
    

    // Performing deep-copy of all the member variables:


    num_of_lines_to_read = external_frst.num_of_lines_to_read;   

    // Getting the lengths of the file paths:
    int source,genome;
    external_frst.Get_File_Path_Lengths(source,genome);

    // Copying the file paths (including terminating null characters):
    if(path_to_source_file == NULL)
    {
        path_to_source_file = new char[source];

        for(int index = 0; index < source; index++)
        {
            path_to_source_file[index] = external_frst.path_to_source_file[index];
        }
    }

    if(path_to_anthrax_genome_file == NULL)
    {
        path_to_anthrax_genome_file = new char[genome];

        for(int index = 0; index < genome; index++)
        {
            path_to_anthrax_genome_file[index] = external_frst.path_to_anthrax_genome_file[index];
        }
    }



   // Deep Copy from the external_frst's linked lists:
   external_frst.all_seq_fragments->Copy_List(*all_seq_fragments);
   external_frst.banthrax_genome_50mers->Copy_List(*banthrax_genome_50mers);
    
    
    // Copying the full B. Anthrax genome array data:
    if(banthrax_genome_full == NULL)
    {
        // Allocating memory first:
        banthrax_genome_full = new char[external_frst.banthrax_genome_full_length];
    }
    //Copy the content:
    for(int index = 0; index < external_frst.banthrax_genome_full_length; index++)
    {
        banthrax_genome_full[index] = external_frst.banthrax_genome_full[index];
    }

} // Copy Ctor() ends





// Class Dtor()
FASTAreadset_LL::~FASTAreadset_LL()
{
    // Getting starting timestamp
    time_t start = time(nullptr);


    // First, empty all the linked list objects held inside this FASTAreadset_LL object:
    all_seq_fragments->~LinkedList();
    banthrax_genome_50mers->~LinkedList();

    all_seq_fragments =  NULL;
    banthrax_genome_50mers = NULL;


    // Now, delete all the arrays:
    delete[] path_to_source_file;
    delete[] path_to_anthrax_genome_file;
    delete[] banthrax_genome_full;


    // Getting ending timestamp
    time_t end = time(nullptr);
    time_t duration = end - start;

    cout<<"\n\t\tTime (in seconds) Required to Destroy the FASTAreadset_LL Object = "<<duration<<endl;

}


// ------------------------------- Non-member Helper Function ----------------------------------------------------------------------


// Clear the given char array by
// overwriting contents with null
// character:
void Clear_Buffer_Array(char* &buffer,int length)
{
    for(int index = 0; index < length; index++)
    {
        buffer[index] = '\0';
    }
}






// ------------------------------------------------ Class Member Functions ------------------------------------------------------------

void FASTAreadset_LL::Get_File_Path_Lengths(int& source_file,int& anthrax_genome_file) const
{

    int index = 0;
    while(path_to_source_file[index]!='\0')
    {
        index++;
    }
    source_file = index+1; // +1 for including the terminating null character



    index = 0;
    while(path_to_anthrax_genome_file[index]!='\0')
    {
        index++;
    }
    anthrax_genome_file = index+1; // +1 for including the terminating null character
}



// Read all the seq data and anthrax genome data:
void FASTAreadset_LL::Read_From_Source_File()
{
    

    if(path_to_source_file == NULL)
    {
        cout<<"\n\t\tNULL File Path for Sequence Fragments Encountered. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }
    if(path_to_anthrax_genome_file == NULL)
    {
        cout<<"\n\t\tNULL File Path for Anthrax Genome Sequence Encountered. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }
    if(num_of_lines_to_read == 0)
    {
        cout<<"\n\t\tZero(0) number of lines specified to read from FASTA dataset. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }


    try
    {
        
        // ----------------- Read the FASTA sequence fragment data first ------------------------------------

       

        // Open an input stream to the file:
        ifstream stream_to_source_file;
        stream_to_source_file.open(path_to_source_file);

        
        // Indicates if the current stream contains header or seq_fragment line
        bool sequence_flag = false; 


        // A buffer char array to read the header line and ignore it
        char* buffer_array_to_ignore;
        buffer_array_to_ignore = new char[max_buffer_length]; 
        
        
        // A buffer char array to read the sequence line
        char* buffer_array_seq_frag;
        buffer_array_seq_frag = new char[all_seq_frag_length];


        //// A buffer char array to save the
        // null terminated seq array
        char* buffer_array_seq_frag_null_terminated;
        buffer_array_seq_frag_null_terminated = new char[all_seq_frag_length+1];


        // Number of seq lines
        // read from FASTA
        int lines_read = 0;


        // Keep reading until you reach the end of the file
        // or the specifed number of FASTA seq fragments
        while(!stream_to_source_file.eof() && lines_read< num_of_lines_to_read) 
        {
            
            if(!sequence_flag) // Ignore the header. Move to the next line
            {
                stream_to_source_file>>buffer_array_to_ignore;
                // Change flag for the next line:
                sequence_flag = true;
            }


            else // Insert this info into the linked list:
            {
                stream_to_source_file>>buffer_array_seq_frag;

                // Copy and include a terminating null character:
                for(int index = 0; index < all_seq_frag_length+1 ; index++)
                {
                    if(index == all_seq_frag_length) // last location should hold the null character
                    {
                        buffer_array_seq_frag_null_terminated[index] = '\0';
                    }
                    else
                    {
                        buffer_array_seq_frag_null_terminated[index] = buffer_array_seq_frag[index];
                    }
                }

                // Insert the char array into the linked list object:
                all_seq_fragments->Insert_Item_At_Front(buffer_array_seq_frag_null_terminated);

                // Clear the buffer array:
                Clear_Buffer_Array(buffer_array_seq_frag,all_seq_frag_length);
                Clear_Buffer_Array(buffer_array_seq_frag_null_terminated,all_seq_frag_length+1);

                lines_read++;

                // Change flag for the next line:
                sequence_flag = false;
            }

        } // while() ends here...

        // Close the input stream:
        stream_to_source_file.close();  




        // ------------------------------------- Now, read the B. Anthrax genome data -----------------------------------------------



        // First, count exactly how many characters are there in the full genome:	

        // Create and link an input stream to the source file:
        ifstream stream_to_banthrax_genome;
        stream_to_banthrax_genome.open(path_to_anthrax_genome_file);
	
	    char* buffer_for_banthrax_genome;
        buffer_for_banthrax_genome = new char[max_buffer_length];
        Clear_Buffer_Array(buffer_for_banthrax_genome,max_buffer_length);
        bool first_line = true;
        
        string temp_string;
        int temp_string_length;

        int genome_length = 0;
	

        while(!stream_to_banthrax_genome.eof())
        {
            if(first_line == true) // Ignore the header line of the genome file
            {
                stream_to_banthrax_genome>>buffer_array_to_ignore;
                first_line = false;
            }
            else
            {
                stream_to_banthrax_genome>>buffer_for_banthrax_genome;

                // Create a string with the read char sequence
                temp_string.assign(buffer_for_banthrax_genome);

                // Get the length of the string
                temp_string_length = temp_string.length();

                // Update the genome length
                genome_length += temp_string_length;

                // Clear the buffer:
                Clear_Buffer_Array(buffer_for_banthrax_genome,max_buffer_length);
            }
        }
	
	
        // Reset the stream to beginning of the file
        stream_to_banthrax_genome.clear();
        stream_to_banthrax_genome.seekg(0,ios::beg);
        first_line = true;


        // Allocate the memory for the genome array:
        banthrax_genome_full_length = genome_length+1; // +1 for terminating null character
        banthrax_genome_full = new char[banthrax_genome_full_length]; // Do not delete[] this until you're in the class Dtor()

       
        int last_index_written_to = -1; // -1 comes before zero (0)
        int genome_index = 0;

	
        // Now, copy the actual contents into the newly allocated array:
        while(!stream_to_banthrax_genome.eof())
        {
             if(first_line) // Ignore the header line of the genome file
            {
                stream_to_banthrax_genome>>buffer_array_to_ignore;
                first_line = false;
            }
            else
            {
                 // Clear buffer:
                Clear_Buffer_Array(buffer_for_banthrax_genome,max_buffer_length);
                
                // Read seq into buffer:
                stream_to_banthrax_genome>>buffer_for_banthrax_genome;

                genome_index = 0;
                // Copy into the array:
                while(buffer_for_banthrax_genome[genome_index] != '\0')
                {   
                    last_index_written_to++;
                    banthrax_genome_full[last_index_written_to] = buffer_for_banthrax_genome[genome_index];
                    genome_index++;
                }              
            }

            // Insert the terminating null character:
            banthrax_genome_full[last_index_written_to+1] = '\0';

        }  // copying genome data into array done

        //close file stream:
        stream_to_banthrax_genome.close();


        // Release all the buffer memories
        // to prevent memory leak:
        delete[] buffer_array_to_ignore;
        delete[] buffer_for_banthrax_genome;
        delete[] buffer_array_seq_frag;
        delete[] buffer_array_seq_frag_null_terminated;
        
    }
    catch(...)
    {
        cout<<"Exception caught while trying to read from source files. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


}




void FASTAreadset_LL::Search_For_Given_Seq(char* &given_seq,ListNode* &location)
{
    all_seq_fragments->Search_List(given_seq,location);
}




void FASTAreadset_LL::Generate_Anthrax_Genome_50mers()
{
    try
    {
        // ----------- Generate all possible 50mers:
        
        
        
        // Utility variables
        int length_of_50mers = 50;
        int index = 0;
        char* buffer;

        while( (index+length_of_50mers-1 < banthrax_genome_full_length-1) &&  (banthrax_genome_full[index]!= '\0') )
        {

            buffer = new char[length_of_50mers+1];
            Clear_Buffer_Array(buffer,length_of_50mers+1);


            for(int i=0; i< length_of_50mers; i++)
            {
                buffer[i] = banthrax_genome_full[i+index];
            }

            index++; // move index to one char to the right

            // Insert th generated 50mer into the linked list:
            banthrax_genome_50mers->Insert_Item_At_Front(buffer);

            // Release array memory to prevent memory leak:
            delete[] buffer;
            buffer = NULL;

        }

        total_50mers_generated = index;
        cout<<"\n\t\tTotal Number of 50mers Observed = "<<total_50mers_generated<<endl;  

    }
    catch(const std::exception& e)
    {
        cout<<"\n\t\tException while creating 50mers from genome data." <<e.what() << '\n';
    }
}




void FASTAreadset_LL::Search_FASTA_Seq_Frags_For_50mers(int num_of_search)
{    

    // Utility variables:
    ListNode* temp_node;
    ListNode* search_result_location;

    int iterations = 0;
    int positive_search_hits = 0;
    
    int temp_node_seq_length;
    char* temp_node_seq_content;


    // Reset the current
    banthrax_genome_50mers->Reset_Current_Pointer();

    while( iterations<num_of_search && iterations<total_50mers_generated)
    {     
        
        temp_node = new ListNode;
        
        // Get the ListNode pointed by current:
        banthrax_genome_50mers->Get_Current_Node(*temp_node);
        
        
        //find the seq length of this node's content and copy into a char array here:
        temp_node_seq_length = temp_node->Get_Node_Seq_Length();       
        temp_node_seq_content = new char[temp_node_seq_length];

        temp_node->Get_Node_Content(temp_node_seq_content);

        
        
        // Now search for this fragment:
        search_result_location = NULL;
        all_seq_fragments->Search_List(temp_node_seq_content,search_result_location);

        if(search_result_location != NULL)
        {
            positive_search_hits++;
        }

        // Move 50mers linked list current pointer to the next node:
        banthrax_genome_50mers->Move_Current_To_Next();

        // Free array memory to prevent memory leak:
        delete[] temp_node_seq_content;

        // Increment counter:
        iterations++;
    }


     // Reset the current
    banthrax_genome_50mers->Reset_Current_Pointer();
   
    cout<<"\n\t\tSearched the FASTA Database for the First "<<num_of_search<<" B. Anthracis 50mers"<<endl;
    cout<<"\n\t\tNumber of Positive Search Hits (instances of 50mers in the FASTA Dataset) = "<<positive_search_hits<<endl;

}