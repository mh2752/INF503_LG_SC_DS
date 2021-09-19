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


We DO NOT assume all the given sequences are 
null terminated. 

Their lengths are explicitely given.
*/


class ListNode
{

    public:

        ListNode(); // Default Ctor
        ListNode(const char*,unsigned int); // Overloaded Ctor
        ~ListNode(); // Default Dtor


        // ----- Function returning the
        // length of this node's content
        // string:
        unsigned int Get_Node_Content_Length();


        // ----- Function returning the 
        // content of this node (pass
        // by reference method)
        //
        // Parameter 1: The char pointer to an array
        //              for storing this node's content
        //
        // Parameter-2: length of the passed array
        //              (does not include null character)
        void Get_Node_Content(char* &,unsigned int);



        // ----- Function for setting the
        // content of this node.
        //
        // Parameter 1: The source array pointer
        //
        // Parameter 2: Length of the content of the
        //              source array
        void Set_Node_Content(const char*, unsigned int);


        // ----- Function for determining if
        // the given cequence is equal to
        // the content of this node.
        //
        // Parameter 1: The char array to compare with this
        //              node's content.
        //
        // Parameter 2: length of the external array.
        bool Is_Seq_Equal_To_Node_Content(const char*,unsigned int);



        // ListNode Pointer Pointing to the
        // Next of this Node. It is NULL
        // by default.
        ListNode *next_node = NULL;


    private:

        char *node_content;
        unsigned int node_content_length;     


};


#endif