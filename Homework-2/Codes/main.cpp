#include "FASTAreadset_LL.h"
#include <cstring>

int main(int c,char** argv)
{

    if((c<5) || (c>6))
    {
        cout<<"Wrong number of command line inputs. Follow the command line input format specified in the readme.txt file."<<endl;        
    }
    else
    {


        // --------------------------------------- Read the Given File Paths and Sub-problem Choice ------------------------------------------------

        string filepath_FASTA(argv[1]);       
        int path_length_FASTA = filepath_FASTA.length();

        // A char array holding the file path details (null terminated)
        char* fp_FASTA;
        fp_FASTA = new char[path_length_FASTA+1];

        for(int i=0;i<path_length_FASTA+1;i++)
        {
            if(i==path_length_FASTA)
            {
                fp_FASTA[i] = '\0';
            }
            else
            {
                fp_FASTA[i] = filepath_FASTA[i];
            }         
        }

        cout<<"Filepath-1 = "<<fp_FASTA<<endl;


        // ------------------------------------------------------------------------------------------------------


        string filepath_Bacillus(argv[2]);        
        int file_path_length_Bacillus = filepath_Bacillus.length();

        // A char array holding the file path details (null terminated)
        char* fp_Bacillus;
        fp_Bacillus = new char[file_path_length_Bacillus+1];

        for(int i=0;i<file_path_length_Bacillus+1;i++)
        {
            if(i == file_path_length_Bacillus)
            {
                fp_Bacillus[i] = '\0';
            }
            else
            {
                fp_Bacillus[i] = filepath_Bacillus[i];
            }
        }

        cout<<"Filepath-2 = "<<fp_Bacillus<<endl;


        string sub_problem_choice(argv[3]);


        // -------------------------------------------------------------------------------------------------


        // Utility variables:
        string p1A("1A");
        string p1B("1B");
        string p1C("1C");
        string p1D("1D");
        string p2A("2A");
        string p2B("2B");




        // Reading the number of lines to read and 
        // number of 50mers to serach for inputs from CLI:        
        int num_of_fasta_line_to_read = 0;
        int num_of_50mers_to_search_for = 0;
        
        // If info can't be parsed, exit gracefully:
        try
        {
            num_of_fasta_line_to_read = atoi(argv[4]);
            if(c==6)
            {
                num_of_50mers_to_search_for = atoi(argv[5]);
            }
        }

        catch(...)
        {
            cout<<"Could not read in line number info supplied as inputs in CLI"<<endl;
            exit(EXIT_FAILURE);
        }


        // ----------- Creating Necessary Objects and Calling Member Functions as Necessary for the Solving Sub-problems ---------------------

       
        

        if(sub_problem_choice.compare(p1A)==0)
        {               
            
            if(num_of_fasta_line_to_read!=0)
            {
                FASTAreadset_LL fasta_ll_object(fp_FASTA,fp_Bacillus,num_of_fasta_line_to_read);            
                
                time_t start = time(nullptr);
                fasta_ll_object.Read_From_Source_File();
                time_t end = time(nullptr);

                time_t duration = end - start;
                cout<<"\n\t\tTime (in seconds) to Read All Data from Source Files = "<<duration<<endl;
            }
            else
            {
                cout<<" Invalid char sequence passed as CLI for required integer values. Enter non-zero +ve integer for each required parameter."<<endl;
            }
            
            
           
        }




        else if(sub_problem_choice.compare(p1B)==0)
        {
            cout<<"Destructor is automatically called each time whenever a FASTAreadset_LL object goes out of scope."<<endl;
        }



        else if(sub_problem_choice.compare(p1C)==0)
        {            
            
            if(num_of_fasta_line_to_read!=0)
            {
                FASTAreadset_LL fasta_ll_object(fp_FASTA,fp_Bacillus,num_of_fasta_line_to_read);
                fasta_ll_object.Read_From_Source_File();
                fasta_ll_object.Generate_Anthrax_Genome_50mers();

                time_t start = time(nullptr);
                FASTAreadset_LL deep_copy_target = fasta_ll_object;
                time_t end = time(nullptr);


                time_t duration = end - start;
                cout<<"\n\t\tTime (in seconds) Required to Deep-copy a FASTAreadset_LL Object = "<<duration<<endl;
            }
            else
            {
              cout<<" Invalid char sequence passed as CLI for required integer values. Enter non-zero +ve integer for each required parameter."<<endl;
            }    
            
        }



        else if(sub_problem_choice.compare(p1D)==0)
        {
            
            if(num_of_fasta_line_to_read!=0)
            {
                FASTAreadset_LL fasta_ll_object(fp_FASTA,fp_Bacillus,num_of_fasta_line_to_read);
                fasta_ll_object.Read_From_Source_File();

                // Preparing the search-key fragments as given on the homework handout:
                string k1("CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT");
                string k2("GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC");
                string k3("CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC");
                string k4("CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA");
                string k5("ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN");

                char* key1;
                key1 = new char[k1.length()+1];
                
                char* key2;
                key2 = new char[k2.length()+1];

                char* key3;
                key3 = new char[k3.length()+1];

                char* key4;
                key4 = new char[k4.length()+1];

                char* key5;
                key5= new char[k5.length()+1];

                // Converting from string to null terminated char arrrays (C-style)
                strcpy(key1,k1.c_str());
                strcpy(key2,k2.c_str());
                strcpy(key3,k3.c_str());
                strcpy(key4,k4.c_str());
                strcpy(key5,k5.c_str());

                // To hold the result
                // returned by the search
                // function:
                ListNode* node1 = NULL;
                ListNode* node2 = NULL;
                ListNode* node3 = NULL;
                ListNode* node4 = NULL;
                ListNode* node5 = NULL;

                
                time_t start = time(nullptr);

                // Searching for fragments, one by one:
                fasta_ll_object.Search_For_Given_Seq(key1,node1);
                fasta_ll_object.Search_For_Given_Seq(key2,node2);
                fasta_ll_object.Search_For_Given_Seq(key3,node3);
                fasta_ll_object.Search_For_Given_Seq(key4,node4);
                fasta_ll_object.Search_For_Given_Seq(key5,node5);

                time_t end = time(nullptr);
                time_t duration = end - start;

                cout<<"\n\t\tTime (in seconds) to Search Given Fragments = "<<duration<<endl;

                if(node1!=NULL)
                {
                    cout<<"\n\t\tSequence Fragment "<<k1<<" FOUND in FASTA Dataset."<<endl;
                }
                if(node2!=NULL)
                {
                    cout<<"\n\t\tSequence Fragment "<<k2<<" FOUND in FASTA Dataset."<<endl;
                }
                if(node3!=NULL)
                {
                    cout<<"\n\t\tSequence Fragment "<<k3<<" FOUND in FASTA Dataset."<<endl;
                }
                if(node4!=NULL)
                {
                    cout<<"\n\t\tSequence Fragment "<<k4<<" FOUND in FASTA Dataset."<<endl;
                }
                if(node5!=NULL)
                {
                    cout<<"\n\t\tSequence Fragment "<<k5<<" FOUND in FASTA Dataset."<<endl;
                }


                // To prevent dangling pointer:
                node1 = NULL;
                node2 = NULL;
                node3 = NULL;
                node4 = NULL;
                node5 = NULL;

                // To prevent memory leak
                delete[] key1;
                delete[] key2;
                delete[] key3;
                delete[] key4;
                delete[] key5;
            }
            else
            {
                cout<<" Invalid char sequence passed as CLI for required integer values. Enter non-zero +ve integer for each required parameter."<<endl;
            }       

            
        }




        else if(sub_problem_choice.compare(p2A)==0)
        {
            
            if(num_of_fasta_line_to_read!=0)
            {
                FASTAreadset_LL fasta_ll_object(fp_FASTA,fp_Bacillus,num_of_fasta_line_to_read);
                fasta_ll_object.Read_From_Source_File();

                time_t start = time(nullptr);
                fasta_ll_object.Generate_Anthrax_Genome_50mers();
                time_t end = time(nullptr);

                time_t duration = end - start;
                cout<<"\n\t\tTime (in seconds) to Create All the 50mers = "<<duration<<endl;
            }
            else
            {
              cout<<" Invalid char sequence passed as CLI for required integer values. Enter non-zero +ve integer for each required parameter."<<endl;
            }        

        }




        else if(sub_problem_choice.compare(p2B)==0)
        {
             
            if(num_of_fasta_line_to_read!=0 && num_of_50mers_to_search_for!=0)
            {
                FASTAreadset_LL fasta_ll_object(fp_FASTA,fp_Bacillus,num_of_fasta_line_to_read);
                fasta_ll_object.Read_From_Source_File();
                fasta_ll_object.Generate_Anthrax_Genome_50mers();
                
                time_t start = time(nullptr);
                fasta_ll_object.Search_FASTA_Seq_Frags_For_50mers(num_of_50mers_to_search_for);
                time_t end = time(nullptr);

                time_t duration = end - start;
                cout<<"\n\t\tTotal time (in seconds) Required to Search for the first "<<num_of_50mers_to_search_for<<" 50mers in FASTA Dataset = "<<duration<<endl;
            }
            else
            {
              cout<<" Invalid char sequence passed as CLI for required integer values. Enter non-zero +ve integer for each required parameter."<<endl;
            }             

        }

        else
        {
            cout<<"Wrong Sub-problem Choice. Run the Program Again."<<endl;
        }
    }   

    return 0;
}