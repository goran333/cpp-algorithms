/*!
 * \file     main.c
 * \brief    Framework to test the string to integer conversion API
 * \author   Pawan Lakshmanan
 * \date     June 16, 2013
 */

#include "my_atoi.h"
#include <stdio.h>

//define a test data structure 
typedef struct test_data_x_
{
   const char *input;
   int expected_output;
}test_data_x;

//list of sample test inputs and expected outputs
static const test_data_x tests[] =
{
   {"0", 0},
   {NULL, MY_ATOI_FAILURE},
   {"", MY_ATOI_FAILURE},
   {"-", MY_ATOI_FAILURE},
   {"1", 1},
   {"-1", -1},
   {"123", 123},
   {"-123", -123},
   {"a123", MY_ATOI_FAILURE},
   {"123a", MY_ATOI_FAILURE},
   {"000123", 123},
   {"12300", 12300},
   {"abc", MY_ATOI_FAILURE},
   {"0x123", MY_ATOI_FAILURE},
};
static const size_t total_tests = sizeof(tests)/sizeof(tests[0]);

int main()
{
   size_t i = 0;
   int output = 0;
   int failed_cnt = 0;

   for(i = 0; i < total_tests; i++)
   {
      printf("Running test %d of %d\n"
	     "Input [%s], Expected output [%d] ...\n",
	     i + 1, total_tests,
	     (NULL == tests[i].input)? "NULL": tests[i].input,
	     tests[i].expected_output);
      
      output = my_atoi(tests[i].input);
      if(output != tests[i].expected_output)
      {
	 printf("ERROR Expected [%d], Got [%d]!\n", 
		tests[i].expected_output, output);
	 failed_cnt++;
      }
      else
      {
	 printf("Success\n");
      }
   }

   printf("\n\n--- Ran %d tests, %d OK, %d FAIL ---\n\n",
	  total_tests, (total_tests - failed_cnt), failed_cnt);

   return 0;
}
