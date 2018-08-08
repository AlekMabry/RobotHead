#include "FaceDetection.h"

FaceDetection::FaceDetection( ) {
  if ( !cascade_frontalface.load( CASCADE_LOCATION_FRONTALFACE )) {
    cascadeLoaded_frontalface = false;
  } else {
    cascadeLoaded_frontalface = true;
  };

  if ( !cascade_glasses.load( CASCADE_LOCATION_GLASSES )) {
    cascadeLoaded_glasses = false;
  } else {
    cascadeLoaded_glasses = true;
  };

  if ( !cascade_smiling.load( CASCADE_LOCATION_SMILING )) {
    cascadeLoaded_smiling = false;
  } else {
    cascadeLoaded_smiling = true;
  };

  faceDatabase = createLBPHFaceRecognizer();
  faceDatabase->load( LBPH_LOCATION );
}

void FaceDetection::findFaces(Mat& frame) {
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    cascade_frontalface.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
    {
      Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
      ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

      Mat faceROI = frame_gray( faces[i] );
      std::vector<Rect> smiles;

      //-- In each face, detect eyes
      cascade_smiling.detectMultiScale( faceROI, smiles, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      if ( smiles.size() > 0 ) {
        printf("Smiling \n");
      } else {
        printf("Not Smiling \n");
      }

      cout << flush;

      //for( size_t j = 0; j < eyes.size(); j++ )
      // {
      //   Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
      //   int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
      //   circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
      // }
    }
    //return frame;
}

void FaceDetection::detectPeople(Mat& frame) {
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  cascade_frontalface.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    Point corner( faces[i].x, faces[i].y );
    Point lowercorner( faces[i].x, faces[i].y+18 );
    Scalar color( 200, 200, 250 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat croppedImage = frame_gray(Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height));

    int label;
    double confidence;
    faceDatabase->predict( croppedImage, label, confidence );

    String labelOutput = to_string( label );
    String confidenceOutput = to_string( confidence );
    putText( frame, labelOutput, corner, FONT_HERSHEY_PLAIN, 1, color, 1, CV_AA, false);
    putText( frame, confidenceOutput, lowercorner, FONT_HERSHEY_PLAIN, 1, color, 1, CV_AA, false);
  }
}
