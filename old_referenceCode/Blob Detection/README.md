# Blob Detection
This program tracks and follows blobs of color within a set HSV color range.

# Tracker.cpp
This is the program that tracks and outputs the center coordinates of the ball or blob of color being detected. These coordinates are sent through stdout.

The program relies on two files, *HSV.txt* and *debug.txt*.

# HSV.txt
This file contains the range of HSV values to be tracked.

# debug.txt
By changing the number in this files, the program will give different outputs.

-If it is set to 0: The program will just output coordinates.
-If it is set to 1: The program will output coordinates and a video feed.
-If it is set to 2: The program will output coordinates, video, and the current HSV range being tracked.

# ServoControl.js
This program controls the beaglebones servos. It uses STDIN to get the values
The tracker.cpp file and the ServoControl.js file work together.

To execute the program type:

    ./tracker | ServoControl.js

Building
========
To build './tracker' run:

    g++ `pkg-config --static --libs opencv` -O3 -o tracker tracker.cpp
