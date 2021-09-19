#include "Queue.h"


/*

Implementation of the Queue class.

Author:
    Nazmul(mh2752@nau.edu)

*/


// ---------------------------------------------------- Begin: Class Ctor & Dtor ----------------------------------------------------------------------------------


Queue::Queue()
{
    // Set front & rear to NULL
    front = NULL;
    rear = NULL;

    // Set stack size to zero
    queue_size = 0;
}


Queue::~Queue()
{
    // Set stack size to zero:
    queue_size = 0;    
    
    // Start de-allocating
    // all memories:   

    Queue_Node* temp;

    while(front!=NULL)
    {
        temp = front;        
        front = front->next_item;


        // De-allocate:
        temp->item = NULL; // To avoid dangling pointer issues in the trie.
        temp->next_item = NULL; // To avoid dangling pointer issues in the stack.

        delete temp;
    }

    rear = NULL;
    
}

// ---------------------------------------------------- End: Class Ctor & Dtor ------------------------------------------------------------------------------------





// ---------------------------------------------------- Begin: Public Member Functions ----------------------------------------------------------------------------

void Queue::Enqueue(Trie_Node* trie_node)
{
    try
    {
        if(front == NULL && rear == NULL)
        {
            // This is the very first node
            // being inserted in the queue:
            Queue_Node* node;
            node = new Queue_Node;

            node->item = trie_node;
            node->next_item = NULL;


            // Update front & rear:
            front = node;
            rear = node;

            // Update size:
            queue_size++;
        }
        else
        {
            Queue_Node* node;
            node = new Queue_Node;

            node->item = trie_node;
            node->next_item = NULL;

            // Insert at the rear:
            rear->next_item = node;

            // Update size:
            queue_size++;

        }
    }
    catch(const std::exception& e)
    {
        cout<<"\n\t\tException Caught While Enqueing an Item to the Queue. Exiting Program."<<endl;
        cout<<"\n\t\tException Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }
    

}

void Queue::Dequeue(Trie_Node*& dequeued_node)
{
    if(!Is_Queue_Empty())
    {
        try
        {
            // Passing the value
            dequeued_node = front->item;

            // Moving front to the
            // next node:
            Queue_Node* temp = front;
            front = front->next_item;

            // If front == NULL, we have dequeued
            // the last node. The queue is empty 
            // now. Set rear to NULL:
            if(front == NULL)
            {
                rear = NULL;
            }

            // Deleting temp:
            temp->item = NULL;
            temp->next_item = NULL;
            delete temp;

            // updating size info:
            queue_size--;

        }
        catch(const std::exception& e)
        {
            cout<<"\n\t\tException Caught While Dequeuing an Item From a Non-empty Queue. Exiting Program."<<endl;
            cout<<"\n\t\tException Details: "<<e.what()<<endl;
            exit(EXIT_FAILURE);
        }
        

    }
    else
    {   
        cout<<"\n\t\tDequeuing From an Empty Queue. Returning NULL Pointer."<<endl;
        dequeued_node = NULL;
    }


}


bool Queue::Is_Queue_Empty()
{
    return ((front == NULL) && (rear == NULL));
}


bool Queue::Is_Queue_Full()
{
    try
    {
        Queue_Node* temp;
        temp = new Queue_Node;
        delete temp;
        return false;
    }
    catch(bad_alloc& exception)
    {
        cout<<"\n\t\tQueue is Full."<<endl;
        return true;
    }
    
}


// ---------------------------------------------------- End: Public Member Functions   ----------------------------------------------------------------------------