
output: main.o FASTA_readset.o
	g++ main.o FASTA_readset.o -o output
main.o: main.cpp
	g++ -c main.cpp
FASTA_readset.o: FASTA_readset.cpp FASTA_readset.h
	g++ -c FASTA_readset.cpp
clean:
	rm *.o output
