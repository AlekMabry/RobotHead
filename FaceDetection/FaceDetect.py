import numpy as np
import sys
import cv2

cascPath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascPath)

video_capture = cv2.VideoCapture(0)

video_capture.set(3, 320)
video_capture.set(4, 280)

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
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        #Find the center of the face
        outxNumPy = x + (w / 2)
        outyNumPy = y + (h / 2)
        outx = outxNumPy.astype('int')
        outy = outyNumPy.astype('int')

        #Find distance from center of screen
        if outx > 160:
            valx = outx - 160
        if outx < 160:
            valx = -1 * (160 - outx)
        if outy > 140:
            valy = outy - 140
        if outy < 140:
            valy = -1 * (140 - outy)

        #Convert to string and output to pipe
        arrayx = np.array_str(valx)
        arrayy = np.array_str(valy)
        sys.stdout.write(arrayx + " " + arrayy+' \n')

    # Display the resulting frame
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
