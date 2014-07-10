/*
 * @file global.h
 * @brief 打印等的定义
 *
 * @version 1.0.1
 * @date 2014-07-08
 * @author zhangshy
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>

#define dePrintf(X,...)	printf("[%s %s: %d]" X, __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define CLEAR(x) memset(&(x), 0, sizeof(x))


#endif /* GLOBAL_H_ */
