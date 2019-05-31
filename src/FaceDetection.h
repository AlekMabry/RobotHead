#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

#define CASCADE_LOCATION_FRONTALFACE "haarcascades/haarcascade_frontalface_default.xml"
#define CASCADE_LOCATION_GLASSES "haarcascades/haarcascade_eye_tree_eyeglasses.xml"
#define CASCADE_LOCATION_SMILING "haarcascades/haarcascade_smile.xml"

#define LBPH_LOCATION "faceDatabase/FaceDatabase01.xml"

using namespace cv;
using namespace std;

#ifndef ROBOCORE_FACEDETECTION_H
#define ROBOCORE_FACEDETECTION_H
#endif

class FaceDetection {

  int totalFaces;       // Number of faces detected
  bool isSmiling[3];    // Is face smiling
  bool hasGlasses[3];   // Does face have glasses
  int shirtHue[3];      // Hue of shirt
  int faceDistance;     // Distance to face

  CascadeClassifier cascade_frontalface;
  CascadeClassifier cascade_glasses;
  CascadeClassifier cascade_smiling;

  Mat currentFrame;

  Ptr<FaceRecognizer> faceDatabase;

  public:
    bool cascadeLoaded_frontalface;
    bool cascadeLoaded_glasses;
    bool cascadeLoaded_smiling;

    FaceDetection();
    void findFaces(Mat& frame, int& xPos, int& yPos);
    void detectPeople(Mat& frame);
};
