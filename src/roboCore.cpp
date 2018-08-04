//#include "opencv2/opencv.hpp"
#include "BlobDetection.h"
#include "FaceDetection.h"
#include "AudioManager.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap(-1); // open the default camera
    namedWindow("Faces", 1);
    Mat frame;

    FaceDetection faceFinder;

    //AudioManager audioManager;

    //audioManager.DecodeBuffer();

    for(;;) {
        cap >> frame;
        frame = faceFinder.findFaces(frame);
        imshow("faces", frame);
        if (waitKey(30) >= 0) break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
