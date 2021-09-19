#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "ListNode.h"


/*

The class implementing the linked list.

We DO NOT assume all given char arrays are null terminated.

*/


class LinkedList
{

    public:

        LinkedList(); // Default Ctor
        ~LinkedList();// Default Dtor


        // ------- Function for inserting given
        // sequence at the front of the list.
        //
        // Parameter 1: The char pointer to the array
        //              whose content is to be inserted
        //              in the linked list.
        //
        // Parameter 2: Length of the given array.
        void Insert_Item_At_Front(const char*,unsigned int);



        // ------ Function for resetting current pointer
        // to the head of the list:
        void Reset_Current_To_Head();

        // ------ Function for resetting current pointer
        // to NULL:
        void Reset_Current_To_NULL();


        // ------ Function for copying the content
        // of the ListNode pointed by current.
        //
        // Parameter 1: The destination ListNode (the next_node of
        //              destination node should be set to NULL)
        void Copy_Current_Node_Content(ListNode*&);



        // ----- Function for moving current
        // pointer to the next node in the list.
        // It won't wrap around the list.
        void Move_Current_To_Next();



        // ----- Function for getting the current
        // length of the list.
        unsigned long int Get_List_Length();


        // ---- Function for Searching for a
        // given sequence.
        //
        // Parameter 1: The char pointer to the array containing
        //              the sequence to search for.
        //
        // Parameter 2: Length of the char array.
        //
        // Parameter 3: A 'pass-by-reference' variable
        //              for holding the search result
        void Search_Item(const char* search_key, unsigned int key_length,bool&);

    private:

        // ListNode pointer pointing
        // to the head of the linked
        // list:
        ListNode* head;

        // ListNode pointer pointing
        // ot the current node of the
        // linked list:
        ListNode *current;

        // Holds current length of
        // the linked list:
        unsigned long int list_length;



        // ------ Function to check if the list is full
        // or not.
        bool Is_List_Full();

        // ------ Function to check if the list
        // is empty or not.
        bool Is_List_Empty();


};


#endif
