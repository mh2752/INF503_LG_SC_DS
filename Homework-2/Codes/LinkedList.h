#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED


/*

The class implementing the linked list.

We assume all given char arrays are null terminated.

*/

#include "ListNode.h"


class LinkedList
{

    public:

        LinkedList(); // Default ctor
        LinkedList(char*&); // Overloaded ctor
        LinkedList(const LinkedList &external_list); // Copy ctor
        ~LinkedList();// Default dtor

        
        void Insert_Item_At_End(char*&);// Insert a ListNode object with the given seq as its content at the end of the LinkedList object.
        void Insert_Item_At_Front(char*&); // O(c) complexity. Better than inserting at the end.       
        bool Is_Full(); // Returns true if no more item can be inserted into the LinkedList.
        bool Is_Empty(); // Returns true if there's no item in the list.
        void Search_List(char*&,ListNode*&); // Search for a given sequence in the list.
        void Delete_Item(char*&); // Delete all nodes having the given sequence as their content (Don't really need this for HW2).
        void Reset_Current_Pointer(); // Resets the current pointer to NULL
        void Set_Current_To_Head(); // Set current to head pointer
        void Get_Current_Node(ListNode&); // Return the node pointed by current
        void Copy_List(LinkedList&) const;
        void Move_Current_To_Next(); // Moves current node to next node. If next node is null, set current to head


    private:

        

        ListNode* head;
        ListNode* current;


};


#endif
