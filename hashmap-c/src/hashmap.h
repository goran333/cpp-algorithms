/*!
 * \file     hashmap.h
 * \brief    Hashmap public APIs
 * \author   Pawan Lakshmanan
 * \date     May 09, 2013
 */

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#pragma once

#ifndef HASHMAP_H_
#define HASHMAP_H_

#define KEY_SIZE (32) //max size of hash key (including NULL terminator)
typedef struct hashmap_x_ hashmap_x; //opaque handle to the hashmap

/*!
 * \brief         Create the hashmap
 * \param[in]     max_size - max number of elements that hashmap will hold
 *
 * \return        Returns ptr to hashmap on success, NULL on failure.
 */
hashmap_x* hashmap_create(int max_size);

/*!
 * \brief         Destroy a previously created hashmap
 * \param[in]     hm - hashmap handle
 *
 * \return        Returns 0 on success, negative number on failure.
 */
int hashmap_destroy(hashmap_x* hm);

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
                   int value);

/*!
 * \brief         Delete an existing element from the hashmap
 * \param[in]     hm - hashmap handle
 * \param[in]     key - key in string format (MUST be NULL-terminated)
 *
 * \return        Returns 0 on success, negative number on failure.
 */
int hashmap_delete(const hashmap_x* hm,
                   const char* key);

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
                 int *value);

#endif //HASHMAP_H_

#ifdef __cplusplus
}
#endif //__cplusplus
