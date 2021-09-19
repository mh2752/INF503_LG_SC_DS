
output: ListNode.o LinkedList.o FASTAreadset_LL.o main.o 
	g++ ListNode.o LinkedList.o FASTAreadset_LL.o main.o -o output

ListNode.o: ListNode.cpp ListNode.h
	g++ -c ListNode.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -c LinkedList.cpp

FASTAreadset_LL.o: FASTAreadset_LL.cpp FASTAreadset_LL.h
	g++ -c FASTAreadset_LL.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output
