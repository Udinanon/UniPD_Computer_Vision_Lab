#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/* TASK 1

Write a program that segments cracks in the asphalt. You can choose one of the segmentation techniques discussed in the course, or find a new one available in OpenCV. To assess the generality of your approach, test your algorithm on the three images provided - the two segments are: crack vs non-crack. Every pixel of the image shall belong to one of the two categories.*/

/* OUR APPROACH
region growing:
 - find darkest pixels (cracks are darker than teh rest of the image)
    - needs top be dynamic (?)
    - blur helps
 - erode to 1 point

 - use region growing like in slides
*/



int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need it
    Mat img = imread("/home/udinanon/C++/Lab5/Task1/Asphalt-1.png");
    
    cout << img.channels() << endl;
    // show image rho
    namedWindow("Original");
    imshow("Original", img);
    Mat gray_image;
    cvtColor(img, gray_image, COLOR_BGR2GRAY);
    GaussianBlur(gray_image, gray_image, Size(3, 3), 2, 2);
    namedWindow("Gray");
    imshow("Gray", gray_image);
    
    // prepare the histogram parameters
    int histSize = 32;
    cout << "Hist Size: " <<  histSize << endl;
    float range[] = {0, 32}; // the upper boundary is exclusive
    const float *histRange[] = {range};

    bool uniform = true, accumulate = false;
    Mat hist;
    // generate the histogram
    // i think he wants a copy ??
    calcHist(&gray_image, 1, 0, Mat(), hist, 1, &histSize, histRange, uniform, accumulate);
    
    normalize(hist, hist, 0, hist.rows, NORM_MINMAX, -1, Mat());
    // now generate tbhe ymage of the histogram
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, img.type(), Scalar(0, 0, 0));
    // and we fill it with our data
    for (int i = 1; i < histSize; i++)
    {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
        Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
        Scalar(255, 255, 255), 2, 8, 0);
    }
    namedWindow("Histogram");
    imshow("Histogram", histImage);
    

    Mat thresh;
    threshold(gray_image, thresh, 5, 255, THRESH_BINARY_INV);

    namedWindow("Threshold");
    imshow("Threshold", thresh);
    
    Mat dilated;
    dilate(thresh, dilated, Mat(), Point(-1, -1), 5);

    namedWindow("dilated");
    imshow("dilated", dilated);


    waitKey(0);


    //string path_edit = "/home/udinanon/C++/Lab4/Task4/street_scene_circle.jpg";
    //imwrite(path_edit, params.clone_image);
    return 0;
}
