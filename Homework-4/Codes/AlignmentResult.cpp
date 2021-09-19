# include "AlignmentResult.h"


/*

Class definitions for the AlignmentResult
class.

Author:
Nazmul (mh2752@nau.edu)

*/



// ----------------------------------------- Begin: Class Ctor & Dtor ---------------------------------------------------------------------------------



// Default Ctor
AlignmentResult::AlignmentResult()
{

    aligned_portion_length = 0;

    aligned_subject_portion = NULL;
    aligned_target_portion = NULL;
    alignment_codes = NULL;
}


// Overloaded Ctor
AlignmentResult::AlignmentResult(unsigned int portion_length)
{
    // Set the length variable:
    aligned_portion_length = portion_length;


    // Allocate memories:
    try
    {
        aligned_subject_portion = new char[aligned_portion_length];
        // Initialize with null character:
        for(unsigned int i=0; i< aligned_portion_length; i++)
        {
            aligned_subject_portion[i] = '\0';
        }



        aligned_target_portion = new char[aligned_portion_length];
        // Initialize with null character:
        for(unsigned int i=0; i< aligned_portion_length; i++)
        {
            aligned_target_portion[i] = '\0';
        }


        alignment_codes = new char[aligned_portion_length];
        // Initialize with null character:
        for(unsigned int i=0; i< aligned_portion_length; i++)
        {
            alignment_codes[i] = '\0';
        }

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught In AlignmentResult Overloaded Constructor. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    
}


// Default Dtor
AlignmentResult::~AlignmentResult()
{

    // De-allocate all three arrays:

    if(aligned_subject_portion != NULL)
    {
        delete[] aligned_subject_portion;
    }
    aligned_subject_portion = NULL;

    if(aligned_target_portion != NULL)
    {
        delete[] aligned_target_portion;
    }
    aligned_target_portion = NULL;

    if(alignment_codes != NULL)
    {
        delete[] alignment_codes;
    }
    alignment_codes = NULL;

    aligned_portion_length = 0;

}

// ----------------------------------------- End: Class Ctor & Dtor  ----------------------------------------------------------------------------------






// ----------------------------------------- Begin: Class Public Member Functions ----------------------------------------------------------------------



void AlignmentResult::Set_Aligned_Portion_Length(unsigned int portion_length)
{
   // Set the length variable:
    aligned_portion_length = portion_length;


    // Allocate memories:
    try
    {
        aligned_subject_portion = new char[aligned_portion_length];
        // Initialize with null character:
        for(unsigned int i=0; i< aligned_portion_length; i++)
        {
            aligned_subject_portion[i] = '\0';
        }



        aligned_target_portion = new char[aligned_portion_length];
        // Initialize with null character:
        for(unsigned int i=0; i< aligned_portion_length; i++)
        {
            aligned_target_portion[i] = '\0';
        }


        alignment_codes = new char[aligned_portion_length];
        // Initialize with null character:
        for(unsigned int i=0; i< aligned_portion_length; i++)
        {
            alignment_codes[i] = '\0';
        }

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught In AlignmentResult Set Length Function. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
}


unsigned int AlignmentResult::Get_Aligned_portion_Length()
{
    return aligned_portion_length;
}



void AlignmentResult::Set_Aligned_Subject_Sequence_Portion(const char* subject_portion,const unsigned int subject_portion_length)
{
    if(subject_portion_length != aligned_portion_length)
    {
        cout<<"\n\t\tDifferent Length for Subject Portion Detected in Parameter. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    else // Same length. Go ahead.
    {
        if(aligned_subject_portion == NULL)
        {
            cout<<"\n\t\tNULL Array Pointer for Aligned Subject Portion Detected. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }
        
        else
        {
            // Go ahead and copy the contents:
            for(unsigned int i=0;i<subject_portion_length;i++)
            {
                aligned_subject_portion[i] = subject_portion[i];
            }
        }

    }
}

void AlignmentResult::Set_Aligned_Target_Sequence_Portion(const char* target_portion, const unsigned int target_portion_length)
{
    if(target_portion_length != aligned_portion_length)
    {
        cout<<"\n\t\tDifferent Length for Target Portion Detected in Parameter. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    else
    {
        if(aligned_target_portion == NULL)
        {
            cout<<"\n\t\tNULL Array Pointer for Aligned Target Portion Detected. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }

        else
        {
            // Go ahead and copy the contents:
            for(unsigned int i=0;i<target_portion_length;i++)
            {
                aligned_target_portion[i] = target_portion[i];
            }
        }
    }
}



void AlignmentResult::Set_Alignment_Codes(const char* codes,const unsigned int codes_length)
{
    if(codes_length != aligned_portion_length)
    {
        cout<<"\n\t\tDifferent Length for Alignment Codes Detected in Parameter. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    else
    {
        if(alignment_codes == NULL)
        {
            cout<<"\n\t\tNULL Array Pointer for Alignment Codes Detected. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }

        else
        {
            // Go ahead and copy the contents:
            for(unsigned int i=0;i<aligned_portion_length;i++)
            {
                alignment_codes[i] = codes[i];
            }
        }
    }
}




void AlignmentResult::Get_Aligned_Subject_Sequence_Portion(char* &subject_array,const unsigned int subject_array_length)
{
    if(subject_array_length != aligned_portion_length)
    {
        cout<<"\n\t\tDifferent Length of the Subject Array Found. Exiting Porgram."<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        if((aligned_subject_portion != NULL) && (aligned_portion_length != 0))
        {
            for(unsigned int i=0;i<subject_array_length;i++)
            {
                subject_array[i] = aligned_subject_portion[i];
            }
        }
        
        else
        {
            cout<<"\n\t\tNULL Aligned Subject Array Detected. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }
    }
}



void AlignmentResult::Get_Aligned_Target_Sequence_Portion(char* &target_array,const unsigned int target_array_length)
{
    if(target_array_length != aligned_portion_length)
    {
        cout<<"\n\t\tDifferent Length of the Target Array Found. Exiting Porgram."<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        if((aligned_target_portion != NULL) && (aligned_portion_length != 0))
        {
            for(unsigned int i=0;i<target_array_length;i++)
            {
                target_array[i] = aligned_target_portion[i];
            }
        }
        
        else
        {
            cout<<"\n\t\tNULL Aligned Target Array Detected. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }
    }
}


void AlignmentResult::Get_Alignment_Codes(char* &codes_array,const unsigned int codes_array_length)
{
    if(codes_array_length != aligned_portion_length)
    {
        cout<<"\n\t\tDifferent Length for Codes Array Detected. Exiting Program Now."<<endl;
        exit(EXIT_FAILURE);
    }

    else
    {
        if((alignment_codes != NULL) && (aligned_portion_length != 0))
        {
            for(unsigned int i=0;i<codes_array_length;i++)
            {
                codes_array[i] = alignment_codes[i];
            }
        }
        else
        {
            cout<<"\n\t\tNULL Aligment Codes Array detected. Exiting Program Now."<<endl;
            exit(EXIT_FAILURE);
        }
    }
}


void AlignmentResult::Print_Results()
{
    cout<<"\nAlignment Results: "<<endl;

    for(unsigned int i = 0; i< aligned_portion_length; i++)
    {
        cout<<aligned_subject_portion[i]<<" ";
    }
    cout<<endl;

    for(unsigned int i = 0; i< aligned_portion_length; i++)
    {
        cout<<alignment_codes[i]<<" ";
    }
    cout<<endl;


    for(unsigned int i = 0; i< aligned_portion_length; i++)
    {
        cout<<aligned_target_portion[i]<<" ";
    }
    cout<<endl;  


}


// ----------------------------------------- End: Class Public Member Functions   ----------------------------------------------------------------------




// ----------------------------------------- Begin: Class Private Member Functions ---------------------------------------------------------------------

// ----------------------------------------- End: Class Private Member Functions   ---------------------------------------------------------------------