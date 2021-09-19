
output: ListNode.o LinkedList.o FASTAreadset_DA.o FASTAreadset_Chain.o main.o 
	g++ ListNode.o LinkedList.o FASTAreadset_DA.o FASTAreadset_Chain.o main.o -o output

ListNode.o: ListNode.cpp ListNode.h
	g++ -c ListNode.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -c LinkedList.cpp

FASTAreadset_DA.o: FASTAreadset_DA.cpp FASTAreadset_DA.h
	g++ -c FASTAreadset_DA.cpp

FASTAreadset_Chain.o: FASTAreadset_Chain.cpp FASTAreadset_Chain.h
	g++ -c FASTAreadset_Chain.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
