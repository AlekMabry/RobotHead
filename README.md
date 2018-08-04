# RobotHead
A cube-like open source robot. It runs on the BeagleBone Black. You can find full documentation on my webpage: einsteiniumstudios.com

The code is undergoing a lot of reworking. Most of the original python code has been coverted into C++ classes. The main file is roboCore.cpp in src/.

If you are following any old tutorials or you are looking for example code from before 8/4/2018, you can find it in the old_referenceCode/ folder.

To use the code, run cmake then compile in AudioModule/ then src/, since roboCore depends on the library in AudioModule.
