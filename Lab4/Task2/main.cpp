#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
struct cannyParams{
    const char *window_name = "Canny";
    int threshold1 = 0.15;
    int threshold2 = 0.45;
    int aperture_size = 3;
    int clean_threshold = 200;
    Mat* img;
};

void onTrackbar(int pos, void *userdata)
{
    cannyParams params = *(static_cast<cannyParams*>(userdata));
    Mat image = *params.img;    
    Mat cleaned_image;
    Mat edge;
    threshold(image, cleaned_image, params.clean_threshold, 0, THRESH_TOZERO);
    Canny(cleaned_image, edge, params.threshold1, params.threshold2, 3);
    imshow(params.window_name, edge);
}

int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need it
    // Read image from disk
    string path;
    if (argc == 2){
        cout << "Reading inpout image from path: " << argv[1] << endl;
        path = argv[1]; 
    }
    else{
        cout << "Expected usage: Lab4Task2 <input_path>" << endl;
        path = "/home/udinanon/C++/Lab4/Task2/street_scene.png";
        cout << "using default path: " << path << endl;
    }
    Mat img = imread(path);
    
    cout << img.channels() << endl;
    // show image 
    namedWindow("Original");
    imshow("Original", img);

    cannyParams params;
    params.img = &img;


    namedWindow(params.window_name);

    // create a toolbar
    createTrackbar("Canny clean threshold", params.window_name, &params.clean_threshold, 255, onTrackbar, &params);
    createTrackbar("Canny threshold 1", params.window_name, &params.threshold1, 1000, onTrackbar, &params);
    createTrackbar("Canny threshold 2", params.window_name, &params.threshold2, 1000, onTrackbar, &params);
    createTrackbar("Canny aperture", params.window_name, &params.aperture_size, 1000, onTrackbar, &params);
    onTrackbar(params.clean_threshold, &params);


    waitKey(0);
    return 0;
}
