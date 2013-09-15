/*!
 * \file     Main.cpp
 * \brief    Framework to test the thread pool implementation.
 * \author   Pawan Lakshmanan
 * \date     June 19, 2013
 */

#include "ThreadPool.h"

int main()
{
   ThreadPool pool(5,   //no of threads
                   36,  //total no of jobs
                   15); //max randomized secs to sleep for each job
   pool.DoWork();

   return 0;
}
