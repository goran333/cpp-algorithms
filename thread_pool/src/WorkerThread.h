/*!
 * \file     WorkerThread.h
 * \brief    A single worker thread which sequentially completes multiple jobs.
 * \author   Pawan Lakshmanan
 * \date     June 19, 2013
 */

#pragma once

#include <boost/thread.hpp>
#include <boost/function.hpp>

class WorkerThread
   
{
public:
   /*!
    * \brief   Define the fn type to be called when Worker is done.
    */
   typedef boost::function<void (const std::string&, size_t, size_t, bool)> ThreadCb;

   /*!
    * \brief   Constructor
    */
   WorkerThread(const std::string& ThreadId,
                size_t NoOfJobs,
                size_t MaxSecsPerJob,
                ThreadCb DoneCb);

   /*!
    * \brief   Get identifier.
    */
   const std::string& GetId() const
   {
      return _ThreadId;
   }

   /*!
    * \brief   Get no of jobs still pending on the Worker.
    */
   size_t GetJobsRemaining() const
   {
      return (_NoOfJobs - _JobsCompleted);
   }

   /*!
    * \brief   User request to stop Worker after completion of current job.
    */
   void StopAfterCurrentJob()
   {
      _StopRequested = true;
   }

   /*!
    * \brief   Join with the worker until it is done.
    */
   void Join();

private:
   const std::string _ThreadId;
   size_t _NoOfJobs, _JobsCompleted, _MaxSecsPerJob;
   bool _StopRequested;
   ThreadCb _DoneCb;
   boost::scoped_ptr<boost::thread> threadPtr;

   /*!
    * \brief   Actual worker function that processes all jobs.
    */
   void _WorkerFn();
};
