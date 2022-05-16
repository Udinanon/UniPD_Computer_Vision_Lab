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
    // Read image from disk
    string path;
    if (argc == 2)
    {
        cout << "Reading input images from path: " << argv[1] << endl;
        path = argv[1];

    }
    else
    {
        cout << "Expected usage: Lab6Task1 <input_path>" << endl;
        path = "/home/udinanon/C++/Computer Vision/Lab8/Task2/data/checkerboard_images/*.png";
        cout << "using default path: " << path << endl;
    }
    vector<String> filenames;
    glob(path, filenames, false);

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

    size_t count = filenames.size(); // number of png files in images folder
    cout << count << endl;
    // populate the images vector
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
            drawChessboardCorners(grey, grid_size, corners, found);
            //imshow("IMAGE", grey);
            //waitKey(0);
            objpoints.push_back(objp);
            imgpoints.push_back(corners);
        }
    }
    Mat cameraMatrix, distCoeffs;
    vector<Mat> rvecs, tvecs;
    calibrateCamera(objpoints, imgpoints, cv::Size(images[0].rows, images[0].cols), cameraMatrix, distCoeffs, rvecs, tvecs);
    std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
    std::cout << "distCoeffs : " << distCoeffs << std::endl;

    // from https://amroamroamro.github.io/mexopencv/opencv/calibration_demo.html https://github.com/opencv/opencv/blob/3.2.0/samples/cpp/tutorial_code/calib3d/camera_calibration/camera_calibration.cpp
    vector<float> perViewErrors;
    vector<Point2f> imagePoints2;
    size_t totalPoints = 0;
    double totalErr = 0, err;
    perViewErrors.resize(objpoints.size());
    for (size_t i = 0; i < objpoints.size(); ++i)
    {
        projectPoints(objpoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);

        err = norm(imgpoints[i], imagePoints2, NORM_L2);

        size_t n = objpoints[i].size();
        perViewErrors[i] = (float)sqrt(err * err / n);
        totalErr += err * err;
        totalPoints += n;
    }

    double mean_reproj_error = sqrt(totalErr / totalPoints);
    cout << mean_reproj_error << endl;
    Mat undistMap, undistMap2;
    initUndistortRectifyMap(cameraMatrix, distCoeffs, rvecs, cameraMatrix, Size(images[0].cols, images[0].rows), CV_32FC1, undistMap, undistMap2);
}