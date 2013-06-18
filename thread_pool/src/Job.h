#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class Job
{
public:
   Job(unsigned int MaxSecsToSleep)
   {
      //TODO: for C++11 use new APIs from <random>
      _SecsToSleep = (std::rand() % MaxSecsToSleep) + 1;
   }

   void DoWork() const
   {
      std::cout << "sleeping for " << _SecsToSleep << " secs\n";
      boost::this_thread::sleep(boost::posix_time::seconds(_SecsToSleep));
      std::cout << "Done sleeping\n";
   }

private:
   unsigned int _SecsToSleep;
};
