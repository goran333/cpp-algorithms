#include <iostream>
#include <cassert>

using namespace std;

static bool isAnagram(string s1,
                      string s2)
{
   
   sort(s1.begin(), s1.end());
   sort(s2.begin(), s2.end());

   return (s1 == s2);
}

static bool isAnagramv2(const string s1,
                        const string s2)
{
   
}

int main()
{
   assert(true == isAnagram(string("pawan"), string("nawap")));
   assert(true == isAnagram(string("test"), string("test2")));
}
