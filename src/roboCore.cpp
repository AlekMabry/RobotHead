#include "opencv2/opencv.hpp"
#include "BlobDetection.h"
#include "FaceDetection.h"
#include "servos.h"
// #include "AudioManager.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
  VideoCapture cap(-1);
  // namedWindow("Faces", 1);
  Mat frame;
  servos Servos;
  
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 160);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 120);

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
  
  int xPos = 0;
  int yPos = 0;
  
  Servos.init();
  
  for(;;) {
    cap >> frame;
    // faceFinder.detectPeople(frame);
    faceFinder.findFaces(frame, xPos, yPos);
    //cout << "[FACE] [";
    //cout << xPos;
    //cout << "] [";
    //cout << yPos;
    //cout << "]\n";
    
    if (xPos != 999)
    {
      int xOffset = xPos - 80;
      if (xOffset > 20)
      {
        Servos.servo_pos[SERVO_NECK_PITCH] += 0.1;
      }
      else
      if (xOffset < 20)
      {
        Servos.servo_pos[SERVO_NECK_PITCH] -= 0.1;
      }
    }
    
    // example comment
    
    
    //cout << flush;
    
    Servos.update();
    
    // imshow("Vision", frame);
    // if (waitKey(30) >= 0) break;
  }

  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
