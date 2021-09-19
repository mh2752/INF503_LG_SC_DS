output: Queue.o Suffix_Trie.o main.o 
	g++ Queue.o Suffix_Trie.o main.o -o output

Queue.o: Queue.cpp Queue.h Trie_Node.h
	g++ -c Queue.cpp

Suffix_Trie.o: Suffix_Trie.cpp Suffix_Trie.h Trie_Node.h
	g++ -c Suffix_Trie.cpp
	
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
