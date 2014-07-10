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
#include "capture.h"

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

/**
 * @brief 捕捉摄像头测试测试程序
 * @param num 捕捉的帧数
 */
static void captureTest(int num) {
	openDevice();
	initDevice();
	start_capturing();
	captureLoop(num);
	stop_capturing();
	uninitDevice();
	closeDevice();
	fprintf(stderr, "\n");
}
int main(int argc, char** argv) {
	String inputImagename = "test.jpg";
	bool change2Gray = false;
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
    /* 将图片信息读入Mat */
    Mat img = imread(inputImagename);
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
    captureTest(70);
    /* 等待按键，关闭窗口 */
    waitKey(0);
    return 0;
}
