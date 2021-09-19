import os
import random



num_seq_read = 10000
dir_path = os.getcwd()
print(dir)
read_prefix = 'R'
num_current_seq = 0

read_header = ['','','_','','_','','_','','_','','_','','_','','_','','_','','_','','_','','_','','_','','_','']
seq_letters = ['A','T','G','C','N']

read_seq = []
read_seq = ['0' for i in range(50)]


filename = dir_path+"\dummy_data.txt"

file_pointer = open(filename,'w')


for i in range(0,num_seq_read):

    read_prefix = '>R'+str(i)+'_'

    # Preparing header
    for j in range(0,28):
        
        if j==0:
            read_header[j] = read_prefix
        
        elif j!=0 and j%2==1:
            read_header[j] = str(random.randint(0,100))

    # Preparing Sequence

    for j in range(0,50):
        read_seq[j] = seq_letters[random.randint(0,4)]

    header = "".join(read_header)
    seq = "".join(read_seq)
    
    file_pointer.write(header)
    file_pointer.write('\n')
    file_pointer.write(seq)
    file_pointer.write('\n')
        





   
