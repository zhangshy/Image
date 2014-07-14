/**
 * @file process.cpp
 * @brief 帧数据处理
 * @date 2014-07-14
 * @version 1.0.1
 * @author zhangshy
 */

#include <pthread.h>
#include "global.h"
#include "process.h"
void* my_process_thread(void* arg) {
	/* 打印线程号 */
	dePrintf("Current thread id is %u\n", (unsigned)pthread_self());
}


