#include "Prefix_Trie.h"


// -------------------------------------------- Begin: Class Ctor & Dtor -------------------------------------------------------------------------------------


// Default ctor:
Prefix_Trie::Prefix_Trie()
{
    
    // Set root node to NULL:
    root = NULL;
    
    // set sars genome array pointer to NULL:
    sars_full_genome = NULL;

    // set sars genome length to zero:
    sars_full_genome_length = 0;

}



// Overloaded ctor
Prefix_Trie::Prefix_Trie(const char** query_set,int num_of_queries,int length_of_a_query)
{
    
    // Set root node to NULL:
    root = NULL;    
    
    // set sars genome array pointer to NULL:
    sars_full_genome = NULL;

    // set sars genome length to zero:
    sars_full_genome_length = 0;
    

    // Utilise the Insert function
    // to insert all the query fragments:

    char* temp_query;

    for(unsigned int row = 0; row < num_of_queries; row++)
    {
        temp_query = new char[length_of_a_query];

        for(unsigned int index = 0; index < length_of_a_query; index++)
        {
            temp_query[index] = query_set[row][index];
        }

        // Call the insert function:
        Insert_Item_In_Trie(temp_query,length_of_a_query);

        // free the memory:
        delete[] temp_query;
    }

}




// Copy ctor
Prefix_Trie::Prefix_Trie(const Prefix_Trie& old_trie)
{
   
    // Set root node to NULL:
    this->root = NULL;
    
    // set sars genome array pointer to NULL:
    this->sars_full_genome = NULL;

    // set sars genome length to zero:
    this->sars_full_genome_length = 0;
  
    
    // Copy the nodes of the old trie:

    // Temp node pointer to the
    // old trie's root:
    Trie_Node* temp;
    temp = old_trie.root;

    if(temp==NULL)
    {
        this->root = NULL;
    }

    else
    {
        Queue old_trie_queue;
        Queue new_trie_queue;

        // Creating the trie node for
        // this new trie:
        Trie_Node* node;
        node = new Trie_Node;
        this->root = node;

        new_trie_queue.Enqueue(this->root);
        old_trie_queue.Enqueue(temp);


        // Loop through the children nodes of the old
        // trie's root in BFS order, and create the 
        // corresponding nodes in the new trie:

        Trie_Node* temp1; // For old trie
        Trie_Node* temp2; // For new trie
        while ( !old_trie_queue.Is_Queue_Empty() )
        {
            // Dequeue the nodes:
            old_trie_queue.Dequeue(temp1);
            new_trie_queue.Dequeue(temp2);

            if(temp1!=NULL && temp2!= NULL)
            {
                if(temp1->A != NULL)
                {
                    // Create corresponding node in the
                    // new trie:
                    Trie_Node* node_for_new_trie;
                    node_for_new_trie = new Trie_Node;

                    // update the child pointer in the temp2
                    // node from new trie:
                    temp2->A = node_for_new_trie;

                    // Insert the nodes into
                    // each corresponding queues:
                    old_trie_queue.Enqueue(temp1->A);
                    new_trie_queue.Enqueue(node_for_new_trie);

                }

                if(temp1->C != NULL)
                {
                    // Create corresponding node in the
                    // new trie:
                    Trie_Node* node_for_new_trie;
                    node_for_new_trie = new Trie_Node;

                    // update the child pointer in the temp2
                    // node from new trie:
                    temp2->C = node_for_new_trie;

                    // Insert the nodes into
                    // each corresponding queues:
                    old_trie_queue.Enqueue(temp1->C);
                    new_trie_queue.Enqueue(node_for_new_trie);

                }

                if(temp1->G != NULL)
                {
                    // Create corresponding node in the
                    // new trie:
                    Trie_Node* node_for_new_trie;
                    node_for_new_trie = new Trie_Node;

                    // update the child pointer in the temp2
                    // node from new trie:
                    temp2->G = node_for_new_trie;

                    // Insert the nodes into
                    // each corresponding queues:
                    old_trie_queue.Enqueue(temp1->G);
                    new_trie_queue.Enqueue(node_for_new_trie);

                }

                if(temp1->T != NULL)
                {
                    // Create corresponding node in the
                    // new trie:
                    Trie_Node* node_for_new_trie;
                    node_for_new_trie = new Trie_Node;

                    // update the child pointer in the temp2
                    // node from new trie:
                    temp2->T = node_for_new_trie;

                    // Insert the nodes into
                    // each corresponding queues:
                    old_trie_queue.Enqueue(temp1->T);
                    new_trie_queue.Enqueue(node_for_new_trie);

                }
            }

        }


        // Copy sars_genome, if it's not empty:
        if(old_trie.sars_full_genome != NULL && old_trie.sars_full_genome_length != 0)
        {
            this->sars_full_genome = new char[old_trie.sars_full_genome_length];
            this->sars_full_genome_length = old_trie.sars_full_genome_length;

            for(unsigned int index = 0; index < old_trie.sars_full_genome_length; index++)
            {
                this->sars_full_genome[index] = old_trie.sars_full_genome[index];
            }
        }        

    }

}







// Class dtor
Prefix_Trie::~Prefix_Trie()
{
    // De-allocate SARS genome array:
    if(sars_full_genome != NULL)
    {
        delete[] sars_full_genome;
        sars_full_genome_length = 0;
    }

    // De-alloacte Trie nodes:
    if(root != NULL)
    {
        
        // Create the queue:
        Queue nodes_queue;

        // Enqueue the root into the stack:
        nodes_queue.Enqueue(root);

        // A temporary trie node:
        Trie_Node* temp_node;

        // Now, 'Enter-The-Loop':
        while( ! nodes_queue.Is_Queue_Empty() )
        {
            nodes_queue.Dequeue(temp_node);

            if(temp_node!=NULL)
            {
                // Push all the children
                // nodes into the stack:
                if(temp_node->A != NULL)
                {
                    nodes_queue.Enqueue(temp_node->A);
                }
                if(temp_node->C != NULL)
                {
                    nodes_queue.Enqueue(temp_node->C);
                }
                if(temp_node->G != NULL)
                {
                    nodes_queue.Enqueue(temp_node->G);
                }
                if(temp_node->T != NULL)
                {
                    nodes_queue.Enqueue(temp_node->T);
                }
            }


            // De-allocate:
            delete temp_node;
            temp_node = NULL;

        } // While loop ends


        // make root NULL:
        root = NULL;

    }
}

// -------------------------------------------- End: Class Ctor & Dtor   -------------------------------------------------------------------------------------













// -------------------------------------------- Begin: Class Public Member Functions -------------------------------------------------------------------------



void Prefix_Trie::Insert_Item_In_Trie(const char* sequence,unsigned int sequence_length)
{   
     // The trie is empty at this moment.
    // This is the first sequence being
    // inserted into the trie.
    if(root == NULL) 
    {
        // Create the root node:
        Trie_Node* node;
        node = new Trie_Node;
        root = node;

        // Now insert the subsequent nodes
        // representing the sequence, starting 
        // from the root node.

        Trie_Node* current_node = root;     
        for(unsigned int i=0; i<sequence_length; i++)
        {
            if(sequence[i] == 'A')
            {   
                // Update the child pointer:
                if(current_node->A == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->A = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->A;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->A;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }
                
            }

            else if(sequence[i] == 'C')
            {   
                // Update the child pointer:
                if(current_node->C == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->C = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->C;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->C;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }               
            }

            else if(sequence[i] == 'G')
            {   
                // Update the child pointer:
                if(current_node->G == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->G = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->G;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->G;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }
                
            }

            else if(sequence[i] == 'T')
            {   
                // Update the child pointer:
                if(current_node->T == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->T = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->T;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->T;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }
                
            }

            else
            {
                cout<<"\n\t\tInvalid Sequence Character Detected. Exiting Program."<<endl;
                exit(EXIT_FAILURE);
            }

        } // Insertion for loop ends.

        current_node = NULL;

    } // Insertion into empty trie done!


    else // The trie is non-empty
    {

        // Now insert the nodes
        // representing the sequence, starting 
        // from the root node.

        Trie_Node* current_node = root;  

        for(unsigned int i=0; i<sequence_length; i++)
        {
            if(sequence[i] == 'A')
            {   
                // Update the child pointer:
                if(current_node->A == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->A = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->A;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->A;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }
                
            }

            else if(sequence[i] == 'C')
            {   
                // Update the child pointer:
                if(current_node->C == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->C = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->C;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->C;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }               
            }

            else if(sequence[i] == 'G')
            {   
                // Update the child pointer:
                if(current_node->G == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->G = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->G;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->G;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }
                
            }

            else if(sequence[i] == 'T')
            {   
                // Update the child pointer:
                if(current_node->T == NULL)
                {
                    // Create a node:
                    Trie_Node* new_node;
                    new_node = new Trie_Node;

                    // Update pointer:
                    current_node->T = new_node;

                    // Move current to this newly
                    // inserted node:
                    current_node = current_node->T;
                }
                else
                {
                    // Just move current pointer:
                    current_node = current_node->T;
                }

                if(i==(sequence_length-1)) // It's the last char for the leaf-node
                {
                    current_node->is_leaf = true;
                }
                
            }

            else
            {
                cout<<"\n\t\tInvalid Sequence Character Detected. Exiting Program."<<endl;
                exit(EXIT_FAILURE);
            }

        } // Insertion for loop ends.

        current_node = NULL;

    }
}





void Prefix_Trie::Search_Item_In_Trie(const char* target_sequence,int target_length,int mismatch_tolerance,bool& is_found)
{
    if(target_sequence == NULL)
    {
        cout<<"\n\t\tEmpty Target Sequence Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }
    if(target_length <= 0)
    {
         cout<<"\n\t\tInvalid Target Sequence Length Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    if(root == NULL) // Empty trie. Nothing to search against.
    {
        is_found = false;
    }

    else
    {
        Trie_Node* current_node;
        Trie_Node* temp_root;

        // Getting root node
        temp_root = root;

        // Pushing temp root into
        // the node stack
        Stack node_stack;
        node_stack.Push(temp_root);

        int mismatch_count = 0;

        for(unsigned int index = 0; index< target_length; index++)
        {
            // Pop the top node from the stack:
            node_stack.Pop(current_node);

            if (index < (target_length-1)) // upto 2nd last char of the target sequence
            {
                if(target_sequence[index] == 'A')
                {
                    if(current_node->A != NULL) // path exists. Push next node into stack.
                    {
                        node_stack.Push(current_node->A);
                    }
                    else // Mismatch detected. Perform mismatch routine.
                    {
                        if(mismatch_count>=mismatch_tolerance) // mismatch threshold crossed. Quit search
                        {
                            is_found = false;
                            break;
                        }

                        else // Mismatch threshold not crossed.
                        {
                            // Update mismatch count
                            mismatch_count++;

                            // Check the 3 sibling sub-tries for
                            // the reaminder portion of the target
                            // sequence substring.

                            // Get the remaining target sequence portion:
                            int reamining_target_length = target_length - index;
                            char* remaining_target;
                            remaining_target = new char[reamining_target_length];
                            for(int i=0;i<reamining_target_length;i++)
                            {
                                remaining_target[i] = target_sequence[i];
                            }

                            bool sibling_search_C = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->C);
                            bool sibling_search_G = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->G);
                            bool sibling_search_T = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->T);

                            if (sibling_search_C || sibling_search_G || sibling_search_T) // any result true, we've found it
                            {
                                is_found = true;
                                break;
                            }
                            else
                            {
                                is_found = false;
                                break;
                            }
                            // De-allocate:
                            delete[] remaining_target;
                        }

                    }
                } // Checking for 'A' done

                else if(target_sequence[index] == 'C')
                {
                    if(current_node->C != NULL) // path exists. Push next node into stack.
                    {
                        node_stack.Push(current_node->C);
                    }
                    else // Mismatch detected. Perform mismatch routine.
                    {
                        if(mismatch_count>=mismatch_tolerance) // mismatch threshold crossed. Quit search
                        {
                            is_found = false;
                            break;
                        }

                        else // Mismatch threshold not crossed.
                        {
                            // Update mismatch count
                            mismatch_count++;

                            // Check the 3 sibling sub-tries for
                            // the reaminder portion of the target
                            // sequence substring.

                            // Get the remaining target sequence portion:
                            int reamining_target_length = target_length - index;
                            char* remaining_target;
                            remaining_target = new char[reamining_target_length];
                            for(int i=0;i<reamining_target_length;i++)
                            {
                                remaining_target[i] = target_sequence[i];
                            }

                            bool sibling_search_A = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->A);
                            bool sibling_search_G = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->G);
                            bool sibling_search_T = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->T);

                            if (sibling_search_A || sibling_search_G || sibling_search_T) // any result true, we've found it
                            {
                                is_found = true;
                                break;
                            }
                            else
                            {
                                is_found = false;
                                break;
                            }
                            // De-allocate:
                            delete[] remaining_target;
                        }

                    }
                } // Checking for 'C' done


                else if(target_sequence[index] == 'G')
                {
                    if(current_node->G != NULL) // path exists. Push next node into stack.
                    {
                        node_stack.Push(current_node->G);
                    }
                    else // Mismatch detected. Perform mismatch routine.
                    {
                        if(mismatch_count>=mismatch_tolerance) // mismatch threshold crossed. Quit search
                        {
                            is_found = false;
                            break;
                        }

                        else // Mismatch threshold not crossed.
                        {
                            // Update mismatch count
                            mismatch_count++;

                            // Check the 3 sibling sub-tries for
                            // the reaminder portion of the target
                            // sequence substring.

                            // Get the remaining target sequence portion:
                            int reamining_target_length = target_length - index;
                            char* remaining_target;
                            remaining_target = new char[reamining_target_length];
                            for(int i=0;i<reamining_target_length;i++)
                            {
                                remaining_target[i] = target_sequence[i];
                            }

                            bool sibling_search_A = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->A);
                            bool sibling_search_C = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->C);
                            bool sibling_search_T = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->T);

                            if (sibling_search_A || sibling_search_C || sibling_search_T) // any result true, we've found it
                            {
                                is_found = true;
                                break;
                            }
                            else
                            {
                                is_found = false;
                                break;
                            }
                            // De-allocate:
                            delete[] remaining_target;
                        }

                    }
                } // Checking for 'G' done


                else if(target_sequence[index] == 'T')
                {
                    if(current_node->T != NULL) // path exists. Push next node into stack.
                    {
                        node_stack.Push(current_node->T);
                    }
                    else // Mismatch detected. Perform mismatch routine.
                    {
                        if(mismatch_count>=mismatch_tolerance) // mismatch threshold crossed. Quit search
                        {
                            is_found = false;
                            break;
                        }

                        else // Mismatch threshold not crossed.
                        {
                            // Update mismatch count
                            mismatch_count++;

                            // Check the 3 sibling sub-tries for
                            // the reaminder portion of the target
                            // sequence substring.

                            // Get the remaining target sequence portion:
                            int reamining_target_length = target_length - index;
                            char* remaining_target;
                            remaining_target = new char[reamining_target_length];
                            for(int i=0;i<reamining_target_length;i++)
                            {
                                remaining_target[i] = target_sequence[i];
                            }

                            bool sibling_search_A = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->A);
                            bool sibling_search_C = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->C);
                            bool sibling_search_G = Search_Sibling_Sub_Trie(remaining_target,reamining_target_length,current_node->G);

                            if (sibling_search_A || sibling_search_C || sibling_search_G) // any result true, we've found it
                            {
                                is_found = true;
                                break;
                            }
                            else
                            {
                                is_found = false;
                                break;
                            }
                            // De-allocate:
                            delete[] remaining_target;
                        }

                    }
                } // Checking for 'T' done


            } // index < (target_length-1) check ends

            
            
            
            else // this is the last char in the target. We've found all previous characters.
            {
                if(target_sequence[index] == 'A')
                {
                    if(current_node->A != NULL)
                    {
                        is_found = true;
                        break;
                    }

                    else // we don't need to check mismatch count. All previous chars were found and mismatch limit was not broken.
                    {
                        if( current_node->C!= NULL || current_node->G != NULL || current_node->T != NULL ) // found with 1 mismatch at the end
                        {
                            is_found = true;
                            break;
                        }
                        else
                        {
                            is_found = false;
                            break;
                        }
                    }
                } // check for 'A'


                else if(target_sequence[index] == 'C')
                {
                    if(current_node->C != NULL)
                    {
                        is_found = true;
                        break;
                    }

                    else // we don't need to check mismatch count. All previous chars were found and mismatch limit was not broken.
                    {
                        if( current_node->A!= NULL || current_node->G != NULL || current_node->T != NULL ) // found with 1 mismatch at the end
                        {
                            is_found = true;
                            break;
                        }
                        else
                        {
                            is_found = false;
                            break;
                        }
                    }
                } // check for 'C'



                else if(target_sequence[index] == 'G')
                {
                    if(current_node->G != NULL)
                    {
                        is_found = true;
                        break;
                    }

                    else // we don't need to check mismatch count. All previous chars were found and mismatch limit was not broken.
                    {
                        if( current_node->A!= NULL || current_node->C != NULL || current_node->T != NULL ) // found with 1 mismatch at the end
                        {
                            is_found = true;
                            break;
                        }
                        else
                        {
                            is_found = false;
                            break;
                        }
                    }
                } // check for 'G'

                else if(target_sequence[index] == 'T')
                {
                    if(current_node->T != NULL)
                    {
                        is_found = true;
                        break;
                    }

                    else // we don't need to check mismatch count. All previous chars were found and mismatch limit was not broken.
                    {
                        if( current_node->A!= NULL || current_node->C != NULL || current_node->G != NULL ) // found with 1 mismatch at the end
                        {
                            is_found = true;
                            break;
                        }
                        else
                        {
                            is_found = false;
                            break;
                        }
                    }
                } // check for 'T'


            } // else of  if(index < (target_length-1))

        } // for() loop ends


    } // else for if(root == NULL)


    





}



void Prefix_Trie::Read_SARS_Genome_From_File(const char* file_path,int file_path_length)
{
    if(file_path == NULL || file_path_length == 0)
    {
        cout<<"\n\t\tEmpty Filepath to Genome File Detected. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    try
    {
        // Open ifstream to file
        ifstream stream_to_file;
        stream_to_file.open(file_path);

        if((!stream_to_file) || (!stream_to_file.is_open()))
        {
            cout<<"\n\t\tCouldnot Open Stream to Data File. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }

        
        // -------------------------------------------------------------------------------------------

        // Find out the size/ total length of the SARS
        // genome sequence:
        
        unsigned long int sequence_length_with_header = 0;
        unsigned long int sequence_length_with_out_header = 0;

        // A 256-length char buffer array:
        char* buffer_1;
        buffer_1 = new char[buffer_length];

        // A temporary string object:
        string temp_str;

        while(!stream_to_file.eof())
        {   
            // Clear the buffer first:
            Clear_Buffer_Array(buffer_1);
            stream_to_file>>buffer_1;

            // Clear the string:
            temp_str.clear();

            // Assign the buffer content
            // to the temp string:
            temp_str.assign(buffer_1);

            // Update length variable:
            sequence_length_with_header += (unsigned long int) temp_str.length();

        }
        // Close the stream:
        stream_to_file.close();

        // Update length of the 'without header' variable:
        sequence_length_with_out_header = sequence_length_with_header - (unsigned long int)sars_genome_header_size;        
        
        // ---------------------------------------------------------------------------------------------------------

        // Allocate required array memories:
        // Memory for initial array (includes header):
        char initial_array[sequence_length_with_header];
        sars_full_genome = new char[sequence_length_with_out_header];
        
        // Update the subject length member variable
        sars_full_genome_length = sequence_length_with_out_header;

        // -----------------------------------------------------------------------------------------------------------

         // Open another stream to the file:
        ifstream stream_to_file_2;
        stream_to_file_2.open(file_path);

        if((!stream_to_file_2) || (!stream_to_file_2.is_open()))
        {
            cout<<"\n\t\tCouldnot Again Open Stream to Data File. Exiting Program."<<endl;
            exit(EXIT_FAILURE);
        }


        // Now, read in the contents into the
        // array this time
        unsigned int temp_str_length = 0;
        unsigned int array_start_index = 0;

        // Index indicating where in the
        // initial array the next character
        // should go:
        unsigned int initial_array_index = 0;

        while((!stream_to_file_2.eof()) && (initial_array_index < sequence_length_with_header))
        {
            Clear_Buffer_Array(buffer_1);
            stream_to_file_2>>buffer_1;

            // Clear temp string and assign
            // buffer content to it:
            temp_str.clear();
            temp_str.assign(buffer_1);

            temp_str_length = temp_str.length();

            // Copy the characters into the array
            // from the string:
            for(unsigned int index = 0; index < temp_str_length; index++,initial_array_index++)
            {
                initial_array[initial_array_index] = temp_str.at(index);
            }

        }
        // Close the stream:
        stream_to_file_2.close();
        

        // Copy from initial array into
        // final array (excluding header)
        for(unsigned int index = 0; index < sars_full_genome_length; index++)
        {
            sars_full_genome[index] = initial_array[index+sars_genome_header_size];
        }

        cout<<"\n\t\tLength of SARS Genome Read From File = "<<sars_full_genome_length<<endl;
       
        // Free buffer and initial arrays
        delete[] buffer_1;        

    }
    catch(const exception& e)
    {
        cout<<"\n\t\tException Caught While Trying to Read From the File. Exiting Program."<<endl;
        cout<<"Exception Details: "<<e.what()<<endl;
        exit(EXIT_FAILURE);
    }

}


void Prefix_Trie::Traverse_Trie_Using_Genome(const char* given_genome,int given_genome_length,int& num_of_generated_kmers,int& num_of_found_kmers)
{
    if(given_genome == NULL || given_genome_length == 0)
    {
        cout<<"\n\t\tEmpty Genome Sequence Given. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    // Set this genome as the new sars_full_genome and
    // search for all kmers:
    if(sars_full_genome != NULL)
    {
        // free it:
        delete[] sars_full_genome;
        sars_full_genome_length = 0;
    }

    // Allocate memories:
    sars_full_genome = new char[given_genome_length];
    sars_full_genome_length = given_genome_length;

    // Copy content:
    for(int i =0; i < given_genome_length; i++)
    {
        sars_full_genome[i] = given_genome[i];
    }


    // Function call:   
    Search_For_All_36mers(num_of_generated_kmers,num_of_found_kmers);
}

void Prefix_Trie::Search_For_All_36mers(int& num_of_kmers_searched_for,int& num_of_kmers_found)
{

    if(sars_full_genome == NULL || sars_full_genome_length == 0)
    {
        cout<<"\n\t\tEmpty SARS Genome Detected in Search For All 36mers. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    // Initializing:
    num_of_kmers_searched_for = 0;
    num_of_kmers_found = 0;


    char* generated_kmer;

    for(unsigned int i=0; i+(length_of_a_kmer-1) < sars_full_genome_length; i++)
    {
        // Allocate memories:
        generated_kmer = new char[length_of_a_kmer];

        // Copy Content:
        for(unsigned int index = 0; index < length_of_a_kmer; index++)
        {
            generated_kmer[index] = sars_full_genome[index+i];
        }

        bool is_found = false;

        // Call the search function:
        Search_Item_In_Trie(generated_kmer,length_of_a_kmer,1,is_found);

        num_of_kmers_searched_for++;

        if(is_found == true)
        {
            num_of_kmers_found++;
        }

        // De-allocate:
        delete[] generated_kmer;
    }   

}


bool Prefix_Trie::Is_Trie_Empty()
{
    return (root == NULL);
}


void Prefix_Trie::Generate_And_Store_36mers(unsigned int num_of_36mers_to_generate)
{
    if(root != NULL)
    {
        cout<<"\n\t\tThe Trie is Not Empty. Empty it Before Stroing 36mers. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    if( sars_full_genome == NULL || sars_full_genome_length == 0)
    {
        cout<<"\n\t\tEmpty SARS Genome Detected While Generating and Storing 36mers. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }


    int random_start_index;
    int counter = 0;
    char* random_kmer;
    
    while(counter < num_of_36mers_to_generate)
    {
        random_start_index = (unsigned long int)rand()%sars_full_genome_length;

        if(random_start_index+(length_of_a_kmer-1) < sars_full_genome_length)
        {
            counter++;

            // Allocate memories:
            random_kmer = new char[length_of_a_kmer];

            // copy content:
            for(int i=0; i< length_of_a_kmer; i++)
            {
                random_kmer[i] = sars_full_genome[random_start_index+i];
            }

            // insert it into the trie:
            Insert_Item_In_Trie(random_kmer,length_of_a_kmer);

            // De-allocate:
            delete[] random_kmer;
            random_kmer = NULL;
        }
    }   
    

}


void Prefix_Trie::Generate_And_Store_Mutated_36mers(unsigned int num_of_36mers_to_generate)
{
    if(root != NULL)
    {
        cout<<"\n\t\tThe Trie is Not Empty. Empty it Before Stroing Mutated 36mers. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }

    if( sars_full_genome == NULL || sars_full_genome_length == 0)
    {
        cout<<"\n\t\tEmpty SARS Genome Detected While Generating and Storing Mutated 36mers. Exiting Program."<<endl;
        exit(EXIT_FAILURE);
    }


    int random_start_index;
    int counter = 0;
    char* random_kmer;
    char char_buffer;
    int mutation_probability;
    int mutated_char_choice;
    
    while(counter < num_of_36mers_to_generate)
    {
        random_start_index = (unsigned long int)rand()%sars_full_genome_length;

        if(random_start_index+(length_of_a_kmer-1) < sars_full_genome_length)
        {
            counter++;

            // Allocate memories:
            random_kmer = new char[length_of_a_kmer];

            // copy content:
            for(int i=0; i< length_of_a_kmer; i++)
            {
                char_buffer = sars_full_genome[random_start_index+i];

                // Check if we want to mutate this character:
                mutation_probability = rand() % 100;

                if(mutation_probability>=0 && mutation_probability <= 4) // we mutate this char
                {                    

                    if(char_buffer == 'A') // mutate to C/ G/ T
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'C';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'G';
                        }
                        else
                        {
                            char_buffer = 'T';
                        }
                    }

                    else if(char_buffer == 'C')
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'A';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'G';
                        }
                        else
                        {
                            char_buffer = 'T';
                        }
                    }

                    else if(char_buffer == 'G')
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'A';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'C';
                        }
                        else
                        {
                            char_buffer = 'T';
                        }
                    }

                    else if(char_buffer == 'T')
                    {
                        mutated_char_choice = rand()%3;

                        if(mutated_char_choice == 0)
                        {
                            char_buffer = 'A';
                        }
                        else if(mutated_char_choice == 1)
                        {
                            char_buffer = 'C';
                        }
                        else
                        {
                            char_buffer = 'G';
                        }
                    }

                }

                random_kmer[i] = char_buffer;
            }

            // insert it into the trie:
            Insert_Item_In_Trie(random_kmer,length_of_a_kmer);

            // De-allocate:
            delete[] random_kmer;
            random_kmer = NULL;
        }
    }

}


unsigned long int Prefix_Trie::Get_Trie_Size()
{
    Trie_Node* temp;
    temp = root;

    unsigned long int trie_size = Count_Nodes(root);
    temp = NULL;
    
    return trie_size;
}



// -------------------------------------------- End: Class Public Member Functions   -------------------------------------------------------------------------



// -------------------------------------------- Begin: Class Private Member Functions ------------------------------------------------------------------------


bool Prefix_Trie::Search_Sibling_Sub_Trie(const char* given_sequence,int sequence_length,Trie_Node* starting_node)
{
    if(starting_node == NULL)
    {
        return false;
    }

    else
    {
        Trie_Node* current_node;
        current_node = starting_node;

        for(unsigned int i=0; i< sequence_length; i++)
        {
            if(given_sequence[i] == 'A')
            {
                if(current_node->A != NULL)
                {
                    current_node = current_node->A;
                }
                else // Path does not exist. Return false
                {
                    current_node = NULL;
                    starting_node = NULL;

                    return false;
                }
            }

            else if(given_sequence[i] == 'C')
            {
                if(current_node->C != NULL)
                {
                    current_node = current_node->C;
                }
                else // Path does not exist. Return false
                {
                    current_node = NULL;
                    starting_node = NULL;

                    return false;
                }
            }

            else if(given_sequence[i] == 'G')
            {
                if(current_node->G != NULL)
                {
                    current_node = current_node->G;
                }
                else // Path does not exist. Return false
                {
                    current_node = NULL;
                    starting_node = NULL;

                    return false;
                }
            }

            else if(given_sequence[i] == 'T')
            {
                if(current_node->T != NULL)
                {
                    current_node = current_node->T;
                }
                else // Path does not exist. Return false
                {
                    current_node = NULL;
                    starting_node = NULL;

                    return false;
                }
            }

            else
            {
                cout<<"\n\t\tInvalid Char in Traversing Sub-Trie Detected. Exiting Program."<<endl;
                exit(EXIT_FAILURE);
            }

        } // for() loop ends

        // No break in path found. All links exist. Return true.
        return true;
    }
}



void Prefix_Trie::Clear_Buffer_Array(char* &given_buffer)
{
    for(unsigned int i=0;i<buffer_length;i++)
    {
        given_buffer[i] = '\0';
    }
}


unsigned long int Prefix_Trie::Count_Nodes(const Trie_Node* node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + Count_Nodes(node->A) + Count_Nodes(node->C) + Count_Nodes(node->G) + Count_Nodes(node->T);
    }
}





// -------------------------------------------- End: Class Private Member Functions   ------------------------------------------------------------------------