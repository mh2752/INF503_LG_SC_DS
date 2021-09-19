


INF503 (Spring-2021)
Homework-5
Md Nazmul Hossain
(mh2752@nau.edu)

----------------------------------------------------------------------------------------------------------------------------------


1) Any specialized module requirements: 

	None (Just need to have 'make' and 'g++' available on the platform).

	Make sure you're passing the correct file path to the text file containing the sequence fragments from the Appnedix B in the HW4 handout. In my case, I placed the text file appendixBfragments.txt in the same folder as my class files on Monsoon (/home/mh2752/INF503/HW4/).


2) Running the program from command line:

General format (Assuming a Linux environment):
			
For Problem 1A to 2C:
				
	srun ./output "path_to_the_SARS_COV2_genome_info_file" subproblem_choice num_of_36mers_to_generate


	e.g.

	For sub-problem A with 5K 36mers to generate: 

	srun ./output "/common/contrib/classroom/inf503/SARS_COV2.txt" A 5000


------------------------------------------------------------- End of readme.txt ----------------------------------------------------