/*!
 * \file     Job.h
 * \brief    Simple job implementation that uses random sleep to simulate work.
 * \author   Pawan Lakshmanan
 * \date     June 19, 2013
 */

#pragma once

#include <cstdlib>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class Job
{
public:
   /*!
    * \brief   Constructor
    */
   Job(const std::string& JobId, unsigned int MaxSecsToSleep):_JobId(JobId)
   {
      //TODO: for C++11 use new APIs from <random>
      _SecsToSleep = (std::rand() % MaxSecsToSleep) + 1;
   }

   /*!
    * \brief   Do the work (simulated using random sleep).
    */
   void DoWork() const
   {
      std::cout << "Job " << _JobId << " will take " << _SecsToSleep << " secs ...\n";
      boost::this_thread::sleep(boost::posix_time::seconds(_SecsToSleep));
      std::cout << "Job " << _JobId << " completed!\n";
   }

private:
   const std::string _JobId;
   unsigned int _SecsToSleep;
};
