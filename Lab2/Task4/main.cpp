/* Task 4
Expand Task 1 plotting the histogram of the image using 256 bins and range [0, 255]. Try
also other values for the number of bins.*/

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
    Mat img = imread("/home/udinanon/C++/Lab2/Task4/image_grayscale.jpg", IMREAD_GRAYSCALE);
    cout << img.channels() << endl;
    // prepare the histogram parameters
    int histSize = 32;
    cout << "Hist Size: " <<  histSize << endl;
    float range[] = {0, 32}; // the upper boundary is exclusive
    const float *histRange[] = {range};

    bool uniform = true, accumulate = false;
    Mat hist;
    // generate the histogram
    // i think he wants a copy ??
    calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, histRange, uniform, accumulate);
    
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

    // save histogram to disk
    string path_pref_hist = "/home/udinanon/C++/Lab2/Task4/image_grayscale_hist_";
    string path_post = ".jpg";
    string path_hist = path_pref_hist + to_string(histSize) + path_post;
    imwrite(path_hist, histImage);
    // to show images, i prefer to save them to disk
/*     imshow("Source image", img);
    imshow("calcHist Demo", histImage); */
    waitKey();

    return 0;
}
