#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <fstream>
#include <string>

typedef unsigned int eq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class ElegantQueue{

//////////FILL THIS IN///////////
public:

    // constructor for elegant queue
    ElegantQueue(std::string q_param = "UQ") : q_param(q_param), queue({}) {}

	void push(Job* &q_entry);
	Job* pop();
	void remove_from_index(const eq_hook &pos); 
	bool check_heap();
	Job* top();
	void printHeap(std::ofstream &outfile);

private:
	std::string q_param;
	std::vector<Job*> queue;
	void PercolateUp(const unsigned int &pos);
	void PercolateDown(const unsigned int &pos);

};

#endif
