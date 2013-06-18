#pragma once

#include <map>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/shared_ptr.hpp>

class ThreadPool: private boost::noncopyable
{
public:
   ThreadPool(unsigned int NoOfThreads, 
              unsigned int NoOfTotalJobs,
              unsigned int MaxSecsPerJob);
   void Simulate();

private:
   unsigned int _NoOfThreads;
   unsigned int _TotalJobs;
   unsigned int _MaxSecs;
   unsigned int _JobsDone;

   std::vector<boost::thread> _Threads;
   std::map<boost::thread::id, unsigned int> _ThreadsJobDoneMap;
   std::map<boost::posix_time::ptime, boost::shared_ptr<boost::thread> > _ThreadsMap;
   boost::barrier _DoneBarrier;
   boost::mutex _JobLock;
   boost::mutex _ThreadLock;
   boost::mutex _ThreadInterruptedLock;

   void JobDoneCb(const std::string& Id,
                  unsigned int JobsDone,
                  unsigned int NoOfJobs);
   void ThreadDoneCb(const std::string& Id,
                     unsigned int JobsDone,
                     unsigned int NoOfJobs);
   void ThreadInterruptedCb(const std::string& Id);
   void WorkerFn(const std::string& ThreadId, 
                 unsigned int NoOfJobs);
   void CreateThread(const std::string& ThreadId,
                     const unsigned int NoOfJobs);
   void DistributeWork();
};
