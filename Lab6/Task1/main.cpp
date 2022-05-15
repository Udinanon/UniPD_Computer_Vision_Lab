#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
    // Read image from disk
    string path, path2;
    if (argc == 3)
    {
        cout << "Reading input image 1 from path: " << argv[1] << endl;
        path = argv[1];
        cout << "Reading input image 2 from path: " << argv[2] << endl;
        path2 = argv[2];
    }
    else
    {
        cout << "Expected usage: Lab6Task1 <input_path> <input_path>" << endl;
        path = "/home/udinanon/C++/Lab6/Task1/img1.png";
        path2 = "/home/udinanon/C++/Lab6/Task1/img2.png";
        cout << "using default path: " << path << endl;
        cout << "using default path2: " << path2 << endl;
    }
    Mat img1 = imread(path);
    cout << img1.channels() << endl;
    Mat img2 = imread(path2);
    cout << img2.channels() << endl;
    Ptr<FastFeatureDetector> FAST = cv::FastFeatureDetector::create();
    vector<KeyPoint> keypoints_img1;
    vector<KeyPoint> keypoints_img2;

    FAST->detect(img1, keypoints_img1);
    FAST->detect(img2, keypoints_img2);

    drawKeypoints(img1, keypoints_img1, img1);
    drawKeypoints(img2, keypoints_img2, img2);
    namedWindow("Keypoints image 1");
    namedWindow("Keypoints image 2");
    imshow("Keypoints image 1", img1);
    imshow("Keypoints image 1", img2);

    Mat descriptors_img1;
    Mat descriptors_img2;
    Ptr<cv::xfeatures2d::BriefDescriptorExtractor> BRIEF = cv ::xfeatures2d::BriefDescriptorExtractor::create();

    BRIEF->compute(img1, keypoints_img1, descriptors_img1);
    BRIEF->compute(img2, keypoints_img2, descriptors_img2);

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::makePtr<cv::FlannBasedMatcher>(cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2));
    std::vector<DMatch> knn_matches;
    matcher->match(descriptors_img1, descriptors_img2, knn_matches, 2);

    Mat img_matches;
    drawMatches(img1, keypoints_img1, img2, keypoints_img2, knn_matches, img_matches, Scalar::all(-1),
                Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    //-- Show detected matches
    namedWindow("Good Matches");
    imshow("Good Matches", img_matches);
    waitKey(0);
}