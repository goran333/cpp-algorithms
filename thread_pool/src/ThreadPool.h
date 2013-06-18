#pragma once

#include "Job.h"

class ThreadPool: private boost::noncopyable
{
public:
   ThreadPool(unsigned int NoOfThreads, 
	      unsigned int NoOfTotalJobs,
	      unsigned int MaxSecsPerJob);
   void Simulate();

private:
   
   std::vector<boost::thread> _Threads;
   
};
