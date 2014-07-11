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
 * 捕捉到的帧数据的处理回调函数
 */
typedef void (*process_image_callback_t) (const void *p, int size);

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
 * @brief 注册帧数据处理的回调函数
 * @param processImage 帧数据处理回调函数，为空时使用默认处理函数
 * @see process_image_callback_t
 */
void registerProcessImageCallback(process_image_callback_t processImage);

/**
 * @brief 捕捉图像
 * @param num 捕捉图像的帧数
 */
void captureLoop(int num);
#endif /* CAPTURE_H_ */
