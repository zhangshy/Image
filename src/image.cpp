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
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    /** 将图片信息读入Mat */
    Mat img = imread("test.jpg");
    if (!img.data) {
        cout << "No image data" << endl;
        return -1;
    }
    /** 显示图片 */
    imshow("test", img);
    /** 等待按键，关闭窗口 */
    waitKey(0);
    return 0;
}
