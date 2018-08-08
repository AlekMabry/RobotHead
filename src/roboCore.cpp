#include "opencv2/opencv.hpp"
#include "BlobDetection.h"
#include "FaceDetection.h"
// #include "AudioManager.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
  VideoCapture cap(-1);
  namedWindow("Faces", 1);
  Mat frame;

  FaceDetection faceFinder;

  if (faceFinder.cascadeLoaded_frontalface) {
    printf("haarcascade_frontalface_default.xml loaded \n");
  } else {
    printf("haarcascade_frontalface_default.xml not loaded \n");
  }

  if (faceFinder.cascadeLoaded_glasses) {
    printf("haarcascade_eye_tree_eyeglasses loaded \n");
  } else {
    printf("haarcascade_eye_tree_eyeglasses not loaded \n");
  }

  if (faceFinder.cascadeLoaded_smiling) {
    printf("haarcascade_smile.xml loaded \n");
  } else {
    printf("haarcascade_smile.xml not loaded \n");
  }

  //AudioManager audioManager;
  //audioManager.DecodeBuffer();

  for(;;) {
    cap >> frame;
    faceFinder.detectPeople(frame);
    imshow("Vision", frame);
    if (waitKey(30) >= 0) break;
  }

  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
