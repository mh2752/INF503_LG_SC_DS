#include "Suffix_Trie.h"


int main(int c,char** argv)
{

   if(c != 4)
   {
       cout<<"Wrong Number of Command Line Parameters Supplied. Try Again."<<endl;
   }

   else
   {        

        // -------------- Getting file path info -------------------------------------

        string file_path_sars,file_path_appendixB,sub_prob_choice;

        file_path_sars.assign(argv[1]);
        file_path_appendixB.assign(argv[2]);
        sub_prob_choice.assign(argv[3]);   



        char* filepath_sars; // SARS
        filepath_sars = new char[file_path_sars.length()+1];
        strcpy(filepath_sars,file_path_sars.c_str());
        int sars_path_length = file_path_sars.length();


        char* filepath_appendixB; // SARS
        filepath_appendixB = new char[file_path_appendixB.length()+1];
        strcpy(filepath_appendixB,file_path_appendixB.c_str());
        int appendixB_path_length = file_path_appendixB.length();
        

        // ----------------------------------------------------------------------------


        if(sub_prob_choice.compare("1A")==0)
        {

            cout<<"\n\t--------------------------------- HW6: Subproblem 1A -----------------------------------"<<endl;


            Suffix_Trie st;

            st.Read_Subject_Sequence_From_File(filepath_sars,sars_path_length);

            time_t start = time(nullptr);

            cout<<"\n\t\tTesting the Search Function with AppendixB Sequences: "<<endl;
            st.Read_And_Search_With_AppendixB(filepath_appendixB,appendixB_path_length);   

            time_t end = time(nullptr);

            time_t duration = end - start;

            cout<<"\n\t\tTime (in seconds) to Complete the Search Process: "<<duration<<endl;            



        }

        else if(sub_prob_choice.compare("1B")==0)
        {

           cout<<"\n\t--------------------------------- HW6: Subproblem 1B -----------------------------------"<<endl;

           Suffix_Trie st;
           st.Read_Subject_Sequence_From_File(filepath_sars,sars_path_length);

           time_t start = time(nullptr);
           unsigned int found_sequences = st.Generate_And_Search_For_5k_36mers();
           time_t end = time(nullptr);

           time_t duration = end - start;

           cout<<"\n\t\tSearch Result for Searching With 5,000 Random 36mers: "<<endl;
           cout<<"\n\t\t\tNumber of 36mers Found: "<<found_sequences<<endl;
           cout<<"\n\t\t\tTime (in seconds) to Complete the Search: "<<duration<<endl;

           // -----------------------------------------------------------------------------------

           start = time(nullptr);
           found_sequences = st.Generate_And_Search_For_50k_36mers();
           end = time(nullptr);

           duration = end - start;

           cout<<"\n\t\tSearch Result for Searching With 50,000 Random 36mers: "<<endl;
           cout<<"\n\t\t\tNumber of 36mers Found: "<<found_sequences<<endl;
           cout<<"\n\t\t\tTime (in seconds) to Complete the Search: "<<duration<<endl;


           // ----------------------------------------------------------------------------------


           start = time(nullptr);
           found_sequences = st.Generate_And_Search_For_100k_36mers();
           end = time(nullptr);

           duration = end - start;

           cout<<"\n\t\tSearch Result for Searching With 100,000 Random 36mers: "<<endl;
           cout<<"\n\t\t\tNumber of 36mers Found: "<<found_sequences<<endl;
           cout<<"\n\t\t\tTime (in seconds) to Complete the Search: "<<duration<<endl;


           unsigned long int trie_size = st.Get_Trie_Size();

           cout<<"\n\t\tSize (#of nodes) of the trie: "<<trie_size<<endl;


        }      


        else
        {
            cout<<"\n\tWrong subproblem choice. Try again!!!"<<endl;
        }


   }


    return 0;

}