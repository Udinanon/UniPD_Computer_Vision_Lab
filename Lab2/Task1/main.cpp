/* Task 1
Write a program that loads the image provided (image.jpg) and shows it. It then converts the
image to grayscale (cv::cvtColor() function) and saves it with the image_grayscale.jpg name.
Consider this last image for the next tasks  --- DONE */

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // Read image from disk
    // i can0t setup the path to be dynamic, where is os.getcwd() when you need it
    Mat img = imread("/home/udinanon/C++/Lab2/Task1/image.jpg");
    
    cout << img.channels() << endl;
    // show image 
    namedWindow("Original");
    imshow("Original", img); 
    waitKey(0);
    // create empty matrix and fill with converted image
    Mat bw_img;
    cvtColor(img, bw_img, cv::COLOR_BGR2GRAY);
    // save
    imwrite("/home/udinanon/C++/Lab2/Task1/image_grayscale.jpg", bw_img);
    return 0;
}
