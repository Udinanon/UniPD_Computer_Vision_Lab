#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char **argv)
{

    cv::Mat img = cv::imread(argv[1]);
    int n_dim = 10;
    std::cout << n_dim << std::endl;
    n_dim = img.channels();
    std::cout << n_dim << std::endl;
    cv::Mat bw_img;
    cv::cvtColor(img, bw_img, cv::COLOR_BGR2GRAY);
    n_dim = bw_img.channels();
    std::cout << n_dim << std::endl;
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    cv::namedWindow("Example 2");
    cv::imshow("Example 2", bw_img);
    char key = cv::waitKey(0);
    std::cout << key << std::endl;

    return 0;
}