#!/bin/bash
#SBATCH --job-name=mh2752_INF503_HW1                     # the name of your job
#SBATCH --output=/scratch/mh2752/mh2752_INF503_HW1.output    # this is the file your output and errors go to
#SBATCH --chdir=/home/mh2752/INF503/HW1/            # your work directory
#SBATCH --time=6:00:00                	    # max time to run the program = 6 HRS  
#SBATCH --mem=4000                          # (total mem) 4GB of memory 
#SBATCH -c1                                 # 1 cpu
#SBATCH --mail-type=ALL			# Receive emails for all job stats change. Remove this line to receive no email updates.


# Uncomment the line below to run subproblem A
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" A

# Uncomment the line below to run subproblem B
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" B

# Uncomment the line below to run subproblem C
#srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" C

# Uncomment the line below to run subproblem E
srun ./output "/common/contrib/classroom/inf503/hw_dataset.fa" E

