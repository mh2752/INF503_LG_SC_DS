#include "Prefix_Trie.h"
#include <cstring>



int main(int c,char** argv)
{

   if(c != 4)
   {
       cout<<"Wrong Number of Command Line Parameters Supplied. Try Again."<<endl;
   }

   else
   {        

        // -------------- Getting file path info -------------------------------------

        string file_path_sars,sub_prob_choice,kmer_num;

        file_path_sars.assign(argv[1]);  
        sub_prob_choice.assign(argv[2]);
        kmer_num.assign(argv[3]);


        char* kmer_num_array;
        kmer_num_array = new char[kmer_num.length()+1];
        strcpy(kmer_num_array,kmer_num.c_str());
        int kmer_num_int = atoi(kmer_num_array);

        if(kmer_num_int == 0)
        {
            cout<<"\n\t\tInvalid Kmer Numbers Given. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }



        char* filepath; // SARS
        filepath = new char[file_path_sars.length()+1];
        strcpy(filepath,file_path_sars.c_str());
        

        // ----------------------------------------------------------------------------


        if(sub_prob_choice.compare("A")==0)
        {

            cout<<"\n\t--------------------------------- HW5: Subproblem A -----------------------------------"<<endl;

            Prefix_Trie trie;

            // Read the genome data from the file:
            trie.Read_SARS_Genome_From_File(filepath,(int)file_path_sars.length());

            // Generate specified number of random 36mers
            trie.Generate_And_Store_36mers(kmer_num_int);

            int searched_items=0;
            int found_items=0;

            trie.Search_For_All_36mers(searched_items,found_items);

            unsigned long int trie_size = trie.Get_Trie_Size();

            cout<<"\n\t\tNumber of Nodes in The Trie   = "<<trie_size<<endl;
            cout<<"\n\t\tNumber of 36mers Searched For = "<<searched_items<<endl;
            cout<<"\n\t\tNumber of 36mers Found        = "<<found_items<<endl;         

           


        }

        else if(sub_prob_choice.compare("B")==0)
        {

            cout<<"\n\t--------------------------------- HW5: Subproblem 1B -----------------------------------"<<endl;

            Prefix_Trie trie;

            // Read the genome data from the file:
            trie.Read_SARS_Genome_From_File(filepath,(int)file_path_sars.length());

            // Generate specified number of random 36mers
            trie.Generate_And_Store_Mutated_36mers(kmer_num_int);

            int searched_items=0;
            int found_items=0;

            trie.Search_For_All_36mers(searched_items,found_items);

            unsigned long int trie_size = trie.Get_Trie_Size();

            cout<<"\n\t\tNumber of Nodes in The Trie   = "<<trie_size<<endl;
            cout<<"\n\t\tNumber of 36mers Searched For = "<<searched_items<<endl;
            cout<<"\n\t\tNumber of 36mers Found        = "<<found_items<<endl;           
            


        }      


        else
        {
            cout<<"\n\tWrong subproblem choice. Try again!!!"<<endl;
        }


   }
    return 0;

}

