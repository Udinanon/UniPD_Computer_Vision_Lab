
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdexcept>

#include "task3.h"

using namespace cv;
using namespace std;


Mat MaxFilter(Mat in_mat, int kernel_size){
    // check for inavlid inputs
    if (kernel_size % 2 == 0 && kernel_size > 1 ){
        throw std::invalid_argument("received even value");
    }
    // calculate lost border due to filter
    int pixel_lost;
    pixel_lost = (kernel_size-1)/2;
    // create output matrix accordingly
    Mat out_mat = Mat::zeros(in_mat.rows-(pixel_lost*2), in_mat.cols-(pixel_lost*2), in_mat.type());
    // loop over pixels to apply the filter
    for (int i = pixel_lost; i < in_mat.rows - pixel_lost; i++)
    {
        for (int j = pixel_lost; j < in_mat.cols - pixel_lost; j++)
        {
            // look at the surrounding pixels to look for the max
            for (int a = -pixel_lost; a < pixel_lost + 1; a++)
            {
                for (int b = -pixel_lost; b < pixel_lost + 1; b++)
                {
                    // we substitute the value in place
                    if (in_mat.at<uchar>(i + a, j + b) > out_mat.at<uchar>(i - pixel_lost, j - pixel_lost))
                    {
                        out_mat.at<uchar>(i - pixel_lost, j - pixel_lost) = in_mat.at<uchar>(i + a, j + b);
                    }
                }
            }

        }
    }
    return out_mat;
}

Mat MinFilter(Mat in_mat, int kernel_size)
{
    // check for inavlid inputs
    if (kernel_size % 2 == 0 && kernel_size > 1)
    {
        throw std::invalid_argument("received even value");
    }
    // calculate lost border due to filter
    int pixel_lost;
    pixel_lost = (kernel_size - 1) / 2;
    // create output matrix accordingly
    Mat out_mat(in_mat.rows - (pixel_lost * 2), in_mat.cols - (pixel_lost * 2), in_mat.type(), Scalar(255));

    // loop over pixels to apply the filter
    for (int i = pixel_lost; i < in_mat.rows - pixel_lost; i++)
    {
        for (int j = pixel_lost; j < in_mat.cols - pixel_lost; j++)
        {
            // look at the surrounding pixels to look for the max
            for (int a = -pixel_lost; a < pixel_lost + 1; a++)
            {
                for (int b = -pixel_lost; b < pixel_lost + 1; b++)
                {
                    // we substitute the value in place
                    if (in_mat.at<uchar>(i + a, j + b) < out_mat.at<uchar>(i - pixel_lost, j - pixel_lost))
                    {
                        out_mat.at<uchar>(i - pixel_lost, j - pixel_lost) = in_mat.at<uchar>(i + a, j + b);
                    }
                }
            }
        }
    }
    return out_mat;
}