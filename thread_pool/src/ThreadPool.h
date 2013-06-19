/*!
 * \file     ThreadPool.h
 * \brief    A thread pool which distributes jobs over multiple threads.
 * \author   Pawan Lakshmanan
 * \date     June 19, 2013
 */

#pragma once

#include <map>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/shared_ptr.hpp>
#include "WorkerThread.h"

class ThreadPool: private boost::noncopyable
{
public:
   /*!
    * \brief   Constructor
    */
   ThreadPool(size_t NoOfThreads, 
              size_t NoOfTotalJobs,
              size_t MaxSecsPerJob):
      _NoOfThreads(NoOfThreads),
      _TotalJobs(NoOfTotalJobs),
      _MaxSecs(MaxSecsPerJob),
      _JobsDone(0),
      _DoneBarrier(2) {}

   /*!
    * \brief   Start all threads and do the work (blocking call).
    */
   void DoWork();

private:
   size_t _NoOfThreads, _TotalJobs, _MaxSecs, _JobsDone;
   typedef std::map<boost::posix_time::ptime, boost::shared_ptr<WorkerThread> > ThreadMapType;
   ThreadMapType _ThreadsMap;
   boost::barrier _DoneBarrier;
   boost::mutex _ThreadLock;
   boost::shared_ptr<WorkerThread> _LastCleanedThread;

   /*!
    * \brief   Create multiple workers and divide TotalJobs among them.
    */
   void _DistributeWork(size_t TotalJobs,
                        size_t NoOfThreads);

   /*!
    * \brief   Create a single worker to complete the requested NoOfJobs.
    */
   void _CreateThread(const std::string& ThreadId,
                      const size_t NoOfJobs);

   /*!
    * \brief   Once a worker completes all its jobs, the following callback 
    *          should be invoked.
    */
   void _ThreadDoneCb(const std::string& Id,
                      size_t JobsDone,
                      size_t NoOfJobs,
                      bool StoppedByUser);
   /*!
    * \brief   Find the oldest thread which still has pending jobs on it and 
    *          request it to stop after current job.
    */
   void _StopOldestValidThread();

   /*!
    * \brief   Cleanup any local resources associated with the worker thread.
    */
   void _CleanupThreadResources(const std::string& ThreadId);
};
