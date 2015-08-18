# RobotHead
 A cube-like open source robot.
 
 The tracker.cpp file and the ServoControl.js file work together.
 To execute the program type: ./tracker | ServoControl.js
 
 
 To build ./tracker
 g++ `pkg-config --static --libs opencv` -O3 -o tracker tracker.cpp
