#include "FASTAreadset_DA.h"
#include "FASTAreadset_Chain.h"
#include <cstring>



int main(int c,char** argv)
{

    if((c<4) || (c>6))
    {
        cout<<"\n\t\tWrong number of command line inputs. Follow the command line input format specified in the readme.txt file."<<endl;        
    }
    else
    {


        // --------------------------------------- Read the Given File Paths and Sub-problem Choice ------------------------------------------------

        string filepath_to_readset(argv[1]);       
        int path_length_readset = filepath_to_readset.length();

        // A char array holding the file path details (null terminated)
        char* fp1;
        fp1 = new char[path_length_readset+1];

        for(int i=0; i<path_length_readset+1; i++)
        {
            if(i==path_length_readset)
            {
                fp1[i] = '\0';
            }
            else
            {
                fp1[i] = filepath_to_readset[i];
            }         
        }

        cout<<"Filepath-1 = "<<fp1<<endl;


        // ------------------------------------------------------------------------------------------------------


        string filepath_Bacillus(argv[2]);        
        int file_path_length_Bacillus = filepath_Bacillus.length();

        // A char array holding the file path details (null terminated)
        char* fp2;
        fp2 = new char[file_path_length_Bacillus+1];

        for(int i=0;i<file_path_length_Bacillus+1;i++)
        {
            if(i == file_path_length_Bacillus)
            {
                fp2[i] = '\0';
            }
            else
            {
                fp2[i] = filepath_Bacillus[i];
            }
        }

        cout<<"Filepath-2 = "<<fp2<<endl;


        
        // --------------------------------------------------------------------------------------------------------

        // Get the subproblem choice:
        string sub_problem_choice(argv[3]);

        // Get the user-specified size info of the hash table:
        string hash_table_size_info("");
        unsigned long int table_size = 0;

        if(c>4)
        {
            // Set the stirng to this value:
            hash_table_size_info.assign(argv[4]);

            // Get the integer representation:
            char *temp;
            temp = new char[hash_table_size_info.length()+1];
            strcpy(temp,hash_table_size_info.c_str());

            table_size = atol(temp);

            if(table_size<0)
            {
                cout<<"\n\t\tInvalid Hash Table Size Info Detected. Exiting Program."<<endl;
                exit(EXIT_FAILURE);
            }

        }



        // Getting the search limit for 2B
        string search_limit("");
        unsigned long int search_limit_as_num = 0;
        if(c>5)
        {
            // Set the string value:
            search_limit.assign(argv[5]);
            char *temp;
            temp = new char[search_limit.length()+1];
            strcpy(temp,search_limit.c_str());

            search_limit_as_num = atol(temp);

        }



        // --------------------------------------------------------------------------------------------------------

        if(sub_problem_choice.compare("1A") == 0)
        {
            // ---- Solve for 1A

            FASTAreadset_DA frst;
            frst.Read_In_Read_Data_Set(fp1);            

            
            unsigned long int collisions = frst.Get_Total_Number_Of_Hash_Collisions();
            unsigned long int unique_seqs = frst.Get_Num_Of_Unique_Hash_Keys();
            unsigned long int hash_table_size = frst.Get_Hash_Table_Size();

            long double load_factor = (long double)unique_seqs/(long double)hash_table_size;


            cout<<"\n\tSubproblem-1A Solutions: "<<endl;
            cout<<"\n\t\tSize of the Hash Table = "<<hash_table_size<<endl;
            cout<<"\n\t\tNumber of Collisions Observed = "<<collisions<<endl;
            cout<<"\n\t\tNumber of Unique Sequences = "<<unique_seqs<<endl;
            cout<<"\n\t\tLoad Factor (alpha_sub_T) = "<<load_factor<<endl; 

        }

        else if(sub_problem_choice.compare("1B") == 0)
        {
            // ---- Solve for 1B

            FASTAreadset_DA frst;
            frst.Read_In_Read_Data_Set(fp1);
            frst.Read_In_Bacillus_Genome(fp2);
            frst.Generate_Bacillus_16mers();


            // Getting starting timestamp:
            time_t start = time(nullptr);


            unsigned long int positive_search_hits = 0;
            positive_search_hits = frst.Search_For_All_16mers();


            // Getting ending timestamp:
            time_t end = time(nullptr);

            // Calculating duration:
            time_t duration = end - start;


            // Printing the results:
            cout<<"\n\tSubproblem-1B Solution: "<<endl;
            cout<<"\n\t\tNumber of Genome 16mer Found in Readset = "<<positive_search_hits<<endl;
            cout<<"\n\t\tTime (in seconds) to Complete the Entire Search Process = "<<duration<<endl;

        }


        else if(sub_problem_choice.compare("2A")==0)
        {
            // Solve for 2A:
            if(table_size==0) // Create a hash table with default size = 10000
            {

                
                FASTAreadset_Chain frst_chain;

                // Starting timestamp:
                time_t start = time(nullptr);

                frst_chain.Read_In_Read_Data_Set(fp1);

                // Ending timestamp:
                time_t end = time(nullptr);
                time_t duration = end-start;        

            
                unsigned long int collisions = frst_chain.Get_Total_Number_Of_Hash_Collisions();                
                unsigned long int hash_table_size = frst_chain.Get_Hash_Table_Size();

                cout<<"\n\tSubproblem-2A Solutions: "<<endl;
                cout<<"\n\t\tSize of the Hash Table = "<<hash_table_size<<endl;
                cout<<"\n\t\tNumber of Collisions Observed = "<<collisions<<endl;
                cout<<"\n\t\tTime (in seconds) Required to Read the Sequence Fragment File = "<<duration<<endl;
               

            }
            else // Hash table size should be set to user specified size value
            {
                FASTAreadset_Chain frst_chain(table_size);

                // Starting timestamp:
                time_t start = time(nullptr);

                frst_chain.Read_In_Read_Data_Set(fp1);

                // Ending timestamp:
                time_t end = time(nullptr);
                time_t duration = end-start;        

            
                unsigned long int collisions = frst_chain.Get_Total_Number_Of_Hash_Collisions();                
                unsigned long int hash_table_size = frst_chain.Get_Hash_Table_Size();

                cout<<"\n\tSubproblem-2A Solutions: "<<endl;
                cout<<"\n\t\tSize of the Hash Table = "<<hash_table_size<<endl;
                cout<<"\n\t\tNumber of Collisions Observed = "<<collisions<<endl;
                cout<<"\n\t\tTime (in seconds) Required to Read the Sequence Fragment File = "<<duration<<endl;
               

            }

            
        }

        else if(sub_problem_choice.compare("2B")==0)
        {
            // Solve for 2B:
            if(table_size!=10000000)
            {
                cout<<"\n\t\tWrong Hash Table Size Supplied for Problem-2(B). It Should Be 10000000. Exiting Program"<<endl;
            }
            else
            {
                FASTAreadset_Chain frst_chain(table_size);


                frst_chain.Read_In_Read_Data_Set(fp1);
                frst_chain.Read_In_Bacillus_Genome(fp2);
                frst_chain.Generate_Bacillus_16mers();
                unsigned long int num_of_16mers = frst_chain.Get_Total_Number_Of_16mers();


                // Getting starting timestamp:
                time_t start = time(nullptr);


                unsigned long int positive_search_hits = 0;
                positive_search_hits = frst_chain.Search_Hash_Table_For_16mers(search_limit_as_num);


                // Getting ending timestamp:
                time_t end = time(nullptr);

                // Calculating duration:
                time_t duration = end - start;


                // Printing the results:
                cout<<"\n\tSubproblem-2B Solution: "<<endl;
                cout<<"\n\t\tNumber of Total 16mers Generated = "<<num_of_16mers<<endl;
                cout<<"\n\t\tSearch Limit for 16mers Search in Hash Table = "<<search_limit_as_num<<endl;
                cout<<"\n\t\tNumber of Genome 16mer Found in Readset = "<<positive_search_hits<<endl;
                cout<<"\n\t\tTime (in seconds) to Complete the Entire Search Process = "<<duration<<endl;

            }
        }

        else
        {
            cout<<"\n\t\tInvalid Choice of Sub Problem. Try Again With Correct Choices. Exiting Program."<<endl;
        }

    }



    return 0;
   
}


