#include "opencv2/opencv.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"

#ifndef ROBOCORE_BLOBDETECTION_H
#define ROBOCORE_BLOBDETECTION_H

using namespace cv;
using namespace std;

struct BlobReturn {
    Mat frameOutput;
    double xPosOutput;
    double yPosOutput;
};

class BlobDetection {
public:
    static double getDistance(double knownWidth, double focalLength, double perWidth);
    static BlobReturn blobDetect(Mat frame);
};

#endif //ROBOCORE_BLOBDETECTION_H
