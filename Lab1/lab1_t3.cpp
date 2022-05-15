#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char **argv)
{
/*     Write a program that creates two images of size 256x256, 
        one channel.Write the pixels using the at() function in order to create :
            ● a vertical gradient in the first image;
            ● an horizontal gradient in the second image.int n_dim = 10; */
    int n_dim = 10; 
    cv::Mat img1(256, 256, CV_8U); // generate random matrix
    for (int i = 0; i < img1.rows; i++){
        for (int j = 0; j < img1.cols; j++){
            img1.at<uchar>(i, j) = (i); // fill it using the for loop value, easy cause the image is 256 large
    }}
    n_dim = img1.channels();
    std::cout << n_dim << std::endl; // this is just to show that the image is one channel
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img1);

    // identical to the previous one using the otehr axis
    cv::Mat img2(256, 256, CV_8U);
    for (int i = 0; i < img2.rows; i++)
    {
        for (int j = 0; j < img2.cols; j++)
        {
            img2.at<uchar>(i, j) = (j);
        }
    }
    n_dim = img2.channels();
    std::cout << n_dim << std::endl;
    cv::namedWindow("Example 2");
    cv::imshow("Example 2", img2);

    /*     Expand the software to create and visualize two other images,
            size 300x300, one channel, with :
                ● a chessboard with squares of size 20
                ● a chessboard with squares of size 50 */

    // the zeros method fills ghe matrix with zeroes and not noise
    cv::Mat chess1 = cv::Mat::zeros(300, 300, CV_8U);
    for (int i = 0; i < chess1.rows; i++)
    {
        for (int j = 0; j < chess1.cols; j++)
        {
            // we use the L1 or taxi metric, by doung an integer division by our base unit, here 20
            int taxi_x = (int)i / 20;
            int taxi_y = (int)j / 20;
            // if the pixel is at L1 distance even then it's white, if it's odd it stays black
            if ((taxi_x + taxi_y) % 2 == 0)
            {
                chess1.at<uchar>(i, j) = 255; // remember that unsigned char is 0-255 and it's casted using mod i think
            }
        }
    }
    n_dim = chess1.channels();
    std::cout << n_dim << std::endl;
    cv::namedWindow("Chessboard 1");
    cv::imshow("Chessboard 1", chess1);
    
    // identical reasoning, just a different base scale 
    cv::Mat chess2 = cv::Mat::zeros(300, 300, CV_8U);
    for (int i = 0; i < chess2.rows; i++)
    {
        for (int j = 0; j < chess2.cols; j++)
        {
            int taxi_x = (int)i / 50;
            int taxi_y = (int)j / 50;

            if ((taxi_x + taxi_y) % 2 == 0)
            {
                chess2.at<uchar>(i, j) = 255; // remember that unsigned char is 0-255 and it's casted using mod i think
            }
        }
    }
    n_dim = chess2.channels();
    std::cout << n_dim << std::endl;
    cv::namedWindow("Chessboard 2");
    cv::imshow("Chessboard 2", chess2);

    cv::waitKey(0);
    return 0;
}
