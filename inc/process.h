/**
 * @file process.h
 * @brief 帧数据处理
 *
 * @date 2014-07-11
 * @version 1.0.1
 * @author: zhangshy
 */

#ifndef PROCESS_H_
#define PROCESS_H_


/**
 * @brief 帧数据处理线程
 */
void* my_process_thread(void* arg);

/**
 * @brief 将yuv422 yuyv的帧数据转化为rgb，并保存
 */
void yuv2rgb(const void *p, int size);


#endif /* PROCESS_H_ */
