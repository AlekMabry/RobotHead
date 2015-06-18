//Use this python script to test your Camera
//Code is from dirty dish detector library (https://gist.github.com/nicknormal/347c18d0b27d45e33f73).

import cv
capture = cv.CaptureFromCAM(-1)
cv.SetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_WIDTH, 960)
cv.SetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_HEIGHT, 720)
im = cv.QueryFrame(capture)
cv.SaveImage("/var/lib/cloud9/Camera_Test.jpg", im)
