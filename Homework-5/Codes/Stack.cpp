#include "Stack.h"


/*

Implementation of the Stack class.

Author:
    Nazmul(mh2752@nau.edu)

*/


// ---------------------------------------------------- Begin: Class Ctor & Dtor ----------------------------------------------------------------------------------


Stack::Stack()
{
    // Set top to NULL
    top = NULL;

    // Set stack size to zero
    stack_size = 0;
}


Stack::~Stack()
{
    // Set stack size to zero:
    stack_size = 0;    
    
    // Start de-allocating
    // all memories:   

    Stack_Node* temp;

    while(top!=NULL)
    {
        temp = top;        
        top = top->next_item;


        // De-allocate:
        temp->item = NULL; // To avoid dangling pointer issues in the trie.
        temp->next_item = NULL; // To avoid dangling pointer issues in the stack.

        delete temp;
    }
    
}

// ---------------------------------------------------- End: Class Ctor & Dtor ------------------------------------------------------------------------------------





// ---------------------------------------------------- Begin: Public Member Functions ----------------------------------------------------------------------------

void Stack::Push(Trie_Node* trie_node)
{
    try
    {
        if(top == NULL)
        {
            // This is the very first node
            // being inserted in the stack:
            Stack_Node* node;
            node = new Stack_Node;

            node->item = trie_node;
            node->next_item = NULL;


            // Update top and size:
            top = node;
            stack_size++;
        }
        else
        {
            Stack_Node* node;
            node = new Stack_Node;

            node->item = trie_node;
            node->next_item = top;

            // Update top and size:
            top = node;
            stack_size++;
        }
    }
    catch(const std::exception& e)
    {
        cout<<"\n\t\tException Caught While Pushing an Item to the Stack. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    

}

void Stack::Pop(Trie_Node*& popped_node)
{
    if(!Is_Stack_Empty())
    {
        try
        {
            // Passing the value
            popped_node = top->item;

            // Moving the top pointer
            // to the next item and 
            // deleting the current top:
            Stack_Node* temp = top;
            top = top->next_item;

            // Deleting temp:
            temp->item = NULL;
            temp->next_item = NULL;
            delete temp;

            // updating size info:
            stack_size--;

        }
        catch(const std::exception& e)
        {
            cout<<"\n\t\tException Caught While Popping an Item From a Non-empty Stack. Exiting Program."<<endl;
            cout<<"\n\t\tException Details: "<<e.what()<<endl;
            exit(EXIT_FAILURE);
        }
        

    }
    else
    {   
        cout<<"\n\t\tPopping From an Empty Stack. Returning NULL Pointer."<<endl;
        popped_node = NULL;
    }


}


bool Stack::Is_Stack_Empty()
{
    return (stack_size == 0);
}

bool Stack::Is_Stack_Full()
{
    try
    {
        Stack_Node* temp;
        temp = new Stack_Node;
        delete temp;
        return false;
    }
    catch(bad_alloc& exception)
    {
        cout<<"\n\t\tStack is Full."<<endl;
        return true;
    }
    
}


// ---------------------------------------------------- End: Public Member Functions   ----------------------------------------------------------------------------