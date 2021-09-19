#include "FASTA_readset.h"



int main(int c,char **argv)
{
    
    
    if(c!=3)
    {
        cout<<"Required number of Command Line Inputs Not Supplied. Run the Program Again."<<endl;
    }

    else
    {
        string filepath(argv[1]);
        int path_length = filepath.length();

        // A char array holding the file path details
        char fp[path_length];
        for(int i=0;i<path_length;i++)
        {
            fp[i] = filepath[i];            
        }

        string problem_choice(argv[2]);

        if(problem_choice.compare("A")==0)
        {
            
            // ------------------------------- Solve Problem A & Show Results ----------------------------------------------------------------------

            // Creating FASTA_readset object:
            FASTA_readset frst(fp,path_length,1000000); // arg1 = file path to data file, arg2 = length of the file path, arg3 = number of sequences to read

            // Getting starting timestamp
            time_t start = time(nullptr);

            // Initializing the Array with first 1 Million Reads
            frst.Read_Data_From_File();
            
            // Getting ending timestamp
            time_t end = time(nullptr);            
            time_t duration = end-start;

            cout<<"\nTime (in seconds) Required to Initialize the Memory with 1 Million reads = "<<duration<<endl;

            

        }

        else if(problem_choice.compare("B")==0)
        {
            // Solve Problem B (read all 36Mil data) & Show Results
            
            // Creating FASTA_readset object:
            FASTA_readset frst(fp,path_length,36000000); // arg1 = file path to data file, arg2 = length of the file path, arg3 = number of sequences to read

            // Getting starting timestamp
            time_t start = time(nullptr);

            // Initializing the Array with first 1 Million Reads
            frst.Read_Data_From_File();
            
            // Getting ending timestamp
            time_t end = time(nullptr);            
            time_t duration = end-start;

            cout<<"\nTime (in seconds) Required to Initialize the Memory with 36 Million reads = "<<duration<<endl;
            
        }

        else if(problem_choice.compare("C")==0)
        {
            // Solve Problem C & Show Results (Compute all stats with 36Mil reads)
		
	    
	   // Getting the First timestamp:
	   time_t start = time(nullptr);

             // Creating FASTA_readset object:
            FASTA_readset frst(fp,path_length,36000000); // arg1 = file path to data file, arg2 = length of the file path, arg3 = number of sequences to read
           
            // Initializing the Array with first 36 Million Reads
            frst.Read_Data_From_File();

            // Calling the Appropriate Member Function(s)
            frst.Compute_All_Stats();
            
	   time_t end = time(nullptr);

	   time_t duration = end-start;

	   cout<<"Total time to read data and compute all stats with 36Mil reads = "<<duration<<endl;
          

        }

        else if(problem_choice.compare("E")==0)
        {
            // Solve Problem E & Show Results

             // Creating FASTA_readset object:
            FASTA_readset frst(fp,path_length,100000); // arg1 = file path to data file, arg2 = length of the file path, arg3 = number of sequences to read
            

            // Initializing the Array with first 1 Million Reads
            frst.Read_Data_From_File();
            
            // Getting starting timestamp
            time_t start = time(nullptr);

            frst.Sort_Seq_Data();
            
            // Getting ending timestamp
            time_t end = time(nullptr);            
            time_t duration = end-start;

            cout<<"\nTime (in seconds) Required to Sort the Read Sequences Alphabetically = "<<duration<<endl;
        }

        else if(problem_choice.compare("D")==0)
        {
            cout<<" Destructor already implemented. If you choose problem A, B, C, or E - the destructor will execute automatically."<<endl;
        }

        else
	{
		cout<<"Wrong Problem Choice. Try Again."<<endl;
	}

      

    }
    
    
    
   
   
    return 0;
}
