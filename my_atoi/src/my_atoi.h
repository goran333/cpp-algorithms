/*!
 * \file     my_atoi.h
 * \brief    A simple string to integer conversion API
 * \author   Pawan Lakshmanan
 * \date     Jun 16, 2013
 */

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#pragma once

#ifndef MY_ATOI_H_
#define MY_ATOI_H_

#include <limits.h>

#define MY_ATOI_FAILURE (INT_MAX)

/*!
 * \brief         Convert an input string to an integer (string MUST be in 
 *                decimal format).
 * \param[in]     str - input string (MUST be NULL-terminated)
 *
 * \return        Returns #MY_ATOI_FAILURE on failure. On success, this 
 *                function returns the converted integer value.
 */
int my_atoi(const char *str);

#endif //MY_ATOI_H_

#ifdef __cplusplus
}
#endif //__cplusplus
