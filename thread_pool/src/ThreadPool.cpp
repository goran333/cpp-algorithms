#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include "ThreadPool.h"
#include "Job.h"


using namespace std;
using namespace boost;
using namespace boost::posix_time;

void ThreadPool::JobDoneCb(const string& Id,
                           unsigned int JobsDone,
                           unsigned int NoOfJobs)
{
   boost::unique_lock<boost::mutex> lock(_JobLock);

   cout << "Thread " << Id << ", completed "
        << JobsDone << " of " << NoOfJobs << " jobs\n";

   _ThreadsJobDoneMap[this_thread::get_id()] = JobsDone;
   
   ++_JobsDone;
   if(_JobsDone == _TotalJobs)
   {
      cout << "All jobs done ...\n";
      _DoneBarrier.wait();
   }
}

void ThreadPool::ThreadInterruptedCb(const string& Id)
{
   unique_lock<mutex> lock(_ThreadInterruptedLock);

   cout << "Thread " << Id << " interrupted!\n";

   unsigned int JobsLeft = 1;

   if(JobsLeft > 1)
   {
      CreateThread(lexical_cast<string>(Id + ".1"), JobsLeft/2);
      CreateThread(lexical_cast<string>(Id + ".2"), JobsLeft/2 + (JobsLeft % 2));
   }
   else
   {
      CreateThread(lexical_cast<string>(Id + ".1"), JobsLeft);
   }
}

void ThreadPool::ThreadDoneCb(const string& Id,
                              unsigned int JobsDone,
                              unsigned int NoOfJobs)
{
   unique_lock<mutex> lock(_ThreadLock);

   cout << "*** COMPLETE *** Thread " << Id << ", completed "
        << JobsDone << " of " << NoOfJobs << " jobs\n";

   if(!_ThreadsMap.empty())
   {
      shared_ptr<thread> OldestThread = _ThreadsMap.begin()->second;
      if(this_thread::get_id() != OldestThread->get_id())
      {
         map<thread::id, unsigned int>::iterator it = _ThreadsJobDoneMap.find(OldestThread->get_id());
         if(_ThreadsJobDoneMap.end() != it)
         {
            if(it->second > 1)
            {
               OldestThread->interrupt();
               OldestThread->join();
            }
         }
      }
      _ThreadsMap.erase(_ThreadsMap.begin());
   }
}

void ThreadPool::WorkerFn(const string& ThreadId, 
                          unsigned int NoOfJobs)
{
   try
   {
      unsigned int count = 0;
      for(unsigned int i = 0; i < NoOfJobs; ++i)
      {
         const string JobId(ThreadId + "." + lexical_cast<string>(i));
         Job(JobId, _MaxSecs).DoWork();
         ++count;
         JobDoneCb(ThreadId, count, NoOfJobs);
      }
      ThreadDoneCb(ThreadId, count, NoOfJobs);
   }
   catch(boost::thread_interrupted const& )
   {
      ThreadInterruptedCb(ThreadId);
   }
}

void ThreadPool::CreateThread(const string& ThreadId,
                              const unsigned int NoOfJobs)
{
   _ThreadsMap.insert(make_pair(microsec_clock::universal_time(), 
                                new thread(bind(&ThreadPool::WorkerFn, this, ThreadId, NoOfJobs))));
}

void ThreadPool::DistributeWork()
{
   unsigned int Remainder = _TotalJobs % _NoOfThreads;
   unsigned int NoOfJobsPerThread = _TotalJobs/_NoOfThreads;

   if(0 == Remainder)
   {
      for(unsigned int i = 0; i < _NoOfThreads; ++i)
      {
         CreateThread(lexical_cast<string>(i), NoOfJobsPerThread);
      }
   }
   else
   {
      //todo: handle this case
   }
}

ThreadPool::ThreadPool(unsigned int NoOfThreads, 
                       unsigned int NoOfTotalJobs,
                       unsigned int MaxSecsPerJob):
   _NoOfThreads(NoOfThreads),
   _TotalJobs(NoOfTotalJobs),
   _MaxSecs(MaxSecsPerJob),
   _JobsDone(0),
   _DoneBarrier(2)
{
}

void ThreadPool::Simulate()
{
   srand(time(0)); //initialize seed
   DistributeWork();
   _DoneBarrier.wait();
}
