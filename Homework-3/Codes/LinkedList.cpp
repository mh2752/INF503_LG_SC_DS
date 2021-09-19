#include "LinkedList.h"

// ------------------------------------ Begin: Class Ctor & Dtor Definitions ------------------------------------------------------



LinkedList::LinkedList()
{
    head = NULL;
    current = NULL;
    list_length = 0;
}


LinkedList::~LinkedList()
{
    // Getting starting timestamp
    time_t start = time(nullptr);

    if(head == NULL)
    {
        // List is already empty. Do nothing.
    }
    else
    {
        ListNode *temp_ptr;        

        while(head != NULL)
        {
            // Point to current node indicated by head
            temp_ptr = head;

            // Move head to next node
            head = head->next_node;

            // Free the node pointed by temp_ptr
            temp_ptr->next_node = NULL; // We don't want dangling pointers, do we???
            temp_ptr->~ListNode(); // Calll ListNode destructor explicitely.
            temp_ptr = NULL;

        }

    }

    // Getting ending timestamp
    time_t end = time(nullptr);

    // Printing out the duration
    time_t  duration = end - start;
    //cout<<"\n\t\tTime (in seconds) To Destroy the LinkedList Object = "<<duration<<endl;
}
// ------------------------------------ End: Class Ctor & Dtor Definitions --------------------------------------------------------





// ------------------------------------ Begin: Class Public Member Function Definitions -------------------------------------------


void LinkedList::Insert_Item_At_Front(const char* source_array,unsigned int source_length)
{

    if(Is_List_Full())
    {
        cout<<"\n\t\tList is Full. Could not insert item. exiting program."<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        // List is not full. Go ahead and
        // insert the item into the list.


        if(Is_List_Empty()) // We are inserting the first item
        {
            
            // Create the ListNode
            ListNode *node_to_insert;
            node_to_insert = new ListNode(source_array,source_length);

            // Set this nodes next node to NULL:
            node_to_insert->next_node = NULL;

            // Update head to point to this node:
            head = node_to_insert;
            // Update list length:
            list_length++;

        }
        else// We are inserting items subsequent to first item
        {

            // Create the ListNode
            ListNode *node_to_insert;
            node_to_insert = new ListNode(source_array,source_length);

            // Set this node's next to the
            // node being pointed by head:
            node_to_insert->next_node = head;

            // Update head:
            head = node_to_insert;
            // Update list length:
            list_length++;

        }
    }


}



void LinkedList::Reset_Current_To_Head()
{
    current = head;
}

void LinkedList::Reset_Current_To_NULL()
{
    current = NULL;
}



void LinkedList::Copy_Current_Node_Content(ListNode* &destination_node)
{
    if(current == NULL)
    {
        // Do nothing. The content of the destination node
        // is already empty.
    }
    else
    {
        // Get the length of the content of the node
        // pointed by the current:
        unsigned int node_content_length = current->Get_Node_Content_Length();

        // Allocate the buffer memory to receive 
        // the content:
        char *receive_node_content;
        receive_node_content = new char[node_content_length];

        // Receive the content:
        current->Get_Node_Content(receive_node_content,node_content_length);

        // Set the content of destination node:
        destination_node->Set_Node_Content(receive_node_content,node_content_length);
        // Set the next node of destination to NULL (to be safe):
        destination_node->next_node = NULL;


        // Release the dynamically allocated memories:
        delete[] receive_node_content;
    }
}



void LinkedList::Move_Current_To_Next()
{
    if(current != NULL)
    {
        current = current->next_node;
    }
}


unsigned long int LinkedList::Get_List_Length()
{
    return list_length;
}


void LinkedList::Search_Item(const char* search_key,unsigned int key_length,bool &search_result)
{
    if(Is_List_Empty())
    {
        search_result = false;
    }
    else
    {
        // Bringing current to the beginning of the
        // linked list:
        Reset_Current_To_Head();

        // Getting the current length
        // of the list:
        unsigned long int current_list_length = Get_List_Length();

        // By default, we assume the item is
        // not in the list:
        search_result = false;


        for(unsigned long int i = 0; i < current_list_length; i++)
        {
            if(i == (current_list_length-1)) // This is the last node we are seeing
            {
                if(current != NULL)
                {
                    if(current->Is_Seq_Equal_To_Node_Content(search_key,key_length))
                    {
                        // Item found. Update search result and break out of the loop:
                        search_result = true;
                        break;
                    }
                }
                else // current is NULL. Done with searching entire list.
                {
                    break;
                }

            }
            else
            {
                if(current!=NULL)
                {
                    if(current->Is_Seq_Equal_To_Node_Content(search_key,key_length))
                    {
                        // Item found. Update search result and break out of the loop:
                        search_result = true;
                        break;
                    }
                    else
                    {   
                        // Item not yet found. Move current
                        // to next node in the list:
                        current = current->next_node;
                    }
                }
                else // current is NULL. Done with searching entire list.
                {
                    break;
                }
            }
        }
        // We are done with our operation. Set
        // current to NULL:
        Reset_Current_To_NULL();
    }
}

// ------------------------------------ End: Class Public Member Function Definitions ---------------------------------------------





// ------------------------------------ Begin: Class Private Member Function Definitions -------------------------------------------


bool LinkedList::Is_List_Full()
{
    try
    {

        ListNode *temp_node;
        temp_node = new ListNode;
        temp_node->~ListNode(); // Calling destructor explicitely.

        return false;

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Checking If List Is Full."<<endl;
        cout<<"\n\t\t\tException Details: "<<e.what()<<endl;
        return true;
    }
    
}

bool LinkedList::Is_List_Empty()
{
    return (list_length == 0);
}

// ------------------------------------ End: Class Private Member Function Definitions ---------------------------------------------