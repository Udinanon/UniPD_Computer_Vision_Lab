/* Modify the callback in Task 2: the new version calculates the mean of the B, G and R values
(separately) in a 9x9 neighborhood around the clicked pixel and prints such values.
*/

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mouse_call(int event, int x, int y, int flags, void* userdata)
{
    Mat image = *(Mat *)userdata; // void pointer is cast to Mat type and then converted to value
    if (event == EVENT_FLAG_LBUTTON){
        // position for debug
        cout << "Left click has been made, Position:(" << x << "," << y << ")" << endl;

        Vec3b triplet = image.at<Vec3b>(y, x); // vaue is extracted
        // output is pushed out
        cout << "Triplet of value:" << triplet << endl;

        int kernel_mov = 10; // (21-1)/2
        float b_values = 0;
        float g_values = 0;
        float r_values = 0;
        int n_values = 0;

        for (int a = x - kernel_mov; a < x + kernel_mov + 1; a++)
        {
            for (int b = y - kernel_mov; b < y + kernel_mov + 1; b++)
            {
                if (a > 0 && b > 0 && a < (image.cols) && b < (image.rows))
                {
                    //cout << "reading pixel color, Position:(" << a << "," << b << ")" << endl;
                    //segmentation fault for some reason, maybe try using image instead of pointer
                    Vec3b value = image.at<Vec3b>(b, a);
                    b_values += int(value[0]);
                    g_values += int(value[1]);
                    r_values += int(value[2]);
                    n_values +=1;
                }
            }
        }
        //cout << "cumulative values in 9x9 neighborhood is (b: " << b_values << ", g:" << g_values << ", r:" << r_values << ")" << endl;
        cout << "valid values read: " << n_values << endl;
        float b_value = b_values / n_values;
        float g_value = g_values / n_values;
        float r_value = r_values / n_values;

        cout << "Average values in 9x9 neighborhood is (b: " << b_value << ", g:" << g_value << ", r:" << r_value << ")" << endl;
    }

}

int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need it
    Mat img = imread("/home/udinanon/C++/Lab3/Task1/robocup.jpg");
    
    cout << img.channels() << endl;
    cout << img.type() << endl;

    // show image 
    namedWindow("Original");
    imshow("Original", img);
    setMouseCallback("Original", mouse_call, &img); // setting the mouse callback for selecting the region with mouse

    waitKey(0);
    return 0;
}
