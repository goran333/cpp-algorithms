#include "WorkerThread.h"
#include "Job.h"

using namespace std;
using namespace boost;

void WorkerThread::_WorkerFn()
{
   for(size_t i = 0; i < _NoOfJobs; ++i)
   {
      if(true == _StopRequested)
      {
         cout << "Thread " << _ThreadId << " stopping because of user request!\n";
         break;
      }
      const string JobId(_ThreadId + "." + lexical_cast<string>(i+1));
      Job(JobId, _MaxSecsPerJob).DoWork();
      ++_JobsCompleted;
   }

   cout << "Thread " << _ThreadId << " exiting, completed " 
        << _JobsCompleted << " of " << _NoOfJobs << " jobs.\n";

   if(!_DoneCb.empty())
   {
      _DoneCb(_ThreadId, _JobsCompleted, _NoOfJobs, _StopRequested);
   }
}

void WorkerThread::Join()
{
   if(NULL != threadPtr.get())
   {
      threadPtr->join();
   }
}

WorkerThread::WorkerThread(const std::string& ThreadId,
                           size_t NoOfJobs,
                           size_t MaxSecsPerJob,
                           ThreadCb DoneCb):
   _ThreadId(ThreadId),
   _NoOfJobs(NoOfJobs),
   _JobsCompleted(0),
   _MaxSecsPerJob(MaxSecsPerJob),
   _StopRequested(false),
   _DoneCb(DoneCb)
{
   threadPtr.reset(new thread(bind(&WorkerThread::_WorkerFn, this)));
}
