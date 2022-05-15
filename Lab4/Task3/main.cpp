#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct processingParameters{
    const char *window_name = "Output";
    int threshold1 = 640;
    int threshold2 = 560;
    int aperture_size = 3;
    int clean_threshold = 200;
    int rho_res = 1;
    int theta_res = 180;
    int hough_thres = 150;
    Mat* lines_image;
    Mat* original_image;
};


void onTrackbar(int pos, void *userdata)
{
    // Prepare the matrices and values
    processingParameters parameters = *(static_cast<processingParameters*>(userdata));
    Mat image = *parameters.original_image;
    Mat lines_image = image.clone();
    Mat edge;
    // Apply Canny
    Canny(image, edge, parameters.threshold1, parameters.threshold2, 3);
    // will hold the results of the detection
    vector<Vec2f> lines;                               
    HoughLines(edge, lines, parameters.rho_res + 1, CV_PI / parameters.theta_res, parameters.hough_thres, 0, 0); // runs the actual detection
    // Draw the lines on the displayed image and compute the intercept with the bottom edge
    int counter = 0;
    vector<Vec2d> valid_lines;
    vector<Vec2i> polyPoints;
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        if (theta < CV_PI / 4 || theta > CV_PI * 3/4)
        {
            Point pt1, pt2;
            Point bottom; 
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            bottom.y = lines_image.rows;
            bottom.x = cvRound(rho / a); //  0 = y = ax+b -> x = -b/a
            // - b / a == - rho/sin / - cos/sin = rho/cos = rho/a
            line(lines_image, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
            circle(lines_image, bottom, 32, Scalar(0, 255, 0), FILLED, LINE_8);
            // these are used to compute the polygon later
            counter++;
            Vec2d line_vals;
            line_vals[0] = a/b;
            line_vals[1] = -double(rho)/b;
            valid_lines.push_back(line_vals);
            polyPoints.push_back(bottom);
        }
    }
    if (valid_lines.size() == 2){
        // if we have only two lines we can compute the intercept
        cout << "TWO LINES" << endl;
        Point intercept;
        double a1 = valid_lines[0][0], a2 = valid_lines[1][0], b1 = valid_lines[0][1], b2 = valid_lines[1][1];
        intercept.x = cvRound((b2-b1)/(a1-a2));
        intercept.y = -cvRound(a1*intercept.x+b1);
        circle(lines_image, intercept, 32, Scalar(0, 255, 0), FILLED, LINE_8);
        // and draw the polygon
        polyPoints.push_back(intercept);
        fillPoly(lines_image, polyPoints, Scalar(255, 0, 0));
        
    }
    cout << counter << endl;
    imshow(parameters.window_name, lines_image);
    parameters.lines_image = &lines_image;
}

int main(int argc, char **argv)
{
    // Read image from disk
    // i can't setup the path to be dynamic, where is os.getcwd() when you need it
    string path;
    if (argc == 2){
        cout << "Reading inpout image from path: " << argv[1] << endl;
        path = argv[1]; 
    }
    else{
        cout << "Expected usage: Lab4Task3 <input_path>" << endl;
        path = "/home/udinanon/C++/Lab4/Task3/street_scene.png";
        cout << "using default path: " << path << endl;
    }
    Mat img = imread(path);
    
    cout << img.channels() << endl;
    // show image 
    namedWindow("Original");
    imshow("Original", img);
    processingParameters parameters;
    parameters.original_image = &img;

    namedWindow(parameters.window_name);

    // create a toolbar
    createTrackbar("Canny threshold 1", parameters.window_name, &parameters.threshold1, 1000, onTrackbar, &parameters);
    createTrackbar("Canny threshold 2", parameters.window_name, &parameters.threshold2, 1000, onTrackbar, &parameters);
    createTrackbar("Hough rho res", parameters.window_name, &parameters.rho_res, 100, onTrackbar, &parameters);
    createTrackbar("Hough angle res", parameters.window_name, &parameters.theta_res, 360, onTrackbar, &parameters);
    createTrackbar("Hough threshold", parameters.window_name, &parameters.hough_thres, 1000, onTrackbar, &parameters);
    onTrackbar(parameters.threshold1, &parameters);

    waitKey(0);
    return 0;
}
