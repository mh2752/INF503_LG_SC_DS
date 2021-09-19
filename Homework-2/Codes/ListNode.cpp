#include "ListNode.h"


// --------------------------------------------- Constructors and Destructor Definitions -----------------------------------------


// Default constructor
ListNode::ListNode()
{
    node_sequence = NULL; // No sequence given.
    next_node = NULL;// We do not have any next node yet.   
}


// Overloaded constructor
ListNode::ListNode(const char* given_seq)
{
    
    // Allocating memory. Program will exit with EXIT_FAILURE status upon allocation failure.
    try
    {

        // Find the length first:
        int length_of_seq = 0;

        while(given_seq[length_of_seq]!='\0')
        {
            length_of_seq++;
        }

        node_sequence = new char[length_of_seq+1];
        

        // Copying the content (including terminating null character):
        for(int index = 0; index<length_of_seq+1; index++)
        {
            node_sequence[index] = given_seq[index];
        }


        next_node = NULL; // We do not have any next node yet.

    }
    catch(bad_alloc& exception)
    {
        cout<<"Memory Allocation for a ListNode Object Failed."<<endl;
        cout<<"\t\tDetails: "<<exception.what()<<endl;
        exit(EXIT_FAILURE);
    }

}



// Copy constructor
ListNode::ListNode(const ListNode &external_node)
{
    // Allocating memory. Program will exit with EXIT_FAILURE status upon allocation failure.
    try
    {

        // Find the length first:
        int length_of_seq = 0;

        while(external_node.node_sequence[length_of_seq]!='\0')
        {
            length_of_seq++;
        }

        node_sequence = new char[length_of_seq+1];
        

        // Copying the content (including terminating null character):
        for(int index = 0; index<length_of_seq+1; index++)
        {
            node_sequence[index] = external_node.node_sequence[index];
        }


        next_node = NULL; // We do not have any next node yet.

    }
    catch(bad_alloc& exception)
    {
        cout<<"Memory Allocation Inside ListNode Copy Constructor Failed."<<endl;
        cout<<"\t\tDetails: "<<exception.what()<<endl;
        exit(EXIT_FAILURE);
    }
  


}



// Class destructor
ListNode::~ListNode()
{    
    // Just release the array memories:
    delete[] node_sequence;

    // The next_node is publicly available. 
    // It should be deleted inside the LinkedList class destructor
    // to avoid any dangling pointer issue.
}


// ------------------------------------------------------ Class Member Function Definitions ----------------------------------------------------------------


// Return the length of the char array
// held inside this node
int ListNode::Get_Node_Seq_Length()
{
    if(node_sequence == NULL)
    {
        return 0;
    }

    else
    {
        int length_of_seq = 0;

        while(node_sequence[length_of_seq]!='\0')
        {
            length_of_seq++;
        }


        return (length_of_seq+1); // +1 for including the null character
    }

}




// Set the char array content of this
// node to the given sequence
void ListNode::Set_Node_Content(char* &given_seq)
{
    // Setting node content. Program will exit with EXIT_FAILURE status upon allocation failure.
    try
    {

        // Find the length first:
        int length_of_seq = 0;

        while(given_seq[length_of_seq]!='\0')
        {
            length_of_seq++;
        }

        node_sequence = new char[length_of_seq+1];
        

        // Copying the content (including terminating null character):
        for(int index = 0; index<length_of_seq+1; index++)
        {
            node_sequence[index] = given_seq[index];
        }


        next_node = NULL; // We do not have any next node yet.

    }
    catch(bad_alloc& exception)
    {
        cout<<"Memory Allocation for a ListNode Object Failed in Set_Node_Content()."<<endl;
        cout<<"\t\tDetails: "<<exception.what()<<endl;
        exit(EXIT_FAILURE);
    }

}



// Return the content of this node 
// using 'pass by reference' technique
void ListNode::Get_Node_Content(char* &external_array)
{

    int node_seq_length = Get_Node_Seq_Length(); // Sequence length including the null character


    // Copying this node's content inside the array pointed by external_array
    for(int index = 0; index<node_seq_length; index++)
    {
        external_array[index] = node_sequence[index];
    }

}
