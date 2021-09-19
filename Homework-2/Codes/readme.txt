
INF503 (Spring-2021)
Homework-2
Md Nazmul Hossain
(mh2752@nau.edu)

----------------------------------------------------------------------------------------------------------------------------------


1) Any specialized module requirements: None (Just need to have 'make' and 'g++' available on the platform)


2) Running the program from command line:

General format (Assuming a Linux environment):
			
For Problem 1(A) to 2(A):
				
	./output "path_to_the_FASTA_input_file" "path_to_the_Bacillus_Anthracis_genome_file" subproblem_choice num_of_FASTA_seq_to_read

For Problem 2(B):

	./output "path_to_the_FASTA_input_file" "path_to_the_Bacillus_Anthracis_genome_file" subproblem_choice num_of_FASTA_seq_to_read num_of_50mers_to_search_for
			
		e.g.:
				
			To run the program for solving subproblem 1A with 36 Million FASTA sequence fragments to read from file:

			./output "/common/contrib/classroom/inf503/hw_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 1A 36000000	




* Subproblem 1B (destructor) will run automatically everytime after any other subproblem is run.
			     