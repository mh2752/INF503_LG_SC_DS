#include "FASTAreadset_DA.h"


// --------------------------------------------  Begin: Class Ctor & Dtor Definitions ---------------------------------------------------



// --------- Class Ctor
FASTAreadset_DA::FASTAreadset_DA()
{

    // Initialize all private
    // variables to zero (0)
    // or NULL as appropriate:    

    // No collisions yet:
    total_collisions = 0;

    // Nothing read-in yet:
    full_bacillus_genome = NULL;

    // Nothing generated yet:
    all_bacillus_16mers = NULL;

    // Not read yet:
    length_of_full_bacillus_genome = 0;


    // --- Allocate memories for
    // the hahsh table here:
    hash_table_size = (unsigned long int) pow(radix_base,max_sequence_length);
   
    try
    {
        hash_table = new bool[hash_table_size];

        // Initializing every cell to false:
        for(unsigned long int index = 0; index < hash_table_size; index++)
        {
            hash_table[index] = false;
        }
        
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught in Constructor While Trying to Allocate Memory For the Hash Table. Exiting Program Now."<<endl;
        cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

}





// ------ Class Dtor
FASTAreadset_DA::~FASTAreadset_DA()
{

    // Release all of the dynamically allocated
    // memories:


    // Getting the starting timestamp
    time_t start = time(nullptr);


    // Release the hash_table memories:
    if(hash_table!=NULL)
    {
        delete[] hash_table;
    }


    // Release Bacillus genome array:
    if(full_bacillus_genome!=NULL)
    {
        delete[] full_bacillus_genome;
    }


    // Release 16mers arrray:
    if(all_bacillus_16mers!=NULL)
    {
        // Call the destructor of the
        // LinkedList object:
        all_bacillus_16mers->~LinkedList();
    }




    // Getting the ending timestamp:
    time_t end = time(nullptr);



    // Printing the duration info:
    time_t duration = end-start;
    cout<<"\n\t\tTime (in seconds) to Destroy the FASTAreadset_DA : "<<duration<<endl; 



}


// --------------------------------------------- End: Class Ctor & Dtor Definitions -------------------------------------------------------






// --------------------------------------------- Begin: All Non-member Helper Functions ---------------------------------------------------

unsigned long int Get_Radix_Digit_Value(char radix_digit)
{
    
    // A = 0, T = 1, G = 2, C = 3
    if(radix_digit == 'A')
    {
        return 0;
    }

    else if(radix_digit == 'T')
    {
        return 1;
    }

    else if(radix_digit == 'G')
    {
        return 2;
    }

    else if(radix_digit == 'C')
    {
        return 3;
    }

    else
    {
        return -1; // Indicating an invalid input was received
    }


}



// --------------------------------------------- End: All Non-member Helper Functions -----------------------------------------------------







// --------------------------------------------- Begin: All Private Member Function Definitions -------------------------------------------


unsigned long int FASTAreadset_DA::Get_Radix_Of_The_Sequence(const char* sequence)
{

    // Creating a string representation
    // of the char sequence:
    string sequence_string(sequence);    


    unsigned long int radix_value = 0;
    unsigned long int radix_digit = 0;
    unsigned int current_exponent = 0;

    
    char temp;
    unsigned long int temp_radix_digit_value = 0;

    
    
    for(int i = 0; i < max_sequence_length; i++)
    {
        temp = sequence_string.at(i);        
        temp_radix_digit_value = Get_Radix_Digit_Value(temp);


        // If digit value is -1, exit with failure status:
        if(temp_radix_digit_value == -1)
        {
            cout<<"\n\t\tInvalid Input Received While Calculating Radix Digit Value. Exiting Program."<<endl;
            cout<<"The Invalid Char is = "<<temp<<" and its radix value is "<<temp_radix_digit_value<<endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            radix_digit = temp_radix_digit_value;

            // Current exponent for the radix base to multiply the 
            // radix digit with:
            current_exponent = (max_sequence_length-1) - i;

            // Calculating the radix value and
            // appending to the variable:
            radix_value += radix_digit * (unsigned long int) pow(radix_base,current_exponent);
        }

    } // for loop ends here


    // returning the result:
    return radix_value;


}


void FASTAreadset_DA::Clear_Buffer_Array(char* &given_buffer)
{
    for(unsigned int i=0;i<buffer_size;i++)
    {
        given_buffer[i] = '\0';
    }
}


void FASTAreadset_DA::Clear_Buffer_Array_With_Length(char* &given_buffer,unsigned int length)
{
    for(unsigned int i=0;i<length;i++)
    {
        given_buffer[i] = '\0';
    }
}


// --------------------------------------------- End: All Private Member Function Definitions -------------------------------------------





// --------------------------------------------- Begin: All Public Member Function Definitions -------------------------------------------



  
void FASTAreadset_DA::Read_In_Read_Data_Set(const char* filepath)
{
    if( (*filepath == '\0') || (filepath == NULL))
    {
        cout<<"\n\t\tEmpty Filepath Received for the Read Data Set. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    else
    {
        // Filepath okay. Read in the data
        // from the file:
        
        if(hash_table == NULL)
        {
            cout<<"\n\t\tAvailable Hash Table is NULL. Exiting Program Now."<<endl;
            exit(EXIT_FAILURE);
        }


        // Read the data file into the hash-table:
        else
        {

            try
            {                

                // Opening an input stream:
                ifstream stream_to_data_file;
                stream_to_data_file.open(filepath);

                if(!stream_to_data_file.is_open())
                {
                    cout<<"\n\t\tThe Input Stream to Readset Data File Could Not be Opened. Exiting Program Now."<<endl;
                    exit(EXIT_FAILURE);
                }

                // Keeps track whether the line is a header
                // or a sequence line. Even lines are headers.
                bool header_flag = true;
                char *buffer;
                buffer = new char[buffer_size];
               

                // Variable for holding radix value of 
                // the sequence:
                unsigned long int seq_radix = 0;

                while(!stream_to_data_file.eof())
                {
                    if(header_flag)
                    {
                        // Read the header into buffer
                        // and ignore
                        stream_to_data_file>>buffer;

                        // Change the flag:
                        header_flag = false;
                    }
                    else
                    {
                        // Read the sequence into buffer
                        Clear_Buffer_Array(buffer); // Clearing the buffer first
                        stream_to_data_file>>buffer;

                        // Get the radix value for this sequence
                        // held in the buffer:
                        seq_radix = Get_Radix_Of_The_Sequence(buffer);


                        // Set the value to 'true' in the hash table
                        // at the position indicated by the seq_radix:
                       
                        if(hash_table[seq_radix]==true) // Already true. Collision case:
                        {
                            total_collisions++;
                            
                        }
                        else // No collision. Just flip the value to true.
                        {   
                            
                            hash_table[seq_radix] = true;
                           
                        }

                        //cout<<"Debug-4"<<endl;

                        // Change the flag:
                        header_flag = true;                                
                        
                    }

                } // While loop ends.


                // Closing the stream:
                if(stream_to_data_file.is_open())
                {
                    stream_to_data_file.close();
                }


                // Release the buffer memory:
                delete[] buffer;
                
            }
            catch(const exception& e)
            {
                cout<<"\n\t\tException Caught While Trying to Read in From the Readset Data File into Hash Table. Exiting Program."<<endl;
                cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
                exit(EXIT_FAILURE);
            }

        } // else() for if(hash_table == NULL) ends here

        
    } // else ends (of filepath check)


} // Read_In_Read_Data_Set(...) function ends here





void FASTAreadset_DA::Read_In_Bacillus_Genome(const char* filepath)
{

    if( (*filepath == '\0') || (filepath == NULL))
    {
        cout<<"\n\t\tEmpty Filepath Received for the Bacillus Genome Data File. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }
    
    else
    {

        try
        {
            // Filepath is okay.

            ifstream stream_to_file;
            stream_to_file.open(filepath);

            if(!stream_to_file.is_open())
            {
                cout<<"\n\t\tCouldnot Open Stream to Bacillus Genome Filepath. Exiting Program Now."<<endl;
                exit(EXIT_FAILURE);
            }

            else
            {

                // ---------- Find the length of the full
                // Bacillus genome first:                  

                    
                    char *buffer_save;
                    buffer_save = new char[buffer_size];

                    string buffer_seq_string;
                    bool header_line = true; // Only the first line is the header.                   

                    while(!stream_to_file.eof())
                    {
                         
                            Clear_Buffer_Array(buffer_save); // Clearing buffer first
                            stream_to_file>>buffer_save;

                            buffer_seq_string.clear();
                            buffer_seq_string.assign(buffer_save);

                            // Update the Bacillus Genome Length:
                            length_of_full_bacillus_genome += buffer_seq_string.length();
                        
                    }

                    // Exclude the characters of the header lines:
                    length_of_full_bacillus_genome = length_of_full_bacillus_genome - 62;
                   

                    // Close the stream
                    if(stream_to_file.is_open())
                    {
                        stream_to_file.close();
                    }

                    // Release buffers:                   
                    delete[] buffer_save;



                // We have the total size of the Bacillus Genome Length. Now
                // allocate memory and read in the data:

                if(full_bacillus_genome != NULL) // To prevent accidental memory leak
                {
                    delete[] full_bacillus_genome;
                }               


                // Allocate the memory:
                full_bacillus_genome = new char[length_of_full_bacillus_genome];
                
                
                // Temporary array for reading full genome including header
                char* full_bacillus_genome_temp;
                full_bacillus_genome_temp = new char[length_of_full_bacillus_genome+62];


                // -------- Now, read in the Bacillus Genome data into the
                // memory:
                ifstream stream_to_file2;
                stream_to_file2.open(filepath);

                if(!stream_to_file2.is_open())
                {
                    cout<<"\n\t\tCouldnot Again Open Stream to Bacillus Genome File. Exiting Program."<<endl;
                    exit(EXIT_FAILURE);
                }

                char *buffer_save2;
                buffer_save2 = new char[buffer_size];

                string buffer_seq_string2;
                int length_of_buffer_seq_string2;
              
                unsigned long int index = 0;
                while(!stream_to_file2.eof())
                {
                   
                        Clear_Buffer_Array(buffer_save2);
                        stream_to_file2>>buffer_save2;

                        // Create a string representation of the sequence:
                        buffer_seq_string2.clear();
                        buffer_seq_string2.assign(buffer_save2);
                        length_of_buffer_seq_string2 = buffer_seq_string2.length();

                        for(int i=0;i<length_of_buffer_seq_string2;i++,index++)
                        {
                            full_bacillus_genome_temp[index] = buffer_seq_string2.at(i);
                        }

                } // while() ends

                //Copying into the actual array (excluding the header chars)
                for(unsigned long int i = 0; i<length_of_full_bacillus_genome; i++)
                {
                    full_bacillus_genome[i] = full_bacillus_genome_temp[i+62];
                }

                // Release temp array:
                delete[] full_bacillus_genome_temp;
              

                // Close stream:
                if(stream_to_file2.is_open())
                {
                    stream_to_file2.close();
                }

                // Release memories:              
                delete[] buffer_save2;


            }// else() for file stream check ends here. We are done reading the Bacillus genome data.
        
        }
        catch(const exception& e)
        {
            cout<<"\n\t\tException Caught While Trying to Read in the Bacillus Genome Data. Exiting Program."<<endl;
            cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
            exit(EXIT_FAILURE);
        }

    }//else for filepath check ends here

}




void FASTAreadset_DA::Generate_Bacillus_16mers()
{

    // ------ Generate all possible 16mers from the
    // Bacillus genome data:


    try
    {
        // First, create the linked list:
        if(all_bacillus_16mers==NULL)
        {
            all_bacillus_16mers = new LinkedList;
        }

       

        char *buffer_to_read_into;
        buffer_to_read_into = new char[length_of_a_16mer+1]; // +1 for null character.
        Clear_Buffer_Array_With_Length(buffer_to_read_into,length_of_a_16mer+1);
      
       

        for(unsigned long int i = 0; i+(length_of_a_16mer-1) < length_of_full_bacillus_genome; i++)
        {
            
          
            
            for(unsigned long int j = 0; j<length_of_a_16mer; j++)
            {
                buffer_to_read_into[j] = full_bacillus_genome[i+j];
            }
            

            // Inserting terminating null character
            buffer_to_read_into[length_of_a_16mer] = '\0';
           
            
            // We ignore the null char at the end here. The LinkedList object
            // can handle it:
            all_bacillus_16mers->Insert_Item_At_Front(buffer_to_read_into,length_of_a_16mer); 

            // Clear the buffer:
            Clear_Buffer_Array_With_Length(buffer_to_read_into,length_of_a_16mer+1);

        }

         
        // Done reading. Release the memories:
        delete[] buffer_to_read_into;
       

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Trying to Generate 16mers From Bacillus Genome Data. Exiting Program."<<endl;
        cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

}


bool FASTAreadset_DA::Search_Hash_Table_For_Given_16mer(const char* given_16mer)
{
    
   try
   {
        // Get the radix value of this sequence:
        unsigned long int radix_value = Get_Radix_Of_The_Sequence(given_16mer);

        if(hash_table[radix_value] == true)
        {
            return true;
        }
        else
        {
            return false;
        }
   }
   catch(const exception& e)
   {
       cout<<"\n\t\tException Caught While Searching Hash Table for a Given 16mer. Exiting Program"<<endl;
       cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
       exit(EXIT_FAILURE);
   }    

}



unsigned long int FASTAreadset_DA::Get_Hash_Table_Size()
{

    return hash_table_size;

}



unsigned long int FASTAreadset_DA::Get_Total_Number_Of_Hash_Collisions()
{

    return total_collisions;

}


unsigned long int FASTAreadset_DA::Get_Num_Of_Unique_Hash_Keys()
{
    unsigned long int num_of_unique_hash_keys = 0;

    for(unsigned long int i = 0; i<hash_table_size; i++)
    {
        if(hash_table[i]==true)
        {
            num_of_unique_hash_keys++;
        }
    }


    return num_of_unique_hash_keys;

}




unsigned long int FASTAreadset_DA::Get_Total_Number_Of_16mers()
{
    unsigned long int total_16mers = 0;

    if(all_bacillus_16mers == NULL)
    {   
       
        return total_16mers;
    }
    else
    {       
        total_16mers = all_bacillus_16mers->Get_List_Length();
        return total_16mers;
    }
}



unsigned long int FASTAreadset_DA::Search_For_All_16mers()
{
    
    try
    {  
        // Get the total num of 16mers:
        unsigned long int num_of_16mers = Get_Total_Number_Of_16mers();


        // Variables for search result info:
        bool search_result = false;
        unsigned long int positive_hits = 0;


        // Buffer array for holding seq from
        // a list node:
        char *buffer_for_list_node_content;
        int node_seq_length;
        
        // A List Node type pointer
        // for accessing current
        // List Node:
        ListNode *temp_list_node;


        // Set list's current pointer
        // to the head:
        all_bacillus_16mers->Reset_Current_To_Head();

        for(unsigned long int i = 0; i < num_of_16mers; i++)
        {
            if(i < num_of_16mers-1)
            {
                temp_list_node = new ListNode; // Has destructor.

                // Obtain current node:
                all_bacillus_16mers->Copy_Current_Node_Content(temp_list_node);
                
                // Obtain current node content:
                node_seq_length = temp_list_node->Get_Node_Content_Length();
                buffer_for_list_node_content = new char[node_seq_length];
                
                temp_list_node->Get_Node_Content(buffer_for_list_node_content,node_seq_length);

                // Search for this node content in the hash table:
                search_result = Search_Hash_Table_For_Given_16mer(buffer_for_list_node_content);

                // Update positive hits:
                if(search_result == true)
                {
                    positive_hits++;
                }


                // move current to next node:
                all_bacillus_16mers->Move_Current_To_Next();


                // Release dyanmically allocated
                // array memories:
                delete[] buffer_for_list_node_content;
                buffer_for_list_node_content = NULL;
                temp_list_node->~ListNode();

            }
            else // current is pointing to the last node right now
            {
                temp_list_node = new ListNode; // Has destructor.

                // Obtain current node:
                all_bacillus_16mers->Copy_Current_Node_Content(temp_list_node);
                
                // Obtain current node content:
                node_seq_length = temp_list_node->Get_Node_Content_Length();
                buffer_for_list_node_content = new char[node_seq_length];
                
                temp_list_node->Get_Node_Content(buffer_for_list_node_content,node_seq_length);


                // Search for this node content in the hash table:
                search_result = Search_Hash_Table_For_Given_16mer(buffer_for_list_node_content);

                // Update positive hits:
                if(search_result == true)
                {
                    positive_hits++;
                }

                //No need to move to next node. We are at the last node.
                // Release dyanmically allocated
                // array memories:
                delete[] buffer_for_list_node_content;
                buffer_for_list_node_content = NULL;
                temp_list_node->~ListNode();

            }
        } // for loop ends

        all_bacillus_16mers->Reset_Current_To_NULL();

        return positive_hits;
        
        

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Searching for All 16mers. Exiting Program."<<endl;
        cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }


}

// --------------------------------------------- End: All Public Member Function Definitions -------------------------------------------
