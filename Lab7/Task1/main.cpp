#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <glob.h>
#include <panoramic_utils.h>
#include <cstdlib>

using namespace cv;
using namespace std;


class imageStitcher{
    public:
        Mat StitchFromFolder(string path, int FOV){
            vector<String> filenames;
            glob(path, filenames, false);
            vector<Mat> images;

            size_t count = filenames.size(); // number of png files in images folder
            cout << count << endl;
            // populate the images vector
            for (size_t i = 0; i < count; i++)
            {
                cout << filenames[i] << endl;
                Mat cylindrical_image = cylindricalProj(imread(filenames[i]), FOV);
                images.push_back(cylindrical_image);
            }
            // create the feature detector
            Ptr<SIFT> SIFT = cv::SIFT::create();
            // image_full is our final image
            Mat image_full = images[0];

            for (size_t i = 1; i < count; i++)
            {
                // we load one of the other images
                Mat image_part_l = images[i - 1];
                Mat image_part_r = images[i];

                // compute the keypoints for the two images
                vector<KeyPoint> keypoints_part_r;
                vector<KeyPoint> keypoints_part_l;
                SIFT->detect(image_part_r, keypoints_part_r);
                SIFT->detect(image_part_l, keypoints_part_l);
                // compute the descriptors of the keypoints
                Mat descriptors_part_r;
                Mat descriptors_part_l;
                SIFT->compute(image_part_r, keypoints_part_r, descriptors_part_r);
                SIFT->compute(image_part_l, keypoints_part_l, descriptors_part_l);
                // prepare the matcher
                Ptr<BFMatcher> matcher = cv::BFMatcher::create();
                std::vector<DMatch> matches;
                // compute the matches
                matcher->match(descriptors_part_l, descriptors_part_r, matches);
                // filter the matches
                std::vector<DMatch> good_matches;
                float ratio = 4;
                cout << ratio << endl;
                float min_dist = numeric_limits<float>::infinity();
                for (int i = 0; i < matches.size(); i++)
                {
                    if (matches[i].distance < min_dist)
                    {
                        min_dist = matches[i].distance;
                    }
                }
                for (int i = 0; i < matches.size(); i++)
                {
                    if (matches[i].distance < min_dist * ratio)
                    {
                        good_matches.push_back(matches[i]);
                    }
                }

                // show only the filtered matches
                Mat img_good_matches;
                drawMatches(image_part_l, keypoints_part_l, image_part_r, keypoints_part_r, good_matches, img_good_matches, Scalar::all(-1),
                            Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
                //-- Show detected matches

                // namedWindow("Good Matches");
                // imshow("Good Matches", img_good_matches);
                //  Extract location of good matches
                std::vector<Point2f> points_part_l, points_part_r;

                for (size_t i = 0; i < good_matches.size(); i++)
                {
                    points_part_l.push_back(keypoints_part_l[good_matches[i].queryIdx].pt);
                    points_part_r.push_back(keypoints_part_r[good_matches[i].trainIdx].pt);
                }

                // Find homography
                Mat mask;
                Mat h = findHomography(points_part_l, points_part_r, mask, RANSAC);
                cout << "h " << h << endl;
                cout << "image_part_r.size[1]: " << image_part_r.size[1] << endl;
                cout << "offset" << h.at<double>(0, 2) << endl;

                Mat added_fragment;
                // our method
                warpPerspective(image_part_r, added_fragment, h, Size(-h.at<double>(0, 2), image_part_r.size[0]));
                Mat final_image(Size(image_full.size[1] + added_fragment.size[1], image_full.size[0]), CV_8U, Scalar(0, 0, 0));

                // image_part.copyTo(final_image(Rect(image_full.size[0], 0, image_part.cols, image_part.rows)));
                // final_image[:, image_full.size[1]:] = image_part;

                // bruno's method
                /*   warpPerspective(image_part_r, added_fragment, h, Size(image_part_r.size[1]/2, image_part_r.size[0]));
                  Mat final_image(Size(image_full.size[1] + added_fragment.size[1], image_full.size[0]), CV_8U, Scalar(0, 0, 0)); */

                

                Rect roi = Rect(Point(0, 0), Size(image_full.cols, image_full.rows));
                Mat final_roi = final_image(roi);
                cout << "channels " << image_full.channels() << endl;

                image_full.copyTo(final_image.rowRange(0, final_image.rows).colRange(0, image_full.cols));
                added_fragment.copyTo(final_image.rowRange(0, final_image.rows).colRange(image_full.cols, image_full.cols + added_fragment.cols));

                image_full = final_image;
            }
            return image_full;
        };
};

int main(int argc, char **argv){
    string path;
    int FOV;
    if (argc == 3)
    {
        path = argv[1];
        FOV = atoi(argv[2]);
        cout << "Reading input images from path: " << path << endl;
        cout << "FOV: " << FOV << endl;
    }
    else
    {
        cout << "Expected usage: Lab7Task1 <input_path>" << endl;
        path = "/home/udinanon/C++/Computer Vision/Lab7/Task1/kitchen/";
        cout << "using default path: " << path << endl;
        FOV = 33;
        cout << "using default FOV: " << FOV << endl;
    }
    // Read images from disk
    imageStitcher stitcher = imageStitcher();
    Mat full_image = stitcher.StitchFromFolder(path, FOV);
    imwrite(path + "/final_image.png", full_image);
    // still need to find how to wticthc images together
    return 0;
}