#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <glob.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
    // Get CLI inputs
    string path;
    cout << "Path is expected to have a subfolder /checkerboard_images/ for calibration and a test_image.png for final testing" << endl;
    if (argc == 2)
    {
        cout << "Recongized path: " << argv[1] << endl;
        path = argv[1];
    }
    else
    {
        cout << "Expected usage: Lab8Task1 <input_path>" << endl;
        path = "/home/udinanon/C++/Computer Vision/Lab8/Task2/data/";
        cout << "using default path: " << path << endl;
    }
    //Prepare paths for images
    vector<String> filenames;
    glob(path + "checkerboard_images/*.png", filenames, false);
    //Prepare vectors for imagepoints, objectpoints, checkerboard size
    vector<Mat> images;
    Size grid_size = Size(5, 6);
    int CHECKERBOARD[2]{5, 6};
    std::vector<std::vector<cv::Point3f>> objpoints;
    std::vector<std::vector<cv::Point2f>> imgpoints;
    std::vector<cv::Point3f> objp;
    for (int i{0}; i < CHECKERBOARD[1]; i++)
    {
        for (int j{0}; j < CHECKERBOARD[0]; j++) 
        {
            objp.push_back(cv::Point3f(j, i, 0));
        }
    }

    // number of png files in images folder
    size_t count = filenames.size(); 
    cout << "Total images in subfolder" << count << endl;
    // Read images from disk and compyte the chessboard corners
    for (size_t i = 0; i < count; i++)
    {
        cout << filenames[i] << endl;
        Mat image = imread(filenames[i]);
        images.push_back(image);
        Mat grey;
        cvtColor(image, grey, COLOR_BGR2GRAY);
        vector<Point2f> corners;
        bool found = findChessboardCorners(grey, grid_size, corners);
        cout << found << endl;
        if (found){
            objpoints.push_back(objp);
            imgpoints.push_back(corners);
        }
    }
    //Compute distortion coefficents
    Mat cameraMatrix, distCoeffs;
    vector<Mat> rvecs, tvecs;
    calibrateCamera(objpoints, imgpoints, cv::Size(images[0].rows, images[0].cols), cameraMatrix, distCoeffs, rvecs, tvecs);
    std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
    std::cout << "distCoeffs : " << distCoeffs << std::endl;
    //Compute Mean Reprojection Error
    vector<Point2f> imagePoints2;
    size_t totalPoints = 0;
    double totalErr = 0, err;
    for (size_t i = 0; i < objpoints.size(); ++i)
    {
        projectPoints(objpoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);

        err = norm(imgpoints[i], imagePoints2, NORM_L2);

        size_t n = objpoints[i].size();
        totalErr += err * err;
        totalPoints += n;
    }
    double mean_reproj_error = sqrt(totalErr / totalPoints);
    cout << "Mean Reprojection Error " << mean_reproj_error << endl;
    // Undistort test image and show both
    Mat undistImg;
    Mat distImage = imread(path + "test_image.png");
    namedWindow("Distorted");
    imshow("Distorted", distImage);
    undistort(distImage, undistImg, cameraMatrix, distCoeffs);
    namedWindow("Corrected");
    imshow("Corrected", undistImg);
    waitKey(0);
    return 0;
}