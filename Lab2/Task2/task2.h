#ifndef task2
#define task2

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>


cv::Mat MaxFilter(cv::Mat in_mat, int kernel_size);

cv::Mat MinFilter(cv::Mat in_mat, int kernel_size);

#endif