import cv2
import sys
from subprocess import call
import os
import numpy as np

cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)

#cv2.SetCaptureProperty(video_capture, cv2.CV_CAP_PROP_FRAME_WIDTH, 320)
#cv2.SetCaptureProperty(video_capture, cv2.CV_CAP_PROP_FRAME_HEIGHT, 280)

video_capture.set(3, 320)
video_capture.set(4, 280)
video_capture.set(6, 2)

while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.cv.CV_HAAR_SCALE_IMAGE
    )

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
	outx = x+(w/2)
	outy = y+(h/2)
	if outx.astype('int') > 160:
                valx = outx.astype('int') - 160
	if outx.astype('int') < 160:
		valx = -1*(160 - outx.astype('int'))
	if outy.astype('int') > 140:
                valy = outy.astype('int') - 140
        if outy.astype('int') < 140:
                valy = -1*(140 - outy.astype('int'))
	arrayx = np.copy(valx)
	arrayy = np.copy(valy)
	sys.stdout.write(arrayx.astype('str')+" "+arrayy.astype('str'))
	sys.stdout.flush()
    # Display the resulting frame
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()

