/**
 * @file process.cpp
 * @brief 帧数据处理
 * @date 2014-07-14
 * @version 1.0.1
 * @author zhangshy
 */

#include "cv.h"
#include "highgui.h"
#include <pthread.h>
#include "global.h"
#include "process.h"

using namespace cv;
static int imageIndex=0;

void* my_process_thread(void* arg) {
	/* 打印线程号 */
	dePrintf("Current thread id is %u\n", (unsigned)pthread_self());
}

void yuv2rgb(const void *p, int size) {
	int rows = 480;	/// rows 横行数，高
	int cols = 640;	/// cols 竖列数，宽
	/** 初始化Mat 高480 宽640 ，高宽 格式：CV_8UC3 */
	Mat img = Mat::zeros(rows, cols, CV_8UC3);
	char imageName[30];
	int i=0, j=0;
	int index = 0;
	int r, g, b;
	unsigned char y, u, v;
	/* 排列为yuyv */
	for (i=0; i<rows; i++) {
		for (j=0; j<cols; j++) {
			y = *(unsigned char*)(p+index);
			if (j&1) {
				/* 奇 */
				u = *(unsigned char*)(p+index-1);
				v = *(unsigned char*)(p+index+1);
			} else {
				/* 偶 */
				u = *(unsigned char*)(p+index+1);
				v = *(unsigned char*)(p+index+3);
			}
			index+=2;
#if 1
			r = y+(292*v>>8)-146;
			g = y-((100*u+148*v)>>8)+124;
			b = y+(520*u>>8)-260;
#else
			r = y+1.14*(v-128);
			g = y-0.39*(u-128)-0.58*(v-128);
			b = y+2.03*(u-128);
#endif
			Vec3b &bgrDst = img.at<Vec3b>(i, j);
			bgrDst[0] = b>255 ? 255 : (b<0 ? 0 : b);
			bgrDst[1] = g>255 ? 255 : (g<0 ? 0 : g);
			bgrDst[2] = r>255 ? 255 : (r<0 ? 0 : r);
		}
	}
	/** sprintf格式化字符串 */
	sprintf(imageName, "img/capture%d.jpg\0", imageIndex++);
	/* 将帧数据保存 */
	imwrite(imageName, img);
}

