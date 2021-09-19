#include "DirectAccessHashTable.h"


/*

Class definition for the DirectAccessHashTable class.

Author:
    Nazmul (mh2752@nau.edu)

*/





// ------------------------------------------------- Begin: Class Ctor & Dtor ------------------------------------------------------------------------


DirectAccessHashTable::DirectAccessHashTable(unsigned int r_base,unsigned int max_seq_length)
{
    // Update the member variables:
    radix_base = r_base;
    max_sequence_length = max_seq_length;


    // Calculate the hash table size:
    hash_table_size = (unsigned long int) pow(radix_base,max_sequence_length);


    // Allocate memories:
    try
    {
        hash_table = new bool[hash_table_size];

        // Initializing every cell to false:
        for(unsigned long int index = 0; index < hash_table_size; index++)
        {
            hash_table[index] = false;
        }



        // For k-th mer info array:
        hash_table_kth_mer_info = new int[hash_table_size];

        // Initialize to -1:
        for(unsigned long int index = 0; index < hash_table_size; index++)
        {
            hash_table_kth_mer_info[index] = -1;
        }


        
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught in Constructor While Trying to Allocate Memory For the Hash Table. Exiting Program Now."<<endl;
        cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

}


DirectAccessHashTable::~DirectAccessHashTable()
{
    if(hash_table!=NULL && hash_table_size !=0)
    {
        delete[] hash_table;
    }

    if(hash_table_kth_mer_info !=NULL && hash_table_size !=0)
    {
        delete[] hash_table_kth_mer_info;
    }
}

// ------------------------------------------------- End: Class Ctor & Dtor --------------------------------------------------------------------------







// ------------------------------------------------- Begin: Class Public Member Functions  ------------------------------------------------------------


void DirectAccessHashTable::Insert_Sequence_Into_DirectAccessHashTable(const char* given_seq,unsigned int seq_length,int seq_kth_mer_info)
{
    if(seq_length != max_sequence_length)
    {
        cout<<"\n\t\tInvalid Sequence Length Inside Insert Function Detected. Exiting Program Now."<<endl;
        exit(EXIT_FAILURE);
    }

    unsigned long int seq_radix = Get_Radix_Of_The_Sequence(given_seq);

    if(hash_table[seq_radix] == false)
    {
        hash_table[seq_radix] = true;

        // Set k-th mer info:
        hash_table_kth_mer_info[seq_radix] = seq_kth_mer_info;
    }

    else
    {
        // Already set. Do nothing.
    }

}


void DirectAccessHashTable::Search_Sequence_In_DirectAccessHashTable(const char* key_seq,unsigned int key_length,bool& found,int& kth_mer_info)
{
    
    if(key_length != max_sequence_length)
    {
        cout<<"\n\t\tInvalid Sequence Length Inside Search Function Detected. Exiting Program Now."<<endl;
        exit(EXIT_FAILURE);
    }


    unsigned long int seq_radix = Get_Radix_Of_The_Sequence(key_seq);

    if(hash_table[seq_radix] == true)
    {
        found = true;
        kth_mer_info = hash_table_kth_mer_info[seq_radix];
    }
    else
    {
        found = false;
        kth_mer_info = -1;
    }

}



unsigned long int DirectAccessHashTable::Get_Size_Of_The_DirectAccessHashTable()
{
    return hash_table_size;
}


// ------------------------------------------------- End: Class Public Member Functions ---------------------------------------------------------------










// ------------------------------------------------- Begin: Class Private Member Functions  ------------------------------------------------------------
unsigned long int DirectAccessHashTable::Get_Radix_Digit_Value(char radix_digit)
{
    
    // A = 0, C = 1, G = 2, T = 3
    if(radix_digit == 'A')
    {
        return 0;
    }

    else if(radix_digit == 'C')
    {
        return 1;
    }

    else if(radix_digit == 'G')
    {
        return 2;
    }

    else if(radix_digit == 'T')
    {
        return 3;
    }

    else
    {
        cout<<"\n\t\tInvalid Char Recieved in Get_Radix_Digit_Value() Function."<<endl;
        exit(EXIT_FAILURE);
    }


}





unsigned long int DirectAccessHashTable::Get_Radix_Of_The_Sequence(const char* sequence)
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



void DirectAccessHashTable::Clear_Buffer_Array(char* &given_buffer)
{
    for(unsigned int i=0; i < buffer_size; i++)
    {
        given_buffer[i] = '\0';
    }
}


void DirectAccessHashTable::Clear_Buffer_Array_With_Length(char* &given_buffer,unsigned int length)
{
    for(unsigned int i=0;i<length;i++)
    {
        given_buffer[i] = '\0';
    }
}

// ------------------------------------------------- End: Class Private Member Functions ---------------------------------------------------------------