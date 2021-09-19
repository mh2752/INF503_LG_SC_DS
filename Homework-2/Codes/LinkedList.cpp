#include "LinkedList.h"


// Default Constructor
LinkedList::LinkedList()
{
    head = NULL;
    current = NULL;
}


// Overloaded Constructor
LinkedList::LinkedList(char* &first_element)
{
    head = NULL;
    current = NULL;

    // Insert the element:
    Insert_Item_At_Front(first_element);

}


// Copy ctor
LinkedList::LinkedList(const LinkedList &external_list)
{    
    if(Is_Empty())
    {
        // This list is empty. Nothing to do.
    }

    else
    {
        // Copy from the external list:
        external_list.Copy_List(*(this));    
    }
}





// Default Destructor
LinkedList::~LinkedList()
{  
   
    // A temporary pointer
    ListNode* temp_ptr;    


    while(head != NULL)
    {
        // Save the current location pointed by head pointer
        temp_ptr = head;

        // Move head pointer to point to the next node in the link:
        head = head->next_node;

        // Free the memory at the location pointed by the temp_ptr
        delete temp_ptr;
    }

    // head is NULL now. Make current NULL, too:
    current = NULL;  

}




// ---------------------------------------------- Class Member Function Definitions --------------------------------

bool LinkedList::Is_Empty()
{
    if(head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool LinkedList::Is_Full()
{
    try
    {
        ListNode* temp_ptr;
        temp_ptr = new ListNode;
        delete temp_ptr;

        return false;
    }
    catch(bad_alloc& exception)
    {
        cout<<"\n\t\tLinkedList Object Is Full."<<endl;
        return true;
    }
    
}



void LinkedList::Reset_Current_Pointer()
{
    current = NULL;
}



// Insert an item at the end of the list
void LinkedList::Insert_Item_At_End(char* &given_seq)
{
    if(head == NULL) // It's an empty list. We are inserting the very first item.
    {
        if(!Is_Full()) // If memory is not full, insert item
        {
            ListNode* node;
        
            node = new ListNode(given_seq);
            node->next_node = NULL; // To be safe.

            head = node; // head now points to the new node.
	   
        }

        else
        {
            // Do nothing. Memory might be available when you try next.
        }

    }

    else // Inserting into a non-empty list
    {

       if(!Is_Full())
       {
            // Locate the end of the list:

            Reset_Current_Pointer(); // To be safe.

            current = head; // current now points to the beginning of the list

            // Traverse to the last node of the list
            while(current->next_node != NULL)
            {
                current = current->next_node;
            }


            // current now points to the last node of the list. Insert the new node at the end of current node:
            ListNode* node;

            node = new ListNode(given_seq);
            node->next_node = NULL; // Being safe.

            current->next_node = node; // current now points to the newly inserted node at the end.

            Reset_Current_Pointer(); // To be safe.


       }
       else
       {
           cout<<"\n\t\tMemory is full. Could not insert item into the linked list."<<endl;
       }

    } // else{} - inserting into non empty list ends here
}





// Insert an item at the front of the list:
void LinkedList::Insert_Item_At_Front(char* &given_seq)
{
    if(head == NULL) // It's an empty list. We are inserting the very first item.
    {
        if(!Is_Full()) // If memory is not full, insert item
        {
            ListNode* node;        
            node = new ListNode(given_seq);
            node->next_node = NULL; // To be safe.

            head = node; // head now points to the new node.
	   
        }

        else
        {
            // Do nothing. Memory might be available when you try next.
        }

    }

    else // Inserting into a non-empty list
    {

       if(!Is_Full())
       {
            // Create the ListNode            
            ListNode* node;
            node = new ListNode(given_seq);
            node->next_node = head; // next node of this node is now the node currently pointed by head

            // Update head pointer
            head = node; // node is now pointed by head

       }
       else
       {
           // Do nothing. Memory might be available when you try next.
       }

    } // else{} - inserting into non empty list ends here
}




void LinkedList::Search_List(char* &given_seq, ListNode* &location)
{
    // Search all list nodes for a match with the given sequence.
    
    if(Is_Empty())
    {
        // No need to search an empty list. Just return NULL:
        location = NULL;
    }

    else
    {      

        Reset_Current_Pointer(); // To be safe.

        current = head; // current now points to the beginning of the list

        string search_key(given_seq);
        bool found = false;
        location = NULL;
        
        string node_content;
        char* node_content_array;
        int content_length = 0;

        while(current != NULL && !found)
        {
            
            // Get the length of the seq pointed by current
            // and copy it into node_content_array:
            content_length = current->Get_Node_Seq_Length();
            node_content_array = new char[content_length];
            current->Get_Node_Content(node_content_array);

            // create the string:
            node_content.assign(node_content_array);


            if(search_key.compare(node_content)==0) // We've found the item
            {
                found = true;
                location = current;
            }

            else // Move current to the next node:
            {
                current = current->next_node;
            }

            // Free array memory to prevent memory leak:
            delete[] node_content_array;           

        }

       
    } // else{} for Is_Empty() ends here.
}




void LinkedList::Delete_Item(char* &given_seq)
{
    // Not required for this Homework.
    // If required, impelement in later HWs.
}

void LinkedList::Set_Current_To_Head()
{
    current = head;
}


void LinkedList::Get_Current_Node(ListNode& external_node)
{
    if(current==NULL)
    {
        Set_Current_To_Head();
    }

    // Copy the content of the current node to external
    // node:
    int content_length = current->Get_Node_Seq_Length();
    char* content;
    content = new char[content_length];
    current->Get_Node_Content(content);

    // Set the external node's content:
    external_node.Set_Node_Content(content);


    // Free content to prevent memory leak:
    delete[] content;

    // Move current to next node:
    current = current->next_node;
}



// Copy the content of this LinkedList
// instance to the given LinkedList instance
// as the function parameter:
void LinkedList::Copy_List(LinkedList& target_list) const
{
    ListNode* temp;
    temp = head;

    int node_seq_length;
    char* node_content;

    while(temp!=NULL)
    {
        node_seq_length = temp->Get_Node_Seq_Length();
        node_content = new char[node_seq_length];
        // Grab the content of the node:
        temp->Get_Node_Content(node_content);

        target_list.Insert_Item_At_Front(node_content);

        temp = temp->next_node;

        // Prevents memory leak:
        delete[] node_content;

    }

}



void LinkedList::Move_Current_To_Next()
{
    if(current == NULL)
    {
        current = head;
    }
    else
    {
        current = current->next_node;
    }
}
