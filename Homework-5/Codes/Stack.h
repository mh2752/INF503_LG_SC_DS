#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Trie_Node.h"

/*

A simple stack class for storing
Trie_Node type pointers.


Author:
    Nazmul (mh2752@nau.edu)

*/



// Struct representing  a node of the Stack
struct Stack_Node
{
    Trie_Node* item = NULL;
    Stack_Node* next_item = NULL;
};


class Stack
{
    public:

        // Default class ctor()
        Stack();

        // Default class dtor()
        ~Stack();


        // Function for pushing an item
        // to the top of the stack.
        //
        // Parameter 1: A Trie_Node* object
        void Push(Trie_Node*);

        // Function for popping an item
        // from the top of the stack.
        //
        // Parameter 1: Trie_Node* pass by reference object
        //              to hold the popped Trie_Node*
        void Pop(Trie_Node*&);


        // Function for checking if
        // the stack is empty:
        bool Is_Stack_Empty();

        // Function for checking if
        // the stack is full:
        bool Is_Stack_Full();


        // Function for returning the current
        // size (#of items) of the stack.
        unsigned long int Get_Current_Size();


    private:

        // Pointer to the top of
        // the Stack object:
        Stack_Node* top;

        // Private variable for saving the
        // stack size information:
        unsigned long int stack_size;
        

};


#endif