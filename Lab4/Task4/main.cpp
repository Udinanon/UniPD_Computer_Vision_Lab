#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


struct processingParameters{
    const char *window_name = "Output";
    int dp = 209;
    int min_dist_div =  43;
    int param1 = 556;
    int param2 = 83;
    int blur_size = 1;
    Mat* clone_image;
    Mat* original_image;
    int sigma_size = 1;
};

void onTrackbar(int pos, void *userdata)
{
    processingParameters params = *(static_cast<processingParameters*>(userdata));
    Mat image = *params.original_image;
    Mat clone_image = image.clone();
    Mat gray_image = image.clone();
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    GaussianBlur(gray_image, gray_image, Size(params.blur_size * 2 + 1, params.blur_size * 2 + 1), params.sigma_size, params.sigma_size);
    GaussianBlur(clone_image, clone_image, Size(params.blur_size * 2 + 1, params.blur_size * 2 + 1), params.sigma_size, params.sigma_size);
    cout << gray_image.channels() << endl;
    vector<Vec3f> circles;
    HoughCircles(gray_image, circles, HOUGH_GRADIENT_ALT, double(params.dp + 1) / 100, clone_image.rows / (params.min_dist_div + 1), params.param1 + 1, double(params.param2 + 1) / 100); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // draw the circle center
         circle(clone_image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
         // draw the circle outline
         circle(clone_image, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }
    imshow(params.window_name, clone_image);
    params.clone_image = &clone_image;
}

int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need     
    string path;
    if (argc == 2){
        cout << "Reading inpout image from path: " << argv[1] << endl;
        path = argv[1]; 
    }
    else{
        cout << "Expected usage: Lab4Task4 <input_path>" << endl;
        path = "/home/udinanon/C++/Lab4/Task4/street_scene.png";
        cout << "using default path: " << path << endl;
    }
    Mat img = imread(path);
    
    cout << img.channels() << endl;
    // show image rho
    namedWindow("Original");
    imshow("Original", img);
    processingParameters params;
    params.original_image = &img;

    namedWindow(params.window_name);

    // create a toolbar
    createTrackbar("dp", params.window_name, &params.dp, 1000, onTrackbar, &params);
    createTrackbar("min dist param", params.window_name, &params.min_dist_div, 100, onTrackbar, &params);
    createTrackbar("param1", params.window_name, &params.param1, 1000, onTrackbar, &params);
    createTrackbar("param2", params.window_name, &params.param2, 200, onTrackbar, &params);
    createTrackbar("blur size", params.window_name, &params.blur_size, 20, onTrackbar, &params);
    createTrackbar("sigma size", params.window_name, &params.sigma_size, 10, onTrackbar, &params);
    onTrackbar(params.dp, &params);


    waitKey(0);
    return 0;
}
