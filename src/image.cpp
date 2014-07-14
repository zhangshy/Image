/**
 * @file image.cpp
 * @brief main函数
 *
 * 显示图像
 * @author zhangshy
 * @version 1.0.1
 * @date 2014-7-3
 */
#include "cv.h"
#include "highgui.h"
#include <getopt.h>             /* getopt_long() */
#include<pthread.h>
#include "capture.h"
#include "process.h"

using namespace cv;

/** 帮助显示 */
static void usage(FILE *fp, int argc, char** argv) {
	fprintf(fp,
			"Usage: %s [options]\n\n"
			"Version 1.0.1\n"
			"Options:\n"
			"-i | --image name	Input image name\n"
			"-h | --help		Print this message\n"
			"-g | --gray		Show gray image\n"
			"",
			argv[0]);
}

/** 命令行参数 */
static const char short_options[] = "i:hg";
static const struct option
long_options[] = {
		{"image",	required_argument,	NULL, 'i'},	///< 输入图像
		{"help",	no_argument,		NULL, 'h'},	///< 帮助
		{"gray",	no_argument,		NULL, 'g'},	///< 显示灰度图像
		{0, 0, 0, 0}
};

static FILE *yuvFd = NULL;
static Mat img;
static int imageIndex=0;
/** 将帧数据直接存入文件 */
static void save2File(const void *p, int size) {
	fwrite(p, size, 1, yuvFd);
}
/**
 * @breif 将yuv422 yuyv的帧数据转化为rgb，并保存
 */
static void yuv2rgb(const void *p, int size) {
	int rows = 480;	/// rows 横行数，高
	int cols = 640;	/// cols 竖列数，宽
	/** 初始化Mat 高480 宽640 ，高宽 格式：CV_8UC3 */
	img = Mat::zeros(rows, cols, CV_8UC3);
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
/**
 * @brief 捕捉摄像头测试测试程序
 * @param num 捕捉的帧数
 */
static void captureTest(int num) {
	openDevice();
	initDevice();
	yuvFd = fopen("test.yuv", "wa+");
#if 0
	registerProcessImageCallback(save2File);
#else
	registerProcessImageCallback(yuv2rgb);
#endif
	start_capturing();
	captureLoop(num);
	stop_capturing();
	uninitDevice();
	closeDevice();
	fclose(yuvFd);
	fprintf(stderr, "\n");
}
int main(int argc, char** argv) {
	String inputImagename = "test.jpg";
	bool change2Gray = false;
	pthread_t processThreadId;
	for (;;) {
		int idx;
		int c;
		/* 解析命令行参数选项 */
		c = getopt_long(argc, argv, short_options, long_options, &idx);
		if (-1==c)
			break;
		switch (c) {
		case 0:	/* getopt_long() flag */
			break;
		case 'i':
			inputImagename = optarg;
			break;
		case 'h':
			usage(stdout, argc, argv);
			exit(EXIT_SUCCESS);
			break;
		case 'g':
			change2Gray = true;
			break;
		}
	}
	/* 创建线程，编译时加-lpthread */
//	pthread_create(&processThreadId, NULL, my_process_thread, NULL);
#if 1
    captureTest(70);
#else
    /* 将图片信息读入Mat */
    img = imread(inputImagename);
#endif
#if 0
    if (!img.data) {
    	printf("No image data\n");
        return -1;
    }
    /* 显示图片 */
    imshow("src", img);
    if (change2Gray) {
        Mat gray;
        /* 灰度图像 */
        cvtColor(img, gray, CV_BGR2GRAY);
        imshow("gray", gray);
    }
    /* 等待按键，关闭窗口 */
    waitKey(0);
#endif
    return 0;
}
