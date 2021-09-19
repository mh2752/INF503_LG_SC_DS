#include "ListNode.h"

// ---------------------------------------------------- Begin: Class Ctor & Dtor Definitions ----------------------------


ListNode::ListNode()
{
    node_content = NULL;
    node_content_length = 0;
    next_node = NULL;
}


ListNode::ListNode(const char* source_array,unsigned int source_length)
{
    try
    {   
        // Allocate memories: 
        node_content = new char[node_content_length];

        // Update node content length info:
        node_content_length = source_length;

        // Now copy source content:
        for(unsigned int index = 0; index< source_length; index++)
        {
            node_content[index] = source_array[index];
        }

        // Set Next Node to NULL:
        next_node = NULL;
        
    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Creating a ListNode Object. Exiting Program Now."<<endl;
        cout<<"\nt\t\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    
}

ListNode::~ListNode()
{
    // Deallocate memories:
    if(node_content!=0)
    {
        delete[] node_content;
        node_content = NULL;
        node_content_length = 0;
    }

    // Deallocate next node inside linked list.
}

// ---------------------------------------------------- End: Class Ctor & Dtor Definitions ----------------------------




// ----------------------------------------- Begin: Class Public Member Function Definitions ----------------------------


unsigned int ListNode::Get_Node_Content_Length()
{
    return node_content_length;
}


void ListNode::Get_Node_Content(char* &destination_array,unsigned int destination_length)
{
    if(destination_length != node_content_length)
    {   
        cout<<"\n\t\tImproper Length for Destination Array in Getting ListNode Content. Exiting Program Now."<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        for(unsigned int index = 0; index < destination_length; index++)
        {
            destination_array[index] = node_content[index];
        }
    }
}


void ListNode::Set_Node_Content(const char* source_array,unsigned int source_length)
{
    if(node_content_length==0)
    {
        // Allocate memory first:
        node_content = new char[source_length];
        node_content_length = source_length;

        // Copy source content:
        for(unsigned int index = 0; index < source_length; index++)
        {
            node_content[index] = source_array[index];
        }
    }
    else // Have to overwrite content:
    {
        if(source_length != node_content_length)
        {   
            cout<<"\n\t\tImproper Length for Source Array in Setting ListNode Content. Exiting Program Now."<<endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            for(unsigned int index = 0; index < source_length; index++)
            {
                node_content[index] = source_array[index];
            }
        }

    }

}


bool ListNode::Is_Seq_Equal_To_Node_Content(const char* external_array,unsigned int external_array_length)
{
    if(external_array_length != node_content_length)
    {
        cout<<"\n\t\tUnequal Length of external Array Received in Checking Content Equality. Exiting Program Now."<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        bool equality_flag = true;

        for(unsigned int index = 0; index < external_array_length; index++)
        {
            if(node_content[index] != external_array[index])
            {
                equality_flag = false;
                break;
            }
        }

        return equality_flag;
    }
}



// ----------------------------------------- End: Class Public Member Function Definitions ----------------------------