//
//  GetLabplacian.cpp
//  
//
//  Created by Dmitriy Borovikov on 01.09.2021.
//

#include "GetLabplacian.hpp"
#include <iostream>

#include <pylon/PylonIncludes.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int GetLabplacian(int height,
                  int width,
                  void* imageBuffer) {
    Mat imageSource = cv::Mat(height, width, CV_8UC1, imageBuffer);
    Mat imageLaplacian;
//    Mat imageSobel;

    Laplacian(imageSource, imageLaplacian, CV_16U);
    //Sobel(imageGrey, imageSobel, CV_16U, 1, 1);

    //The average grayscale of the image
    double meanValue = 0.0;
    meanValue = mean(imageLaplacian)[0];

    printf("mean: %f\n", meanValue);
}
