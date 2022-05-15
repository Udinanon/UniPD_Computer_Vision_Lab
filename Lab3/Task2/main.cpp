

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mouse_call(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_FLAG_LBUTTON){
        Mat* image = (Mat *)userdata; // void pointer is cast to Mat type
        Vec3b triplet = image->at<Vec3b>(y, x); // vaue is extracted
        // output is pushed out
        cout << "Left click has been made, Position:(" << x << "," << y << ")" << endl;
        cout << "Triplet of value:" << triplet << endl;
    }

}

int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need it
    Mat img = imread("/home/udinanon/C++/Lab3/Task1/robocup.jpg");
    
    cout << img.channels() << endl;
    // show image 
    namedWindow("Original");
    imshow("Original", img);
    setMouseCallback("Original", mouse_call, &img); // setting the mouse callback for selecting the region with mouse

    waitKey(0);
    return 0;
}
