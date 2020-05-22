HOMEWORK 10: JOB PRIORITIZATION


NAME:  Vishaal Kasinath


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.
Online resources should have specific URLs

http://users.cms.caltech.edu/~donnie/cs11/cpp/lab5/index.html
Lab Exercise 11 priority_queue.h
Lab11_post.pdf

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  16


EXTRA CREDIT
As described in the hw.pdf create a new ElegantQueue that can function as a TimeQueue or
as an UrgentQueue. Describe the changes you had to make to main/Job, and how your ElegantQueue
supports both getting the highest urgency Job and getting the earliest Job.

The basic idea was to use an "identifier" - that indicates the "type of queue."
I choose to have this identifier (string q_param) as one of the attributes of the ElegantQueue class
All subsequent code required minor modifications to use an if-then-else clause based on value of q_param
To minimize code changes - I used typedefs of UrgentQueue and TimeQueue as alias for ElegantQueue

ElegantQueue highlights (ElegantQueue.h):
1. Created a new class ElegantQueue (Declaration ElegantQueue.h, Implemenation ElegantQueue.cpp)
2. Added a typedef int eq_hook - that was used for managing the position of the job in the ElegantQueue
3. Added attribute (q_param) => that was used to identify the "type of queue."
   valid values will be (for this homework): "UQ" for priority queue and "TQ" for time queue
   
Elegant Queue highlights (ElegantQueue.cpp):
1. Merged class functions for both types of queues (priority/UQ and time/TQ)
2. For push function, added an if-then-class depending on value of q_param
3. printHeap was modified to use q_param instead of hardcoded values of "UQ" and "TQ" in output
4. PercolateUp uses an if-then-else depending on queue value of q_param
   if q_param = UQ, percolate up for max-heap based on priority
   if q_param = TQ, percolate up for min-heap based on timestamp
5. PercolateDown uses an if-then-else depending on queue value of q_param
   if q_param = UQ, percolate up for max-heap based on priority
   if q_param = TQ, percolate up for min-heap based on timestamp
6. check_heap() uses an if-then-else depending on queue value of q_param
   if q_param = UQ, check for heap property based on priority
   if q_param = TQ, check for heap property based on timestamp
   
Changes to Job_extra.h:
1. Added 2 typedefs for ElegantQueue => UrgentQueue and TimeQueue. This way, changes to main_extra.cpp kept to a minimum
2. Job class attributes priority_ptr and time_ptr defined using the new typedef/alias UrgentQueue and TimeQueue
3. Job class attributes urgent_hook and time_hook defined using the new typedef/alias e_hook

Changes to Job_extra.cpp: 
1. Changed include to "Job_extra.h"
   
Changes to main_extra.cpp
1. Modified include section (removed UrgentQueue.h, TimeQueue.h, Job.h and added ElegantQueue.h, Job_extra.h)
2. UrgentQueue uq initialization modified to use ElegantQueue constructor with q_param = "UQ"
3. TimeQueue tq   initialization modified to use ElegantQueue constructor with q_param = "TQ"


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


