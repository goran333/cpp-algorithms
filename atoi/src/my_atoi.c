/*!
 * \file     my_atoi.c
 * \brief    Implement a string to integer conversion API
 * \author   Pawan Lakshmanan
 * \date     June 16, 2013
 */

#include "my_atoi.h"
#include <stdio.h>

/*!
 * \brief         Check if given character is '-'
 * \param[in]     c - input character
 *
 * \return        Returns 1 if character is '-', otherwise returns 0.
 */
static inline int is_negative(char c)
{
   return (('-' == c)? 1: 0);
}

/*!
 * \brief         Convert a single character to an integer
 * \param[in]     c - input character
 *
 * \return        Returns converted integer on success. On failure, returns < 0.
 */
static int convert_char(char c)
{
   int temp = c - '0';
   if((temp >= 0) && (temp <= 9))
   {
      return temp;
   }
   else
   {
      return -1;
   }
}

/*!
 * \brief         Convert an input string to an integer
 * \param[in]     str - input string (MUST be NULL-terminated)
 *
 * \return        Returns #MY_ATOI_FAILURE on failure. On success, this 
 *                function returns the converted integer value.
 */
int my_atoi(const char *str)
{
   //check for valid input
   if(NULL == str)
   {
      return MY_ATOI_FAILURE;
   }

   //local variables 
   int i = 0;
   int multiplier = 1;
   int sum = 0;
   int converted_num = -1;
   int loop_entered = 0;

   //handle leading '-' character
   if(is_negative(str[0]))
   {
      multiplier = -1;
      i = 1; //point to next character
   }

   //loop till end of string
   while('\0' != str[i])
   {
      //set flag to indicate that 'sum' holds a usable return value
      loop_entered = 1;

      converted_num = convert_char(str[i]);
      if(converted_num < 0)
      {
	 sum = MY_ATOI_FAILURE;
	 break; //invalid characters, break out of the loop
      }
      else
      {
	 sum = (sum * 10) + converted_num;
      }
      i++;
   }

   return (loop_entered)? (sum * multiplier): MY_ATOI_FAILURE;
}
