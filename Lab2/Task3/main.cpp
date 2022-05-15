/*Task 3
Expand Task 2 using the median filter and the gaussian smoothing filter provided by
OpenCV. Show the results.*/

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

#include "task3.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat img = imread("/home/udinanon/C++/Lab2/Task2/image_grayscale.jpg", IMREAD_GRAYSCALE);
    cout << img.channels() << endl;
    int filter_sizes[] = {3, 5, 11};

    for (int filter_size:filter_sizes){
        cout << "FILTER SIZE:" << filter_size << endl;
        string path_post = ".jpg";

        Mat img2 = MinFilter(img, filter_size);
        string path_pref_min = "/home/udinanon/C++/Lab2/Task3/image_grayscale_min_";
        string path_min = path_pref_min + to_string(filter_size) + path_post;
        imwrite(path_min, img2);

        Mat img3 = MaxFilter(img, filter_size);
        string path_pref_max = "/home/udinanon/C++/Lab2/Task3/image_grayscale_max_";
        string path_max = path_pref_max + to_string(filter_size) + path_post;
        imwrite(path_max, img3);

        Mat gauss_img;
        GaussianBlur(img, gauss_img, Size(filter_size, filter_size), 0);
        string path_pref_gauss = "/home/udinanon/C++/Lab2/Task3/image_grayscale_gauss_";
        string path_gauss = path_pref_gauss + to_string(filter_size) + path_post;
        imwrite(path_gauss, gauss_img);

        Mat med_img;
        medianBlur(img, med_img, filter_size);
        string path_pref_med = "/home/udinanon/C++/Lab2/Task3/image_grayscale_med_";
        string path_med = path_pref_med + to_string(filter_size) + path_post;
        imwrite(path_med, med_img);
    }
    return 0;
}
