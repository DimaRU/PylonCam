//
//  FocusMeasure.cpp
//
//
//  Created by Dmitriy Borovikov on 01.09.2021.
//

#include "FocusMeasure.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

double laplacianMeasure(int width, int height, void* imageBuffer) {
    Mat imageSource = cv::Mat(height, width, CV_8UC1, imageBuffer);
    Mat imageLaplacian;
    double focusMeasure;

    Laplacian(imageSource, imageLaplacian, CV_16U);
    focusMeasure = mean(imageLaplacian)[0];
    return focusMeasure;
}

double sobelMeasure(int width, int height, void* imageBuffer) {
    Mat imageSource = cv::Mat(height, width, CV_8UC1, imageBuffer);
    Mat imageSobel;
    double focusMeasure;

    Sobel(imageSource, imageSobel, CV_16U, 1, 1);
    focusMeasure = mean(imageSobel)[0];
    return focusMeasure;
}

double varianceMeasure(int width, int height, void* imageBuffer) {
    Mat imageSource = cv::Mat(height, width, CV_8UC1, imageBuffer);
    Mat focusMeasureImage;
    Mat meanStdValueImage;
    double focusMeasure;

    meanStdDev(imageSource, focusMeasureImage, meanStdValueImage);
    focusMeasure = meanStdValueImage.at<double>(0, 0);
    return focusMeasure;
}
