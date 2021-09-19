output: AlignmentResult.o SmithWaterman.o SmithWaterman_Blast.o DirectAccessHashTable.o main.o 
	g++ AlignmentResult.o SmithWaterman.o SmithWaterman_Blast.o DirectAccessHashTable.o main.o -o output

AlignmentResult.o: AlignmentResult.cpp AlignmentResult.h
	g++ -c AlignmentResult.cpp

SmithWaterman.o: SmithWaterman.cpp SmithWaterman.h
	g++ -c SmithWaterman.cpp

SmithWaterman_Blast.o: SmithWaterman_Blast.cpp SmithWaterman_Blast.h
	g++ -c SmithWaterman_Blast.cpp

DirectAccessHashTable.o: DirectAccessHashTable.cpp DirectAccessHashTable.h 
	g++ -c DirectAccessHashTable.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
