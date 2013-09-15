#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>

#define START_MARK \
   boost::posix_time::ptime start(boost::posix_time::microsec_clock::local_time())
#define END_MARK \
   boost::posix_time::ptime end(boost::posix_time::microsec_clock::local_time()); \
   std::cout << __FUNCTION__ << " took " << (end - start).total_milliseconds() << " ms\n"

static const unsigned int N = 1000000; 

typedef struct CRecord
{
   CRecord(const size_t& a_offset,
	   const float& a_score)
      : m_offset(a_offset), m_score(a_score) {}
   CRecord(): m_offset(0), m_score(0) {}
   size_t m_offset;
   float m_score;
}CRecord;
typedef std::vector<CRecord> TRecordVec;

bool operator==(const CRecord &d1, const CRecord& d2)
{
   return ((d1.m_offset == d2.m_offset) && (d1.m_score == d2.m_score));
}

static inline bool RecCmp(const CRecord& a1,
			  const CRecord& a2)
{
   return (a1.m_offset < a2.m_offset);
}

static void InitList(TRecordVec& a_list,
		     const unsigned int a_n)
{
   START_MARK;
   std::cout << __FUNCTION__ << " initializing " << a_n << " elements ...\n";

   for (size_t i = 0; i < a_n; ++i)
   {
      a_list.push_back(CRecord(rand() % N,
			       rand() % N));
   }
   std::sort(a_list.begin(), a_list.end(), RecCmp);

   END_MARK;
}

static void SetUnionMorV1(const TRecordVec& a1,
			  const TRecordVec& a2,
			  TRecordVec& a)
{
   START_MARK;

   TRecordVec::const_iterator first1(a1.begin());
   TRecordVec::const_iterator last1(a1.end());
   TRecordVec::const_iterator first2(a2.begin());
   TRecordVec::const_iterator last2(a2.end());
   a.reserve(a1.size() + a2.size());

   while (true)
   {
      if (first1==last1)
      {
	 std::copy(first2,last2,std::back_inserter(a));
	 break;
      }
      if (first2==last2)
      {
	 std::copy(first1,last1,std::back_inserter(a));
	 break;
      }
      if (RecCmp(*first1, *first2)) { a.push_back(*first1); ++first1; }
      else if (RecCmp(*first2, *first1)) { a.push_back(*first2); ++first2; }
      else 
      {
	 //std::cout << "Records with offset " << (*first1).m_offset << " are same\n";
	 CRecord l_tmp(*first1);
	 l_tmp.m_score = (*first1).m_score + (*first2).m_score;
	 a.push_back(l_tmp);
	 ++first1;
	 ++first2;
      }
   }

   std::cout << "Result size " << a.size() << '\n';
   END_MARK;
}

static void SetUnionMorV2(const TRecordVec& a1,
			  const TRecordVec& a2,
			  TRecordVec& a)
{
   START_MARK;

   TRecordVec::const_iterator first1(a1.begin());
   TRecordVec::const_iterator last1(a1.end());
   TRecordVec::const_iterator first2(a2.begin());
   TRecordVec::const_iterator last2(a2.end());
   a.reserve(a1.size() + a2.size());

   while (true)
   {
      if (first1==last1)
      {
	 std::copy(first2,last2,std::back_inserter(a));
	 break;
      }
      if (first2==last2)
      {
	 std::copy(first1,last1,std::back_inserter(a));
	 break;
      }
      if (RecCmp(*first1, *first2))
      {
	 TRecordVec::const_iterator lower1(std::lower_bound(first1, last1, *first2, RecCmp));
	 std::copy(first1,lower1,std::back_inserter(a));
	 first1 = lower1;
      }
      else if (RecCmp(*first2, *first1))
      {
	 TRecordVec::const_iterator lower2(std::lower_bound(first2, last2, *first1, RecCmp));
	 std::copy(first2,lower2,std::back_inserter(a));
	 first2 = lower2;
      }
      else 
      {
	 //std::cout << "Records with offset " << (*first1).m_offset << " are same\n";
	 CRecord l_tmp(*first1);
	 l_tmp.m_score = (*first1).m_score + (*first2).m_score;
	 a.push_back(l_tmp);
	 ++first1;
	 ++first2;
      }
   }

   std::cout << "Result size " << a.size() << '\n';
   END_MARK;
}

int main(int argc, char **argv)
{
   unsigned int n = N;
   if (argc > 1)
      n = boost::lexical_cast<int>(argv[1]);

   TRecordVec l_list1, l_list2;
   //srand(time(NULL));
   InitList(l_list1, n);
   InitList(l_list2, n);

   TRecordVec l_result1, l_result2, l_result3;
   SetUnionMorV1(l_list1, l_list2, l_result1);
   SetUnionMorV2(l_list1, l_list2, l_result2);
   if (l_result1 != l_result2)
       std::cout << " Vectors are not equal!!!\n";

   //SetUnionMorV3(l_list1, l_list2, l_result3);

   return 0;
}
