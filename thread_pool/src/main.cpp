#include "ThreadPool.h"

int main()
{
   ThreadPool pool(10,  //no of threads
		   120, //total no of jobs
		   30); //max secs to sleep for each job
   pool.Simulate();

   return 0;
}
