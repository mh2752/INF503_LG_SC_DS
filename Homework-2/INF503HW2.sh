#!/bin/bash
#SBATCH --job-name=mh2752_INF503_HW2                     # the name of your job
#SBATCH --output=/scratch/mh2752/mh2752_INF503_HW2.output    # this is the file your output and errors go to
#SBATCH --chdir=/home/mh2752/INF503/HW2/            # your work directory
#SBATCH --time=12:00:00                	    # max time to run the program = 6 HRS  
#SBATCH --mem=10240                         # (total mem) 10GB of memory 
#SBATCH -c1                                 # 1 cpu
#SBATCH --mail-type=ALL			# Receive emails for all job stats change. Remove this line to receive no email updates.


# Uncomment below line for sub problem 1A:
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 1A 36000000

# Uncomment below line for sub problem 1C:
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 1C 36000000

# Uncomment below line for sub problem 1D:
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 1D 36000000


# Uncomment below line for sub problem 2A:
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 2A 36000000

# Uncomment below line for sub problem 2B (searching for first 1000 50mers in the FASTA dataset):
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" "/common/contrib/classroom/inf503/test_genome.fasta" 2B 36000000 1000

