#ifndef LISTNODE_H_INCLUDED
#define LISTNODE_H_INCLUDED

#include<iostream>
#include<string>
#include<ctime>
#include<stdlib.h>
#include<fstream>
using namespace std;


/*
This is the Node class which will create 
and help in maintain the nodes required
in creating the LinkedList object.


We assume all the given sequences are 
null terminated.
*/


class ListNode
{

    public:
        
        // ------------------------------------- Class Constructors & Destructor Declarations ------------------------------------------

        ListNode(); // Default class ctor
        ListNode(const char*); // Overloaded ctor. Parameter is the char string to store.
        ListNode(const ListNode &external_node); // Class copy constructor
        ~ListNode(); // Class destructor



        // ------------------------------------- Class Public Member Function Declarations -----------------------------------------------


        // Return the length of the sequence stored in this ListNode,
        // including the terminatiing null character.
        int Get_Node_Seq_Length();
        
        
        // Will return a copy of the stored string using 'pass by reference' technique:
        void Get_Node_Content(char*&);


        // Will set the string content of the node with the given sequence string:
        void Set_Node_Content(char*&);   



        // ------------------------------------------- Publicly Accessible Class Variable -----------------------------------------------

        
        // Pointer to the next node in the link:
        ListNode* next_node;       


    
    private:

        char* node_sequence; // Char array holding the sequence      


};


#endif