#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "Trie_Node.h"

/*

A simple queue class for storing
Trie_Node type pointers.


Author:
    Nazmul (mh2752@nau.edu)

*/



// Struct representing  a node of the Stack
struct Queue_Node
{
    Trie_Node* item = NULL;
    Queue_Node* next_item = NULL;
};


class Queue
{
    public:

        // Default class ctor()
        Queue();

        // Default class dtor()
        ~Queue();


        // Function for enqueing an item
        // into the queue.
        //
        // Parameter 1: A Trie_Node* object
        void Enqueue(Trie_Node*);

        // Function for dequeuing an item
        //
        // Parameter 1: Trie_Node* pass by reference object
        //              to hold the dequeud Trie_Node*
        void Dequeue(Trie_Node*&);


        // Function for checking if
        // the queue is empty:
        bool Is_Queue_Empty();

        // Function for checking if
        // the queue is full:
        bool Is_Queue_Full();


        // Function for returning the current
        // size (#of items) of the queue.
        unsigned long int Get_Current_Size();


    private:

        // Front of the queue:
        Queue_Node* front;

        // Rear of the queue:
        Queue_Node* rear;



        // Private variable for saving the
        // stack size information:
        unsigned long int queue_size;
        

};












#endif