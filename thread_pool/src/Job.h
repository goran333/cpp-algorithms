#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class Job
{
public:
   Job(const std::string& JobId, unsigned int MaxSecsToSleep):_JobId(JobId)
   {
      //TODO: for C++11 use new APIs from <random>
      _SecsToSleep = (std::rand() % MaxSecsToSleep) + 1;
   }

   void DoWork() const
   {
      std::cout << "Job " << _JobId << " will take " << _SecsToSleep << " secs ...\n";
      boost::this_thread::sleep(boost::posix_time::seconds(_SecsToSleep));
      std::cout << "Job " << _JobId << " completed!\n";
   }

private:
   unsigned int _SecsToSleep;
   std::string _JobId;
};
