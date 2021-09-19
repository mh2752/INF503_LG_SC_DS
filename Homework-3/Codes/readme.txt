
INF503 (Spring-2021)
Homework-3
Md Nazmul Hossain
(mh2752@nau.edu)

----------------------------------------------------------------------------------------------------------------------------------


1) Any specialized module requirements: None (Just need to have 'make' and 'g++' available on the platform)


2) Running the program from command line:

General format (Assuming a Linux environment):
			
For Problem 1A to 1B:
				
	./output "path_to_the_FASTA_Readset_input_file" "path_to_the_Bacillus_Anthracis_genome_file" subproblem_choice 

	e.g:

		To run for subproblem 1A:

		./output "/common/contrib/classroom/inf503/hw3_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 1A

For Problem 2A:

	./output "path_to_the_FASTA_Readset_input_file" "path_to_the_Bacillus_Anthracis_genome_file" subproblem_choice hash_table_size
			
		e.g.:
				
			To run sub problem 2A:

			./output "/common/contrib/classroom/inf503/hw3_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 2A 10000


For Problem 2B:

	./output "path_to_the_FASTA_Readset_input_file" "path_to_the_Bacillus_Anthracis_genome_file" subproblem_choice hash_table_size  search_limit
			
		e.g.:		

			./output "/common/contrib/classroom/inf503/hw3_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 2B 10000000 1000