#include <vector>
#include <ctime>

#include "Job.h"
#include "TimeQueue.h"

/* ******************************************************************
    GENERAL COMMENTS FOR TimeQueue FUNCTIONS
   Assume the array/vector is 1-based, instead of 0-based].
   when coding, will just do a -1 [just easier to understand & track]
   In a heap - Consider k-th element of the vector, the 
   the left child of the k-th element is located at 2*k index
   the right child of the k-th element is located at 2*k +1 index
   the parent is located at (k/2) index 
   ******************************************************************
*/


Job* TimeQueue::top(){
  if (time_queue.empty())
    return NULL;
  return time_queue[0]; 
}

void TimeQueue::push( Job* &q_entry )
{

  unsigned int pos = time_queue.size();             //position of newly inserted item
  q_entry->time_hook  = pos;
  q_entry->time_ptr = this;
  time_queue.push_back(q_entry);
  PercolateUp(pos);

}

// this requires job with oldest (smallest) timestamp bubble up to root
// so we use the "min-heap" strategy [all child will be > its parent] - what was done in lab/lec
// the most recent job will be at the bottom, oldest job will be at the top
// percolate up process
// Compare the added entry with its parent 
// if parent > added entry, swap the added entry with the parent. 
// The comparison is repeated until the parent is less than or equal to the percolating entry
// step 1:  the index of the parent for this last added element is at (n/2)
// step 2:  since this is a non-heap, swap value at (n/2) with value at n, if needed
// step 4:  check for heap. if good, return else set n--; loop to step 1, until n=1
void TimeQueue::PercolateUp(const unsigned int &pos){
  unsigned int loc = pos+1;
  while (loc >= 1){

    unsigned int parent = loc/2;

    if (parent < 1) 
      return;                // return if parent index goes out of range
    
    // if valid heap, return
    if (check_heap())
      return;
    
    if (time_queue[loc-1]->timestamp < time_queue[parent-1]->timestamp){
      //swap values between parent and current loc
      std::swap(time_queue[loc-1], time_queue[parent-1]);
      // change time_hook for the jobs in parent and loc
      time_queue[loc-1]->time_hook    = loc-1;
      time_queue[parent-1]->time_hook = parent-1;
      // if valid heap after swap, return gracefully
      
      if (check_heap())
        return;

    }

    loc--;
  }
}

Job* TimeQueue::pop(){
 if (time_queue.empty())
    return NULL;

    // this job at root needs to be removed
    // save it so we can pass it back, and remove it from time queue
    // then, just call remove_from_index, with pos = 0
  Job* first_in_queue = time_queue[0];    
  remove_from_index(0);
  return first_in_queue;  
}

void TimeQueue::remove_from_index(const uq_hook &pos){
  if (time_queue.empty())
    return;

  Job* last = time_queue.back();
  time_queue[pos] = last;
  time_queue.pop_back();
  PercolateDown(pos);
}

// this requires job with oldest (smallest) timestamp bubble up to root
// so we use the "min-heap" strategy [all child will be > its parent] - what was done in lab
// the most recent job will be at the bottom, oldest job will be at the top
//percolate down process
// 1. with node, find smallest child of node
// 2. Swap node with its smallest child, if node-value > smallest_child-value
// 3. Repeat steps 3 & 4 until no swaps needed.
void TimeQueue::PercolateDown(const unsigned int &pos){
  unsigned int loc  = pos+1;
  unsigned int imax = time_queue.size();
  while (loc <= imax){
    unsigned int left  = loc*2;
    unsigned int right = loc*2 + 1;
    if (right > imax )                        // if right is going out of bounds
      right = left;                        // set left (the one less) and right to be the same
    unsigned int swap = 0;
    if (right <= imax){
      if (time_queue[left-1]->timestamp < time_queue[right-1]->timestamp)    // check if left child < right child
        swap = left;                                                    // if so, largest child is left
      else
        swap = right;                            
      // at this point, we now know what to swap with [the smallest child]
      if (time_queue[swap-1]->timestamp < time_queue[loc-1]->timestamp){
        std::swap(time_queue[swap-1], time_queue[loc-1]);
        // change time_hook for the jobs in swap and loc
        time_queue[loc-1]->time_hook  = loc-1;
        time_queue[swap-1]->time_hook = swap-1;
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
bool TimeQueue::check_heap(){
  // remember, we are doing a min heap for timestamp. 
  // so every node should be <= its child nodes
  // Returns true if time_queue represents a heap
  // Start from root and go till the last node 
  unsigned int n = time_queue.size();                   // size of our time queue
  for (unsigned int i = 1; i <= n; i++) { 
    if     ( ((2*i -1 < n) && time_queue[2*i -1]->timestamp < time_queue[i-1]->timestamp) ||
          (2*i < n && time_queue[2*i]->timestamp < time_queue[i-1]->timestamp) )
            return false; 
    } 
    return true; 
}

void TimeQueue::printHeap(std::ofstream &outfile){
  outfile << "TQ " << time_queue.size() << " jobs:" << std::endl;
  for (unsigned int i=0; i< time_queue.size(); i++)
    outfile << "\t" << time_queue[i];
}