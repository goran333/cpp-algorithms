#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/bind.hpp>
#include "ThreadPool.h"

using namespace std;
using namespace boost;


void ThreadPool::JobDoneCb(int Id, 
			   unsigned int JobsDone,
			   unsigned int NoOfJobs)
{
   //add io lock here
   cout << "Thread " << Id << ", completed "
	<< JobsDone << " of " << NoOfJobs << " jobs\n";
}

void ThreadPool::WorkerFn(int Id, 
			  int NoOfJobs)
{
   _Bar.wait();

   unsigned int count = 0;

   for(unsigned int i = 0; i < NoOfJobs; ++i)
   {
      Job(_MaxSecs).DoWork();
      ++count;
      JobDoneCb(Id, count, NoOfJobs);
   }
}

ThreadPool::ThreadPool(unsigned int NoOfThreads, 
		       unsigned int NoOfTotalJobs,
		       unsigned int MaxSecsPerJob):
   _TotalJobs(NoOfTotalJobs), 
xo   _MaxSecs(MaxSecsPerJob), 
   _JobsDone(0), 
   _Bar(NoOfThreads) 
{
   for(unsigned int i = 0; i < NoOfThreads; ++i)
   {
      thread(bind(&ThreadPool::WorkerFn, this, i));
   }
}

void ThreadPool::Simulate()
{
   
   
}
