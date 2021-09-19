#include "SmithWaterman.h"
#include "SmithWaterman_Blast.h"


// Helper function prototype declaration:
void Prepare_Similarity_Score_Matrix(int**&);



int main(int c,char** argv)
{

   if(c<4 || c>4)
   {
       cout<<"Wrong Number of Command Line Parameters Supplied. Try Again."<<endl;
   }

   else
   {
        //--------------  Preparing the 5x5 similarity score matrix ------------------
        int** sim_matrix;
        sim_matrix = new int*[5];
        for(int i=0;i<5;i++)
        {
            sim_matrix[i] = new int[5];
        }
        Prepare_Similarity_Score_Matrix(sim_matrix);

        // -------------- Getting file path info -------------------------------------

        string file_path_sars,file_path_fragments,sub_prob_choice;

        file_path_sars.assign(argv[1]);
        file_path_fragments.assign(argv[2]);
        sub_prob_choice.assign(argv[3]);

        char* filepath_1; // SARS
        char* filepath_2; // fragments

        filepath_1 = new char[file_path_sars.length()+1];
        filepath_2 = new char[file_path_fragments.length()+1];

        strcpy(filepath_1,file_path_sars.c_str());
        strcpy(filepath_2,file_path_fragments.c_str());

        // ----------------------------------------------------------------------------


        if(sub_prob_choice.compare("1A")==0)
        {

            cout<<"\n\t--------------------------------- HW4: Subproblem 1A -----------------------------------"<<endl;            

            SmithWaterman sw(sim_matrix);

            time_t time_1 = time(nullptr);

            // Read the data from SARS file:
            sw.Read_SARS_Genome_Data(filepath_1,(const unsigned int)file_path_sars.length());            
            time_t time_2 = time(nullptr);
            cout<<"\n\tTime (in seconds) to read the SARS-COV2 Genome Data = "<<(time_2-time_1)<<endl;
            
            // Test against AppendixB Fragments:
            sw.Test_Against_AppendixB_Fragments(filepath_2,(unsigned int)file_path_fragments.length());
            time_t time_3 = time(nullptr);
            cout<<"\n\tTime (in seconds) to test against Appendix-B fragments = "<<(time_3-time_2)<<endl;


        }

        else if(sub_prob_choice.compare("1B")==0)
        {

            cout<<"\n\t--------------------------------- HW4: Subproblem 1B -----------------------------------"<<endl;
            
            SmithWaterman sw(sim_matrix);

            // Read the data from SARS file:
            sw.Read_SARS_Genome_Data(filepath_1,(const unsigned int)file_path_sars.length());

            time_t time1 = time(nullptr);

               
            sw.Test_Against_Random_1K_Fragments();
            time_t time2 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 1K random sequences = "<<(time2-time1)<<endl;

            sw.Test_Against_Random_10K_Fragments();
            time_t time3 = time(nullptr);
            cout<<"\n\t\tTime to test against 10K random sequences = "<<(time3-time2)<<endl;

            sw.Test_Against_Random_100K_Fragments();
            time_t time4 = time(nullptr);
            cout<<"\n\t\tTime to test against 100K random sequences = "<<(time4-time3)<<endl;

            sw.Test_Against_Random_1Million_Fragments();
            time_t time5 = time(nullptr);
            cout<<"\n\t\tTime to Test Against 1Million Random Sequences = "<<(time5-time4)<<endl;


        }

        else if(sub_prob_choice.compare("2A")==0)
        {

            cout<<"\n\t--------------------------------- HW4: Subproblem 2A -----------------------------------"<<endl;

            SmithWaterman_Blast swb(sim_matrix);

            swb.Read_SARS_Genome_Data(filepath_1,(const unsigned int)file_path_sars.length());
            swb.Generate_And_Load_SARS_Seeds();

            time_t time_1 = time(nullptr);
            swb.Test_Against_AppendixB_Fragments(filepath_2,(unsigned int)file_path_fragments.length());
            time_t time_2 = time(nullptr);

            cout<<"\n\t\t Time (in seconds) to test against Appendix-B fragments = "<<(time_2-time_1)<<endl;

        }

        else if(sub_prob_choice.compare("2B")==0)
        {
            cout<<"\n\t--------------------------------- HW4: Subproblem 2B -----------------------------------"<<endl;
            
            SmithWaterman_Blast swb(sim_matrix);

            // Read and Load data:
            swb.Read_SARS_Genome_Data(filepath_1,(const unsigned int)file_path_sars.length());
            swb.Generate_And_Load_SARS_Seeds();

            time_t time_1 = time(nullptr);           

            swb.Test_Against_Random_1K_Fragments();
            time_t time_2 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 1K random fragments = "<<(time_2-time_1)<<endl;

            swb.Test_Against_Random_10K_Fragments();
            time_t time_3 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 10K random fragments = "<<(time_3-time_2)<<endl;
            
            
            swb.Test_Against_Random_100K_Fragments();
            time_t time_4 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 100K random fragments = "<<(time_4-time_3)<<endl;


            swb.Test_Against_Random_1Million_Fragments();
            time_t time_5 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 100K random fragments = "<<(time_5-time_4)<<endl;     


        }

        else if(sub_prob_choice.compare("2C")==0)
        {
            cout<<"\n\t--------------------------------- HW4: Subproblem 2C -----------------------------------"<<endl;
            
            SmithWaterman_Blast swb(sim_matrix);

            // Read and Load data:
            swb.Read_SARS_Genome_Data(filepath_1,(const unsigned int)file_path_sars.length());
            swb.Generate_And_Load_SARS_Seeds();

            time_t time_1 = time(nullptr);

            swb.Test_Against_100K_Random_SARS_Fragments();
            time_t time_2 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 100K random (non-mutated) SARS-COV2 genome fragments = "<<(time_2-time_1)<<endl;

            swb.Test_Against_100K_Random_Mutated_SARS_Fragments();
            time_t time_3 = time(nullptr);
            cout<<"\n\t\tTime (in seconds) to test against 100K random (mutated) SARS-COV2 genome fragments = "<<(time_3-time_2)<<endl;
        }


        else
        {
            cout<<"\n\tWrong subproblem choice. Try again!!!"<<endl;
        }


        // Free memories:
        for(int i=0;i<5;i++)
        {
            delete[] sim_matrix[i];
        }
        delete[] sim_matrix;
   }
    return 0;

}





// --------------------------------------------- Helper Function Definitions --------------------------

void Prepare_Similarity_Score_Matrix(int** &matrix)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(i==j)
            {
                matrix[i][j] = 2; // Match score
            }

            else if(j==4)
            {
                matrix[i][j] = -3; // Gap penalty
            }

            else if(i==4)
            {
                matrix[i][j] = -3; // Gap penalty
            }
            else
            {
                matrix[i][j] = -1; // Mismatch score
            }
        }
    }
}

// -------------------------------------- End of All Helper Functions -----------------------------------------