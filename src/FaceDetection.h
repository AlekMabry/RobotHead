#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

#ifndef ROBOCORE_FACEDETECTION_H
#define ROBOCORE_FACEDETECTION_H
#endif

class FaceDetection {
    String face_cascade_name;
    CascadeClassifier face_cascade;

    public:
      FaceDetection();
      Mat findFaces(Mat frame);
};
