/*
 * @file capture.h
 *
 * @version 1.0.1
 * @author zhangshy
 * @date 2014-07-07
 */

#ifndef CAPTURE_H_
#define CAPTURE_H_

enum io_method {
	IO_METHOD_READ,
	IO_METHOD_MMAP,
	IO_METHOD_USERPTR,
};

struct buffer {
	void *start;
	size_t length;
};

/**
 * 输出错误信息，并exit
 */
void errno_exit(const char *s);

/**
 * @brief 打开摄像头设备
 *
 * 默认打开/dev/video0，模式为O_RDWR | O_NONBLOCK
 */
void openDevice(void);

void closeDevice(void);

void initDevice(void);

void uninitDevice(void);

void start_capturing(void);

void stop_capturing(void);

/**
 * @brief 捕捉图像
 * @param num 捕捉图像的帧数
 */
void captureLoop(int num);
#endif /* CAPTURE_H_ */
