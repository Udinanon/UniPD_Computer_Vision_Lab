/* ## Task 5
Expand Task 4 by creating a new image whose pixels are:
● equal to the input image if the corresponding pixel in the mask is black;
● equal to a given color otherwise.
Choose the triplet (92, 37, 201) as the new color. This image is generated from scratch at
every new click on the original image.
Are you able to change the color of the T-shirts?
Are you able to change the color of the ball?
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
    int threshold = 55; //15 was not enough
    Vec3b new_color = Vec3b(92, 37, 201);
     if (event == EVENT_FLAG_LBUTTON)
    {
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
        int b_value = b_values / n_values;
        int g_value = g_values / n_values;
        int r_value = r_values / n_values;

        cout << "Average values in 9x9 neighborhood is (b: " << b_value << ", g:" << g_value << ", r:" << r_value << ")" << endl;
        Vec3f reference = Vec3f(b_value, g_value, r_value);
        Mat output_image;
        image.copyTo(output_image);

        for (int i = 0; i < output_image.rows; i++)
        {
            for (int j = 0; j < output_image.cols; j++)
            {
                Vec3f diff = reference - Vec3f(image.at<Vec3b>(i, j));
                // unsigned ints don't have negatives, we need to use values that have them
                if (abs(diff[0]) < threshold && abs(diff[1]) < threshold && abs(diff[2]) < threshold ){
                    output_image.at<Vec3b>(i, j) = new_color;
                }
            }
        }
        namedWindow("Mask");
        imshow("Mask", output_image);
        string path_edit = "/home/udinanon/C++/Lab3/Task5/robocup_edited.jpg";
        imwrite(path_edit, output_image);
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
