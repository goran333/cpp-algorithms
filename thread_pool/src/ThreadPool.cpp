#include "ThreadPool.h"
 #include "WorkerThread.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
using namespace boost::posix_time;

void ThreadPool::_StopOldestValidThread()
{
   if(!_ThreadsMap.empty())
   {
      //first element is always the oldest thread
      ThreadMapType::iterator it = _ThreadsMap.begin();
      while(_ThreadsMap.end() != it)
      {
         if(it->second->GetJobsRemaining() > 1)
         {
            it->second->StopAfterCurrentJob();
            break;
         }
         ++it;
      }
   }
}

void ThreadPool::_CleanupThreadResources(const string& ThreadId)
{
   //TODO: find a more efficient way to lookup than O(N)
   if(!_ThreadsMap.empty())
   {
      ThreadMapType::iterator it = _ThreadsMap.begin();
      while(_ThreadsMap.end() != it)
      {
         if(ThreadId == it->second->GetId())
         {
            _LastCleanedThread = it->second;
            _ThreadsMap.erase(it);
            break;
         }
         ++it;
      }
   }
}

void ThreadPool::_ThreadDoneCb(const string& Id,
                               size_t JobsDone,
                               size_t NoOfJobs,
                               bool StoppedByUser)
{
   unique_lock<mutex> lock(_ThreadLock);

   cout << "*** COMPLETE *** Thread " << Id << ", completed "
        << JobsDone << " of " << NoOfJobs << " jobs, user stopped = " 
        << StoppedByUser << "\n";

   //cleanup resources associated with this thread
   _CleanupThreadResources(Id);

   if(true == StoppedByUser)
   {
      //need to distribute remaning jobs on 2 new threads
      _DistributeWork(NoOfJobs - JobsDone, 2);
   }
   else
   {
      //thread completed all its jobs, stop oldest thread which has pending jobs
      _StopOldestValidThread();
   }

   //Are all the jobs completed?
   _JobsDone += JobsDone;
   if(_JobsDone >= _TotalJobs)
   {
      cout << "ALL DONE: Completed jobs " << _JobsDone << " of " << _TotalJobs << "\n";
      _DoneBarrier.wait();
   }
}

void ThreadPool::_CreateThread(const string& ThreadId,
                               size_t NoOfJobs)
{
   //store the created thread with its creation time as key so that 
   //oldest threads are always on top of the map
   _ThreadsMap.insert(make_pair(microsec_clock::universal_time(),
                                new WorkerThread(ThreadId, NoOfJobs, _MaxSecs, 
                                                 bind(&ThreadPool::_ThreadDoneCb, this, _1, _2, _3, _4))));
}

void ThreadPool::_DistributeWork(size_t TotalJobs,
                                 size_t NoOfThreads)

{
   static size_t _ThreadIdSeed = 1; //monotonically increasing thread ids
 
   size_t NoOfJobsPerThread = 0;
   size_t Remainder = 0;

   if((0 == TotalJobs) || (0 == NoOfThreads))
   {
      //nothing to do
      return;
   }
   else if(1 == NoOfThreads)
   {
      //schedule all jobs on 1 thread
      NoOfJobsPerThread = TotalJobs;
   }
   else if(TotalJobs <= NoOfThreads)
   {
      //schedule 1 job per thread and create minimal number of threads
      NoOfJobsPerThread = 1;
      NoOfThreads = TotalJobs;
   }
   else
   {
      //"normal" case, figure out no of jobs per thread
      Remainder = TotalJobs % NoOfThreads;
      NoOfJobsPerThread = TotalJobs/NoOfThreads;
   }

   //schedule perfectly divisible jobs on n-1 threads
   size_t i = 0;
   for(i = 0; i < NoOfThreads - 1; ++i)
   {
      _CreateThread(lexical_cast<string>(_ThreadIdSeed + i), NoOfJobsPerThread);
   }

   //schedule remaining jobs on last thread
   _CreateThread(lexical_cast<string>(_ThreadIdSeed + i), NoOfJobsPerThread + Remainder);

   //increment counter to guarantee a unique thread id on next call
   _ThreadIdSeed += NoOfThreads;
}

void ThreadPool::DoWork()
{
   //initialize seed
   srand(time(0));

   //distribute work among threads
   _DistributeWork(_TotalJobs, _NoOfThreads);

   //wait for all work to be completed 
   _DoneBarrier.wait();

   //wait for last thread to finish
   _LastCleanedThread->Join();
}
