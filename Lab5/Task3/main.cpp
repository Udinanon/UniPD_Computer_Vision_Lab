#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;



int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need it
    Mat img = imread("/home/udinanon/C++/Lab5/Task3/robocup.jpg");
    
    cout << img.channels() << endl;
    // show image 
    namedWindow("Original");
    imshow("Original", img);



    //string path_edit = "/home/udinanon/C++/Lab4/Task4/street_scene_circle.jpg";
    //imwrite(path_edit, params.clone_image);
    return 0;
}
