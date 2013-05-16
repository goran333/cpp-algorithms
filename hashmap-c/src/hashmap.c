/*!
 * \file     hashmap.c
 * \brief    Implementation of the hashmap APIs (does NOT handle collisions).
 * \author   Pawan Lakshmanan
 * \date     May 09, 2013
 */

#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node_x_
{
   bool in_use;
   char key[KEY_SIZE];
   int value;
}node_x;

struct hashmap_x_
{
   int max_size;
   node_x *nodes;
};

/*!
 * \brief         Get an index into the array of nodes.
 * \param[in]     key - key in string format (MUST be NULL-terminated)
 * \param[in]     max_size - max number of elements that hashmap will hold
 *
 * \return        Returns valid index on success, negative number on failure.
 */
static int get_index(const char *key, 
                     int max_size)
{
   if((NULL == key) || (max_size <= 0))
   {
      printf("Bad input arg(s), key<%p> max_size<%d>!\n", 
             key, max_size);
      return -1;
   }

   unsigned long seed = 428; //my bday
   int i = 0;

   //NOTE: Very simple hashing fn, will not hold up for 
   //      production code (instead use something standard e.g. SHA-1)
   while('\0' != key[i])
   {
      seed = (i + 1) * (seed + key[i]); //TODO: check for overflow
      i++;
   }
   return (seed % max_size);
}

/*!
 * \brief         Perform a safe copy of data to a node
 * \param[in]     node - ptr to the node
 * \param[in]     key - key in string format (MUST be NULL-terminated)
 * \param[in]     value - value associated with the key
 *
 * \return        Returns valid index on success, negative number on failure.
 */
static int copy_to_node(node_x *node,
                        const char* key,
                        int value)
{
   if( (NULL == node) || (NULL == key))
   {
      printf("Bad input arg(s), node<%p> key<%p>!\n", 
             node, key);
      return -1;
   }

   int ret = -1;
   char temp[KEY_SIZE] = "";

   //store into temp key first
   strncpy(temp, key, sizeof(temp));
   temp[sizeof(temp) - 1] = '\0'; //null terminate

   //confirm that key was fully copied without truncation
   if(strlen(temp) != strlen(key))
   {
      printf("Key %s is too long, %d > max %d\n",
             key, strlen(key) + 1, sizeof(temp));
   }
   else
   {
      strncpy(node->key, temp, sizeof(node->key));
      node->key[sizeof(node->key) - 1] = '\0'; //null terminate
      node->value = value;
      node->in_use = true;
      ret = 0;
   }
   return ret;
}
                        
/*!
 * \brief         Create the hashmap
 * \param[in]     max_size - max number of elements that hashmap will hold
 *
 * \return        Returns ptr to hashmap on success, NULL on failure.
 */
hashmap_x* hashmap_create(int max_size)
{
   if(max_size <= 0)
   {
      printf("Bad input arg(s), max_size<%d>!\n", max_size);
      return NULL;
   }

   hashmap_x* hm = NULL;

   //allocate the control block
   hm = calloc(1, sizeof(hashmap_x));
   if(NULL == hm)
   {
      printf("Failed to calloc control block!\n");
   }
   else
   {
      //allocate the nodes
      hm->max_size = max_size;
      hm->nodes = calloc(max_size, sizeof(node_x));
      if(NULL == hm->nodes)
      {
         printf("Failed to calloc %d nodes!\n", max_size);
         free(hm);
         hm = NULL;
      }
   }
   return hm;
}

/*!
 * \brief         Destroy a previously created hashmap
 * \param[in]     hm - hashmap handle
 *
 * \return        Returns 0 on success, negative number on failure.
 */
int hashmap_destroy(hashmap_x* hm)
{
   if(NULL != hm)
   {
      if(NULL != hm->nodes)
      {
         free(hm->nodes);
         hm->nodes = NULL;
      }
      free(hm);
   }
   return 0;
}

/*!
 * \brief         Insert an element into the hashmap
 * \param[in]     hm - hashmap handle
 * \param[in]     key - key in string format (MUST be NULL-terminated)
 * \param[in]     value - value associated with the key
 *
 * \return        Returns 0 on success, negative number on failure.
 */
int hashmap_insert(hashmap_x* hm,
                   const char* key,
                   int value)
{
   if((NULL == hm) || (NULL == key))
   {
      printf("Bad input arg(s), hm<%p> key<%p>!\n", 
             hm, key);
      return -1;
   }

   int ret = -1;
   int index = -1;

   index = get_index(key, hm->max_size);
   if(index < 0)
   {
      printf("Failed to get index for key %s!\n", key);
   }
   else if(true == hm->nodes[index].in_use)
   {
      //TODO: This could be a collision ... handle it
      printf("Cannot insert, key %s already in use!\n", key);
   }
   else
   {
      ret = copy_to_node(&hm->nodes[index],
                         key,
                         value);
   }
   return ret;
}

/*!
 * \brief         Delete an existing element from the hashmap
 * \param[in]     hm - hashmap handle
 * \param[in]     key - key in string format (MUST be NULL-terminated)
 *
 * \return        Returns 0 on success, negative number on failure.
 */
int hashmap_delete(const hashmap_x* hm,
                   const char* key)
{
   if((NULL == hm) || (NULL == key))
   {
      printf("Bad input arg(s), hm<%p> key<%p>!\n", 
             hm, key);
      return -1;
   }

   int ret = -1;
   int index = -1;

   index = get_index(key, hm->max_size);
   if(index < 0)
   {
      printf("Failed to get index for key %s!\n", key);
   }
   else if(true != hm->nodes[index].in_use)
   {
      printf("Cannot delete, key %s is not in use!\n", key);
   }
   else
   {
      hm->nodes[index].in_use = false;
      //No need to clear key/value, they will be over-written on next write
      ret = 0;
   }
   return ret;
}

/*!
 * \brief         Read a value associated with a key in the hashmap
 * \param[in]     hm - hashmap handle
 * \param[in]     key - key in string format (MUST be NULL-terminated)
 * \param[out]    value - the read value will be stored here
 *
 * \return        Returns 0 on success, negative number on failure.
 */
int hashmap_read(const hashmap_x* hm,
                 const char* key,
                 int *value)
{
   if((NULL == hm) || (NULL == key) || (NULL == value))
   {
      printf("Null input arg(s), hm<%p> key<%p> value<%p>!\n", 
             hm, key, value);
      return -1;
   }

   int ret = -1;
   int index = -1;

   index = get_index(key, hm->max_size);
   if(index < 0)
   {
      printf("Failed to get index for key %s!\n", key);
   }
   else if(true != hm->nodes[index].in_use)
   {
      printf("Cannot read, key %s is not in use!\n", key);
   }
   else
   {
      //TODO: add a check here to confirm that the key
      //      in hashmap actually matches the provided key
      *value = hm->nodes[index].value;
      ret = 0;
   }
   return ret;
}
