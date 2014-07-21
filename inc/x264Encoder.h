/*
 * x264Encoder.h
 *
 *  Created on: Jul 16, 2014
 *      Author: zsy
 */

#ifndef X264ENCODER_H_
#define X264ENCODER_H_
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief 初始化x264
 * @param width 宽
 * @param height 高
 * @param rate 帧率
 */
void init_x264(int width, int height, int rate);

/**
 * @brief 使用x264 编码h264
 */
void encode2h264(const void *p, int size);

void deinit_x264(void);

#ifdef __cplusplus
}
#endif
#endif /* X264ENCODER_H_ */
