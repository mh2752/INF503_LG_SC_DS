


INF503 (Spring-2021)
Homework-6
Md Nazmul Hossain
(mh2752@nau.edu)

----------------------------------------------------------------------------------------------------------------------------------


1) Any specialized module requirements: 

	None (Just need to have 'make' and 'g++' available on the platform).

	Make sure you're passing the correct file path to the text file containing the sequence fragments from the Appnedix B in the HW6 handout. In my case, I placed the text file AppendixB.txt in the same folder as my class files on Monsoon (/home/mh2752/INF503/HW6/).


2) Running the program from command line:

General format (Assuming a Linux environment):		

				
	srun   ./output    "path_to_the_SARS_COV2_genome_info_file"   "path_to_AppendixB_fragments_file" subproblem_choice 


	e.g.

	For sub-problem 1A:

	srun ./output "/common/contrib/classroom/inf503/SARS_COV2.txt" "/home/mh2752/INF503/HW6/AppendixB.txt" 1A


------------------------------------------------------------- End of readme.txt ----------------------------------------------------