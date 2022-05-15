#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;

/*
Task 4
    Edit the software in Task 2 by adding a function that checks if the number of channels of the
    input image is 3. If so, it sets to 0 the first channel and visualizes the image. Which color is
    missing? Try other versions that set to 0 the second or the third channel. Which color is
    missing in such cases? What is the color coding used by OpenCV?
*/

// It seems to be a for of BGR, instad of RGB

int main(int argc, char **argv){
    Mat img = imread("/home/udinanon/C++/Lab1/Lena_color.jpg");
    namedWindow("Original");
    imshow("Original", img);
    /*
    int n_dims = img.channels();
    std::cout << n_dims << std::endl;
    Mat channels[3];
    if (n_dims == 3){
        split(img, channels);
        namedWindow("R");
        imshow("R", channels[2]);
        namedWindow("G");
        imshow("G", channels[1]);
        namedWindow("B");
        imshow("B", channels[0]);
    }*/
    namedWindow("Rotated");
    int rotation = 57;
    int Height = img.rows / 2;             // getting middle point of rows//
    int Width = img.cols / 2;              // getting middle point of height//
    Mat for_Rotation = getRotationMatrix2D(Point(Width, Height), (rotation - 180), 1); // affine transformation matrix for 2D rotation//
    Mat for_Rotated;                                                                   // declaring a matrix for rotated image
    warpAffine(img, for_Rotated, for_Rotation, img.size());                            // applying affine transformation//
    imshow("AfterRotation", for_Rotated);                                              // show rotated image//

    Point2f srcTri[3];
    srcTri[0] = Point2f(0.f, 0.f);
    srcTri[1] = Point2f(img.cols - 1.f, 0.f);
    srcTri[2] = Point2f(0.f, img.rows - 1.f);
    Point2f dstTri[3];
    dstTri[0] = Point2f(0.f, img.rows * 0.33f);
    dstTri[1] = Point2f(img.cols * 0.85f, img.rows * 0.25f);
    dstTri[2] = Point2f(img.cols * 0.15f, img.rows * 0.7f);

    Mat warp_mat = getAffineTransform(srcTri, dstTri);
    Mat warp_dst = Mat::zeros(img.rows, img.cols, img.type());
    warpAffine(img, warp_dst, warp_mat, warp_dst.size());
    namedWindow("Warped");
    imshow("Warped", warp_dst);

    waitKey(0);
    return 0;
}

