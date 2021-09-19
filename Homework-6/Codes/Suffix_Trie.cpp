#include "Suffix_Trie.h"



// --------------------------------------------------- Begin: Classs Ctor & Dtor ------------------------------------------------------------------


// Default Ctor():
Suffix_Trie::Suffix_Trie()
{
    root = NULL;
    sars_full_genome = NULL;
    sars_full_genome_length = 0;

}


// Overloaded Ctor():
Suffix_Trie::Suffix_Trie(const char* sequence,unsigned int sequence_length)
{
    root = NULL;

    try
    {
        // Allocating memory for sars_full_genome array:
        sars_full_genome_length = sequence_length;

        sars_full_genome = new char[sars_full_genome_length];

        // Copy into the array:
        for(unsigned int index = 0; index < sars_full_genome_length; index++)
        {
            sars_full_genome[index] = sequence[index];
        }

        // Call the function to genrate and insert
        // all the suffixes into the trie:
        Generate_And_Insert_Sequence_Suffixes(sars_full_genome,sars_full_genome_length); 


    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException caught while in overloaded constructor. Exiting program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    


}


// Default Dtor():
Suffix_Trie::~Suffix_Trie()
{
    // De-allocate SARS genome array:
    if(sars_full_genome != NULL)
    {
        delete[] sars_full_genome;
        sars_full_genome_length = 0;
    }

    // De-alloacte Trie nodes:
    if(root != NULL)
    {
        
        // Create the queue:
        Queue nodes_queue;

        // Enqueue the root into the stack:
        nodes_queue.Enqueue(root);

        // A temporary trie node:
        Trie_Node* temp_node;

        // Now, 'Enter-The-Loop':
        while( ! nodes_queue.Is_Queue_Empty() )
        {
            nodes_queue.Dequeue(temp_node);

            if(temp_node!=NULL)
            {
                // Push all the children
                // nodes into the stack:
                if(temp_node->A != NULL)
                {
                    nodes_queue.Enqueue(temp_node->A);
                }
                if(temp_node->C != NULL)
                {
                    nodes_queue.Enqueue(temp_node->C);
                }
                if(temp_node->G != NULL)
                {
                    nodes_queue.Enqueue(temp_node->G);
                }
                if(temp_node->T != NULL)
                {
                    nodes_queue.Enqueue(temp_node->T);
                }
                if(temp_node->DS != NULL)
                {
                    nodes_queue.Enqueue(temp_node->DS);
                }
            }


            // De-allocate:
            delete temp_node;
            temp_node = NULL;

        } // While loop ends


        // make root NULL:
        root = NULL;

    }

}

// --------------------------------------------------- End: Classs Ctor & Dtor  -------------------------------------------------------------------







// --------------------------------------------------- Begin: Class Public Member Functions ------------------------------------------------------

void Suffix_Trie::Read_Subject_Sequence_From_File(const char* file_path,int file_path_length)
{
    if(file_path == NULL || file_path_length == 0)
    {
        cout<<"\n\t\tEmpty Filepath to Genome File Detected. Exiting Program."<<endl;
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
        
        // ---------------------------------------------------------------------------------------------------------

        // Allocate required array memories:
        // Memory for initial array (includes header):
        char initial_array[sequence_length_with_header];
        sars_full_genome = new char[sequence_length_with_out_header];
        
        // Update the subject length member variable
        sars_full_genome_length = sequence_length_with_out_header;

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
        

        // Copy from initial array into
        // final array (excluding header)
        for(unsigned int index = 0; index < sars_full_genome_length; index++)
        {
            sars_full_genome[index] = initial_array[index+sars_genome_header_size];
        }

        cout<<"\n\t\tLength of SARS Genome Read From File = "<<sars_full_genome_length<<endl;

        
        // Populating the trie:
        Generate_And_Insert_Sequence_Suffixes(sars_full_genome,sars_full_genome_length);
       
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


void Suffix_Trie::Read_And_Search_With_AppendixB(const char* file_path,int file_path_length)
{
        if(file_path == NULL || file_path_length == 0)
        {
        cout<<"\n\t\tEmpty Filepath to Genome File Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE); 
        }

         // Open ifstream to file
        ifstream stream_to_file;
        stream_to_file.open(file_path);

        if((!stream_to_file) || (!stream_to_file.is_open()))
        {
            cout<<"\n\t\tCouldnot Open Stream to AppendixB Data File. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }

        
        // -------------------------------------------------------------------------------------------
      

        // 256-length char buffer arrays:
        char* buffer_1;
        char* buffer_2;
        buffer_1 = new char[buffer_length];
        buffer_2 = new char[buffer_length];

        // A temporary string object:
        string temp_str;

        // A char type pointer for holding the sequence:
        char* temp_seq;

        unsigned int temp_seq_length;

        bool is_found;

        while(!stream_to_file.eof())
        {   
            // Clear the buffer first:
            Clear_Buffer_Array(buffer_1);
            Clear_Buffer_Array(buffer_2);
            
            stream_to_file>>buffer_1; // The header
            stream_to_file>>buffer_2; // The sequence

            // Clear the string:
            temp_str.clear();

            // Assign the buffer content
            // to the temp string:
            temp_str.assign(buffer_2);

            temp_seq_length = temp_str.length();

            // Copy it into the array:
            temp_seq = new char[temp_seq_length];
            for(unsigned int i = 0; i < temp_seq_length; i++)
            {
                temp_seq[i] = temp_str[i];
            }

            is_found = Search_In_Trie(temp_seq,temp_seq_length);

            if(is_found == true)
            {
                cout<<"\n\t\tSequence: "<<buffer_2<<" was found in the trie."<<endl;
            }
            else
            {
               cout<<"\n\t\tSequence: "<<buffer_2<<" was NOT found in the trie."<<endl; 
            }


            // Free the array:
            delete[] temp_seq;            

        }
        // Close the stream:
        stream_to_file.close();

        // Free buffers:
        delete[] buffer_1;
        delete[] buffer_2; 



}




void Suffix_Trie::Insert_Into_Trie(const char* given_sequence,unsigned int given_sequence_length)
{
    if(given_sequence == NULL || given_sequence_length == 0)
    {
        cout<<"\n\t\tTrying to insert an empty sequence into the trie. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


    try
    {
        if(root == NULL) // Inserting the first sequence into an empty trie
        {
            // Create the root node:
            Trie_Node* node;
            node = new Trie_Node;
            root = node;           
            
            
            Trie_Node* current_node;
            current_node = root;
            char char_at_current_index;

            for(unsigned int index = 0; index < given_sequence_length; index++)
            {
                char_at_current_index = given_sequence[index];

                if(char_at_current_index == 'A')
                {
                        if(current_node->A == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->A = temp_node;
                            current_node = current_node->A;
                        }
                        else
                        {
                            current_node = current_node->A;
                        }                   

                }

                else if(char_at_current_index == 'C')
                {
                        if(current_node->C == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->C = temp_node;

                            current_node = current_node->C;
                        }

                        else
                        {
                            current_node = current_node->C;
                        }
                }

                else if(char_at_current_index == 'G')
                {
                        if(current_node->G == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->G = temp_node;
                            current_node = current_node->G;
                        }
                        else
                        {
                            current_node = current_node->G;
                        }
                }

                else if(char_at_current_index == 'T')
                {
                        if(current_node->T == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->T = temp_node;

                            current_node = current_node->T;
                        }
                        else
                        {
                            current_node = current_node->T;
                        }

                }

                else if(char_at_current_index == '$')
                {
                        if(current_node->DS == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->DS = temp_node;
                        }

                }                

            } // for loop ends

            // To avoid dangling pointer:
            current_node = NULL;
        }

        
        else // The trie is not empty
        {
            Trie_Node* current_node;
            current_node = root;
            char char_at_current_index;

            for(unsigned int index = 0; index < given_sequence_length; index++)
            {
                char_at_current_index = given_sequence[index];

                if(char_at_current_index == 'A')
                {
                        if(current_node->A == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->A = temp_node;
                            current_node = current_node->A;
                        } 
                        else
                        {
                            current_node = current_node->A;
                        }                  

                }

                else if(char_at_current_index == 'C')
                {
                        if(current_node->C == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->C = temp_node;

                            current_node = current_node->C;
                        }
                        else
                        {
                            current_node = current_node->C;
                        }
                }

                else if(char_at_current_index == 'G')
                {
                        if(current_node->G == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->G = temp_node;
                            current_node = current_node->G;
                        }
                        else
                        {
                            current_node = current_node->G;
                        }
                }

                else if(char_at_current_index == 'T')
                {
                        if(current_node->T == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->T = temp_node;

                            current_node = current_node->T;
                        }
                        else
                        {
                            current_node = current_node->T;
                        }

                }

                else if(char_at_current_index == '$')
                {
                        if(current_node->DS == NULL)
                        {
                            // Create node
                            Trie_Node* temp_node;
                            temp_node = new Trie_Node;

                            // Update pointer
                            current_node->DS = temp_node;
                        }

                }                

            } // for loop ends

            // To avoid dangling pointer:
            current_node = NULL;           

        }
        
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException caught while trying to insert a sequence into the trie. Exiting program."<<endl;;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }    

}




bool Suffix_Trie::Search_In_Trie(const char* sequence, unsigned int sequence_length)
{
    
    if(sequence == NULL || sequence_length == 0)
    {
        cout<<"\n\t\tTrying to search for a NULL sequence. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }

    if(root == NULL) // Empty trie. Nothing to search against. Returning false.
    {
        return false;
    }

    else
    {
        Trie_Node* current_node;
        current_node = root;

        char char_at_current_index;
        
        // Initially, we assume the
        // sequence does not exist
        // in the trie.
        bool is_found = false;

        for(unsigned int index = 0; index < sequence_length; index++)
        {
            char_at_current_index = sequence[index];

            if(index == sequence_length-1) 
            {
                if(char_at_current_index == 'A')
                {
                    if(current_node->A != NULL) 
                    {
                        is_found = true;
                    }
                   
                }

                else if(char_at_current_index == 'C')
                {
                    if(current_node->C != NULL) 
                    {
                       is_found = true;
                    }
                    
                }

                else if(char_at_current_index == 'G')
                {
                    if(current_node->G != NULL) 
                    {
                        is_found = true;
                    }
                    
                }

                else if(char_at_current_index == 'T')
                {
                    if(current_node->T != NULL) 
                    {
                        is_found = true;
                    }
                    
                }
               
            }

            else
            {
                if(char_at_current_index == 'A')
                {
                    if(current_node->A != NULL) // The path exists!!!
                    {
                        // Go to the next node in the link:
                        current_node = current_node->A;
                    }
                    else // The path does not exist.
                    {
                        // break out of the loop:
                        break;
                    }
                }

                else if(char_at_current_index == 'C')
                {
                    if(current_node->C != NULL) // The path exists!!!
                    {
                        // Go to the next node in the link:
                        current_node = current_node->C;
                    }
                    else // The path does not exist.
                    {
                        // break out of the loop:
                        break;
                    }
                }

                else if(char_at_current_index == 'G')
                {
                    if(current_node->G != NULL) // The path exists!!!
                    {
                        // Go to the next node in the link:
                        current_node = current_node->G;
                    }
                    else // The path does not exist.
                    {
                        // break out of the loop:
                        break;
                    }
                }

                else if(char_at_current_index == 'T')
                {
                    if(current_node->T != NULL) // The path exists!!!
                    {
                        // Go to the next node in the link:
                        current_node = current_node->T;
                    }
                    else // The path does not exist.
                    {
                        // break out of the loop:
                        break;
                    }
                }              

            }

            
            
        } // For loop ends here.

        // Preventing danling pointer:
        current_node = NULL;


        // Return the resultP:
        return is_found;
    }

}



unsigned int Suffix_Trie::Generate_And_Search_For_5k_36mers()
{
    if(root == NULL)
    {
        cout<<"\n\t\tThe trie is empty. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


    unsigned int num_of_36mers_to_generate = 5000;

    unsigned int positive_search_hits = 0;
    bool search_result;
   

    int random_start_index;
    int counter = 0;
    char* random_kmer;
    
    while(counter < num_of_36mers_to_generate)
    {
        random_start_index = (unsigned int) rand() % sars_full_genome_length;

        if(random_start_index+(length_of_a_kmer-1) < sars_full_genome_length)
        {
            counter++;

            // Allocate memories:
            random_kmer = new char[length_of_a_kmer]; // +1 for terminating $ character

            // copy content:
            for(int i=0; i< length_of_a_kmer; i++)
            {
                random_kmer[i] = sars_full_genome[random_start_index+i];
            }


            search_result = Search_In_Trie(random_kmer,length_of_a_kmer);
            if(search_result == true)
            {
                positive_search_hits++;
            }
            
            // De-allocate:
            delete[] random_kmer;
            random_kmer = NULL;
        }
    } // while loop ends

    return positive_search_hits;   
}


unsigned int Suffix_Trie::Generate_And_Search_For_50k_36mers()
{
    if(root == NULL)
    {
        cout<<"\n\t\tThe trie is empty. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


    unsigned int num_of_36mers_to_generate = 50000;

    unsigned int positive_search_hits = 0;
    bool search_result;
   

    int random_start_index;
    int counter = 0;
    char* random_kmer;
    
    while(counter < num_of_36mers_to_generate)
    {
        random_start_index = (unsigned int) rand() % sars_full_genome_length;

        if(random_start_index+(length_of_a_kmer-1) < sars_full_genome_length)
        {
            counter++;

            // Allocate memories:
            random_kmer = new char[length_of_a_kmer]; // +1 for terminating $ character

            // copy content:
            for(int i=0; i< length_of_a_kmer; i++)
            {
                random_kmer[i] = sars_full_genome[random_start_index+i];
            }


            search_result = Search_In_Trie(random_kmer,length_of_a_kmer);
            if(search_result == true)
            {
                positive_search_hits++;
            }
            
            // De-allocate:
            delete[] random_kmer;
            random_kmer = NULL;
        }
    } // while loop ends

    return positive_search_hits;   
}


unsigned int Suffix_Trie::Generate_And_Search_For_100k_36mers()
{
    if(root == NULL)
    {
        cout<<"\n\t\tThe trie is empty. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


    unsigned int num_of_36mers_to_generate = 100000;

    unsigned int positive_search_hits = 0;
    bool search_result;
   

    int random_start_index;
    int counter = 0;
    char* random_kmer;
    
    while(counter < num_of_36mers_to_generate)
    {
        random_start_index = (unsigned int) rand() % sars_full_genome_length;

        if(random_start_index+(length_of_a_kmer-1) < sars_full_genome_length)
        {
            counter++;

            // Allocate memories:
            random_kmer = new char[length_of_a_kmer]; // +1 for terminating $ character

            // copy content:
            for(int i=0; i< length_of_a_kmer; i++)
            {
                random_kmer[i] = sars_full_genome[random_start_index+i];
            }


            search_result = Search_In_Trie(random_kmer,length_of_a_kmer);
            if(search_result == true)
            {
                positive_search_hits++;
            }
            
            // De-allocate:
            delete[] random_kmer;
            random_kmer = NULL;
        }
    } // while loop ends

    return positive_search_hits;   
}



bool Suffix_Trie::Is_Trie_Empty()
{
    return (root == NULL);
}


unsigned long int Suffix_Trie::Get_Trie_Size()
{
    Trie_Node* temp;
    temp = root;

    unsigned long int trie_size = Count_Nodes(root);
    temp = NULL;
    
    return trie_size;
}



void Suffix_Trie::Test_With_First10_36mers()
{
    if(root == NULL)
    {
        cout<<"\n\t\tThe trie is empty. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


    unsigned int num_of_36mers_to_generate = 10;    
    bool search_result;
   

    int random_start_index;
    int counter = 0;
    char* array_kmer;
    
   for(unsigned int index=0; index< 10; index++)
   {
        
            array_kmer = new char[length_of_a_kmer];

            for(int j = 0; j < length_of_a_kmer; j++)
            {
                array_kmer[j] = sars_full_genome[index+j];
            }          


            search_result = Search_In_Trie(array_kmer,length_of_a_kmer);

            if(search_result == true)
            {
                cout<<"Found!!!"<<endl;
                
            }
            
            // De-allocate:
            delete[] array_kmer;
            array_kmer = NULL;

    } // for loop ends

}


// --------------------------------------------------- End: Class Public Member Functions  -------------------------------------------------------











// --------------------------------------------------- Begin: Class Private Member Functions ------------------------------------------------------
void Suffix_Trie::Clear_Buffer_Array(char* &given_buffer)
{
    for(unsigned int i=0;i<buffer_length;i++)
    {
        given_buffer[i] = '\0';
    }
}


void Suffix_Trie::Generate_And_Insert_Sequence_Suffixes(const char* sequence, unsigned int sequence_length)
{
    
    if( sequence == NULL || sequence_length == 0)
    {
        cout<<"\n\t\tEmpty SARS-COV2 sequence detected. Exiting program."<<endl;
        exit(EXIT_FAILURE);
    }


    try
    {       
        
        char* temp_seq_array;
        temp_seq_array = NULL;
        unsigned int temp_seq_array_length; // Decrement by 1 for the suffixes

        for(unsigned int i = 0; i < sequence_length; i++)
        {        

           
                // Calculating the length for the temp sequence:
                temp_seq_array_length = (sequence_length - i)+1; // +1 for adding '$'
                temp_seq_array = new char[temp_seq_array_length];


                // Copying:
                for(unsigned int index = 0; index < temp_seq_array_length; index++)
                {

                    if(index == temp_seq_array_length-1)
                    {
                        temp_seq_array[index] = '$';
                    }

                    else
                    {
                        temp_seq_array[index] = sequence[i+index];
                    }

                }

                          

                // Call the insert function:
                Insert_Into_Trie(temp_seq_array,temp_seq_array_length);

                // De-allocate temp seq array:
                if(temp_seq_array != NULL)
                {
                    
                    delete[] temp_seq_array;
                    temp_seq_array = NULL;
                    temp_seq_array_length = 0;

                }            

        } // for loop ends


            // Inserting the last '$' suffix string:
            temp_seq_array_length = 1;
            temp_seq_array = new char[temp_seq_array_length];
            temp_seq_array[0] = '$';

            // Call the insert function:
            Insert_Into_Trie(temp_seq_array,temp_seq_array_length);

            // Free memories:
            delete[] temp_seq_array;
            temp_seq_array = NULL;
            temp_seq_array_length = 0;

      

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException caught while generating and inserting sequence suffixes. Exiting program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }   

}


unsigned long int Suffix_Trie::Count_Nodes(const Trie_Node* node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + Count_Nodes(node->A) + Count_Nodes(node->C) + Count_Nodes(node->G) + Count_Nodes(node->T) + Count_Nodes(node->DS);
    }
}






// --------------------------------------------------- End: Class Private Member Functions  -------------------------------------------------------