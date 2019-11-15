// JQueue: a job queue using a max-heap and function pointers
// Based on MQueue by Scott Bennett (sb13@umbc.edu)
// CMSC 341, Spring 2019

#include "JQueue.h"

//
// Priority functions compute an integer priority for a job.  Internal
// computations may be floating point, but must return an integer.
//
// Function definitions are below main()
//

int priorityFn1(const job_t &job);
int priorityFn2(const job_t &job);

int main() {

  // Create a job queue with capacity five and priority function
  // priorityFn1()

  JQueue jobQueue(-1, priorityFn1);

  // Create some test jobs and insert them into the queue
  
  job_t testJob1("test1", 50, 3, 11,  16, 1024, 120);
  job_t testJob2("test2", 50, 7,  5, 128,  512, 300);
  job_t testJob3("test3", 20, 3,  0, 128, 1024, 1800);
  job_t testJob4("test1a", 50, 3, 11,  16, 1024, 120);
  job_t testJob5("test1ab", 35, 7, 10,  19, 1050, 200);


  jobQueue.insertJob(testJob3);
  //jobQueue.dump();
  //std::cout << std::endl;
  jobQueue.insertJob(testJob1);
  //jobQueue.dump();
  //std::cout << std::endl;
  jobQueue.insertJob(testJob2);
  //jobQueue.dump();
  //std::cout << std::endl;
  jobQueue.insertJob(testJob4);
  //jobQueue.dump();
  //std::cout << std::endl;
  jobQueue.insertJob(testJob5);
  
  jobQueue.dump();
  // Print the queue, change priority function, print again, change
  // again, print again.  Changing the priority function should cause
  // the heap to be rebuilt.
  /*
  jobQueue.printJobQueue();
  
  jobQueue.setPriorityFn(priorityFn2);
  //jobQueue.dump();
  
  jobQueue.printJobQueue();

  jobQueue.setPriorityFn(priorityFn1);

  jobQueue.printJobQueue();
  */
  //Remove and print jobs in priority order
  //jobQueue.dump();

  //test copy constructor
  std::cout << "This is the copy" << std::endl;
  JQueue *jobQueue2 = new JQueue(jobQueue);
  jobQueue2->dump();

  //test assignment operator
  std::cout << "This is the assignment" << std::endl;
  JQueue Jb(5,priorityFn1);
  Jb = *jobQueue2;
  Jb.dump();

  
  delete jobQueue2;
  Jb.dump();
  std::cout << "This is the original" << std::endl;
  jobQueue.dump();
  /*
  std::cout << "\nFinal queue in priority order:\n";
  while (jobQueue.numJobs() > 0) {
    job_t job = jobQueue.getNextJob();
    std::cout << job << " (" << priorityFn1(job) << ")" << std::endl;
  }
  std::cout << std::endl;
  //jobQueue.dump();
  */
  return 0;
}

int priorityFn1(const job_t &job) {
  float pri;

  // 100 (regular user) + 100 (regular group) + job priority
  pri = 200 + job.m_priority;

  // If special user (7 or 23) add 200 
  if (job.m_user == 7 || job.m_user == 23) pri += 200;

  // If special group (0 or 11) add 100
  if (job.m_group == 0 || job.m_group == 11) pri += 100;

  // Subtract weighted proc, mem, and time
  //   1.0 * proc, 0.01 * mem, (1/3600) * time
  pri = pri - job.m_proc - 0.01*job.m_mem - (1.0/3600.0)*job.m_time;

  return int(pri);
}

int priorityFn2(const job_t&job) {
  return int(job.m_time);
}