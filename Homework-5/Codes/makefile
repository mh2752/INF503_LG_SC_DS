output: Stack.o Queue.o Prefix_Trie.o main.o 
	g++ Stack.o Queue.o Prefix_Trie.o main.o -o output

Stack.o: Stack.cpp Stack.h Trie_Node.h
	g++ -c Stack.cpp

Queue.o: Queue.cpp Queue.h Trie_Node.h
	g++ -c Queue.cpp

Prefix_Trie.o: Prefix_Trie.cpp Prefix_Trie.h Trie_Node.h
	g++ -c Prefix_Trie.cpp
	
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
