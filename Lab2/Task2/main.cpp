/* Task 1
Write a program that loads the image provided (image.jpg) and shows it. It then converts the
image to grayscale (cv::cvtColor() function) and saves it with the image_grayscale.jpg name.
Consider this last image for the next tasks  --- DONE 

 Task 2
Expand Task 1 implementing a max filter and a min filter in two dedicated functions
(implemented by you in a separate source file) that manipulate the pixels directly. Such
functions accept an integer representing the size of the kernel, and check that it is an odd
number. If it is even, the function does not process the image. Apply the filters using several
kernel sizes and find the best option that removes the electric cables in the background
without corrupting the image too much.

Task 3
Expand Task 2 using the median filter and the gaussian smoothing filter provided by
OpenCV. Show the results.

Task 4
Expand Task 1 plotting the histogram of the image using 256 bins and range [0, 255]. Try
also other values for the number of bins.

Task 5
Expand Task 4 including histogram equalization using the dedicated OpenCV function and
visualize the result. */

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

#include "task2.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat img = imread("/home/udinanon/C++/Lab2/Task2/image_grayscale.jpg", IMREAD_GRAYSCALE);
    cout << img.channels() << endl;
    // easier to manage multiple versions
    int filter_sizes[] = {3, 5, 7, 11, 13, 15, 21, 37};

    for (int filter_size:filter_sizes){
        cout << "FILTER SIZE:" << filter_size << endl;

        string path_post = ".jpg";

        Mat img2 = MinFilter(img, filter_size);
        string path_pref_min = "/home/udinanon/C++/Lab2/Task2/image_grayscale_min_";
        
        string path_min = path_pref_min + to_string(filter_size) + path_post_min;
        imwrite(path_min, img2);

        Mat img3 = MaxFilter(img, filter_size);
        string path_pref_max = "/home/udinanon/C++/Lab2/Task2/image_grayscale_max_";
        string path_post_max = ".jpg";
        string path_max = path_pref_max + to_string(filter_size) + path_post_max;
        imwrite(path_max, img3);
    }
    return 0;
}
