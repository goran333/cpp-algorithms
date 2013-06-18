#include <assert.h>
#include <stdbool.h>
#include <string.h>

static bool is_palindrome(const char *str)
{
   if(NULL == str)
      return false;

   size_t i = 0;
   size_t len = strlen(str);
   size_t j = len - 1;

   for(i = 0; i < (len/2); i++)
   {
      if(str[i] != str[j])
	 return false;
      j--;
   }

   return true;
}

int main()
{
   assert(true == is_palindrome("pawap"));
   assert(true == is_palindrome(""));
   assert(true == is_palindrome("a"));
   assert(true != is_palindrome("pawan"));
   assert(true != is_palindrome(NULL));

   return 0;
}
