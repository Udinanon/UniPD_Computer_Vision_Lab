#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct cannyParams{
    const char *window_name = "Canny";
    int threshold1 = 0;
    int threshold2 = 0;
    int aperture_size = 0;
    Mat* img;
};

void onTrackbar(int pos, void* userdata){
    // cast the user data to our stryìuct and extract values
    cannyParams params = *(static_cast<cannyParams*>(userdata));
    Mat image = *params.img;
    Mat edge;
    // compute the necessary parameters
    int canny_aperture = 3 + 2 * params.aperture_size;
    double canny_thr1 = params.threshold1 / 100;
    double canny_thr2 = params.threshold2 / 100;
    // generate the image and show it 
    Canny(image, edge, canny_thr1, canny_thr2, canny_aperture);
    imshow(params.window_name, edge);
}

int main(int argc, char **argv)
{
    // Read image from disk
    string path;
    if (argc == 2){
        cout << "Reading inpout image from path: " << argv[1] << endl;
        path = argv[1]; 
    }
    else{
        cout << "Expected usage: Lab4Task1 <input_path>" << endl;
        path = "/home/udinanon/C++/Lab4/Task1/street_scene.png";
        cout << "using default path: " << path << endl;
    }
    Mat img = imread(path);
    cout << img.channels() << endl;
    // show image 
    namedWindow("Original");
    imshow("Original", img);

    // using a strict to share the necessary data with the functions
    cannyParams params;
    params.img = &img;
    namedWindow(params.window_name);

    // create a  series of toolbars
    createTrackbar("Canny threshold 1", params.window_name, &params.threshold1, 1E6, onTrackbar, &params);
    createTrackbar("Canny threshold 2", params.window_name, &params.threshold2, 1E6, onTrackbar, &params);
    createTrackbar("Canny aperture", params.window_name, &params.aperture_size, 2, onTrackbar, &params);
    onTrackbar(params.threshold1, &params);


    waitKey(0);
    return 0;
}
