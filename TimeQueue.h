#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <fstream>

typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{

//////////FILL THIS IN///////////
public:
	void push(Job* &q_entry);
	Job* pop();
	void remove_from_index(const tq_hook &pos); 
	bool check_heap();
	Job* top();
	void printHeap(std::ofstream &outfile);

private:
	std::vector<Job*> time_queue;
	void PercolateUp(const unsigned int &pos);
	void PercolateDown(const unsigned int &pos);


};

#endif
