Any specialized module requirements: None (Just need to have make and g++ available on the platform)


Running the program from command line:

	General format:
			output "path_to_the_input_data_file" subproblem_name
			
			e.g.:
				
			     To run the program for solving subproblem B with input file being located
			     at your home folder (assuming a Windows environment) with the file name being
			     'hw_dataset.fa', the command should be as following:

			     output "C:\\Users\\your_user_name\\hw_dataset.fa" B    

			     [Here, output is the executable file created after you've run the makefile (or compiled the .h and .cpp 
			     files with g++). Replace B with A or C or E to run the program for those subproblems.]


			     *** Subproblem D (destructor) runs automatically after each subproblem is run. No need to
				run it explicitely.

			     