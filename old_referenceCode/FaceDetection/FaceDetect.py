import numpy as np
import sys
import cv2

debug = 1

cascPath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)

#This slows down the incoming video in order to avoid lag.
video_capture.set(cv2.cv.CV_CAP_PROP_FPS,2)
video_capture.set(3, 160)
video_capture.set(4, 120)

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
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 0), 2)

        #Find the center of the face
        outxNumPy = x + (w / 2)
        outyNumPy = y + (h / 2)
        outx = outxNumPy.astype('int')
        outy = outyNumPy.astype('int')

        #Find distance from center of screen
        if outx > 80:
            valx = outx - 80
        if outx < 80:
            valx = -1 * (80 - outx)
        if outy > 60:
            valy = outy - 60
        if outy < 60:
            valy = -1 * (60 - outy)

        #Convert to string and output to pipe
        arrayx = np.array_str(valx)
        arrayy = np.array_str(valy)
        sys.stdout.write(arrayx + " " + arrayy+' \n')
        sys.stdout.flush()

    # Display the resulting frame
    if debug == 1:
        cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
if debug == 1:
    video_capture.release()
    cv2.destroyAllWindows()
