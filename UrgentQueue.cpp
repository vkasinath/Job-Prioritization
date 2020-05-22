#include <vector>
#include <ctime>

#include "Job.h"
#include "UrgentQueue.h"

/* ******************************************************************
    GENERAL COMMENTS FOR UrgentQueue FUNCTIONS
   Assume the array/vector is 1-based, instead of 0-based].
   when coding, will just do a -1 [just easier to understand & track]
   In a heap - Consider k-th element of the vector, the 
   the left child of the k-th element is located at 2*k index
   the right child of the k-th element is located at 2*k +1 index
   the parent is located at (k/2) index 
   ******************************************************************
*/


Job* UrgentQueue::top(){
  if (prio_queue.empty())
    return NULL;
  return prio_queue[0]; 
}

void UrgentQueue::push( Job* &q_entry )
{

  unsigned int pos = prio_queue.size();             //position of newly inserted item
  q_entry->urgent_hook  = pos;
  q_entry->priority_ptr = this;
  prio_queue.push_back(q_entry);
  PercolateUp(pos);

}

// this requires job with highest priority to bubble up to root
// so we use the "max-heap" strategy [all child will be < its parent]
// percolate up process
// Compare the added entry with its parent 
// if parent < added entry, swap the added entry with the parent. 
// The comparison is repeated until the parent is less than or equal to the percolating entry
// step 1:  the index of the parent for this last added element is at (n/2)
// step 2:  since this is a non-heap, swap value at (n/2) with value at n, if needed
// step 3:  check for heap. if good, return else set n--; loop to step 1, until n=1
void UrgentQueue::PercolateUp(const unsigned int &pos){
  unsigned int loc = pos+1;
  while (loc >= 1){

    unsigned int parent = loc/2;

    if (parent < 1) 
      return;                // return if parent index goes out of range
    
    // if valid heap, return
    if (check_heap())
      return;
    
    if (prio_queue[loc-1]->priority > prio_queue[parent-1]->priority){
      //swap values between parent and current loc
      std::swap(prio_queue[loc-1], prio_queue[parent-1]);
      // change urgent_hook for the jobs in parent and loc
      prio_queue[loc-1]->urgent_hook    = loc-1;
      prio_queue[parent-1]->urgent_hook = parent-1;
      // if valid heap after swap, return gracefully
      
      if (check_heap())
        return;

    }

    loc--;
  }
}

Job* UrgentQueue::pop(){
 if (prio_queue.empty())
    return NULL;

    // this job at root needs to be removed
    // save it so we can pass it back, and remove it from time queue
    // then, just call remove_from_index, with pos = 0
  Job* first_in_queue = prio_queue[0];    
  remove_from_index(0);
  return first_in_queue;  
}

void UrgentQueue::remove_from_index(const uq_hook &pos){
  if (prio_queue.empty())
    return;

  Job* last = prio_queue.back();
  prio_queue[pos] = last;
  prio_queue.pop_back();
  PercolateDown(pos);
}

// this requires job with highest priority to percolate root to its valid position
// remember, we use the "max-heap" strategy [all child will be < its parent]
// percolate down process
// 1. with node, find largest child of node
// 2. Swap node with its largest child, if node-value < largest_child-value
// 3. Repeat steps 3 & 4 until no swaps needed.
void UrgentQueue::PercolateDown(const unsigned int &pos){
  unsigned int loc  = pos+1;
  unsigned int imax = prio_queue.size();
  while (loc <= imax){
    unsigned int left  = loc*2;
    unsigned int right = loc*2 + 1;
    if (right > imax )                        // if right is going out of bounds
      right = left;                        // set left (the one less) and right to be the same
    unsigned int swap = 0;
    if (right <= imax){
      if (prio_queue[left-1]->priority > prio_queue[right-1]->priority)    // check if left child > right child
        swap = left;                                                    // if so, largest child is left
      else
        swap = right;                            
      // at this point, we now know what to swap with [the largest child]
      if (prio_queue[swap-1]->priority > prio_queue[loc-1]->priority){
        std::swap(prio_queue[swap-1], prio_queue[loc-1]);
        // change urgent_hook for the jobs in swap and loc
        prio_queue[loc-1]->urgent_hook  = loc-1;
        prio_queue[swap-1]->urgent_hook = swap-1;
        loc = swap;
      }
      else
        loc++;
      if (check_heap())
        return;
    }
    else 
      break;
  }
}

// Check if the queue is a valid heap
bool UrgentQueue::check_heap(){
  // remember, we are doing a max heap for priority. 
  // so every node should be >= its child nodes
  // Returns true if prio_queue represents a heap
  // Start from root and go till the last node 
  unsigned int n = prio_queue.size();                   // size of our priority queue
  for (unsigned int i = 1; i <= n; i++) { 
    if     ( ((2*i -1 < n) && prio_queue[2*i -1]->priority > prio_queue[i-1]->priority) ||
          (2*i < n && prio_queue[2*i]->priority > prio_queue[i-1]->priority) )
            return false; 
    } 
    return true; 
}

void UrgentQueue::printHeap(std::ofstream &outfile){
  outfile << "UQ " << prio_queue.size() << " jobs:" << std::endl;
  for (unsigned int i=0; i< prio_queue.size(); i++)
    outfile << "\t" << prio_queue[i];
}
