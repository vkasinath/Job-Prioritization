#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <fstream>

typedef unsigned int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{

//////////FILL THIS IN///////////
public:
	void push(Job* &q_entry);
	Job* pop();
	void remove_from_index(const uq_hook &pos); 
	bool check_heap();
	Job* top();
	void printHeap(std::ofstream &outfile);

private:
	std::vector<Job*> prio_queue;
	void PercolateUp(const unsigned int &pos);
	void PercolateDown(const unsigned int &pos);

};

#endif
