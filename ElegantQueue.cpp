#include <vector>
#include <ctime>

#include "Job_extra.h"
#include "ElegantQueue.h"

/* ******************************************************************
    GENERAL COMMENTS FOR ALL ElegantQueue FUNCTIONS
   Assume the array/vector is 1-based, instead of 0-based].
   when coding, will just do a -1 [just easier to understand & track]
   In a heap - Consider k-th element of the vector, the 
   the left child of the k-th element is located at 2*k index
   the right child of the k-th element is located at 2*k +1 index
   the parent is located at (k/2) index 
   ******************************************************************
*/


Job* ElegantQueue ::top(){
  if (queue.empty())
    return NULL;
  return queue[0]; 
}

void ElegantQueue::push( Job* &q_entry )
{

  unsigned int pos = queue.size();             //position of newly inserted item
  if (q_param == "UQ"){
    q_entry->urgent_hook  = pos;
    q_entry->priority_ptr = this;
  }
  else if (q_param == "TQ"){
    q_entry->time_hook  = pos;
    q_entry->time_ptr = this;
  }
  queue.push_back(q_entry);
  PercolateUp(pos);

}


// for UQ, job with highest priority to bubble up to root [max-heap]
// for TQ, job with lowest timestamp to bubble up to root [min-heap]
// percolate up process
// Compare the added entry with its parent 
// for UQ, if parent < added entry, swap the added entry with the parent. 
// for TQ, if parent > added entry, swap the added entry with the parent. 
// check for heap and repeat
// step 1:  the index of the parent for this last added element is at (n/2)
// step 2:  since this is a non-heap, swap value at (n/2) with value at n, if needed
// step 3:  check for heap. if good, return else set n--; loop to step 1, until n=1
void ElegantQueue::PercolateUp(const unsigned int &pos){
  unsigned int loc = pos+1;
  while (loc >= 1){

    unsigned int parent = loc/2;

    if (parent < 1) 
      return;                // return if parent index goes out of range
    
    // if valid heap, return
    if (check_heap())
      return;
    
    if (q_param == "UQ"){
      if (queue[loc-1]->priority > queue[parent-1]->priority){
        //swap values between parent and current loc
        // Job* temp = queue[parent-1];
        // queue[parent-1] = queue[loc-1];
        // queue[loc-1] = temp;
        std::swap(queue[loc-1], queue[parent-1]);
        // change urgent_hook for the jobs in parent and loc
        queue[loc-1]->urgent_hook    = loc-1;
        queue[parent-1]->urgent_hook = parent-1;
        // if valid heap after swap, return gracefully
        
        if (check_heap())
          return;

      }
    }
    else if (q_param == "TQ"){
      if (queue[loc-1]->timestamp < queue[parent-1]->timestamp){
        //swap values between parent and current loc
        // Job* temp = queue[parent-1];
        // queue[parent-1] = queue[loc-1];
        // queue[loc-1] = temp;
        std::swap(queue[loc-1], queue[parent-1]);
        // change time_hook for the jobs in parent and loc
        queue[loc-1]->time_hook    = loc-1;
        queue[parent-1]->time_hook = parent-1;
        // if valid heap after swap, return gracefully
        
        if (check_heap())
          return;
      }
    }
    loc--;
  }
}

Job* ElegantQueue::pop(){
 if (queue.empty())
    return NULL;

    // this job at root needs to be removed
    // save it so we can pass it back, and remove it from time queue
    // then, just call remove_from_index, with pos = 0
  Job* first_in_queue = queue[0];    
  remove_from_index(0);
  return first_in_queue;  
}

void ElegantQueue::remove_from_index(const eq_hook &pos){
  if (queue.empty())
    return;

  Job* last = queue.back();
  queue[pos] = last;
  queue.pop_back();
  PercolateDown(pos);
}

// for UQ job with highest priority should percolate to valid position [max-heap]
// for TQ job with lowest timestamp should percolate to valid position [min-heap]
// percolate down process
// 1. for UQ select largest child of node, based on priority
// 2. for TQ select smallest child of node, based on timestamp
// 2. Swap node with its selected child
// 3. Repeat steps 3 & 4 until no swaps needed
void ElegantQueue::PercolateDown(const unsigned int &pos){
  unsigned int loc  = pos+1;
  unsigned int imax = queue.size();
  while (loc <= imax){
    unsigned int left  = loc*2;
    unsigned int right = loc*2 + 1;
    if (right > imax )                        // if right is going out of bounds
      right = left;                        // set left (the one less) and right to be the same
    unsigned int swap = 0;
    if (right <= imax){

      if (q_param == "UQ"){
        if (queue[left-1]->priority > queue[right-1]->priority)    // check if left child > right child
          swap = left;                                                    // if so, largest child is left
        else
          swap = right; 
          // at this point, we now know what to swap with [the largest child]
        if (queue[swap-1]->priority > queue[loc-1]->priority){
          // Job* temp = queue[loc-1];
          // queue[loc-1] = queue[swap-1];
          // queue[swap-1] = temp;
          std::swap(queue[swap-1], queue[loc-1]);
          // change urgent_hook for the jobs in swap and loc
          queue[loc-1]->urgent_hook  = loc-1;
          queue[swap-1]->urgent_hook = swap-1;
          loc = swap;    
        } 
      }  

      else if (q_param == "TQ"){
        if (queue[left-1]->timestamp < queue[right-1]->timestamp)    // check if left child > right child
          swap = left;                                                    // if so, largest child is left
        else
          swap = right;
          // at this point, we now know what to swap with [the largest child]
        if (queue[swap-1]->timestamp < queue[loc-1]->timestamp){
          // Job* temp = queue[loc-1];
          // queue[loc-1] = queue[swap-1];
          // queue[swap-1] = temp;
          std::swap(queue[swap-1], queue[loc-1]);
          // change time_hook for the jobs in swap and loc
          queue[loc-1]->time_hook  = loc-1;
          queue[swap-1]->time_hook = swap-1;
          loc = swap; 
        }                           
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
// for UQ, do a max heap check [every node should be >= its child nodes]
// for TQ, do a min heap check [every node should be <= its child nodes]
// Returns true if queue represents a heap
// Start from root and go till the last node 
bool ElegantQueue::check_heap(){
  unsigned int n = queue.size();                   // size of our priority queue
  for (unsigned int i = 1; i <= n; i++) { 
    if (q_param == "UQ"){
      if    ( ((2*i -1 < n) && queue[2*i -1]->priority > queue[i-1]->priority) ||
            (2*i < n && queue[2*i]->priority > queue[i-1]->priority) )
        return false;
    }
    else if (q_param == "TQ"){
      if    ( ((2*i -1 < n) && queue[2*i -1]->timestamp < queue[i-1]->timestamp) ||
            (2*i < n && queue[2*i]->timestamp < queue[i-1]->timestamp) )
        return false; 
    }
  } 
  return true; 
}

void ElegantQueue::printHeap(std::ofstream &outfile){
  outfile << q_param << " " << queue.size() << " jobs:" << std::endl;
  for (unsigned int i=0; i< queue.size(); i++)
    outfile << "\t" << queue[i];
}
