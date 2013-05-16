/*!
 * \file     main.c
 * \brief    Framework to test hashmap APIs
 * \author   Pawan Lakshmanan
 * \date     May 09, 2013
 */

#include "hashmap.h"
#include <stdio.h>

#define NO_OF_DAYS_IN_WEEK (7)
#define HASH_SIZE (256)

typedef struct hashmap_pair_x_
{
   char key[KEY_SIZE];
   int value;
}hashmap_pair_x;

static const hashmap_pair_x weekday_pairs[NO_OF_DAYS_IN_WEEK] = 
{
   {"Sunday", 0},
   {"Monday", 1},
   {"Tuesday", 2},
   {"Wednesday", 3},
   {"Thursday", 4},
   {"Friday", 5},
   {"Saturday", 6}
};

static int insert_test(hashmap_x* hm)
{
   if(NULL == hm)
   {
      printf("Null input arg(s), hm<%p>!\n", hm);
      return -1;
   }

   int i = 0;
   int ret = -1;

   for(i = 0; i < NO_OF_DAYS_IN_WEEK; i++)
   {
      ret = hashmap_insert(hm,
                           weekday_pairs[i].key,
                           weekday_pairs[i].value);
      if(0 != ret)
      {
         printf("Failed to insert <%s, %d>, ret %d!\n",
                weekday_pairs[i].key, weekday_pairs[i].value, ret);
         ret = -1;
         break; //from for loop
      }
      else
      {
         printf("Successfuly inserted - <%s, %d>\n",
                weekday_pairs[i].key, weekday_pairs[i].value);
      }
   }
   return ret;
}

static int read_test(hashmap_x* hm)
{
   if(NULL == hm)
   {
      printf("Null input arg(s), hm<%p>!", hm);
      return -1;
   }

   int i = 0;
   int ret = -1;
   int value = -1;

   //read known values
   for(i = 0; i < NO_OF_DAYS_IN_WEEK; i++)
   {
      value = -1;
      ret = hashmap_read(hm,
                         weekday_pairs[i].key,
                         &value);
      if((0 != ret) || (value != weekday_pairs[i].value))
      {
         printf("Failed to read <%s>, ret %d, expected %d, got %d!\n",
                weekday_pairs[i].key, ret, weekday_pairs[i].value, value);
         ret = -1;
         break; //from for loop
      }
      else
      {
         printf("Successfuly read - <%s, %d>\n",
                weekday_pairs[i].key, value);
      }
   }

   //read unknown value - should fail
   ret = hashmap_read(hm, "UnknownDay", &value);
   if(0 == ret)
   {
      printf("Expected read failure on %s, got success instead, value %d!\n",
             "UnknownDay", value);
      ret = -1;
   }

   return ret;
}

static int delete_test(hashmap_x* hm)
{
   if(NULL == hm)
   {
      printf("Null input arg(s), hm<%p>!\n", hm);
      return -1;
   }

   int i = 0;
   int ret = -1;

   //delete known values
   for(i = 0; i < NO_OF_DAYS_IN_WEEK; i++)
   {
      ret = hashmap_delete(hm,
                           weekday_pairs[i].key);
      if(0 != ret)
      {
         printf("Failed to delete <%s>, ret %d!\n",
                weekday_pairs[i].key, ret);
         ret = -1;
         break; //from for loop
      }
   }

   //delete unknown value - should fail
   ret = hashmap_delete(hm, "UnknownDay");
   if(0 == ret)
   {
      printf("Expected delete failure on %s, got success instead!\n",
             "UnknownDay");
      ret = -1;
   }

   return ret;
}

int main()
{
   int ret = -1;
   hashmap_x *hm = NULL; //ptr to hashmap

   hm = hashmap_create(HASH_SIZE);
   if(NULL != hm)
   {
      //run the test(s)
      ret = insert_test(hm);
      if(0 == ret)
      {
         (void)read_test(hm);
         (void)delete_test(hm);
      }
      (void)hashmap_destroy(hm);
      hm = NULL;
   }
   else
   {
      printf("Failed to create hashmap, ret <%p>!\n", hm);
   }

   return 0;
}
